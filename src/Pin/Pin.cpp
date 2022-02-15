#include "Pin.hpp"

namespace nts
{
    bool Pin::otherIsSelf(const std::shared_ptr<IComponent> &other) const
    {
        return other.get() == _component.get();
    }

    bool Pin::isLinkedTo(const std::shared_ptr<IComponent> &other, std::size_t pin) const
    {
        for (const auto it : _links) {
            if (it.first.get() == other.get() && it.second == pin) {
                return true;
            }
        }
        return false;
    }

    void InputPin::setLink(const std::shared_ptr<IComponent> &other, std::size_t otherPin)
    {
        if (otherIsSelf(other) == true) {
            throw std::runtime_error("You cannot link a pin to his composant itself");
        } else if (isLinkedTo(other, otherPin) == true) {
            throw std::runtime_error("Already linked");
        } else if (other->getPinType(otherPin) != PinType::OUTPUT) {
            throw std::runtime_error("Cannot link output to input");
        }
        _links.push_back({other, otherPin});
    }

    void OutputPin::setLink(const std::shared_ptr<IComponent> &other, std::size_t otherPin)
    {
        (void)other;
        (void)otherPin;
        throw std::runtime_error("Cannot link output");
    }

}
