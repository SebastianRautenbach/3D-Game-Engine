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
	
	for (auto asset : assets) {
		ImGui::Button(asset.path.c_str());

		if (ImGui::BeginDragDropSource()) {

			
			std::wstring nine = string_to_wstring(asset.id).c_str();
			const wchar_t* wstr = nine.c_str();


			ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", wstr, (wcslen(wstr) + 1) * sizeof(wchar_t));
			ImGui::EndDragDropSource();
		}

	}
	
	
	
	
	ImGui::End();
}
