#pragma once

#ifndef GLOBALS_COMMON_H
#define GLOBALS_COMMON_H

#include <string>
#include <vector>

#define EDITOR_STATUS 0x001
#define RUNTIME_STATUS 0x002
#define CLIENT_PACKAGED_STATUS 0x003
#define SERVER_PACKAGED_STATUS 0x004

#define CONSOLE_ERROR_LOG 0x000
#define CONSOLE_WARNING_LOG 0x001
#define CONSOLE_GENERAL_LOG 0x002
#define CONSOLE_SUCCESS_LOG 0x003

#define MATERIAL_EDITOR_WINDOW 0x001

extern int engine_status;


namespace wizm {

	struct console_out_s {
		std::string log;
		int log_type;
	};

	struct window_open_s {
		int window_type;
		bool open;
		std::string window_open_with_id;
	};


	extern std::vector<wizm::console_out_s> global_console_out;
	extern wizm::window_open_s window_open;
	
	inline void add_console_line(std::string msg, int log_type) {
		global_console_out.emplace_back("\n" + msg, log_type);
		if (global_console_out.size() > 50) {
			global_console_out.erase(global_console_out.begin(), global_console_out.begin() + (global_console_out.size() - 50));
		}
	}
	
}


#endif // GLOBALS_H


