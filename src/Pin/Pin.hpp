#pragma once

#include <functional>
#include <list>
#include <memory>

#include "../Tristate.hpp"
#include "./Link.hpp"

namespace nts {

class Component;
class Link;

class Pin {
public:
protected:
    std::size_t _pin;
    std::vector<std::unique_ptr<Link>> _links;
    PinType _type;
    bool _visited = false;
    Tristate _state = Tristate::UNDEFINED;

public:
    Component &_component;
    Pin(Component &component, std::size_t pin, PinType type);
    virtual ~Pin() = default;

    bool otherIsSelf(const Component &other) const;
    bool isLinkedTo(const Component &other, std::size_t pin) const;
    void setLink(Component &other, std::size_t otherPin);
    const std::vector<std::unique_ptr<Link>> &getLinks(void) const;

    PinType getType(void) const;
    Tristate getState(void) const;
    Pin &setState(Tristate state);

    bool isVisited(void) const;
    Pin &visit(void);
    Pin &unvisit(void);

    virtual Tristate compute(void);

    Tristate update(Tristate state);

    Component &getComponent(void);

    std::size_t getPin(void) const;
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
