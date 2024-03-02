#include "entity sys/components/cube_test_comp.h"

namespace wizm {

	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cube_sm_component::cube_sm_component()
	{
		m_component_type = eStaticMesh;

		m_material = new core_material("missing_texture.png");

		m_draw_data = new core_arr_vertex_buffer(vertices, indices);
		m_draw_data->create_attrib_arr(0, 3, 5 * sizeof(float), 0);
		m_draw_data->create_attrib_arr(1, 2, 5 * sizeof(float), (3 * sizeof(float)));
		m_draw_data->create_buffer();
	}



	cube_sm_component::~cube_sm_component()
	{
		m_draw_data->destroy_buffer();
	}

	//-----------------------------------------------------------------------

	void cube_sm_component::component_preupdate()
	{
	}



	void cube_sm_component::component_update()
	{
		m_material->update_material();
		
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, this->get_local_position());
		model = glm::scale(model, this->get_local_scale());
		m_material->m_shader->setMat4("model", model);
		

		m_draw_data->bind_buffer();
		m_draw_data->draw_buffer(5);
		m_draw_data->unbind_buffer();
		
		m_material->unbind_material();
	}




	void cube_sm_component::component_postupdate()
	{
	}

	

	//-----------------------------------------------------------------------

}