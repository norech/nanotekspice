#include "Components.hpp"

#include <fstream>
#include <iostream>

namespace nts {
Component4001::Component4001(const std::string& name)
    : GenericComponent7In5OutInternal(name) {}

Component4011::Component4011(const std::string& name)
    : GenericComponent7In5OutInternal(name) {}

Component4030::Component4030(const std::string& name)
    : GenericComponent7In5OutInternal(name) {}

Component4071::Component4071(const std::string& name)
    : GenericComponent7In5OutInternal(name) {}

Component4081::Component4081(const std::string& name)
    : GenericComponent7In5OutInternal(name) {}

HalfAdder::HalfAdder(const std::string& name) : Component(name) {
    addInputPin(1).addInputPin(2).addOutputPin(3).addOutputPin(4);

    this->setLink(3, *_s, 3);
    this->setLink(4, *_c, 3);
    _c->setLink(1, *this, 1);
    _c->setLink(2, *this, 2);
    _s->setLink(1, *this, 1);
    _s->setLink(2, *this, 2);
}

Logger::Logger(const std::string& name) : Component(name) {
    addInputPin(1)
        .addInputPin(2)
        .addInputPin(3)
        .addInputPin(4)
        .addInputPin(5)
        .addInputPin(6)
        .addInputPin(7)
        .addInputPin(8)
        .addInputPin(9)
        .addInputPin(10);
}

void Logger::simulate() {
    Component::simulate();

    if (this->compute(10) != FALSE)  // inhibit pin
        return;
    if (this->compute(9) != FALSE)  // clock pin
        return;

    Tristate state;
    char value = 0;
    bool unknown = false;
    for (int i = 8; i >= 0; i--) {
        state = this->compute(i + 1);
        if (state == UNDEFINED) {
            unknown = true;
            state = FALSE;
        }
        value = (value << 1) + state;
    }
    std::ofstream logfile("./log.bin", std::ios_base::app);
    if (logfile.bad()) {
        std::cerr << "Error: cannot open log file" << std::endl;
        return;
    }
    if (unknown) {
        std::cerr << "Warning: unknown value" << std::endl;
    }
    logfile.write(&value, 1);
    logfile.close();
}

FullAdder::FullAdder(const std::string& name) : Component(name) {
    addInputPin(1).addInputPin(2).addInputPin(3);
    addOutputPin(4).addOutputPin(5);

    this->setLink(5, *_cresult, 3);
    this->setLink(4, *_hadders[1], 3);

    _cresult->setLink(1, *_hadders[0], 4);
    _cresult->setLink(2, *_hadders[1], 4);

    _hadders[1]->setLink(1, *_hadders[0], 3);
    _hadders[1]->setLink(2, *this, 3);

    _hadders[0]->setLink(1, *this, 1);
    _hadders[0]->setLink(2, *this, 2);
}

Component4008::Component4008(const std::string& name) : Component(name) {
    const std::vector<std::size_t> inPins = {15, 1, 2, 3, 4, 5, 6, 7, 9};
    const std::vector<std::size_t> outPins = {14, 13, 12, 11, 10};

    for (int i = 0; i < inPins.size(); i++) addInputPin(inPins[i]);
    for (int i = 0; i < outPins.size(); i++) addOutputPin(outPins[i]);

    // set all inputs (not carry)
    const std::vector<std::pair<std::size_t, std::size_t>> inputs = {
        {15, 1}, {2, 3}, {4, 5}, {6, 7}};
    for (int i = 0; i < inputs.size(); i++) {
        _adders[_adders.size() - 1 - i]->setLink(1, *this, inputs[i].first);
        _adders[_adders.size() - 1 - i]->setLink(2, *this, inputs[i].second);
    }
    const std::vector<std::size_t> outputs = {13, 12, 11, 10};
    for (int i = 0; i < outputs.size(); i++) {
        this->setLink(outputs[i], *_adders[_adders.size() - i - 1], 4);
    }

    // set Last carry out
    this->setLink(14, *_adders[_adders.size() - 1], 5);
    // set First carry in
    _adders[0]->setLink(3, *this, 9);
    // set all carrys in adders
    for (int i = 0; i < _adders.size() - 1; i++) {
        _adders[_adders.size() - 1 - i]->setLink(
            3, *_adders[_adders.size() - 2 - i], 5);
    }
}

DFlipFlopWithSetAndReset::DFlipFlopWithSetAndReset(const std::string& name)
    : Component(name) {
    addInputPin(1).addInputPin(2).addInputPin(3).addInputPin(4);
    addOutputPin(5).addOutputPin(6);

    this->setLink(5, *_q, 3);
    this->setLink(6, *_nq, 3);

    _q->setLink(1, *this, 1);
    _q->setLink(2, *_ins[1], 3);
    _q->setLink(2, *_nq, 3);

    _nq->setLink(1, *_q, 3);
    _nq->setLink(1, *_ins[2], 3);
    _nq->setLink(2, *this, 2);

    _ins[0]->setLink(1, *this, 1);
    _ins[0]->setLink(2, *_ins[3], 3);
    _ins[0]->setLink(2, *_ins[2], 1);

    _ins[1]->setLink(1, *_ins[0], 3);
    _ins[1]->setLink(2, *this, 2);
    _ins[1]->setLink(2, *this, 3);

    _ins[2]->setLink(1, *_ins[0], 2);
    _ins[2]->setLink(2, *this, 3);
    _ins[2]->setLink(1, *_ins[3], 3);

    _ins[3]->setLink(1, *_ins[2], 3);
    _ins[3]->setLink(2, *this, 2);
    _ins[3]->setLink(2, *this, 4);
}

Component4013::Component4013(const std::string& name) : Component(name) {
    addInputPin(3)
        .addInputPin(5)
        .addInputPin(6)
        .addInputPin(4)
        .addInputPin(9)
        .addInputPin(8)
        .addInputPin(10)
        .addInputPin(11)
        .addOutputPin(1)
        .addOutputPin(2)
        .addOutputPin(13)
        .addOutputPin(12);

    // Set outs
    this->setLink(1, *_latches[0], 5);
    this->setLink(2, *_latches[0], 6);
    this->setLink(13, *_latches[1], 5);
    this->setLink(12, *_latches[1], 6);

    // Set clocks
    _latches[0]->setLink(3, *this, 3);
    _latches[0]->setLink(3, *this, 11);

    // Set Datas
    _latches[0]->setLink(4, *this, 5);
    _latches[1]->setLink(4, *this, 9);

    // Set sets
    _latches[0]->setLink(1, *this, 6);
    _latches[1]->setLink(1, *this, 8);

    // Set resets
    _latches[0]->setLink(2, *this, 4);
    _latches[1]->setLink(2, *this, 10);
}

}  // namespace nts
