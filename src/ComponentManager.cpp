#include "ComponentManager.hpp"

namespace nts {

ComponentManager::ComponentManager() {}

ComponentManager::~ComponentManager() {}

std::unique_ptr<IComponent> createComponent(const std::string& type) {
    switch (type) {
        case "4001":
            return create4001();
        case "4013":
            return create4013();
        case "4040":
            return create4040();
        default:
            throw new Error("Unknown component type");
    }
}

std::unique_ptr<IComponent> create4001() const noexcept {}

std::unique_ptr<IComponent> create4013() const noexcept {}

std::unique_ptr<IComponent> create4040() const noexcept {}

}  // namespace nts
