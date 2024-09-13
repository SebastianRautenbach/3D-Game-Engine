#pragma once
#include "entity sys/component.h"
#include "angelscript/include/angelscript.h"
#include "add_on/scriptbuilder/scriptbuilder.h"
#include "add_on/scriptstdstring/scriptstdstring.h"

#include "other utils/common.h"

using namespace lowlevelsys;

namespace wizm {

	class scripting_component : public core_component {


	public:
		
		scripting_component();
		~scripting_component();
		
		
		void component_preupdate() override;
		void component_update(float delta_time) override;
		void component_postupdate() override;
		std::shared_ptr<core_component> _copy() const;

		void apply_script(std::string path);

	public:
		
		
		
		void on_start();
		void on_update(float delta_time);
		static void print(const std::string& in);



		static void MessageCallback(const asSMessageInfo* msg) {
			std::cerr << "AngelScript: " << msg->message << std::endl;
		}



	private:
		asIScriptFunction* m_onupdate_func = nullptr;
		asIScriptFunction* m_onstart_func = nullptr;
		asIScriptEngine* m_script_engine = nullptr;
		asIScriptContext* m_context = nullptr;

		bool m_initiated_scripts = false;

	};


}