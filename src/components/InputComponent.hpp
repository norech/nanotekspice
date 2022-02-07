#pragma once

#include "../Tristate.hpp"
#include "./IComponent.hpp"

namespace nts {

class InputComponent : public IComponent {
public:
    InputComponent();
    ~InputComponent();
    InputComponent(const InputComponent& other) = default;
    operator=(const InputComponent& other) = default;

    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;
    void setLink(std::size_t pin, nts::IComponent& other,
                 std::size_t otherPin) override;
    void dump() const override;

protected:
    State value = UNDEFINED;
};

}  // namespace nts
