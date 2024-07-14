#include "update_manager.h"

using namespace wizm;


//-----------------------------------------------------------------------

void update_manager::render_setup(int window_size_x, int window_size_y, const char* window_name)
{

	m_scene = new core_scene;

	m_gl_renderer = new lowlevelsys::gl_renderer;

	m_gl_renderer->setup(window_size_x, window_size_y, window_name, m_scene);

	m_timer = new core_timer;

	base_layer = new gui_layer(m_gl_renderer->window);
	m_layer_stack = new layer_stack();

	m_layer_stack->PushLayer(base_layer);

	m_framebuffer = new core_framebuffer(window_size_x, window_size_y);

	m_layer_stack->PushLayer(new viewport_layer(m_framebuffer->buffer_id ,m_gl_renderer->camera, m_scene));
	m_layer_stack->PushLayer(new scene_ui_layer(m_scene, m_gl_renderer));
	m_layer_stack->PushLayer(new performace_ui_layer(m_scene));
	m_layer_stack->PushLayer(new properties_ui_layer(m_scene, m_gl_renderer));
	m_layer_stack->PushLayer(new content_browser_layer());
	m_layer_stack->PushLayer(new project_modifier(m_scene));

	{
		// this is for testing the entity component system

		
		m_asset_manager = new asset_manager();
		auto back_pack = m_asset_manager->load<staticmesh_asset>("001", "resources/models/backpack.obj");
		auto cube = m_asset_manager->load<staticmesh_asset>("002", "resources/models/cube.fbx");

		m_scene->add_entity("Dir light");
		m_scene->add_entity("backpack");
		m_scene->add_entity("pointlight");


		m_scene->m_entities[0]->add_component(std::make_shared<directionallight_component>());
		m_scene->m_entities[0]->m_components_list[0]->set_rotation(glm::vec3(-0.2f, -1.0f, -0.3f));

		m_scene->m_entities[1]->add_component(std::make_shared<staticmesh_component>(back_pack));
		m_scene->m_entities[1]->m_components_list[0]->set_position(glm::vec3(0.0));
		m_scene->m_entities[1]->m_components_list[0]->set_rotation(glm::vec3(0));
		m_scene->m_entities[1]->m_components_list[0]->set_scale(glm::vec3(.1));

		m_scene->m_entities[2]->add_component(std::make_shared<pointlight_component>());;
		m_scene->m_entities[2]->add_component(std::make_shared<staticmesh_component>(cube));
		m_scene->m_entities[2]->m_components_list[0]->set_position(glm::vec3(-0.0f));
		m_scene->m_entities[2]->m_components_list[1]->set_position(glm::vec3(-0.0f));
		m_scene->m_entities[2]->m_components_list[1]->set_rotation(glm::vec3(0));
		m_scene->m_entities[2]->m_components_list[1]->set_scale(glm::vec3(.1));



		m_scene->m_entities[2]->set_position(glm::vec3(.8));

		auto back_back = std::dynamic_pointer_cast<staticmesh_component>(m_scene->m_entities[1]->m_components_list[0]);
		if (back_back)
		{
			back_back->m_material->set_texture("backpack/diffuse.png", eDiffuse);
			back_back->m_material->set_texture("backpack/specular.png", eSpecular);
		}

		m_gl_renderer->update_draw_data();



	}
}



//-----------------------------------------------------------------------




void update_manager::pre_render()
{	
	m_scene->scene_preupdate();

	m_gl_renderer->pre_render(is_running, m_timer->get_delta_time());
}




//-----------------------------------------------------------------------



void update_manager::render()
{
	m_timer->update_delta_time();


	m_gl_renderer->render(m_timer->get_delta_time());

	// my dumb ass thought wrong but the m_scene is actually where the draw calls are being called not 
	// the gl_renderer. Dont ask me why, I though I was being clever

	m_framebuffer->bind_buffer();
	m_scene->scene_update();
	m_framebuffer->unbind_buffer();

	// I want to involve this to a bigger system but this only handles GUI so far
	base_layer->begin();
	for (auto layer = m_layer_stack->begin(); layer != m_layer_stack->end(); layer++)
		(*layer)->update(m_timer->get_delta_time());
	base_layer->end();
}


//-----------------------------------------------------------------------



void update_manager::post_render()
{
	
	m_scene->scene_postupdate();

	m_gl_renderer->post_render(m_timer->get_delta_time());
	
}


//-----------------------------------------------------------------------
