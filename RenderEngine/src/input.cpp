#include "input.h"
#include "iostream"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


//////////////////////////////////////////////////////////////////////////
// DEFAULT CONSTRUCTOR
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

input_manager::input_manager(GLFWwindow* window, float width, float height)
	:m_window(window), w_width(width), w_height(height)
{
	last_mouse_pos.x = width / 2;
	last_mouse_pos.y = height / 2;

	glfwSetKeyCallback(window, input_manager::keyCallback);
	glfwSetScrollCallback(window, input_manager::scroll_callback);

	_mouse_info.scroll_offset = 0.0f;
}


//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------


void input_manager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
 	if (action == GLFW_PRESS) {
 		keys[key] = true;
 	}
 	else if (action == GLFW_RELEASE) {
 		keys[key] = false;
 	}
}


//-----------------------------------------------------------------------

void input_manager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	_mouse_info.scroll_offset = static_cast<float>(yoffset);
}
//-----------------------------------------------------------------------

bool input_manager::has_key_been_pressed(int key)
{
	
	auto it = keys.find(key);
	if (it != keys.end()) {
		return it->second;
 	}
	return false;
	
}

//-----------------------------------------------------------------------







//-----------------------------------------------------------------------



mouse_info input_manager::get_mouse_offset_new()
{
	double mouse_x, mouse_y;
	mouse_info return_info;


	
	if (!_mouse_info.mousemoved)
	{
		set_mouse_cursor_pos(w_width / 2, w_height / 2);
		glfwGetCursorPos(m_window, &mouse_x, &mouse_y);
		
		last_mouse_pos.x = mouse_x;
		last_mouse_pos.y = mouse_y;
		_mouse_info.mousemoved = true;
	}
	else
	{
		
		glfwGetCursorPos(m_window, &mouse_x, &mouse_y);
	}
	
	
	return_info.x_offset = mouse_x - last_mouse_pos.x;
	return_info.y_offset = -last_mouse_pos.y + mouse_y;
	
	last_mouse_pos.x = mouse_x;
	last_mouse_pos.y = mouse_y;
	
	set_mouse_cursor_pos(w_width / 2, w_height / 2);

	return return_info;

}

//-----------------------------------------------------------------------



std::unordered_map<int, bool> input_manager::keys;
mouse_info input_manager::_mouse_info;
glm::vec2 input_manager::last_mouse_pos;