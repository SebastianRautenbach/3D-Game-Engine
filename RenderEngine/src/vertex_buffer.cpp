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


