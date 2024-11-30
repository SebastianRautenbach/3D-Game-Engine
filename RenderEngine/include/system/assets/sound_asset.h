#pragma once
#include "system/assets.h"
#include "system/core_renderable.h"
#include <filesystem>
#include <fmod.hpp>
#include <fmod_errors.h>


namespace wizm {

	class sound_asset : public core_asset, public core_renderable {
	public:
		void load(const std::string& path) override {
			if (!path.empty())
			{
				std::filesystem::path filepath(path);						
				file_name = filepath.filename().string();
				m_filepath = filepath.string();
			}
		}

		void setup() {
			auto result = m_system->createSound(m_filepath.c_str(), FMOD_3D, nullptr, &m_sound);
		}

		void stop(FMOD::Channel* channel) {
			if (channel) {
				channel->stop();
			}

		}

		void play(bool loop, FMOD::Channel** channel, bool is_3d) {
			if (m_system && m_sound) {
				m_sound->setMode((is_3d ? FMOD_3D : FMOD_2D) | (loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));
				if (is_3d) { m_sound->set3DMinMaxDistance(1.0f, 100.0f); }
				m_system->playSound(m_sound, nullptr, false, channel);
			}
		}


		void set_3d_attrib(const FMOD_VECTOR position, const FMOD_VECTOR velocity, FMOD::Channel* channel) {
			if (channel) {
				channel->set3DAttributes(&position, &velocity);
			}
		}

		void release() {
			if (m_sound) {
				m_sound->release();
				m_sound = nullptr;
			}
		}


	public:
		std::string m_filepath;
		FMOD::System* m_system;
		FMOD::Sound* m_sound = nullptr;
		
	};
}