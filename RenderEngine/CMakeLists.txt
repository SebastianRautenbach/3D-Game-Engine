cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(RenderEngine C CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)   
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME RenderEngine)

set(CMAKE_STARTUP_PROJECT RenderEngine)





################################################################################
# Source groups
################################################################################
set(Header_Files
    "include/core_application.h"
    "include/dependencies/add_on/scriptarray/scriptarray.h"
    "include/dependencies/add_on/scriptbuilder/scriptbuilder.h"
    "include/dependencies/add_on/scriptstdstring/scriptstdstring.h"
    "include/dependencies/filetypes.h"
    "include/dependencies/imgui/backends/imgui_impl_glfw.h"
    "include/dependencies/imgui/backends/imgui_impl_opengl3.h"
    "include/dependencies/imgui/imconfig.h"
    "include/dependencies/imgui/imgui.h"
    "include/dependencies/imgui/imgui_internal.h"
    "include/dependencies/imgui/imstb_rectpack.h"
    "include/dependencies/imgui/imstb_textedit.h"
    "include/dependencies/imgui/imstb_truetype.h"
    "include/dependencies/ImGuizmo/ImCurveEdit.h"
    "include/dependencies/ImGuizmo/ImGradient.h"
    "include/dependencies/ImGuizmo/ImGuizmo.h"
    "include/dependencies/ImGuizmo/ImSequencer.h"
    "include/dependencies/sqlite3.h"
    "include/entity sys/component.h"
    "include/entity sys/component_types.h"
    "include/entity sys/components/all_components_list.h"
    "include/entity sys/components/boxvolume_component.h"
    "include/entity sys/components/camera_component.h"
    "include/entity sys/components/light_component.h"
    "include/entity sys/components/pointlight_component.h"
    "include/entity sys/components/scripting_component.h"
    "include/entity sys/components/sound_component.h"
    "include/entity sys/entity.h"
    "include/gl core/core shader.h"
    "include/gl core/core_camera.h"
    "include/gl core/engine_shader_types.h"
    "include/gl core/vertex_buffer.h"
    "include/gl renderer/gl_renderer.h"
    "include/input.h"
    "include/input_types.h"
    "include/layers/asset_viewer_layer.h"
    "include/layers/content_browser_layer.h"
    "include/layers/gui_cntx.h"
    "include/layers/layer.h"
    "include/layers/layers_define.h"
    "include/layers/layerstack.h"
    "include/layers/material_editor_layer.h"
    "include/layers/performance_ui_layer.h"
    "include/layers/properties_ui_layer.h"
    "include/layers/scene_ui_layer.h"
    "include/layers/script_debug_layer.h"
    "include/layers/script_editor_layer.h"
    "include/layers/UI/popup_window.h"
    "include/other utils/common.h"
    "include/other utils/extra_utils.h"
    "include/other utils/IDGEN.h"
    "include/other utils/matrix_math.h"
    "include/other utils/ZER.h"
    "include/scene.h"
    "include/system/asset_class.h"
    "include/system/asset_importer.h"
    "include/system/asset_manager.h"
    "include/system/assets.h"
    "include/system/assets/assettypes.h"
    "include/system/assets/entity_asset.h"
    "include/system/assets/material_asset.h"
    "include/system/assets/mesh_asset.h"
    "include/system/assets/script_asset.h"
    "include/system/assets/sound_asset.h"
    "include/system/assets/texture_asset.h"
    "include/system/assettypes.h"
    "include/system/audio_listener.h"
    "include/system/audio_manager.h"
    "include/system/billboard.h"
    "include/system/billboard_manager.h"
    "include/system/bounding_volume.h"
    "include/system/camera_3d.h"
    "include/system/camera_manager.h"
    "include/system/compose_level.h"
    "include/system/compose_material.h"
    "include/system/compute_cluster_test.h"
    "include/system/core_mesh.h"
    "include/system/core_model.h"
    "include/system/core_renderable.h"
    "include/system/draw_ray.h"
    "include/system/filewatcher.h"
    "include/system/input_manager.h"
    "include/system/material.h"
    "include/system/material_types.h"
    "include/system/node.h"
    "include/system/scene_manager.h"
    "include/system/scripting/compose_script.h"
    "include/system/scripting/script_controller.h"
    "include/system/scripting/scripting_functions.h"
    "include/system/scripting/scripting_objects.h"
    "include/system/tag.h"
    "include/system/timer.h"
    "include/update_manager.h"
    "include/viewport/viewport_gui.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "include/dependencies/add_on/scriptarray/scriptarray.cpp"
    "include/dependencies/add_on/scriptbuilder/scriptbuilder.cpp"
    "include/dependencies/add_on/scriptstdstring/scriptstdstring.cpp"
    "include/dependencies/add_on/scriptstdstring/scriptstdstring_utils.cpp"
    "include/dependencies/glad.c"
    "include/dependencies/imgui/backends/imgui_impl_glfw.cpp"
    "include/dependencies/imgui/backends/imgui_impl_opengl3.cpp"
    "include/dependencies/imgui/imgui.cpp"
    "include/dependencies/imgui/imgui_demo.cpp"
    "include/dependencies/imgui/imgui_draw.cpp"
    "include/dependencies/imgui/imgui_tables.cpp"
    "include/dependencies/imgui/imgui_widgets.cpp"
    "include/dependencies/ImGuizmo/ImCurveEdit.cpp"
    "include/dependencies/ImGuizmo/ImGradient.cpp"
    "include/dependencies/ImGuizmo/ImGuizmo.cpp"
    "include/dependencies/ImGuizmo/ImSequencer.cpp"
    "include/dependencies/sqlite3.c"
    "include/dependencies/tinyfiledialogs.c"
    "include/entity sys/components/directionallight_component.h"
    "include/entity sys/components/spotlight_component.h"
    "include/entity sys/components/staticmesh_component.h"
    "include/layers/viewport_layer.h"
    "include/other utils/copy_to_clipboard.h"
    "include/other utils/strconvr.h"
    "include/system/mouse_picking.h"
    "src/app.cpp"
    "src/components/boxvolume_component.cpp"
    "src/components/camera_component.cpp"
    "src/components/component.cpp"
    "src/components/directionallight_component.cpp"
    "src/components/light_component.cpp"
    "src/components/pointlight_component.cpp"
    "src/components/scripting_component.cpp"
    "src/components/sound_component.cpp"
    "src/components/spotlight_component.cpp"
    "src/components/staticmesh_component.cpp"
    "src/core shader.cpp"
    "src/entity.cpp"
    "src/input.cpp"
    "src/layers/asset_viewer_layer.cpp"
    "src/layers/content_browser_layer.cpp"
    "src/layers/gui_layer.cpp"
    "src/layers/layerstack.cpp"
    "src/layers/material_editor_layer.cpp"
    "src/layers/performance_ui_layer.cpp"
    "src/layers/properties_ui_layer.cpp"
    "src/layers/scene_ui_layer.cpp"
    "src/layers/script_debug_layer.cpp"
    "src/layers/script_editor_layer.cpp"
    "src/layers/viewport_layer.cpp"
    "src/material.cpp"
    "src/other utils/common.cpp"
    "src/scene.cpp"
    "src/sdl renderer/gl_renderer.cpp"
    "src/systems/asset_manager.cpp"
    "src/systems/billboard.cpp"
    "src/systems/billboard_manager.cpp"
    "src/systems/camera_3d.cpp"
    "src/systems/camera_manager.cpp"
    "src/systems/compute_cluster_test.cpp"
    "src/systems/core_mesh.cpp"
    "src/systems/core_model.cpp"
    "src/systems/core_renderable.cpp"
    "src/systems/input_manager.cpp"
    "src/systems/node.cpp"
    "src/systems/scene_manager.cpp"
    "src/systems/scripting/script_controller.cpp"
    "src/tag.cpp"
    "src/timer.cpp"
    "src/update_manager.cpp"
    "src/vertex_buffer.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE RenderEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDebug
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDebug
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies/imgui;"
        "${CMAKE_CURRENT_SOURCE_DIR}/RenderEngine/include/dependencies/imgui;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies/fmod;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies/angelscript/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies/imgui;"
        "${CMAKE_CURRENT_SOURCE_DIR}/RenderEngine/include/dependencies/imgui;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies/fmod;"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/dependencies/angelscript/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "glfw3dll;"
        "opengl32;"
        "assimp-vc143-mtd;"
        "angelscript64d;"
        "fmod_vc;"
        "fmodL_vc"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "glfw3dll;"
        "opengl32;"
        "assimp-vc143-mtd;"
        "angelscript64d;"
        "fmod_vc;"
        "fmodL_vc"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/lib"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/lib"
    )
endif()


################################################################################
# Copy .dll files into Debug/Release folders
################################################################################
# Specify the source directory containing the .dll files
set(DLL_SOURCE_DIR "${CMAKE_SOURCE_DIR}/DLL")

# Specify the target directories
set(DLL_OUTPUT_DIR_DEBUG "${CMAKE_BINARY_DIR}/x64/Debug")
set(DLL_OUTPUT_DIR_RELEASE "${CMAKE_BINARY_DIR}/x64/Release")

# Copy .dll files for Debug
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DLL_OUTPUT_DIR_DEBUG}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${DLL_SOURCE_DIR}"
        "${DLL_OUTPUT_DIR_DEBUG}"
    COMMENT "Copying .dll files to Debug folder"
    VERBATIM
)

# Copy .dll files for Release
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DLL_OUTPUT_DIR_RELEASE}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${DLL_SOURCE_DIR}"
        "${DLL_OUTPUT_DIR_RELEASE}"
    COMMENT "Copying .dll files to Release folder"
    VERBATIM
)