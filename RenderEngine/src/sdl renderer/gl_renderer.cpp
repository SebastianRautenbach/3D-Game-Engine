#include "gl renderer/gl_renderer.h"
#include <vector>



void lowlevelsys::gl_renderer::setup(int window_size_x, int window_size_y, const char* window_name, core_scene* scene)
{
	w_width = window_size_x;
	w_height = window_size_y;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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




	camera = std::make_shared<core_3d_camera>(w_width, w_height);
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


	glfwGetFramebufferSize(window, &w_width, &w_height);
	glViewport(0, 0, w_width, w_height);
	glClearColor(0.77f, 0.839f, 0.968f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	
}




//-----------------------------------------------------------------------

void lowlevelsys::gl_renderer::render(float deltaTime)
{

	if (m_input_manager->has_key_been_pressed(GLFW_KEY_LEFT_ALT))
	{		
		m_input_manager->set_hide_mouse_cursor(true);
		
		camera->AddYaw(m_input_manager->get_mouse_offset_new().x_offset * .01);
		camera->AddPitch(m_input_manager->get_mouse_offset_new().y_offset * .01);



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
	glfwPollEvents();
	glfwSwapBuffers(window);
}



//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
// I fucking HATE this way of doing this hollyyyy shit
// please someone with a brain help me

void lowlevelsys::gl_renderer::update_draw_data()
{

	if (m_scene->total_component_count() != shader_count || m_scene->m_reloaded) {

		std::vector<std::shared_ptr<pointlight_component>> pointlights;
		std::vector<std::shared_ptr<staticmesh_component>> meshes;
		std::vector<std::shared_ptr<directionallight_component>> dirlights;

		for (auto& i : m_scene->m_entities) {
			for (auto& per_ent : i->m_components_list)
			{
				auto mesh_comps = std::dynamic_pointer_cast<staticmesh_component>(per_ent);
				if (mesh_comps)
					meshes.push_back(mesh_comps);

				auto light_comps = std::dynamic_pointer_cast<pointlight_component>(per_ent);
				if (light_comps)
					pointlights.push_back(light_comps);

				auto directional_comps = std::dynamic_pointer_cast<directionallight_component>(per_ent);
				if (directional_comps)
					dirlights.push_back(directional_comps);

			}
		}


		for (int i = 0; i < pointlights.size(); i++)
		{
			pointlights[i]->shader = shdr;
			pointlights[i]->light_index = i;

		}


		for (auto& i : meshes) {
			i->m_material->m_shader = shdr;
			i->m_material->on_change_material();
			i->m_model->m_camera = camera;
			i->m_model->init_boundingvolume(i->m_model->retrieve_all_vertices(),
				i->get_transform()
			);
		}

		for (auto& i : meshes) {
			auto y = i->m_model->get_size();

			/*
				I need to reconstruct it by its size and not it vertices
			*/

			std::cout << "x:" << y.x << ", y:" << y.y << ", z:" << y.z << "\n";
		}

		for (auto& i : dirlights) {
			i->shader = shdr;
		}


		shdr->setInt("ammount_of_pointlights", pointlights.size());



		shader_count = m_scene->total_component_count();
		
	}
}



//-----------------------------------------------------------------------


void lowlevelsys::gl_renderer::on_exit()
{
	glfwTerminate();
	
}

//-----------------------------------------------------------------------
