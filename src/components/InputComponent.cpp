#include "InputComponent.hpp"

#include <iostream>

nts::InputComponent::InputComponent() { }

nts::InputComponent::~InputComponent() { }

void nts::InputComponent::simulate(std::size_t tick)
{
    throw std::runtime_error("simulate not implemented");
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    throw std::runtime_error("compute not implemented");
}

void nts::InputComponent::setLink(std::size_t pin, nts::IComponent& other,
    std::size_t otherPin) { }

void nts::InputComponent::dump() const { }
