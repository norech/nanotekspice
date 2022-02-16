#pragma once

#include "Component.hpp"

namespace nts {
class SpecialComponent : public Component {
protected:
    SpecialComponent(const std::string& name);

public:
    Tristate compute(std::size_t pin) override;

    void simulate(std::size_t tick) override;
};

class Input : public SpecialComponent {
public:
    Input(const std::string& name);
};

class Clock : public Input {
public:
    Clock(const std::string& name);

    void simulate(std::size_t tick) override;
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
