#include "layers/content_browser_layer.h"
#include "other utils/strconvr.h"
#include "IconsFontAwesome5.h"


wizm::content_browser_layer::content_browser_layer()
{
	watcher = new filewatcher();
	assets = asset_import.retrieve_all_assets();

	folder_texture = new core_gl_texture("resources/images/folder_icon.png");
	file_texture = new core_gl_texture("resources/images/file_icon.png");
}

wizm::content_browser_layer::~content_browser_layer()
{
	delete watcher;
	delete folder_texture;
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

	auto contents = get_directory_content(current_directory);
	ImGui::Columns(static_cast<int>(panel_width), 0, false);
	
	
    for (const auto& entry : get_directory_content(current_directory)) {
        auto file_name = entry.filename().string();
        ImGui::PushID(file_name.c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        if (std::filesystem::is_directory(entry)) {
            //---------------------------------------------------------------------------------------------------------------	FOLDER
            ImGui::ImageButton((ImTextureID)folder_texture->texture_id, { thumdnail_size / 2, thumdnail_size / 2 }, { 0,1 }, { 1,0 });
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                current_directory = entry;
            }
            ImGui::Text(file_name.c_str());
        }
        else {
            //---------------------------------------------------------------------------------------------------------------	FILE
            ImGui::ImageButton((ImTextureID)file_texture->texture_id, { thumdnail_size / 2, thumdnail_size / 2 }, { 0,1 }, { 1,0 });
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetTooltip("%s", entry.filename().string().c_str());

                std::wstring asset_id;
                for (const auto& asset : assets) {
                    auto asset_path = std::filesystem::directory_entry(asset.path).path().string();
                    std::replace(asset_path.begin(), asset_path.end(), '/', '\\');
                    auto entry_path = entry.string();

                    if (asset_path == entry_path) {
                        asset_id = string_to_wstring(asset.id);
                    }
                }

                const wchar_t* wstr = asset_id.c_str();

                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", wstr, (wcslen(wstr) + 1) * sizeof(wchar_t));
                ImGui::EndDragDropSource();
            }
            ImGui::Text(file_name.c_str());
        }
        ImGui::PopStyleColor();
        ImGui::NextColumn();
        ImGui::PopID();
    }

	
	ImGui::End();
}

std::vector<std::filesystem::path> wizm::content_browser_layer::get_directory_content(const std::filesystem::path& path)
{
	std::vector<std::filesystem::path> contents;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		contents.push_back(entry.path());
	}
	return contents;


}
