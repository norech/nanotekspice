#pragma once

#include <map>
#include "Pin.hpp"

namespace nts
{
class Chip
{
private:
    std::map<size_t, std::unique_ptr<Pin>> _pins;

public:
    Chip(void) = default;
    ~Chip() = default;

    template<typename T>
    void addPin(size_t pin)
    {
        _pins[pin] = std::make_unique<T>(this->pin, pin);
    }

};

}