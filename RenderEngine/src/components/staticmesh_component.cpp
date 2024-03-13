#include "entity sys/components/staticmesh_component.h"

wizm::staticmesh_component::staticmesh_component(const char* file_path)
{
	m_component_type = eStaticMesh;
	m_model = new core_model(file_path);
	m_material = new core_material();
}

wizm::staticmesh_component::~staticmesh_component()
{
}

void wizm::staticmesh_component::component_preupdate()
{
}

void wizm::staticmesh_component::component_update()
{
	m_material->update_material();

	m_model_mtx = glm::mat4(1);

	set_local_position(m_position);
	set_world_rotation(m_rotation);
	set_local_scale(m_scale);

	m_material->m_shader->setMat4("model", m_model_mtx);

	m_model->render_model(m_material->m_shader);
}

void wizm::staticmesh_component::component_postupdate()
{
}
