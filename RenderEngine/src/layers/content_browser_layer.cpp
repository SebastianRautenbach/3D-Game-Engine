#include "layers/content_browser_layer.h"



wizm::content_browser_layer::content_browser_layer()
{
	//std::string path = "backpack/diffuse.png";
	//asset_manager.add_asset(eImage, path);
	//asset_manager.add_asset(eImage, "sdff/sdfdfs");
	//texture_test = new core_gl_texture(path.c_str());
	
}

wizm::content_browser_layer::~content_browser_layer()
{
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
	
	
	static float time = 0.0;
	

	
	
	ImGui::End();
}
