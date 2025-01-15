#include "layers/performance_ui_layer.h"
#include "system/scene_manager.h"

wizm::performace_ui_layer::performace_ui_layer()
	:core_layer("performance layer")
{
}

wizm::performace_ui_layer::~performace_ui_layer()
{
}

void wizm::performace_ui_layer::OnAttach()
{
}

void wizm::performace_ui_layer::OnDetach()
{
}

void wizm::performace_ui_layer::update(float delta_time)
{
	ImGui::Begin("Performance");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	
	
	static unsigned int amm_verts = 0;
	if(ImGui::Button("Get total triangles in scene"))
	{
		amm_verts = 0;
		for (const auto& ent : global_scene->m_entities)
		{
			for (const auto& comp : ent->m_components_list)
			{
				auto staticmesh = dynamic_cast<staticmesh_component*>(comp);
				if (staticmesh)
					amm_verts += staticmesh->m_model->get_triangles();
			}
		}
	}
	std::string tot_vert_str = "total triangles:" + std::to_string(amm_verts);
	ImGui::Text(tot_vert_str.c_str());
	
	ImGui::End();
}
