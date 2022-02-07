#pragma once

#include "../State.hpp"

class IComponent {
public:
    IComponent();
    virtual ~IComponent();

    virtual State getValue() const;
    virtual void nextSimulation();

private:
};
