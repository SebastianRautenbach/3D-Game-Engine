#include "layers/viewport_layer.h"
#include "other utils/matrix_math.h"
#include "input.h"

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


    ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" [T] ").x, 25); 
    ImVec2 buttonPosition = ImVec2((0 + buttonSize.x), (0 + buttonSize.y));

    static int guizmo_type = ImGuizmo::OPERATION::TRANSLATE;
    
    ImGui::SetCursorPos(buttonPosition);
    if (ImGui::Button("[T]", buttonSize))
    {
        guizmo_type = ImGuizmo::OPERATION::TRANSLATE;
        m_snap_value = 0.5f;
    }
    ImGui::SameLine();
    if (ImGui::Button("[R]", buttonSize))
    {
        guizmo_type = ImGuizmo::OPERATION::ROTATE;
        m_snap_value = 45.0f;
    }
    ImGui::SameLine();
    if (ImGui::Button("[S]", buttonSize))
    {
        guizmo_type = ImGuizmo::OPERATION::SCALE;
        m_snap_value = 0.5f;
    }
    ImGui::SameLine();
    buttonSize = ImVec2(ImGui::CalcTextSize(" [Snap] ").x, 25);
    if (ImGui::Button("[Snap]", buttonSize))
        m_should_snap = !m_should_snap;


    // GIZMO


    

    if(m_scene->get_crnt_entity())
    {
        auto ent = m_scene->get_crnt_entity();
        glm::mat4 mat = ent->get_transform();

    
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        glm::mat4 viewMatrix = m_camera->GetViewMatrix();
        
        glm::mat4 projectionMatrix = m_camera->GetProjectionMatrix();

  
        if (m_input_manager->has_key_been_pressed(GLFW_KEY_LEFT_CONTROL))
            m_should_snap = true;

        float snapvals[3] = { m_snap_value, m_snap_value , m_snap_value };


        ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
            (ImGuizmo::OPERATION)guizmo_type,
            ImGuizmo::LOCAL, glm::value_ptr(mat), nullptr, m_should_snap ? snapvals : nullptr);

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 position = glm::vec3(0);
            glm::vec3 rotation = glm::vec3(0);
            glm::vec3 scale = glm::vec3(0);


         
            lowlevelsys::decompose_transform(mat, position, rotation, scale);
            glm::vec3 deltaRot = glm::vec3(0);


            deltaRot = rotation - ent->get_rotation();
            ent->set_position(position);        
            ent->add_rotation(deltaRot);
            ent->set_scale(scale);
        }

    }


    ImGui::End();
}
