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

extern int engine_status;


namespace wizm {

	struct console_out_s {
		std::string log;
		int log_type;
	};

	extern std::vector<wizm::console_out_s> global_console_out;
	
	inline void add_console_line(std::string msg, int log_type) {
		global_console_out.emplace_back("\n" + msg, log_type);
	}
	
}


#endif // GLOBALS_H


