#include "Renderer.h"

using namespace wizm;


//-----------------------------------------------------------------------

void default_renderer::render_setup(int window_size_x, int window_size_y, const char* window_name)
{

	m_scene = new core_scene;

	m_gl_renderer = new lowlevelsys::gl_renderer;

	m_gl_renderer->setup(window_size_x, window_size_y, window_name, m_scene);

	m_timer = new core_timer;


	{
		// this is for testing the entity component system
		m_scene->add_entity("cool");
		m_scene->add_entity("cooler");
		m_scene->add_entity("pointlight");


		m_scene->m_entities[0]->add_component(std::make_shared<directionallight_component>());
		m_scene->m_entities[0]->m_components_list[0]->set_local_rotation(glm::vec3(-0.2f, -1.0f, -0.3f));

		m_scene->m_entities[1]->add_component(std::make_shared<cube_sm_component>());
		m_scene->m_entities[1]->add_component(std::make_shared<cube_sm_component>());
		m_scene->m_entities[1]->m_components_list[0]->set_local_scale(glm::vec3(0.4f));
		m_scene->m_entities[1]->m_components_list[0]->set_local_position(glm::vec3(-0.0f));
		m_scene->m_entities[1]->m_components_list[0]->set_local_rotation(glm::vec3(-0.0f));
		m_scene->m_entities[1]->m_components_list[1]->set_local_scale(glm::vec3(0.4f));
		m_scene->m_entities[1]->m_components_list[1]->set_local_position(glm::vec3(-0.1f));
		m_scene->m_entities[1]->m_components_list[1]->set_local_rotation(glm::vec3(-0.0f));


		m_scene->m_entities[2]->add_component(std::make_shared<pointlight_component>());
		m_scene->m_entities[2]->add_component(std::make_shared<cube_sm_component>());
		m_scene->m_entities[2]->m_components_list[0]->set_local_position(glm::vec3(-0.0f));
		m_scene->m_entities[2]->m_components_list[1]->set_local_position(glm::vec3(-0.0f));
		m_scene->m_entities[2]->m_components_list[1]->set_local_scale(glm::vec3(.1f));
		m_scene->m_entities[2]->m_components_list[1]->set_local_rotation(glm::vec3(.0f));



		// cast to its actual class ensuring it's is the correct component by testing if it's not null
		auto comp_change_test = std::dynamic_pointer_cast<cube_sm_component>(m_scene->m_entities[1]->m_components_list[0]);
		if (comp_change_test)
		{
			comp_change_test->m_material->set_texture("wood.png", mDiffuse);
			comp_change_test->m_material->set_texture("wood_spec.png", mSpecular);
		}
		
		m_scene->m_entities[1]->add_position(glm::vec3(1));
		
		test_model = new Model("C:/Users/karat/Documents/GitHub/RenderEngine/RenderEngine/FinalBaseMesh.obj");

		m_gl_renderer->update_draw_data();



	}





	

}



//-----------------------------------------------------------------------




void default_renderer::pre_render()
{	
	m_scene->scene_preupdate();
	m_gl_renderer->pre_render(is_running, m_timer->get_delta_time());
}




//-----------------------------------------------------------------------



void default_renderer::render()
{
	m_timer->update_delta_time();
	m_scene->scene_update();
	m_gl_renderer->render(m_timer->get_delta_time());
	test_model->Draw(*m_gl_renderer->shdr);
}


//-----------------------------------------------------------------------



void default_renderer::post_render()
{
	m_scene->scene_postupdate();
	m_gl_renderer->post_render(m_timer->get_delta_time());
}


//-----------------------------------------------------------------------
