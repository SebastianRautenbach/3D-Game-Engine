#include "layers/gui_cntx.h"
#include "scene.h"

wizm::gui_layer::gui_layer(GLFWwindow* window, core_scene* scene)
    : core_layer("gui_layer"), m_scene(scene)
{
    m_window = window;
}

wizm::gui_layer::~gui_layer()
{
    OnDetach();
}

void wizm::gui_layer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;        
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;      
   
   

   
    ImGui::StyleColorsDark();
   

   
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }


    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void wizm::gui_layer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void wizm::gui_layer::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 12.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

    static bool show_save_popup = false;
    static char map_name[128] = "GAME/new_save.zer";


    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save-as"))
            {
                show_save_popup = true;
            }
            if (ImGui::MenuItem("Save"))
            {
                m_scene->save_map_data("");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::PopStyleVar();

    if (show_save_popup) {
        ImGui::OpenPopup("Save Map As");
    }


    if (ImGui::BeginPopupModal("Save Map As", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Enter the map name:");
        ImGui::InputText("##map_name", map_name, IM_ARRAYSIZE(map_name));

        if (ImGui::Button("OK", ImVec2(120, 0))) {


            m_scene->save_map_data(map_name);

            show_save_popup = false;


            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            show_save_popup = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");
    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

    ImGui::End();


}



void wizm::gui_layer::end()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }


}