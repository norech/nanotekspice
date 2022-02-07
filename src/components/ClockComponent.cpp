#include "ClockComponent.hpp"

#include "InputComponent.hpp"

nts::ClockComponent::ClockComponent() : InputComponent() {}

nts::ClockComponent::~ClockComponent() : ~InputComponent() {}

void nts::ClockComponent::simulate(std::size_t tick) override {
    InputComponent::simulate(tick);
    value = (value == TRUE) ? FALSE : TRUE;
}
