#include "layers/viewport_layer.h"

wizm::viewport_layer::viewport_layer(unsigned int fbID, core_3d_camera* camera)
    : core_layer("viewport_layer"), m_fbID(fbID), m_camera(camera)
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
    ImGui::End();
}
