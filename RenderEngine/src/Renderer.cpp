#include "Renderer.h"

using namespace wizm;


//-----------------------------------------------------------------------

void default_renderer::render_setup(size_t window_size_x, size_t window_size_y, const char* window_name)
{
	m_gl_renderer = new lowlevelsys::gl_renderer;

	m_gl_renderer->setup(window_size_x, window_size_y, window_name);
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
