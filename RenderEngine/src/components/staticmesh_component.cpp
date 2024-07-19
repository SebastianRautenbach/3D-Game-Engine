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

void wizm::staticmesh_component::component_update()
{
	m_material->update_material();

	m_material->m_shader->setMat4("model", get_transform());

	m_model->draw(m_material->m_shader);

	m_material->unbind_material();
}

void wizm::staticmesh_component::component_postupdate()
{
}

void wizm::staticmesh_component::change_mesh(const char* file_path)
{
	//m_model = new core_model(file_path);
}
