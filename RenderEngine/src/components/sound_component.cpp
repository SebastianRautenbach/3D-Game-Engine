#include "entity sys/components/sound_component.h"
#include "other utils/common.h"


wizm::sound_component::sound_component()
{
	m_component_type = eSound3D;
}

wizm::sound_component::~sound_component()
{
	stop();
}

void wizm::sound_component::component_preupdate()
{

}

void wizm::sound_component::component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
{

	if (engine_status == RUNTIME_STATUS) {
		if (!on_runtime) { 
			on_start(); 
		}
		else {
			on_update();
		}
	}
	else if(engine_status == EDITOR_STATUS) {
		stop();
	}

	
}

void wizm::sound_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::sound_component::_copy() const
{
	auto new_s_comp = std::make_shared<sound_component>();
	new_s_comp->set_position(this->get_position());
	new_s_comp->set_rotation(this->get_rotation());
	new_s_comp->set_scale(this->get_scale());
	new_s_comp->asset_id = this->asset_id;
	new_s_comp->m_loop = this->m_loop;
	new_s_comp->m_sound_asset = this->m_sound_asset;
	new_s_comp->m_is_active = this->m_is_active;

	return new_s_comp;
}

void wizm::sound_component::on_start()
{
	stopped = false;
	on_runtime = true;
	play();
}

void wizm::sound_component::on_update()
{
	glm::vec3 pos = get_world_position();
	FMOD_VECTOR fmod_pos = { pos.x, pos.y, pos.z };
	FMOD_VECTOR fmod_vel = { 0.0f, 0.0f, 0.0f };
	m_sound_asset->set_3d_attrib(fmod_pos, fmod_vel, m_channel);

}

void wizm::sound_component::play()
{
	m_sound_asset->play(m_loop, &m_channel, m_is3d);
}

void wizm::sound_component::stop()
{
	if(!stopped)
	{		
		m_sound_asset->stop(m_channel);
		stopped = true;
	}
}

