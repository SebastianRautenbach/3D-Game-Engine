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

    glm::mat4 rotation = glm::mat4_cast(glm::quat(m_rotation));
        
    glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), m_translation) * rotation * 
        glm::scale(glm::mat4(1.0f), m_scale);


    if (m_parent_node != nullptr) {
        
        glm::mat4 parentTransform = m_parent_node->get_transform();
        return parentTransform * localTransform;
    }
    else {
       
        return localTransform;
    }
}
