#include "gl renderer/gl_renderer.h"
#include <vector>



void lowlevelsys::gl_renderer::setup(int window_size_x, int window_size_y, const char* window_name, core_scene* scene)
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




	camera = new core_3d_camera(w_width, w_height);
	camera->SetPosition(glm::vec3(-1.76043, 1.11876, 1.69863));
	camera->SetPitch(-0.438943);
	camera->SetYaw(-0.769122);

	shdr = new core_gl_shader("shaders/default_vrtx_shdr.glsl", "shaders/default_frgmnt_shdr.glsl");

	m_scene = scene;

	

	




	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


//-----------------------------------------------------------------------

void lowlevelsys::gl_renderer::pre_render(bool& is_running, float deltaTime)
{
	is_running = !glfwWindowShouldClose(window);

	glClearColor(0.77f, 0.839f, 0.968f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}




//-----------------------------------------------------------------------

void lowlevelsys::gl_renderer::render(float deltaTime)
{
	
	std::string fps = std::to_string(1.f / deltaTime);
	glfwSetWindowTitle(window, fps.c_str());


	if (m_input_manager->has_key_been_pressed(GLFW_KEY_LEFT_ALT))
	{		

		m_input_manager->set_hide_mouse_cursor(true);
		
		camera->AddYaw(m_input_manager->get_mouse_offset_new().x_offset * deltaTime);
		camera->AddPitch(m_input_manager->get_mouse_offset_new().y_offset * deltaTime);



		if (m_input_manager->has_key_been_pressed(GLFW_KEY_W))
			camera->MoveForward(1 * deltaTime);
		
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_S))
			camera->MoveForward(-1 * deltaTime);

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_D))
			camera->MoveRight(1 * deltaTime);

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_A))
			camera->MoveRight(-1 * deltaTime);

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_E))
			camera->MoveUp(1 * deltaTime);

		if (m_input_manager->has_key_been_pressed(GLFW_KEY_Q))
			camera->MoveUp(-1 * deltaTime);

		
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_UP))
			m_scene->m_entities[2]->add_position(glm::vec3(1 * deltaTime, 0, 0));
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_DOWN))
			m_scene->m_entities[2]->add_position(glm::vec3(-1 * deltaTime, 0, 0));
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_LEFT))
			m_scene->m_entities[2]->add_position(glm::vec3(0, 0, -1 * deltaTime));
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_RIGHT))
			m_scene->m_entities[2]->add_position(glm::vec3(0, 0, 1 * deltaTime));
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_O))
			m_scene->m_entities[2]->add_position(glm::vec3(0, 1 * deltaTime, 0));
		if (m_input_manager->has_key_been_pressed(GLFW_KEY_L))
			m_scene->m_entities[2]->add_position(glm::vec3(0, -1 * deltaTime, 0));

	
	}
	else
	{
		m_input_manager->set_hide_mouse_cursor(false);
		m_input_manager->mouse_stop_move();
	}
	







	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	view = camera->GetViewMatrix();
	projection = camera->GetProjectionMatrix();
	unsigned int viewLoc = glGetUniformLocation(shdr->get_shader_id() , "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	shdr->setMat4("projection", projection);

	shdr->setVec3("camPos", camera->GetPosition());

	shdr->use_shader();
}




void lowlevelsys::gl_renderer::post_render(float deltaTime)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}



//-----------------------------------------------------------------------



void lowlevelsys::gl_renderer::update_draw_data()
{

	


	for (auto& i : m_scene->m_entities)
	{
		for (auto& per_ent : i->m_components_list)
		{
			auto comp_per_ent = std::dynamic_pointer_cast<staticmesh_component>(per_ent);

			if (comp_per_ent) {
				comp_per_ent->m_material->m_shader = shdr;
				
				//comp_per_ent->m_material->m_shininess = 32;
				comp_per_ent->m_material->set_texture("backpack/diffuse.png", eDiffuse);
				comp_per_ent->m_material->set_texture("backpack/specular.png", eSpecular);
				
				comp_per_ent->m_material->on_change_material();
			}

			// get all point lights 

			auto light = std::dynamic_pointer_cast<pointlight_component>(per_ent);
			if (light) {
				static int amm_lights = 0;
				light->shader = shdr;
				light->light_index = amm_lights;
				shdr->setInt("ammount_of_pointlights", amm_lights + 1);
				++amm_lights;
			}

			auto directional_light = std::dynamic_pointer_cast<directionallight_component>(per_ent);
			if (directional_light) {
				directional_light->shader = shdr;
			}

		}
	}
	
	
}



//-----------------------------------------------------------------------


void lowlevelsys::gl_renderer::on_exit()
{
	glfwTerminate();
	
}
