#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

out vec3 FragPos;
out vec2 oTexture;
out vec3 Normal;
out vec4 FragPosLightSpace;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 light_matrix;


void main()
{


	FragPos = vec3(model * vec4(aPos, 1.0));
	FragPosLightSpace = light_matrix * vec4(FragPos, 1.0);

	Normal = mat3(transpose(inverse(model))) * aNormal;  
	
	gl_Position = projection * view * vec4(FragPos, 1.0);
	oTexture = aTexture;
  
}