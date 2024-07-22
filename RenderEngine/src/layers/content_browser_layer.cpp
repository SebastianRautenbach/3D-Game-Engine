#include "layers/content_browser_layer.h"



wizm::content_browser_layer::content_browser_layer()
{
	watcher = new filewatcher();
	
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
	
	
	if (ImGui::Button("import")) {
		watcher->refresh();
		assets = asset_import.retrieve_all_assets();
	}
	
	for (auto asset : assets) {
		ImGui::Text(asset.path.c_str());
		ImGui::SameLine();
		ImGui::Text(asset.id.c_str());
	}
	
	
	ImGui::End();
}
