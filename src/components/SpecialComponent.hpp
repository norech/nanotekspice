#pragma once

#include "Component.hpp"

namespace nts {
class SpecialComponent : public Component {
protected:
    SpecialComponent(const std::string& name);

public:
    Tristate compute(std::size_t pin) override;

    void simulate(void) override;
};

class Input : public SpecialComponent {
public:
    Input(const std::string& name);
    virtual void setValue(Tristate value);
};

class Clock : public Input {
private:
    bool _alreadyInvertedOnce = false;

public:
    Clock(const std::string& name);

    void onPinChanged(size_t pin) override;

    void simulate(void) override;
    void setValue(Tristate value) override;
};

class Output : public SpecialComponent {
public:
    Output(const std::string& name);
};

class True : public SpecialComponent {
public:
    True(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

class False : public SpecialComponent {
public:
    False(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

}  // namespace nts
