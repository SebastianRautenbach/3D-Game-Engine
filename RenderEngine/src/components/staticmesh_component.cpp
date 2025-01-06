#include "entity sys/components/staticmesh_component.h"

wizm::staticmesh_component::staticmesh_component()
{
	m_component_type = eStaticMesh;
}

wizm::staticmesh_component::staticmesh_component(std::shared_ptr<staticmesh_asset> mesh)
{
	m_component_type = eStaticMesh;
	m_model = mesh;

}

wizm::staticmesh_component::~staticmesh_component()
{
	
}

void wizm::staticmesh_component::component_preupdate()
{
}

void wizm::staticmesh_component::component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
{
	if (!m_model) { return; }

	int meshes = m_model->get_mesh()->meshes.size();
	int materials = m_model->material_count();
	
	
	while (materials > m_materials.size()) {
		m_materials.emplace_back();
	}

	shader->setMat4("model", get_transform());

	for (int i = 0; i < meshes; i++) {

		int mat_index = m_model->get_mesh()->meshes[i].m_material_index;

		if (m_materials[mat_index])
			m_materials[mat_index]->draw(shader);

		

		m_model->draw(i);
		
		if (m_materials[mat_index])
			m_materials[mat_index]->unbind();
	}
}

void wizm::staticmesh_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::staticmesh_component::_copy() const
{
	auto new_sc_comp = std::make_shared<staticmesh_component>();

	new_sc_comp->set_position(this->get_position());
	new_sc_comp->set_rotation(this->get_rotation());
	new_sc_comp->set_scale(this->get_scale());

	new_sc_comp->m_mesh_asset_id = this->m_mesh_asset_id;
	new_sc_comp->m_is_active = this->m_is_active;
	
	new_sc_comp->m_model = this->m_model;

	new_sc_comp->m_materials = this->m_materials;
	new_sc_comp->m_material_asset_ids = this->m_material_asset_ids;

	return new_sc_comp;
}
