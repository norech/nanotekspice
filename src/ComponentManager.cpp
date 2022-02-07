#include "ComponentManager.hpp"

#include <functional>
#include <unordered_map>

namespace nts {

ComponentManager::ComponentManager() { }

ComponentManager::~ComponentManager() { }

std::unique_ptr<IComponent> ComponentManager::createComponent(
    const std::string& type)
{
    std::unordered_map<std::string,
        std::function<std::unique_ptr<IComponent>()>>
        component_map = {
            { "4001", [this]() { return create4001(); } },
            { "4013", [this]() { return create4013(); } },
            { "4040", [this]() { return create4040(); } },
        };

    auto component = component_map.find(type);
    if (component == component_map.end()) {
        throw Error("Unknown component type");
    }
    return component->second();
}

std::unique_ptr<IComponent> ComponentManager::create4001() const
{
    throw Error("Not implemented");
}

std::unique_ptr<IComponent> ComponentManager::create4013() const
{
    throw Error("Not implemented");
}

std::unique_ptr<IComponent> ComponentManager::create4040() const
{
    throw Error("Not implemented");
}

} // namespace nts
