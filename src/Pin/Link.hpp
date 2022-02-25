#pragma once

#include <memory>

namespace nts {

class Component;
class Pin;

class Link {
private:
    Component &_originComponent;
    std::size_t _originPinIndex;
    Component &_targetComponent;
    std::size_t _targetPinIndex;

public:
    Link(Component &originComponent, std::size_t originPin,
         Component &targetComponent, std::size_t targetPin);
    Link(const Link &) = default;

    ~Link() = default;

    bool otherIsSelf(const Component &other) const;
    bool isLinkedTo(const Component &other, std::size_t pin) const;

    Component &getTargetComponent(void);
    std::size_t getTargetPinIndex(void) const;
    Pin &getTargetPin(void) const;

    Component &getOriginComponent(void);
    std::size_t getOriginPinIndex(void) const;
    Pin &getOriginPin(void) const;
};

}  // namespace nts
