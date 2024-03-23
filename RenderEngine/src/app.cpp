#include <iostream>
#include <string>
#include "update_manager.h"
#include "imgui/imgui.h"



int main(int argc, char* args[]) {
	
	wizm::update_manager* renderer = new wizm::update_manager;
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