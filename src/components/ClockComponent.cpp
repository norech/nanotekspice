#include "ClockComponent.hpp"

#include "InputComponent.hpp"

namespace nts {

ClockComponent::ClockComponent()
    : InputComponent()
{
}

ClockComponent::~ClockComponent() { }

void ClockComponent::simulate(std::size_t tick)
{
    InputComponent::simulate(tick);
    value = (value == TRUE) ? FALSE : TRUE;
}

} // namespace nts
