#include "InputComponent.hpp"

InputComponent::InputComponent() {}

InputComponent::~InputComponent() {}

State InputComponent::getValue() const override { return value; }

void InputComponent::nextSimulation() override {}
