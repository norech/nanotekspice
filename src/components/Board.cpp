#include "Board.hpp"

#include "SpecialComponent.hpp"

namespace nts {

Board::Board(Circuit* circuit)
    : Component(circuit->getName()),
      _circuit(std::unique_ptr<Circuit>(circuit)) {
    for (auto& component : circuit->getComponents()) {
        if (component.first.find("pin_") == 0) {
            int pinId = std::stoi(component.first.substr(4));

            if (dynamic_cast<Input*>(component.second.get())) {
                addInputPin(pinId);
            }
            else if (dynamic_cast<Output*>(component.second.get())) {
                addOutputPin(pinId);
            }
        }
    }
}

void Board::simulate() { _circuit->simulate(); }

Tristate Board::compute(std::size_t pinIndex) {
    if (getPin(pinIndex).getType() == OUTPUT) {
        for (auto& it : _pins) {
            Pin& pin = *it.second;
            if (pin.getType() == INPUT) {
                _circuit->setInput("pin_" + std::to_string(pin.getPin()),
                                   pin.compute());
            }
        }
        _circuit->simulate();
        return _circuit->getOutput("pin_" + std::to_string(pinIndex));
    }
    else {
        Pin& pin = getPin(pinIndex);
        Tristate state = pin.compute();
        _circuit->setInput("pin_" + std::to_string(pinIndex), state);
        return state;
    }
}

}  // namespace nts
