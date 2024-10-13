#include "entity sys/components/staticmesh_component.h"

wizm::staticmesh_component::staticmesh_component()
{
	m_component_type = eStaticMesh;
	m_material = std::make_unique<core_material>();
}

wizm::staticmesh_component::staticmesh_component(std::shared_ptr<staticmesh_asset> mesh)
{
	m_component_type = eStaticMesh;
	m_model = mesh;
	m_material = std::make_unique<core_material>();
}

wizm::staticmesh_component::~staticmesh_component()
{
	
}

void wizm::staticmesh_component::component_preupdate()
{
}

void wizm::staticmesh_component::component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
{
	if (m_material->m_shader != shader)
	{
		m_material->m_shader = shader;
		m_material->on_change_material();
	}

	if (m_model) {
		m_material->update_material();

		m_material->m_shader->setMat4("model", get_transform());

		m_model->draw();

		m_material->unbind_material();
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

	new_sc_comp->m_asset_id = this->m_asset_id;
	new_sc_comp->m_is_active = this->m_is_active;
	if (this->m_material) {
		*new_sc_comp->m_material = *this->m_material;
	}
	new_sc_comp->m_model = this->m_model;

	return new_sc_comp;
}
