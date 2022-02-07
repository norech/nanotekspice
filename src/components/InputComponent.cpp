#include "InputComponent.hpp"

nts::InputComponent::InputComponent() {}

nts::InputComponent::~InputComponent() {}

void nts::InputComponent::simulate(std::size_t tick) override {}

nts::Tristate nts::InputComponent::compute(std::size_t pin) override {}

void nts::InputComponent::setLink(std::size_t pin, nts::IComponent& other,
                                  std::size_t otherPin) override {}

void nts::InputComponent::dump() const override {}
