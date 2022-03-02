#include "Board.hpp"
namespace nts {
Board::Board(Circuit* circuit)
    : Component(circuit->getName()),
      _circuit(std::unique_ptr<Circuit>(circuit)) {
    for (auto& component : circuit->getComponents()) {
        if (component.first.find("in_") == 0) {
            addInputPin(std::atoi(component.first.substr(3).c_str()));
        }
        else if (component.first.find("out_") == 0) {
            addOutputPin(std::atoi(component.first.substr(4).c_str()));
        }
    }
}
void Board::simulate() { _circuit->simulate(); }

Tristate Board::compute(std::size_t pinIndex) {
    if (getPin(pinIndex).getType() == OUTPUT) {
        for (auto& it : _pins) {
            Pin& pin = *it.second;
            if (pin.getType() == INPUT) {
                _circuit->setInput("in_" + std::to_string(pin.getPin()),
                                   pin.compute());
            }
        }
        return _circuit->getOutput("out_" + std::to_string(pinIndex));
    }
    else {
        Pin& pin = getPin(pinIndex);
        Tristate state = pin.compute();
        _circuit->setInput("in_" + std::to_string(pinIndex), state);
        return state;
    }
}  // namespace nts

}  // namespace nts
