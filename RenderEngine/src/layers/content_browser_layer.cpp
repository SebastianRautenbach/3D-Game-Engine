#include "layers/content_browser_layer.h"



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
		ImGui::Text("%s", asset.path.c_str());
		ImGui::SameLine();
		ImGui::Text("%s", asset.id.c_str());

		char buff[255];
		strncpy_s(buff, asset.id.c_str(), sizeof(buff));
		buff[sizeof(buff) - 1] = '\0';  // Ensure null-termination

		std::string label = "##" + asset.id;
		ImGui::InputText(label.c_str(), buff, sizeof(buff));

	}

	
	
	
	ImGui::End();
}
