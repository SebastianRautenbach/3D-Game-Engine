#pragma once
#include <string>


namespace wizm {

	class core_layer {

    public:
        core_layer(const std::string& name = "Layer") : m_DebugName(name) {}
        virtual ~core_layer() = default;

        virtual void OnAttach() {} 
        virtual void OnDetach() {} 
        virtual void update(float delta_time) {}
        virtual void OnImGuiRender() {}

        std::string get_layer_name() { return m_DebugName; }

    protected:
        std::string m_DebugName;


	};

}