#include "gl core/vertex_buffer.h"





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


core_framebuffer::core_framebuffer(int32_t width, int32_t height)
{
	if (this->buffer_id)
	{
		destroy_buffer();
	}

	m_width = width;
	m_height = height;

	glGenFramebuffers(1, &this->buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, this->buffer_id);
	glCreateTextures(GL_TEXTURE_2D, 1, &m_tex_id);
	glBindTexture(GL_TEXTURE_2D, m_tex_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex_id, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_id);
	glBindTexture(GL_TEXTURE_2D, m_depth_id);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_id, 0);

	GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(m_tex_id, buffers);

	unbind_buffer();

}

core_framebuffer::~core_framebuffer()
{
}

void core_framebuffer::create_fbuffer(int32_t width, int32_t height)
{
	if (this->buffer_id)
	{
		destroy_buffer();
	}

	m_width = width;
	m_height = height;

	glGenFramebuffers(1, &this->buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, this->buffer_id);
	glCreateTextures(GL_TEXTURE_2D, 1, &m_tex_id);
	glBindTexture(GL_TEXTURE_2D, m_tex_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex_id, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_id);
	glBindTexture(GL_TEXTURE_2D, m_depth_id);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_id, 0);

	GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(m_tex_id, buffers);

	unbind_buffer();
}

void core_framebuffer::gen_buffer()
{
}

void core_framebuffer::bind_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->buffer_id);
	glViewport(0, 0, m_width, m_height);
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
