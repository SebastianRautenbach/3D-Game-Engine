#include "system/billboard.h"

wizm::billboard_core::billboard_core(eBillboardType type, std::shared_ptr<core_gl_shader> shader, std::shared_ptr<core_3d_camera> camera)
	:m_camera(camera), m_shader(shader)
{

}

void wizm::billboard_core::draw()
{
}
