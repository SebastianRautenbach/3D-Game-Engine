#include <iostream>
#include <string>
#include "Renderer.h"


int main(int argc, char* args[]) {
	
	wizm::default_renderer* renderer = new wizm::default_renderer;
	renderer->render_setup(1920 , 1080 , "Wizm");

	while (renderer->is_running)
	{
		renderer->pre_render();
		renderer->render();
		renderer->post_render();
 	}
	renderer->m_gl_renderer->on_exit();

	return 0;

}