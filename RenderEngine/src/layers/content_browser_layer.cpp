#include "layers/content_browser_layer.h"
#include "other utils/strconvr.h"

wizm::content_browser_layer::content_browser_layer()
{
	watcher = new filewatcher();
	assets = asset_import.retrieve_all_assets();
}

wizm::content_browser_layer::~content_browser_layer()
{
	delete watcher;
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

	auto contents = get_directory_content(current_directory);
	for (const auto& entry : contents) {
		if (std::filesystem::is_directory(entry)) {
			if (ImGui::Button(entry.filename().string().c_str())) {
				current_directory = entry;
			}
		}
		else {

			if (ImGui::Button(entry.filename().string().c_str())) {
			}
			if (ImGui::BeginDragDropSource()) {
				ImGui::SetTooltip("%s", entry.string().c_str());

				std::wstring asset_id;
				for (const auto& asset : assets) {

					auto asset_path = std::filesystem::directory_entry(asset.path).path().string();
					std::replace(asset_path.begin(), asset_path.end(), '/', '\\');
					auto entry_path = entry.string();
					
	
					if (asset_path == entry_path)
					{
						asset_id = string_to_wstring(asset.id);
					}
				}

				const wchar_t* wstr = asset_id.c_str();

				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", wstr, (wcslen(wstr) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}
		}
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
