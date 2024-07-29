#include "layers/content_browser_layer.h"
#include "other utils/strconvr.h"
#include "IconsFontAwesome5.h"
#include "filetypes.h"

wizm::content_browser_layer::content_browser_layer(asset_manager* p_asset_manager)
    :m_asset_manager(p_asset_manager)
{
	watcher = new filewatcher();
	assets = asset_import.retrieve_all_assets();

    folder_file_texture = new core_gl_texture("resources/images/folder_icon.png");
	file_texture = new core_gl_texture("resources/images/file_icon.png");
    mesh_file_icon = new core_gl_texture("resources/images/mesh_file_icon.png");
    image_file_icon = new core_gl_texture("resources/images/image_file_icon.png");
    map_file_icon = new core_gl_texture("resources/images/map_file_icon.png");
}

wizm::content_browser_layer::~content_browser_layer()
{
	delete watcher;
	delete folder_file_texture;
    delete mesh_file_icon;
    delete image_file_icon;
    delete map_file_icon;
}

void wizm::content_browser_layer::OnAttach()
{
	
}

void wizm::content_browser_layer::OnDetach()
{
	
}




void wizm::content_browser_layer::update(float delta_time)
{
	ImGui::Begin("Content Browser");
	
	
	if (ImGui::Button("refresh")) {
		watcher->refresh();
		assets = asset_import.retrieve_all_assets();
	}

	if (ImGui::Button("...##back")) {
		if(current_directory != "GAME")
			current_directory = current_directory.parent_path();
	}

	float thumdnail_size = 256;
	float panel_width = ImGui::GetContentRegionAvail().x / thumdnail_size * 2;

    if (panel_width < 1) { panel_width = 1; }

	auto contents = get_directory_content(current_directory);
	ImGui::Columns(static_cast<int>(panel_width), 0, false);
	
    static std::string new_file_name;
    static std::string selected_file_path;
	
    for (const auto& entry : get_directory_content(current_directory)) {
        auto file_name = entry.filename().string();
        ImGui::PushID(file_name.c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        if (std::filesystem::is_directory(entry)) {
            //---------------------------------------------------------------------------------------------------------------	FOLDER
            ImGui::ImageButton((ImTextureID)folder_file_texture->texture_id, { thumdnail_size / 2, thumdnail_size / 2 }, { 0,1 }, { 1,0 });
            
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                ImGui::OpenPopup("FilePopup");
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                current_directory = entry;
            }
            ImGui::Text(file_name.c_str());
        }
        else {
            //---------------------------------------------------------------------------------------------------------------	FILE
            ImTextureID final_texture_icon = (ImTextureID)file_texture->texture_id;
            
            if(is_mesh_file(file_name))
                final_texture_icon = (ImTextureID)mesh_file_icon->texture_id;
            else if(is_texture_file(file_name))
                final_texture_icon = (ImTextureID)image_file_icon->texture_id;
            else if (is_map_file(file_name))
                final_texture_icon = (ImTextureID)map_file_icon->texture_id;

               

            ImGui::ImageButton(final_texture_icon, { thumdnail_size / 2, thumdnail_size / 2 }, { 0,1 }, { 1,0 });

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                ImGui::OpenPopup("FilePopup");
                //selected_file_path = entry.string();
                new_file_name = file_name;
            }

            if (ImGui::BeginPopup("FilePopup")) {
                if (ImGui::MenuItem("Delete")) {
                   
                    std::filesystem::remove(entry);
                    std::cout << "File deleted: " << entry << std::endl; 
                }
                if (ImGui::MenuItem("Rename")) {
                    
                    ImGui::SetKeyboardFocusHere();
                }

               
                ImGui::InputText("##RenameFile", &new_file_name[0], ImGuiInputTextFlags_EnterReturnsTrue);
                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    if (new_file_name.c_str()) {
                        std::filesystem::path parent_path = entry.parent_path();
                        std::filesystem::path new_path = parent_path / new_file_name.c_str();                  
                        if (new_path.extension() == ".zer") {
                            try {                                
                                std::filesystem::rename(entry, new_path);
                                std::cout << "File renamed to: " << new_path << std::endl;
                            }
                            catch (const std::filesystem::filesystem_error& e) {
                                std::cerr << "Error renaming file: " << e.what() << std::endl;
                            }
                        }
                        else {
                            std::cerr << "New file name must end with .zer" << std::endl;
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }


                ImGui::EndPopup();
            }

            
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetTooltip("%s", entry.filename().string().c_str());

                std::wstring asset_id;
                const wchar_t* wstr = L"";
                
                if (entry.filename().string().find(".zer") != -1) {
                    
                    asset_id = string_to_wstring(entry.string());
                    wstr = asset_id.c_str();
                }


                for (const auto& asset : assets) {
                    auto asset_path = std::filesystem::directory_entry(asset.path).path().string();
                    std::replace(asset_path.begin(), asset_path.end(), '/', '\\');
                    auto entry_path = entry.string();

                    if (asset_path == entry_path) {
                        asset_id = string_to_wstring(asset.id);
                        wstr = asset_id.c_str();
                    }
                }

                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", wstr, (wcslen(wstr) + 1) * sizeof(wchar_t));
                ImGui::EndDragDropSource();
            }
            ImGui::Text(file_name.c_str());
        }





        ImGui::PopStyleColor();
        ImGui::NextColumn();
        ImGui::PopID();
    }

	
    update_add_content_ui(current_directory);

	ImGui::End();
}

void wizm::content_browser_layer::update_add_content_ui(const std::filesystem::path& path) {
    //if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows)) {
    //    ImGui::OpenPopup("RightClickPopup");
    //}
    //
    //if (ImGui::BeginPopup("RightClickPopup")) {
    //    if (ImGui::MenuItem("Create Map (.zer)")) {
    //        // Code to create a file with the ".zer" extension
    //        std::filesystem::path new_map_path = path / "new_map.zer";
    //        std::ofstream file(new_map_path);
    //        if (file.is_open()) {
    //            // Write initial content to the file if needed
    //            file.close();
    //        }
    //    }
    //
    //    // Add more options here as needed
    //    // if (ImGui::MenuItem("Another Option")) {
    //    //     // Handle another option
    //    // }
    //
    //    ImGui::EndPopup();
    //}


}

std::vector<std::filesystem::path> wizm::content_browser_layer::get_directory_content(const std::filesystem::path& path)
{
	std::vector<std::filesystem::path> contents;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		contents.push_back(entry.path());
	}
	return contents;
}
