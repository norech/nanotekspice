#pragma once

#include <functional>
#include <memory>

#include "../Tristate.hpp"

namespace nts {

class Component;

class Pin {
public:
    using Link = std::pair<std::reference_wrapper<Component>, std::size_t>;

protected:
    std::reference_wrapper<Component> _component;
    std::size_t _pin;
    std::vector<Link> _links;
    PinType _type;
    bool _visited = false;
    Tristate _state = Tristate::UNDEFINED;

public:
    Pin(Component &component, std::size_t pin, PinType type);
    virtual ~Pin() = default;

    Pin(const Pin &) = delete;

    bool otherIsSelf(const Component &other) const;
    bool isLinkedTo(const Component &other, std::size_t pin) const;
    void setLink(Component &other, std::size_t otherPin);

    PinType getType(void) const;
    Tristate getState(void) const;
    Pin &setState(Tristate state);

    bool isVisited(void) const;
    Pin &visit(void);
    Pin &unvisit(void);

    virtual Tristate compute(void);

    Tristate update(Tristate state);
};

class InputPin : public Pin {
public:
    InputPin(Component &component, std::size_t pin);
};

class OutputPin : public Pin {
public:
    OutputPin(Component &component, std::size_t pin);
};
}  // namespace nts
