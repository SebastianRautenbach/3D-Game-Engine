#include "layers/material_editor_layer.h"
#include "other utils/strconvr.h"
#include "system/scene_manager.h"

wizm::material_editor_layer::material_editor_layer(asset_manager* asset_manager, gl_renderer* renderer)
    :m_asset_manager(asset_manager), m_renderer(renderer)
{
    framebuffer_spec spec;
    spec.Width = 150;
    spec.Height = 150;
    spec.attachment = { framebuffer_texture_format::RGBA8, framebuffer_texture_format::Depth };
    material_fbo = new core_framebuffer(spec);
    
    sphere.load("resources/models/sphere.fbx");
    sm_comp = new staticmesh_component(std::make_shared<staticmesh_asset>(sphere));

    light = new directionallight_component();
    light->m_brightness = 10;

    m_camera = new camera_core_3d(150, 150);
    m_camera->set_position(glm::vec3(0.0, 0.0, 3.0));

    m_shader = std::shared_ptr<core_gl_shader>(new core_gl_shader("shaders/default_vrtx_shdr.glsl", "shaders/material_frgmnt_shdr.glsl"));
}

wizm::material_editor_layer::~material_editor_layer()
{
    delete sm_comp;
    delete m_renderer;
    delete m_asset_manager;
    delete diffuse_image;
    delete sepcular_image;
    delete material_fbo;
    delete m_camera;
    delete light;
}

void wizm::material_editor_layer::OnAttach()
{
}

void wizm::material_editor_layer::OnDetach()
{
}

void wizm::material_editor_layer::update(float delta_time)
{

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = m_camera->get_view_matrix();
    projection = m_camera->get_projection_matrix();

    m_shader->use_shader();
    m_shader->setFloat("zNear", m_camera->get_near());
    m_shader->setFloat("zFar", m_camera->get_far());
    m_shader->setMat4("inverseProjection", glm::inverse(m_camera->get_projection_matrix()));
    m_shader->setUVec2("screenDimensions", { m_camera->get_window_size().x, m_camera->get_window_size().y });


    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    m_shader->setMat4("perspective", view);
    m_shader->setVec3("camPos", m_camera->get_position());
    m_shader->setVec3("camFront", m_camera->get_forward_vector());





   material_fbo->bind_buffer();
   
   sm_comp->component_preupdate();
   sm_comp->component_update(delta_time, m_shader);
   sm_comp->component_postupdate();
   
   light->component_preupdate();
   light->component_update(delta_time, m_shader);
   light->component_postupdate();
   
   
   material_fbo->unbind_buffer();



	ImGui::Begin("material editor");

    
    ImGui::Image((ImTextureID)material_fbo->get_color_attachment_render_id(0), ImVec2(150, 150));
    if (ImGui::BeginDragDropTarget()) {

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

            const wchar_t* id = (const wchar_t*)payload->Data;
            if (m_asset_manager->get_asset_details_from_id(wstring_to_string(id)).type == tMATERIAL)
            {
                m_material = std::dynamic_pointer_cast<material_asset>(m_asset_manager->get_all_assets()[wstring_to_string(id)]);
                sm_comp->m_materials[0] = m_material;
            }
        }

        ImGui::EndDragDropTarget();
    }

    if(m_material && m_material->m_diffuse_texture)
        ImGui::ImageButton((ImTextureID)m_material->m_diffuse_texture->texture->texture_id, ImVec2(150, 150));
    else
        ImGui::Button("diffuse texture", ImVec2(150, 150));
    if (ImGui::BeginDragDropTarget()) {

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

            const wchar_t* id = (const wchar_t*)payload->Data;
            if (m_asset_manager->get_asset_details_from_id(wstring_to_string(id)).type == tTEXTURE)
            {
                if (m_material) {
                    m_material->diffuse_asset_id = wstring_to_string(id);
                    m_material->m_diffuse_texture = std::dynamic_pointer_cast<texture_asset>(m_asset_manager->get_all_assets()[m_material->diffuse_asset_id]);
                }
            }
        }

        ImGui::EndDragDropTarget();
    }

    if (m_material && m_material->m_specular_texture)
        ImGui::ImageButton((ImTextureID)m_material->m_specular_texture->texture->texture_id, ImVec2(150, 150));
    else
        ImGui::Button("specular texture", ImVec2(150, 150));
    if (ImGui::BeginDragDropTarget()) {

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

            const wchar_t* id = (const wchar_t*)payload->Data;
            if (m_asset_manager->get_asset_details_from_id(wstring_to_string(id)).type == tTEXTURE)
            {
                if (m_material) {
                    m_material->specular_asset_id = wstring_to_string(id);
                    m_material->m_specular_texture = std::dynamic_pointer_cast<texture_asset>(m_asset_manager->get_all_assets()[m_material->specular_asset_id]);
                }
            }
        }

        ImGui::EndDragDropTarget();
    }

    if (ImGui::Button("save material")) {
        filedata::ZER save_t;
        save_t.read_file_cntx(m_material->_path);
        save_t["material"]["textures"].set_string("diffuse", { m_material->diffuse_asset_id });
        save_t["material"]["textures"].set_string("specular", { m_material->specular_asset_id });
        save_t.save_file(save_t, m_material->_path);
    }

	
	ImGui::End();
}
