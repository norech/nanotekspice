#include "../circuit/Circuit.hpp"

namespace nts {

Circuit *Circuit::circuit = nullptr;

Circuit::Circuit(void) {
    if (circuit == nullptr) circuit = this;
}

Circuit *Circuit::getInstance(void) { return Circuit::circuit; }

Component* Circuit::getFromName(const std::string& name)
{
    Circuit *circuit = Circuit::getInstance();

    for (auto& it : circuit->_components) {
        if (it->getName() == name)
            return it.get();
    }
    return nullptr;
}

Component *Circuit::addComponent(const std::string& type, const std::string& name) {
    Circuit *circuit = Circuit::getInstance();

    if (circuit->getFromName(name) != nullptr) {
        throw std::runtime_error("Cannot add twice a component with the same name");
    }
    throw std::runtime_error("No component can be added yet");
}

}  // namespace nts
