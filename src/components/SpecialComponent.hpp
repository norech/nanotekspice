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
    void setValue(Tristate value);
};

class Clock : public Input {
private:
    bool _alreadyInvertedOnce = false;

public:
    Clock(const std::string& name);

    void simulate(void) override;
};

class Output : public SpecialComponent {
public:
    Output(const std::string& name);
};

class Boolean : public SpecialComponent {
protected:
    Boolean(const std::string& name, bool value);
};

class True : public Boolean {
public:
    True(const std::string& name);
};

class False : public Boolean {
public:
    False(const std::string& name);
};

}  // namespace nts
