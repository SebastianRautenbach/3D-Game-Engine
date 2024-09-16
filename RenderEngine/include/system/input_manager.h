#pragma once
#ifndef GLOBALS_INPUT_MANAGER_H
#define GLOBALS_INPUT_MANAGER_H

#include "input.h"

enum input_keys {
    eKEY_W = GLFW_KEY_W,
    eKEY_S = GLFW_KEY_S,
    eKEY_A = GLFW_KEY_A,
    eKEY_D = GLFW_KEY_D,
    eKEY_SPACE = GLFW_KEY_SPACE,
    eKEY_ENTER = GLFW_KEY_ENTER
};

extern input_manager* global_input_manager;


#endif // GLOBALS_H