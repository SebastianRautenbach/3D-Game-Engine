#include "system/billboard.h"

wizm::billboard_core::billboard_core(eBillboardType type, std::shared_ptr<core_gl_shader> shader)
	:m_shader(shader)
{
	
	m_verices.emplace_back(
		vertex_data(glm::vec3(-0.5f, 0.5f, 0.0f)),
		vertex_data(glm::vec3(0.5f, 0.5f, 0.0f)),
		vertex_data(glm::vec3(0.5f, -0.5f, 0.0f)),
		vertex_data(glm::vec3(-0.5f, -0.5f, 0.0f))
	);

	vertex_buffer = new core_arr_vertex_buffer(m_verices, m_indices);
	vertex_buffer->bind_buffer();
	vertex_buffer->create_attrib_arr(0, 3, sizeof(vertex_data), 0);
	vertex_buffer->create_buffer();
}

wizm::billboard_core::~billboard_core()
{
	delete vertex_buffer;
}

void wizm::billboard_core::draw(glm::mat4 transform)
{
	m_shader->use_shader();

	m_shader->setMat4("model", transform);
	vertex_buffer->bind_buffer();
	vertex_buffer->draw_buffer(m_indices.size());
	vertex_buffer->unbind_buffer();
}
