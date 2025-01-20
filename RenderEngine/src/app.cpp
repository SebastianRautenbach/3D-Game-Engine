#include <iostream>
#include <string>
#include "update_manager.h"
#include "imgui/imgui.h"
#include <Windows.h>


int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int) {
	
	wizm::update_manager* updater = new wizm::update_manager;
	updater->render_setup(1920 , 1080 , "Wizm");

	while (updater->is_running)
	{
		updater->pre_render();
		updater->render();
		updater->post_render();
 	}
	delete updater;

	return 0;

}