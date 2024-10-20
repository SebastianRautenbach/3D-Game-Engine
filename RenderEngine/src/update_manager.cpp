#include "update_manager.h"
#include "system/mouse_picking.h"
#include "system/scene_manager.h"


using namespace wizm;


//-----------------------------------------------------------------------


void update_manager::render_setup(int window_size_x, int window_size_y, const char* window_name)
{

	global_scene = new core_scene;

	m_camera_manager = std::make_shared<camera_manager>();

	m_gl_renderer = new lowlevelsys::gl_renderer;

	m_gl_renderer->setup(window_size_x, window_size_y, window_name, m_camera_manager);

	m_timer = new core_timer;

	framebuffer_spec specs;

	specs.attachment = { framebuffer_texture_format::DEPTH24STENCIL8, framebuffer_texture_format::RGBA8 };
	specs.Width = window_size_x;
	specs.Height = window_size_y;
	m_framebuffer = new core_framebuffer(specs);

	compute_cluster_test = new compute_cluster(m_gl_renderer->m_shdrs, m_gl_renderer->m_shdrs[4], m_gl_renderer->m_shdrs[5],  m_camera_manager->m_viewport_camera);
	

	m_asset_manager = new asset_manager();

	base_layer = new gui_layer(m_gl_renderer->window, m_camera_manager, m_asset_manager);

	m_layer_stack = new layer_stack();

	m_layer_stack->PushLayer(base_layer);

	m_billboard_manager = new billboard_manager(m_gl_renderer->m_shdrs[2]);

	m_layer_stack->PushLayer(new script_debug_layer());
	m_layer_stack->PushLayer(new viewport_layer(m_framebuffer->buffer_id, m_camera_manager, m_gl_renderer));
	m_layer_stack->PushLayer(new scene_ui_layer(m_gl_renderer));
	m_layer_stack->PushLayer(new performace_ui_layer());
	m_layer_stack->PushLayer(new properties_ui_layer(m_gl_renderer, m_asset_manager));
	m_layer_stack->PushLayer(new content_browser_layer(m_asset_manager));
}



//-----------------------------------------------------------------------




void update_manager::pre_render()
{
	global_scene->scene_preupdate();
	m_asset_manager->assign_assets();
	m_gl_renderer->update_draw_data();
	compute_cluster_test->update_lights();
	m_gl_renderer->pre_render(is_running, m_timer->get_delta_time());
}




//-----------------------------------------------------------------------



void update_manager::render()
{

	m_timer->update_delta_time();

    m_gl_renderer->render(m_timer->get_delta_time());

	// test
	compute_cluster_test->update();

	// depth pass
	//m_gl_renderer->m_shdrs[3]->use_shader();
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//glDepthMask(GL_TRUE);
	//glClear(GL_DEPTH_BUFFER_BIT);
	//global_scene->scene_update(m_timer->get_delta_time(), m_gl_renderer->m_shdrs[3]);
	
	// Main render pass 
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	m_framebuffer->bind_buffer();
	m_gl_renderer->m_shdrs[0]->use_shader();
	//glDepthMask(GL_TRUE);  
	global_scene->scene_update(m_timer->get_delta_time(), m_gl_renderer->m_shdrs[0]);
	m_billboard_manager->render();


	m_framebuffer->unbind_buffer();

	// I want to evolve this to a bigger system but this only handles GUI so far
	base_layer->begin();
	for (auto layer = m_layer_stack->begin(); layer != m_layer_stack->end(); layer++)
		(*layer)->update(m_timer->get_delta_time());
	base_layer->end();
}


//-----------------------------------------------------------------------



void update_manager::post_render()
{

	global_scene->scene_postupdate();

	m_gl_renderer->post_render(m_timer->get_delta_time());

}


//-----------------------------------------------------------------------