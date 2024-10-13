#define STB_IMAGE_IMPLEMENTATION
#include "gl core/core shader.h"
#include "other utils/extra_utils.h"



//-----------------------------------------------------------------------


core_gl_shader::core_gl_shader(const char* vertex_file_path, const char* fragment_file_path)
{

	std::string VShaderFF = read_file_to_str(vertex_file_path);
	std::string FShaderFF = read_file_to_str(fragment_file_path);
	const char* vertexShaderSource = VShaderFF.c_str();
	const char* fragmentShaderSource = FShaderFF.c_str();


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");


	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	checkCompileErrors(fragmentShader, "FRAGMENT");


	shader_id = glCreateProgram();
	glAttachShader(shader_id, vertexShader);
	glAttachShader(shader_id, fragmentShader);
	glLinkProgram(shader_id);

	int success;
	char infoLog[512];

	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


core_gl_shader::core_gl_shader(const char* compute_file_path)
{
	std::string CShaderFF = read_file_to_str(compute_file_path);
	const char* compute_shader_source = CShaderFF.c_str();

	unsigned int comute_shader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(comute_shader, 1, &compute_shader_source, NULL);
	glCompileShader(comute_shader);

	checkCompileErrors(comute_shader, "COMPUTE");

	shader_id = glCreateProgram();
	glAttachShader(shader_id, comute_shader);
	glLinkProgram(shader_id);



	glDeleteShader(comute_shader);

}



//-----------------------------------------------------------------------


void core_gl_shader::use_shader()
{
	glUseProgram(shader_id);
}






//-----------------------------------------------------------------------




core_gl_texture::core_gl_texture(const char* file_path, bool vert_on_load)
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(vert_on_load);
	unsigned char* data = stbi_load(file_path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum internalFormat = GL_RGBA;

		if (nrChannels == 1) {
			internalFormat = GL_RED;
		}
		else if (nrChannels == 3) {
			internalFormat = GL_RGB;
		}
		else if (nrChannels == 4) {
			internalFormat = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << file_path << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);


}

void core_gl_texture::bind_texture()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void core_gl_texture::delete_texture()
{
	glDeleteTextures(1, &texture_id);
}

void core_gl_texture::unbind_texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void core_gl_texture::set_texture(const char* file_path, bool vert_on_load)
{
	glBindTexture(GL_TEXTURE_2D, texture_id);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(vert_on_load);

	unsigned char* data = stbi_load(file_path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
