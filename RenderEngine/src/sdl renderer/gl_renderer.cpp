#include "gl renderer/gl_renderer.h"
#include <vector>



void lowlevelsys::gl_renderer::setup(size_t window_size_x, size_t window_size_y, const char* window_name)
{
	w_width = window_size_x;
	w_height = window_size_y;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(window_size_x, window_size_y, window_name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}


	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	


	// manage input --------------------------------------------------------------------- /
	m_input_manager = new input_manager(window, static_cast<float>(w_width), static_cast<float>(w_height));




	// Testing -------------------------------------------------------------------------- /

	timer = new core_timer;

	camera = new core_3d_camera(w_width, w_height);
	camera->SetPosition(glm::vec3(-1.76043, 1.11876, 1.69863));
	camera->SetPitch(-0.438943);
	camera->SetYaw(-0.769122);

	shdr = new core_gl_shader("vrtx_shdr.txt", "frgmnt_shdr.txt");

	test_cubes.emplace_back(new cube_sm_component);
	test_cubes.emplace_back(new cube_sm_component);

	test_cubes[1]->set_local_position(glm::vec3(.5f));
	test_cubes[1]->set_local_scale(glm::vec3(.5f));
	test_cubes[0]->set_local_position(glm::vec3(-1.5f));
	test_cubes[0]->set_local_scale(glm::vec3(.5f));



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


//-----------------------------------------------------------------------

void lowlevelsys::gl_renderer::pre_render(bool& is_running)
{
	is_running = !glfwWindowShouldClose(window);

	glClearColor(0.77f, 0.839f, 0.968f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}




//-----------------------------------------------------------------------

void lowlevelsys::gl_renderer::render()
{
	timer->update_delta_time();

	if (m_input_manager->has_key_been_pressed(GLFW_KEY_LEFT_ALT))
	{		

		m_input_manager->set_hide_mouse_cursor(true);
		
		
		camera->AddYaw(m_input_manager->get_mouse_offset_new().x_offset * timer->get_delta_time());
		camera->AddPitch(m_input_manager->get_mouse_offset_new().y_offset * timer->get_delta_time());



		if (m_input_manager->has_key_been_pressed(GLFW_KEY_W))
			camera->MoveForward(1 * timer->get_delta_time());
		
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_S))
			camera->MoveForward(-1 * timer->get_delta_time());

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_D))
			camera->MoveRight(1 * timer->get_delta_time());

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_A))
			camera->MoveRight(-1 * timer->get_delta_time());

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_E))
			camera->MoveUp(1 * timer->get_delta_time());

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_Q))
			camera->MoveUp(-1 * timer->get_delta_time());
		
 	}
	else
	{
		m_input_manager->set_hide_mouse_cursor(false);
		m_input_manager->mouse_stop_move();
	}
	






	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	view = camera->GetViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)w_width / (float)w_height, 0.1f, 100.0f);
	unsigned int modelLoc = glGetUniformLocation(shdr->get_shader_id(), "model");
	unsigned int viewLoc = glGetUniformLocation(shdr->get_shader_id() , "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	shdr->setMat4("projection", projection);


	// VBO & VAO's
	shdr->use_shader();
	

	// Model Render
	
	for (auto& i : test_cubes) {
		
		if(i->m_component_type == eStaticMesh)
		{
			model = glm::mat4(1.f);
			model = glm::translate(model, i->get_local_position());
			model = glm::scale(model, i->get_local_scale());
			shdr->setMat4("model", model);
			i->component_update();
		}
	}


	
	


}

void lowlevelsys::gl_renderer::post_render()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void lowlevelsys::gl_renderer::on_exit()
{
	glfwTerminate();
	
}
