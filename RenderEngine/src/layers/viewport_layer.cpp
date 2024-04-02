#include "layers/viewport_layer.h"

wizm::viewport_layer::viewport_layer(unsigned int fbID, core_3d_camera* camera, core_scene* scene)
    : core_layer("viewport_layer"), m_fbID(fbID), m_camera(camera), m_scene(scene)
{
}

wizm::viewport_layer::~viewport_layer()
{
}

void wizm::viewport_layer::OnAttach()
{

}

void wizm::viewport_layer::OnDetach()
{
}

void wizm::viewport_layer::update()
{
    ImGui::Begin("Viewport");
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ImVec2 mSize = { viewportPanelSize.x, viewportPanelSize.y };
    m_camera->SetAspect(mSize.x / mSize.y);


    ImGui::Image(reinterpret_cast<void*>(m_fbID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


    // GIZMO
    
    if (m_scene->get_crnt_entity())
    {
        auto ent = m_scene->get_crnt_entity();

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        float wWidth = (float)ImGui::GetWindowWidth();
        float wHeight = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, wWidth, wHeight);
       
        
        glm::mat4 transform = glm::mat4(1.0);
        transform = glm::translate(transform, ent->m_position);
        transform = glm::rotate(transform, ent->m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::rotate(transform, ent->m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, ent->m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::scale(transform, ent->m_scale);
        
        ImGuizmo::Manipulate(glm::value_ptr(m_camera->GetViewMatrix()),
            glm::value_ptr(m_camera->GetProjectionMatrix()), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL,
            glm::value_ptr(transform));
    }


    ImGui::End();
}
