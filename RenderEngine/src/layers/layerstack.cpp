#include "layers/layerstack.h"

wizm::layer_stack::~layer_stack()
{
    for (core_layer* layer : m_Layers) {
        layer->OnDetach();
        delete layer;
    }
  
}


//----------------------------------------------------------------------

void wizm::layer_stack::PushLayer(core_layer* layer)
{
    m_Layers.emplace_back(layer);
    layer->OnAttach();
}

void wizm::layer_stack::PopLayer(core_layer* layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        (*it)->OnDetach();
        m_Layers.erase(it);
    }
}
