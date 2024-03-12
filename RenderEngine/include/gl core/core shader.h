#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


class core_gl_shader {
public:
	core_gl_shader(const char* vertex_file_path, const char* fragment_file_path);
	void use_shader();
	unsigned int get_shader_id() { return shader_id; }

public:
	unsigned int shader_id;


public:
	void setBool(const char* name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shader_id, name), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const char* name, int value) const
	{
		glUniform1i(glGetUniformLocation(shader_id, name), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const char* name, float value) const
	{
		glUniform1f(glGetUniformLocation(shader_id, name), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const char* name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(shader_id, name), 1, &value[0]);
	}
	void setVec2(const char* name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shader_id, name), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const char* name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shader_id, name), 1, &value[0]);
	}
	void setVec3(const char* name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shader_id, name), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const char* name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(shader_id, name), 1, &value[0]);
	}
	void setVec4(const char* name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(shader_id, name), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const char* name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const char* name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const char* name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, &mat[0][0]);
	}



private:
	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}



};

class core_gl_texture {

public:
	core_gl_texture(const char* file_path);
	void bind_texture();
	void unbind_texture();
	void set_texture(const char* file_path);

public:
	unsigned int texture_id;

};