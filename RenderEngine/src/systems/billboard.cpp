#include "system/billboard.h"

wizm::billboard_core::billboard_core()
{



	// I will change this static linking later
    core_gl_shader shader("shaders/billboard_vrtx.glsl",
		"shaders/billboard_frgment.glsl");

	core_gl_texture light("resources/images/light.png");
	m_billboards.emplace_back(eLight, light, shader);



    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and copy vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind EBO and copy index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void wizm::billboard_core::pre_update()
{
    //m_billboards[0].shader.use_shader();
    m_billboards[0].texture.bind_texture();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void wizm::billboard_core::update()
{
   
    

}

void wizm::billboard_core::post_update()
{
}
