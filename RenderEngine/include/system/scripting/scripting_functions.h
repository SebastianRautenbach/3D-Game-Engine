#pragma once

#ifndef SCRIPTING_FUNCTIONS
#define SCRIPTING_FUNCTIONS

#include "angelscript/include/angelscript.h"
#include "add_on/scriptbuilder/scriptbuilder.h"
#include "add_on/scriptstdstring/scriptstdstring.h"
#include <string>
#include <iostream>
#include "system/scene_manager.h"
#include "system/asset_importer.h"
#include "system/input_manager.h"

/*
	These following function are copied from the hpl1 engine on github https://github.com/FrictionalGames/HPL1Engine/blob/5e441bbb247a7473e75cc0f05ca8a5b62c6ec64c/include/system/Script.h#L42
	I just like the way they did it and I am also to lazy XD
*/

#ifdef __GNUC__
#ifdef __ppc__
#define __stdcall
#else
#define __stdcall __attribute__((stdcall))
#endif
#endif

#define SCRIPT_DEFINE_FUNC(return, funcname) \
			SCRIPT_FUNC_BEGIN(funcname, return, "") \
			SCRIPT_RETURN_CALL_##return funcname(); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_1(return, funcname, arg0) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_2(return, funcname, arg0, arg1) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_3(return, funcname, arg0, arg1, arg2) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_4(return, funcname, arg0, arg1, arg2, arg3) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_5(return, funcname, arg0, arg1, arg2, arg3, arg4) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_6(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_7(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5, arg6) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5","#arg6) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_ARG_##arg6(6); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_8(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5","#arg6","#arg7) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_ARG_##arg6(6); \
			SCRIPT_ARG_##arg7(7); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_9(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5","#arg6","#arg7","#arg8) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_ARG_##arg6(6); \
			SCRIPT_ARG_##arg7(7); \
			SCRIPT_ARG_##arg8(8); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7,_arg8); \
			SCRIPT_FUNC_END(funcname,return)

#define SCRIPT_DEFINE_FUNC_10(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5","#arg6","#arg7","#arg8","#arg9) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_ARG_##arg6(6); \
			SCRIPT_ARG_##arg7(7); \
			SCRIPT_ARG_##arg8(8); \
			SCRIPT_ARG_##arg9(9); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_arg7,_arg8,_arg9); \
			SCRIPT_FUNC_END(funcname,return)

#define SCRIPT_DEFINE_FUNC_12(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5, arg6, \
				arg7, arg8, arg9, arg10, arg11) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5","#arg6 \
				","#arg7","#arg8","#arg9","#arg10","#arg11) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_ARG_##arg6(6); \
			SCRIPT_ARG_##arg7(7); \
			SCRIPT_ARG_##arg8(8); \
			SCRIPT_ARG_##arg9(9); \
			SCRIPT_ARG_##arg10(10); \
			SCRIPT_ARG_##arg11(11); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6, \
					_arg7,_arg8,_arg9,_arg10,_arg11); \
			SCRIPT_FUNC_END(funcname,return)
#define SCRIPT_DEFINE_FUNC_17(return, funcname, arg0, arg1, arg2, arg3, arg4, arg5, arg6, \
				arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) \
			SCRIPT_FUNC_BEGIN(funcname, return, #arg0","#arg1","#arg2","#arg3","#arg4","#arg5","#arg6 \
				","#arg7","#arg8","#arg9","#arg10","#arg11","#arg12","#arg13","#arg14","#arg15","#arg16) \
			SCRIPT_ARG_##arg0(0); \
			SCRIPT_ARG_##arg1(1); \
			SCRIPT_ARG_##arg2(2); \
			SCRIPT_ARG_##arg3(3); \
			SCRIPT_ARG_##arg4(4); \
			SCRIPT_ARG_##arg5(5); \
			SCRIPT_ARG_##arg6(6); \
			SCRIPT_ARG_##arg7(7); \
			SCRIPT_ARG_##arg8(8); \
			SCRIPT_ARG_##arg9(9); \
			SCRIPT_ARG_##arg10(10); \
			SCRIPT_ARG_##arg11(11); \
			SCRIPT_ARG_##arg12(12); \
			SCRIPT_ARG_##arg13(13); \
			SCRIPT_ARG_##arg14(14); \
			SCRIPT_ARG_##arg15(15); \
			SCRIPT_ARG_##arg16(16); \
			SCRIPT_RETURN_CALL_##return funcname(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6, \
					_arg7,_arg8,_arg9,_arg10,_arg11,_arg12,_arg13,_arg14,_arg15,_arg16); \
			SCRIPT_FUNC_END(funcname,return)

#define SCRIPT_FUNC_BEGIN(funcname, return, args) \
		namespace GenericScript { \
			static std::string funcname##_return = #return; \
			static std::string funcname##_arg = args; \
			void funcname##_Generic(asIScriptGeneric *gen) { \
				SCRIPT_RETURN_##return;

#define SCRIPT_FUNC_END(funcname, return) \
				SCRIPT_SET_RETURN_##return; \
			} \
		}

// Parameter Macros
#define SCRIPT_ARG_string(n) std::string _arg##n = *(std::string *)gen->GetArgObject(n)
#define SCRIPT_ARG_float(n) float _arg##n = gen->GetArgFloat(n)
#define SCRIPT_ARG_int(n) int _arg##n = gen->GetArgDWord(n)
#define SCRIPT_ARG_bool(n) bool _arg##n = gen->GetArgDWord(n)
// Return Value Macros
#define SCRIPT_RETURN_string std::string _ret
#define SCRIPT_RETURN_CALL_string _ret =
#define SCRIPT_SET_RETURN_string gen->SetReturnObject(&_ret)
#define SCRIPT_RETURN_bool bool _ret
#define SCRIPT_RETURN_CALL_bool _ret =
#define SCRIPT_SET_RETURN_bool gen->SetReturnDWord(_ret ? -1 : 0)
#define SCRIPT_RETURN_int int _ret
#define SCRIPT_RETURN_CALL_int _ret =
#define SCRIPT_SET_RETURN_int gen->SetReturnDWord(_ret)
#define SCRIPT_RETURN_float float _ret
#define SCRIPT_RETURN_CALL_float _ret =
#define SCRIPT_SET_RETURN_float gen->SetReturnFloat(_ret)
#define SCRIPT_RETURN_void
#define SCRIPT_RETURN_CALL_void
#define SCRIPT_SET_RETURN_void

#if defined(AS_MAX_PORTABILITY)
#define SCRIPT_REGISTER_FUNC(funcname) \
		GenericScript::funcname##_return+" "#funcname" ("+GenericScript::funcname##_arg+")", (void *)GenericScript::funcname##_Generic, asCALL_GENERIC
#else
#define SCRIPT_REGISTER_FUNC(funcname) \
		GenericScript::funcname##_return+" "#funcname" ("+GenericScript::funcname##_arg+")", (void *)funcname, asCALL_STDCALL
#endif


namespace engine_scripting
{
	
	


	static void __stdcall print(std::string& msg) {
		std::cout << msg << "\n";
	}
	SCRIPT_DEFINE_FUNC_1(void, print, string);


	//------------------------------------------------- STATIC INPUT
	//--------------------------------------------------------------

	static bool has_key_pressed(int key) {
		return global_input_manager->has_key_been_pressed(key);
	}
	SCRIPT_DEFINE_FUNC_1(bool, has_key_pressed, int);

	
	//-------------------------------------------------- STATIC MESH
	//--------------------------------------------------------------
	
	static void change_mesh(std::string entity_name, int component_index ,std::string asset_id) {
		auto entity = global_scene->get_entity_name(entity_name);
		
		if(entity->m_components_list.size() > component_index) {
			auto sm_comp = std::dynamic_pointer_cast<staticmesh_component>(entity->m_components_list[component_index]);
			sm_comp->m_asset_id = asset_id;
			global_scene->m_reloaded = true;
		}
	}
	SCRIPT_DEFINE_FUNC_3(void, change_mesh, string, int, string)
	
	
	
	//--------------------------------------------------   TRANSFORM
	//--------------------------------------------------------------
	// entity
	
	static void set_entity_rotation(std::string entity_name, float p, float y, float r) {
		auto entity = global_scene->get_entity_name(entity_name);
		entity->set_rotation(glm::vec3(p, y, r));
	}
	SCRIPT_DEFINE_FUNC_4(void, set_entity_rotation, string, float, float, float);
	
	//-----------------------------------------------------------------------
	
	static void add_entity_rotation(std::string entity_name, float p, float y, float r) {
		auto entity = global_scene->get_entity_name(entity_name);
		entity->add_rotation(glm::vec3(p, y, r));
	}
	SCRIPT_DEFINE_FUNC_4(void, add_entity_rotation, string, float, float, float);
	
	//-----------------------------------------------------------------------
	
	
	static void set_entity_position(std::string entity_name, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
		entity->set_position(glm::vec3(x, y, z));
	}
	SCRIPT_DEFINE_FUNC_4(void, set_entity_position, string, float, float, float);
	
	//-----------------------------------------------------------------------
	
	static void add_entity_position(std::string entity_name, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
		entity->add_position(glm::vec3(x, y, z));
	}
	SCRIPT_DEFINE_FUNC_4(void, add_entity_position, string, float, float, float);
	
	
	//-----------------------------------------------------------------------
	
	
	static void set_entity_scale(std::string entity_name, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
		entity->set_scale(glm::vec3(x, y, z));
	}
	SCRIPT_DEFINE_FUNC_4(void, set_entity_scale, string, float, float, float);
	
	//-----------------------------------------------------------------------
	
		
	static void add_entity_scale(std::string entity_name, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
		entity->add_scale(glm::vec3(x, y, z));
	}
	SCRIPT_DEFINE_FUNC_4(void, add_entity_scale, string, float, float, float);
	
	// component
	
	static void set_component_rotation(std::string entity_name, int component_index, float p, float y, float r) {
		auto entity = global_scene->get_entity_name(entity_name);
	
		if (entity->m_components_list.size() > component_index) {
			auto comp = entity->m_components_list[component_index];
			comp->set_rotation(glm::vec3(p, y, r));
		}
	}
	SCRIPT_DEFINE_FUNC_5(void, set_component_rotation, string, int, float, float, float);
	
	//-----------------------------------------------------------------------
	
	static void add_component_rotation(std::string entity_name, int component_index, float p, float y, float r) {
		auto entity = global_scene->get_entity_name(entity_name);
	
		if (entity->m_components_list.size() > component_index) {
			auto comp = entity->m_components_list[component_index];
			comp->add_rotation(glm::vec3(p, y, r));
		}
	}
	SCRIPT_DEFINE_FUNC_5(void, add_component_rotation, string, int, float, float, float);
	
	//-----------------------------------------------------------------------
	
	
	static void set_component_position(std::string entity_name, int component_index, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
	
		if (entity->m_components_list.size() > component_index) {
			auto comp = entity->m_components_list[component_index];
			comp->set_position(glm::vec3(x, y, z));
		}
	}
	SCRIPT_DEFINE_FUNC_5(void, set_component_position, string, int, float, float, float);
	
	
	//-----------------------------------------------------------------------
	
	
	static void add_component_position(std::string entity_name, int component_index, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
	
		if (entity->m_components_list.size() > component_index) {
			auto comp = entity->m_components_list[component_index];
			comp->add_position(glm::vec3(x, y, z));
		}
	}
	SCRIPT_DEFINE_FUNC_5(void, add_component_position, string, int, float, float, float);
	
	
	//-----------------------------------------------------------------------
	
	
	static void set_component_scale(std::string entity_name, int component_index, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
	
		if (entity->m_components_list.size() > component_index) {
			auto comp = entity->m_components_list[component_index];
			comp->set_scale(glm::vec3(x, y, z));
		}
	}
	SCRIPT_DEFINE_FUNC_5(void, set_component_scale, string, int, float, float, float);
	
	
	//-----------------------------------------------------------------------
	
	static void add_component_scale(std::string entity_name, int component_index, float x, float y, float z) {
		auto entity = global_scene->get_entity_name(entity_name);
	
		if (entity->m_components_list.size() > component_index) {
			auto comp = entity->m_components_list[component_index];
			comp->add_scale(glm::vec3(x, y, z));
		}
	}
	SCRIPT_DEFINE_FUNC_5(void, add_component_scale, string, int, float, float, float);


	//-----------------------------------------------------------------------





bool add_script_func(asIScriptEngine* script_engine, const std::string& func_decl, void* function, int call_conv) {

	if (script_engine->RegisterGlobalFunction(func_decl.c_str(),
		asFUNCTION(function), call_conv) < 0)
	{
		std::cerr << "Couldn't add func: " << func_decl.c_str() << "\n";
		return false;
	}

	return true;
}

class scripting_functions {
public:

	void init_scripts(asIScriptEngine* script_engine) {

		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(print));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(has_key_pressed));

		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(change_mesh));
		
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(set_entity_rotation));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(add_entity_rotation));
		
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(set_entity_position));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(add_entity_position));
		
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(set_entity_scale));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(add_entity_scale));
		
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(set_component_rotation));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(add_component_rotation));
		
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(set_component_position));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(add_component_position));
		
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(set_component_scale));
		add_script_func(script_engine, SCRIPT_REGISTER_FUNC(add_component_scale));
	}
};


}



#endif


