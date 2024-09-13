#include "entity sys/components/scripting_component.h"


wizm::scripting_component::scripting_component()
{
	m_component_type = eScripting;
	m_script_engine = asCreateScriptEngine();
	if (!m_script_engine) {
		
	}
	
	m_script_engine->SetMessageCallback(asFUNCTION(MessageCallback), nullptr, asCALL_CDECL);
	RegisterStdString(m_script_engine);


	// GONNA HAVE TO MAKE A SEPRATE FUNCTION FOR THESE

	m_script_engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
}

wizm::scripting_component::~scripting_component()
{
	if (m_context) {
		m_context->Release();
	}
	if (m_script_engine) {
		m_script_engine->Release();
	}
}

void wizm::scripting_component::component_preupdate()
{
}

void wizm::scripting_component::component_update(float delta_time)
{
	if (engine_status == RUNTIME_STATUS) {
	
		if (m_initiated_scripts) {
		
			on_update(delta_time);
		}
		else
		{
			on_start();
			m_initiated_scripts = true;
		}

	}
	else
	{
		m_initiated_scripts = false;
	}
}

void wizm::scripting_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::scripting_component::_copy() const
{
	return std::shared_ptr<core_component>();
}

void wizm::scripting_component::apply_script(std::string path)
{
	CScriptBuilder builder;
	int r = builder.StartNewModule(m_script_engine, "GameScriptModule");
	if (r < 0) {
		return;
	}

	r = builder.AddSectionFromFile(path.c_str());
	if (r < 0) {
		return;
	}



	r = builder.BuildModule();
	if (r < 0) {
		return;
	}

	asIScriptModule* mod = m_script_engine->GetModule("GameScriptModule");
	m_onstart_func = mod->GetFunctionByDecl("void on_start()");
	m_onupdate_func = mod->GetFunctionByDecl("void on_update(float)");

	if (!m_onstart_func || !m_onupdate_func) {
		return;
	}

	m_context = m_script_engine->CreateContext();
	if (!m_context) {
		return;
	}
}


/*
		THIS IS FOR SCRIPTING
		THESE FUNCTIONS ARE CALLED AS SOON
		AS THE EDITOR PLAYS OR THE STANDALONE GAME

*/

void wizm::scripting_component::on_start()
{
	if (m_context && m_onstart_func) {
		m_context->Prepare(m_onstart_func);
		int r = m_context->Execute();
		if (r != asEXECUTION_FINISHED) {
			
		}
	}
}

void wizm::scripting_component::on_update(float delta_time)
{
	if (m_context && m_onupdate_func) {
		m_context->Prepare(m_onupdate_func);
		m_context->SetArgFloat(0, delta_time);
		int r = m_context->Execute();
		if (r != asEXECUTION_FINISHED) {

		}
	}
}



void wizm::scripting_component::print(const std::string& in)
{
	std::cout << in << std::endl;

}
