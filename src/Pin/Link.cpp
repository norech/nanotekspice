#include "./Link.hpp"

#include "../components/Component.hpp"

namespace nts {

Link::Link(Component &originComponent, std::size_t originPin,
           Component &targetComponent, std::size_t targetPin)
    : _originComponent(originComponent),
      _originPinIndex(originPin),
      _targetComponent(targetComponent),
      _targetPinIndex(targetPin) {}

Component &Link::getOriginComponent(void) { return _originComponent; }

size_t Link::getOriginPinIndex(void) const { return _originPinIndex; }

Pin &Link::getOriginPin(void) const {
    return _originComponent.getPin(_originPinIndex);
}

Component &Link::getTargetComponent(void) { return _targetComponent; }

size_t Link::getTargetPinIndex(void) const { return _targetPinIndex; }

Pin &Link::getTargetPin(void) const {
    return _targetComponent.getPin(_targetPinIndex);
}

}  // namespace nts
