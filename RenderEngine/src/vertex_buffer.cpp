#include "gl core/vertex_buffer.h"
#include <iostream>

static const unsigned int max_framebuffer_size = 8192;


//-----------------------------------------------------------------------


void core_vertex_buffer::gen_buffer()
{
	glGenBuffers(1, &this->buffer_id);
}



//-----------------------------------------------------------------------


void core_vertex_buffer::bind_buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer_id);
	glBufferData(GL_ARRAY_BUFFER, this->mvertices.size() * sizeof(vertex_data), &this->mvertices[0], GL_STATIC_DRAW);
}

//-----------------------------------------------------------------------

void core_vertex_buffer::unbind_buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//-----------------------------------------------------------------------

void core_vertex_buffer::destroy_buffer()
{
	glDeleteBuffers(1, &this->buffer_id);
}




//-----------------------------------------------------------------------

void core_index_buffer::gen_buffer()
{
	glGenBuffers(1, &this->buffer_id);
}


//-----------------------------------------------------------------------

void core_index_buffer::bind_buffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mindices.size() * sizeof(unsigned int), this->mindices.data(), GL_STATIC_DRAW);
}




//-----------------------------------------------------------------------

void core_index_buffer::unbind_buffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


//-----------------------------------------------------------------------





void core_index_buffer::destroy_buffer()
{
	glDeleteBuffers(1, &this->buffer_id);
}



	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR FOR VAO
	//////////////////////////////////////////////////////////////////////////


core_arr_vertex_buffer::core_arr_vertex_buffer( std::vector<vertex_data>& vertices, std::vector<unsigned int>& indices)
{

	glGenVertexArrays(1, &this->buffer_id);
	vbo = new core_vertex_buffer(vertices);
	ibo = new core_index_buffer(indices);

	
}

core_arr_vertex_buffer::~core_arr_vertex_buffer()
{
}




//-----------------------------------------------------------------------


void core_arr_vertex_buffer::create_buffer() {
	bind_buffer();

	vbo->bind_buffer();
	ibo->bind_buffer();

	for (const auto& i : vertex_attribs)
	{
		glVertexAttribPointer(i.layout, i.size, GL_FLOAT, GL_FALSE, i.stride, (void*)i.attrib_length);
		glEnableVertexAttribArray(i.layout);
	}

	vbo->unbind_buffer();
	unbind_buffer();
}


//-----------------------------------------------------------------------

void core_arr_vertex_buffer::draw_buffer(unsigned int size_of_row)
{
	bind_buffer();
	glDrawElements(GL_TRIANGLES, size_of_row, GL_UNSIGNED_INT, 0);
	unbind_buffer();
}





//-----------------------------------------------------------------------

void core_arr_vertex_buffer::bind_buffer()
{
	glBindVertexArray(this->buffer_id);
}




//-----------------------------------------------------------------------

void core_arr_vertex_buffer::unbind_buffer()
{
	glBindVertexArray(0);
}





//-----------------------------------------------------------------------

void core_arr_vertex_buffer::destroy_buffer()
{
	vbo->destroy_buffer();
	ibo->destroy_buffer();
	glDeleteBuffers(1, &this->buffer_id);
}




//-----------------------------------------------------------------------


void core_arr_vertex_buffer::create_attrib_arr(unsigned int layout, int size, int stride, int attrib_length)
{
	vertex_attribs.emplace_back(layout, size, stride, attrib_length);
}



//-----------------------------------------------------------------------


core_framebuffer::core_framebuffer(framebuffer_spec spec)
	:m_spec(spec)
{


	for (auto format : m_spec.attachment.attachments) {
		if (!lowlevelsys::is_depth_format(format.texture_format))
			m_color_attachment_spec.emplace_back(format);
		else
			m_depth_attachment_spec = format.texture_format;
	}

	create_fbuffer();

}

core_framebuffer::~core_framebuffer()
{
	destroy_buffer();
}



void core_framebuffer::create_fbuffer()
{
	if (this->buffer_id)
	{
		destroy_buffer();
	}

	glGenFramebuffers(1, &this->buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, this->buffer_id);

	bool multisample = m_spec.Samples > 1;

	if (m_color_attachment_spec.size()) {

		m_color_attachments.resize(m_color_attachment_spec.size());
		lowlevelsys::create_texture(multisample, m_color_attachments.data(), m_color_attachments.size());


		for (int i = 0; i < m_color_attachments.size(); i++) {
			lowlevelsys::bind_texture(multisample, m_color_attachments[i]);
			switch (m_color_attachment_spec[i].texture_format) {
				case framebuffer_texture_format::RGBA8:
					lowlevelsys::attach_color_texture(m_color_attachments[i], m_spec.Samples, GL_RGBA8, GL_RGBA, m_spec.Width, m_spec.Height, i);
					break;

				case framebuffer_texture_format::RED_INTEGER:
					lowlevelsys::attach_color_texture(m_color_attachments[i], m_spec.Samples, GL_R32I, GL_RED_INTEGER, m_spec.Width, m_spec.Height, i);
					break;
			}
		}
	}
	if (m_depth_attachment_spec.texture_format != framebuffer_texture_format::None) {
		lowlevelsys::create_texture(multisample, &m_depth_attachment, 1);
		lowlevelsys::bind_texture(multisample, m_depth_attachment);
		switch (m_depth_attachment_spec.texture_format) {
		case framebuffer_texture_format::DEPTH24STENCIL8:
			lowlevelsys::attach_depth_texture(m_depth_attachment, m_spec.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_spec.Width, m_spec.Height);
			break;
		}
	}
	if (m_color_attachments.size() > 1) {
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(m_color_attachments.size(), buffers);
	}
	else if (m_color_attachments.empty()) {
		glDrawBuffer(GL_NONE);
	}
	unbind_buffer();
}

void core_framebuffer::resize(unsigned int width, unsigned int height)
{
	if (width == 0 || height == 0 || width > max_framebuffer_size || height > max_framebuffer_size)
	{
		m_spec.Width = width;
		m_spec.Height = height;
		create_fbuffer();
		return;
	}
}

void core_framebuffer::gen_buffer()
{
}

void core_framebuffer::bind_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->buffer_id);
	glViewport(0, 0, m_spec.Width, m_spec.Height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void core_framebuffer::unbind_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void core_framebuffer::destroy_buffer()
{
	if (this->buffer_id)
	{
		glDeleteFramebuffers(GL_FRAMEBUFFER, &this->buffer_id);
		glDeleteTextures(1, &m_tex_id);
		glDeleteTextures(1, &m_depth_id);
		m_tex_id = 0;
		m_depth_id = 0;


	}

}
