#pragma once
#include "gl core/vertex_buffer.h"
#include "gl core/core shader.h"
#include "system/core_model.h"

class draw_ray {
public:
    /*
        Testing purposes
        Draws a rectangle based on ray_origin and ray_dir
        when update is called
    */

    glm::vec3 calculateRayEndpoint(const glm::vec3& origin, const glm::vec3& direction, float length)
    {
        return origin + direction * length;
    }
                                      
                              
    draw_ray(glm::vec3 ray_origin, glm::vec3 ray_direction) {
        float rayLength = 100.f;

        ray_direction = glm::normalize(ray_direction);

        glm::vec3 rayEndPoint = calculateRayEndpoint(ray_origin, ray_direction, rayLength);
        

        std::vector<vertex_data> vertices = { vertex_data(glm::vec3(ray_origin.x, ray_origin.y, ray_origin.z)), vertex_data(glm::vec3(rayEndPoint.x, rayEndPoint.y, rayEndPoint.z))};
        std::vector<unsigned int> indices = { 0,0 };
        buffered_ray = new core_arr_vertex_buffer(vertices, indices);
        
        buffered_ray->bind_buffer();
        buffered_ray->create_attrib_arr(0, 3, sizeof(vertex_data), 0);
        buffered_ray->create_buffer();

    }

    void re_draw(glm::vec3 ray_origin, glm::vec3 ray_direction) {
        buffered_ray->destroy_buffer();
        delete buffered_ray;


        float rayLength = 100.f;

        ray_direction = glm::normalize(ray_direction);

        glm::vec3 rayEndPoint = calculateRayEndpoint(ray_origin, ray_direction, rayLength);


        std::vector<vertex_data> vertices = { vertex_data(glm::vec3(ray_origin.x, ray_origin.y, ray_origin.z)), vertex_data(glm::vec3(rayEndPoint.x, rayEndPoint.y, rayEndPoint.z)) };
        std::vector<unsigned int> indices = { 0,0 };
        buffered_ray = new core_arr_vertex_buffer(vertices, indices);

        buffered_ray->bind_buffer();
        buffered_ray->create_attrib_arr(0, 3, sizeof(vertex_data), 0);
        buffered_ray->create_buffer();
    
    
    }

    void on_update() {
       
        
        glLineWidth(5.f);

        buffered_ray->bind_buffer();
        glDrawArrays(GL_LINES, 0, 2);
        buffered_ray->unbind_buffer();

    }

    ~draw_ray() { delete buffered_ray; }

public:
    core_arr_vertex_buffer* buffered_ray;
    std::vector<unsigned int> rect_indices;
    GLuint VBO, VAO, EBO;

};
