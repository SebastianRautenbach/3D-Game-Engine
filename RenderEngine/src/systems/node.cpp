#include "system/node.h"



//////////////////////////////////////////////////////////////////////////
// DEFAULT CONSTRUCTOR
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------




//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------

wizm::core_node::core_node()
	:m_translation(0.0f), m_rotation(0.0f), m_scale(1.0f)
{
}

void wizm::core_node::set_position(const glm::vec3& position)
{
    m_translation = position;
}

void wizm::core_node::add_position(const glm::vec3& offset)
{
    m_translation += offset;
}

void wizm::core_node::set_rotation(const glm::vec3& rotation)
{
    m_rotation = rotation;
}

void wizm::core_node::add_rotation(const glm::vec3& deltaRotation)
{
    m_rotation += deltaRotation;
}

void wizm::core_node::set_scale(const glm::vec3& scale)
{
    m_scale = scale;
}

void wizm::core_node::add_scale(const glm::vec3& deltaScale)
{
    m_scale += deltaScale;
}

glm::mat4 wizm::core_node::get_transform()
{
    //glm::mat4 matrix = glm::mat4(1.0f);

    //matrix = glm::translate(matrix, m_translation);
    //matrix = glm::rotate(matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    //matrix = glm::rotate(matrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    //matrix = glm::rotate(matrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    //matrix = glm::scale(matrix, m_scale);

    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), m_translation);
    glm::mat4 rotationMatX = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    glm::mat4 rotationMatY = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    glm::mat4 rotationMatZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_scale);
    
    
    glm::mat4 localTransform = translationMat * rotationMatX * rotationMatY * rotationMatZ * scaleMat;


    if (m_parent_node != nullptr) {
        // If there is a parent, multiply by the parent's world transform
        glm::mat4 parentTransform = m_parent_node->get_transform();
        return parentTransform * localTransform;
    }
    else {
        // If there's no parent, the local transform is the world transform
        return localTransform;
    }


   // return matrix;
}
