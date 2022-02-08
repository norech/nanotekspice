#pragma once

#include "../Tristate.hpp"
#include "./IComponent.hpp"

namespace nts {

class InputComponent : public IComponent {
public:
    InputComponent();
    ~InputComponent();
    InputComponent(const InputComponent& other) = default;
    InputComponent& operator=(const InputComponent& other) = default;

    virtual void simulate(std::size_t tick) override;
    Tristate compute(std::size_t pin) final;
    void setLink(std::size_t pin, IComponent& other,
        std::size_t otherPin) final;
    void dump() const final;

protected:
    Tristate value = UNDEFINED;
};

} // namespace nts

