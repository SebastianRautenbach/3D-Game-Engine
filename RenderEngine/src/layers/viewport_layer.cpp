#include "layers/viewport_layer.h"
#include "other utils/matrix_math.h"
#include "input.h"
#include "other utils/strconvr.h"
#include "system/mouse_picking.h"

wizm::viewport_layer::viewport_layer(unsigned int fbID, std::shared_ptr<core_3d_camera> camera, core_scene* scene, gl_renderer* renderer)
    : core_layer("viewport_layer"), m_fbID(fbID), m_camera(camera), m_scene(scene), m_renderer(renderer)
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

void wizm::viewport_layer::update(float delta_time)
{
    ImGui::Begin("Viewport");
     
    
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ImVec2 mSize = { viewportPanelSize.x, viewportPanelSize.y };
    m_camera->SetAspect(mSize.x / mSize.y);


    ImGui::Image(reinterpret_cast<void*>(m_fbID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    if (ImGui::BeginDragDropTarget()) {

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

            const wchar_t* id = (const wchar_t*)payload->Data;
            if(wstring_to_string(id).find(".zer") != -1)
            {
                m_scene->read_map_data(wstring_to_string(id));
                m_scene->m_reloaded = true;
            }


            
        }

        ImGui::EndDragDropTarget();
    }


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

    

    if(m_scene->get_crnt_entity())
    {
        auto ent = m_scene->get_crnt_entity();
        glm::mat4 mat = ent->get_transform();


        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
    
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);



        glm::mat4 viewMatrix = m_camera->GetViewMatrix();
        
        glm::mat4 projectionMatrix = m_camera->GetProjectionMatrix();

        m_should_snap = false;
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

    if(!ImGuizmo::IsUsing() && ImGui::IsWindowHovered())
    {
        static ImVec2 rectStart(-1, -1);
        static ImVec2 rectEnd(-1, -1);

 
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            
            
            
            get_mouse_pick();
            
            rectStart = ImGui::GetMousePos();
            rectEnd = rectStart;             
        
           
        }

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            properties_mouse_pick();
        }

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            rectEnd = ImGui::GetMousePos(); 
        }

       
        if (rectStart.x >= 0 && rectStart.y >= 0 && rectEnd.x >= 0 && rectEnd.y >= 0) {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            draw_list->AddRectFilled(rectStart, rectEnd, IM_COL32(0, 0, 255, 100)); 
        }


        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            rectStart = ImVec2(-1, -1);
            rectEnd = ImVec2(-1, -1);
        }
    }
    
    
    
    
    if (ImGui::BeginPopup("ModEnt") && m_scene->get_crnt_entity() != nullptr) {

        ImGui::Text("Modify Entity");
        ImGui::Separator();
        
        if (ImGui::MenuItem("Delete")) {
            m_scene->m_entities.erase(std::find(m_scene->m_entities.begin(), m_scene->m_entities.end(), m_scene->get_crnt_entity()));

            m_renderer->update_draw_data();

            m_scene->set_crnt_entity(nullptr);
        }
        if (ImGui::MenuItem("Duplicate")) {

            auto name = m_scene->get_crnt_entity()->m_ent_ID;

            while (m_scene->does_ent_name_exist(name)) {
                name += "(1)";
            }


            auto crnt = m_scene->get_crnt_entity()->copy_(name);
            m_scene->add_entity(crnt);
            m_scene->set_crnt_entity(crnt);
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

void wizm::viewport_layer::get_mouse_pick()
{
    ImVec2 crnt_mouse_pos = ImGui::GetMousePos();
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 window_size = ImGui::GetWindowSize();


    glm::vec2 rel_mouse_pos(crnt_mouse_pos.x - window_pos.x, crnt_mouse_pos.y - window_pos.y);
    glm::vec2 norm_mouse_pos(rel_mouse_pos.x / window_size.x, rel_mouse_pos.y / window_size.y);


    glm::vec3 ray_dir = ray::ray_cast(norm_mouse_pos, glm::vec2(1.0f, 1.0f), m_camera->GetProjectionMatrix(), m_camera->GetViewMatrix());
    glm::vec3 ray_pos = ray::ray_origin(m_camera->GetViewMatrix());

    m_scene->set_crnt_entity(get_ent_pick(ray_dir, ray_pos));
}

void wizm::viewport_layer::properties_mouse_pick()
{
    ImVec2 crnt_mouse_pos = ImGui::GetMousePos();
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 window_size = ImGui::GetWindowSize();


    glm::vec2 rel_mouse_pos(crnt_mouse_pos.x - window_pos.x, crnt_mouse_pos.y - window_pos.y);
    glm::vec2 norm_mouse_pos(rel_mouse_pos.x / window_size.x, rel_mouse_pos.y / window_size.y);


    glm::vec3 ray_dir = ray::ray_cast(norm_mouse_pos, glm::vec2(1.0f, 1.0f), m_camera->GetProjectionMatrix(), m_camera->GetViewMatrix());
    glm::vec3 ray_pos = ray::ray_origin(m_camera->GetViewMatrix());

    m_scene->set_crnt_entity(get_ent_pick(ray_dir, ray_pos));
    if (m_scene->get_crnt_entity() != nullptr) { ImGui::OpenPopup("ModEnt"); }

   
}

std::shared_ptr<core_entity> wizm::viewport_layer::get_ent_pick(glm::vec3 ray_dir, glm::vec3 ray_pos)
{
    std::vector<std::shared_ptr<core_entity>> touched_ents;

    for (const auto& ent : m_scene->m_entities) {
        for (const auto& comp : ent->m_components_list) {
            auto sm_comp = std::dynamic_pointer_cast<staticmesh_component>(comp);
            auto li_comp = std::dynamic_pointer_cast<light_component>(comp);
            if (sm_comp) {        
                sm_comp->m_model->update_boundingvolume(ent->get_position(), ent->get_rotation(), ent->get_scale());
                if (sm_comp->m_model->ray_intersect(ray_dir, ray_pos)) 
                    touched_ents.emplace_back(ent);
                
            }
            if (li_comp)
            {
                li_comp->update_boundingvolume(ent->get_position(), ent->get_rotation(), glm::vec3(1.0));
                if (li_comp->ray_intersect(ray_dir, ray_pos))
                    touched_ents.emplace_back(ent);
            }
        }
    }
    

    if (touched_ents.empty())
        return nullptr;



    auto close_ent = touched_ents[0];
    for(const auto ent : touched_ents) {
        float distance = glm::distance(close_ent->get_position(), m_camera->GetPosition());
        float crnt_distnace = glm::distance(ent->get_position(), m_camera->GetPosition());
        if (distance > crnt_distnace) {
            close_ent = ent;
        }
    }

    if (close_ent)
        return close_ent;
    else
        return nullptr;
}
