#include "system/scripting/script_controller.h"
#include "system/scripting/scripting_functions.h"
#include "other utils/common.h"

script_controller::script_controller(std::string path)
{
	m_script_engine = asCreateScriptEngine();


	module_id = "module_" + generate_unique_id();


	m_script_engine->SetMessageCallback(asFUNCTION(MessageCallback), nullptr, asCALL_CDECL);
	RegisterStdString(m_script_engine);

	engine_scripting::scripting_functions sf;
	sf.init_variables(m_script_engine);
	sf.init_scripts(m_script_engine);

	reload_script(path);

}

script_controller::~script_controller()
{
	m_script_engine->DiscardModule(module_id.c_str());
	m_context->Release();
}

void script_controller::reload_script(std::string path)
{
	CScriptBuilder builder;
	int r = builder.StartNewModule(m_script_engine, module_id.c_str());
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

	asIScriptModule* mod = m_script_engine->GetModule(module_id.c_str());
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

void script_controller::on_start()
{
	if (m_context && m_onstart_func) {
		m_context->Prepare(m_onstart_func);
		int r = m_context->Execute();
		if (r != asEXECUTION_FINISHED) {

		}
	}
}

void script_controller::on_update(float delta_time)
{
	if (m_context && m_onupdate_func) {
		m_context->Prepare(m_onupdate_func);
		m_context->SetArgFloat(0, delta_time);
		int r = m_context->Execute();
		if (r != asEXECUTION_FINISHED) {

		}
	}
}

void script_controller::MessageCallback(const asSMessageInfo* msg)
{
	global_console_out = "console: ";
	global_console_out += msg->message;
}
