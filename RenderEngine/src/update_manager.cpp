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

	//framebuffer_spec specs_depth;
	//specs_depth.attachment = { framebuffer_texture_format::DEPTH24STENCIL8, framebuffer_texture_format::RGBA8 };
	//specs_depth.Width = 1024;
	//specs_depth.Height = 1024;
	//m_framebuffer_depth = new core_framebuffer(specs_depth);
	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_gl_renderer->m_shdrs[2]->use_shader();
	m_gl_renderer->m_shdrs[2]->setInt("shadowMap", 3);


	compute_cluster_test = new compute_cluster(m_gl_renderer->m_shdrs, m_gl_renderer->m_shdrs[4], m_gl_renderer->m_shdrs[5],  m_camera_manager);
	

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

	
	compute_cluster_test->update();


	// depth pass -- shadow pass
	m_gl_renderer->m_shdrs[3]->use_shader();
	global_scene->update_light_components(m_timer->get_delta_time(), m_gl_renderer->m_shdrs[3]);
	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	global_scene->scene_update(m_timer->get_delta_time(), m_gl_renderer->m_shdrs[3]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// Main render pass 
	m_framebuffer->bind_buffer();
	m_gl_renderer->m_shdrs[0]->use_shader();
	glDepthMask(GL_TRUE);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	global_scene->scene_update(m_timer->get_delta_time(), m_gl_renderer->m_shdrs[0]);
	global_scene->update_light_components(m_timer->get_delta_time(), m_gl_renderer->m_shdrs[0]);
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