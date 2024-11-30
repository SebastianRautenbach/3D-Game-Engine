#include "entity sys/components/scripting_component.h"


wizm::scripting_component::scripting_component()
{
	m_component_type = eScripting;
}

wizm::scripting_component::~scripting_component()
{
}

void wizm::scripting_component::component_preupdate()
{
}

void wizm::scripting_component::component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
{
	if(!m_script_asset) {
		return;
	}

	if (engine_status == RUNTIME_STATUS) {

		if (m_script_asset->m_initiated_script) {
			m_script_asset->on_update(delta_time);
		}
		else
		{
			m_script_asset->on_start();
			m_script_asset->m_initiated_script = true;
		}

	}
	else
	{
		m_script_asset->m_initiated_script = false;
	}
}	

void wizm::scripting_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::scripting_component::_copy() const
{
	auto new_sc_comp = std::make_shared<scripting_component>();
	new_sc_comp->set_position(this->get_position());
	new_sc_comp->set_rotation(this->get_rotation());
	new_sc_comp->set_scale(this->get_scale());
	new_sc_comp->script_asset_id = this->script_asset_id;
	new_sc_comp->m_is_active = this->m_is_active;
	new_sc_comp->m_script_asset = this->m_script_asset;


	return new_sc_comp;
}