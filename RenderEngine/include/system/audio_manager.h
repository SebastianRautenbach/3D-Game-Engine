#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

namespace wizm {
	class audio_manager {
	public:
		audio_manager() : system(nullptr) {
            init();
        }

        ~audio_manager() { cleanup(); }

        void init() {
            
            auto result = FMOD::System_Create(&system);
            if (!system) {            
                std::cout << "fmod system failed to init\n";
                return;
            }
            
            result = system->init(512, FMOD_INIT_NORMAL, nullptr);
        }

        void update() {            
            if (system) {
                system->update();
            }
        }


        void cleanup() {         
            if (system) {
                system->release();
                system = nullptr;
            }
        }



	public:
		FMOD::System* system;
	};
}