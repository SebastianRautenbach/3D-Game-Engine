#pragma once

#ifndef GLOBALS_COMMON_H
#define GLOBALS_COMMON_H

#include <string>

#define EDITOR_STATUS 0x001
#define RUNTIME_STATUS 0x002
#define CLIENT_PACKAGED_STATUS 0x003
#define SERVER_PACKAGED_STATUS 0x004

extern int engine_status;
extern std::string global_console_out;

#endif // GLOBALS_H


