#include "layers/performance_ui_layer.h"

wizm::performace_ui_layer::performace_ui_layer(core_scene* scene)
	:core_layer("performance layer"), m_scene(scene)
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
	if(ImGui::Button("Get total vertices in scene"))
	{
		amm_verts = 0;
		for (const auto& ent : m_scene->m_entities)
		{
			for (const auto& comp : ent->m_components_list)
			{
				auto staticmesh = std::dynamic_pointer_cast<staticmesh_component>(comp);
			//	if (staticmesh)
			//		amm_verts += staticmesh->m_model->total_vertices;
			}
		}
	}
	std::string tot_vert_str = "total vertices:" + std::to_string(amm_verts);
	ImGui::Text(tot_vert_str.c_str());
	
	ImGui::End();
}
