#pragma once

#include "../State.hpp"
#include "./IComponent.hpp"

class InputComponent : public IComponent {
public:
    InputComponent();
    ~InputComponent();
    InputComponent(const InputComponent& other) = default;
    operator=(const InputComponent& other) = default;

    State getValue() const override;
    void nextSimulation() override;

private:
    State value = UNDEFINED;
};
