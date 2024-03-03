#include "Renderer.h"

using namespace wizm;


//-----------------------------------------------------------------------

void default_renderer::render_setup(size_t window_size_x, size_t window_size_y, const char* window_name)
{

	m_scene = new core_scene;

	m_gl_renderer = new lowlevelsys::gl_renderer;

	m_gl_renderer->setup(window_size_x, window_size_y, window_name, m_scene);



	m_scene->add_entity("cool");
	m_scene->add_entity("cooler");
	m_scene->m_entities[0]->add_component(std::make_shared<cube_sm_component>());
	m_scene->m_entities[0]->m_components_list[0]->set_local_scale(glm::vec3(0.4f));
	m_scene->m_entities[0]->m_components_list[0]->set_local_position(glm::vec3(-0.0f));


	m_scene->m_entities[1]->add_component(std::make_shared<cube_sm_component>());
	m_scene->m_entities[1]->add_component(std::make_shared<cube_sm_component>());
	m_scene->m_entities[1]->m_components_list[0]->set_local_scale(glm::vec3(0.4f));
	m_scene->m_entities[1]->m_components_list[0]->set_local_position(glm::vec3(-0.0f));
	m_scene->m_entities[1]->m_components_list[1]->set_local_scale(glm::vec3(0.4f));
	m_scene->m_entities[1]->m_components_list[1]->set_local_position(glm::vec3(-0.1f));
	m_scene->m_entities[1]->set_position(glm::vec3(2));

	m_gl_renderer->update_draw_data();

}



//-----------------------------------------------------------------------




void default_renderer::pre_render()
{	
	m_gl_renderer->pre_render(is_running);
}




//-----------------------------------------------------------------------



void default_renderer::render()
{
	m_gl_renderer->render();
}


//-----------------------------------------------------------------------



void default_renderer::post_render()
{
	m_gl_renderer->post_render();
}





//-----------------------------------------------------------------------
