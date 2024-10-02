#pragma once

namespace wizm {
	
	enum eCompType {
		eStaticMesh,
		eSound3D,
		eSprite,
		ePointLight,
		eSpotLight,
		eDirectionalLight,
		eCamera,
		eScripting
	};

	inline bool is_light_component(eCompType type) {
		return type == ePointLight || type == eSpotLight || type == eDirectionalLight;
	}

}