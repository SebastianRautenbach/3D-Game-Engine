#pragma once
#include <string>
#include "angelscript/include/angelscript.h"
#include "add_on/scriptbuilder/scriptbuilder.h"
#include "add_on/scriptstdstring/scriptstdstring.h"
#include "other utils/IDGEN.h"
#include <iostream>


class script_controller {

public:
	script_controller(std::string path);
	~script_controller();
	
	bool reload_script(std::string path);
	void reset();

	void on_start();
	void on_update(float delta_time);

	static void MessageCallback(const asSMessageInfo* msg);

private:
	std::string module_id = "", m_path = "";
	asIScriptFunction* m_onupdate_func = nullptr;
	asIScriptFunction* m_onstart_func = nullptr;
	asIScriptEngine* m_script_engine = nullptr;
	asIScriptContext* m_context = nullptr;
	bool m_initiated_scripts = false;

};