#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


struct attrib_info {
	unsigned int layout;
	int size;
	int stride;
	int attrib_length;
};



class core_buffer_object {
public:
	virtual void gen_buffer() {};
	virtual void bind_buffer() {};
	virtual void unbind_buffer() {};
	virtual void destroy_buffer() {};

public:
	GLuint buffer_id;
};


class core_vertex_buffer : public core_buffer_object {
public:
	void gen_buffer() override;
	void bind_buffer() override;
	void unbind_buffer() override;
	void destroy_buffer() override;

	// default constructor 
	core_vertex_buffer(std::vector<float>& vertices) : mvertices(vertices) {gen_buffer();}
	
public:
	std::vector<float> mvertices;

};


class core_index_buffer : public core_buffer_object {
public:
	void gen_buffer() override;
	void bind_buffer() override;
	void unbind_buffer() override;
	void destroy_buffer() override;

	// default constructor 
	core_index_buffer(std::vector<unsigned int>& indices) : mindices(indices) {gen_buffer();}

public:
	std::vector<unsigned int> mindices;
};



class core_arr_vertex_buffer : public core_buffer_object {
	
public:
	// default constructor
	core_arr_vertex_buffer(std::vector<float>& vertices, std::vector<unsigned int>& indices);
	
	void create_buffer();
	void bind_buffer() override;
	void unbind_buffer() override;
	void destroy_buffer() override;
	void create_attrib_arr(unsigned int layout, int size, int stride, int attrib_length);

public:
	core_index_buffer* ibo;
	core_vertex_buffer* vbo;
	std::vector<attrib_info> vertex_attribs;
	
};