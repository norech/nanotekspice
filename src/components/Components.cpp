#include "Components.hpp"

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

// FullAdder logic
// 1: in1
// 2: in2
// 3: cin
// 4: sum
// 5: cout
Component4008::Component4008(const std::string& name) : Component(name) {
    const std::vector<std::size_t> inPins = {15, 1, 2, 3, 4, 5, 6, 7, 9};
    const std::vector<std::size_t> outPins = {14, 13, 12, 11, 10};

    for (int i = 0; i < inPins.size(); i++) addInputPin(inPins[i]);
    for (int i = 0; i < outPins.size(); i++) addOutputPin(outPins[i]);

    // set all inputs (not carry)
    const std::vector<std::pair<std::size_t, std::size_t>> inputs = { 
        {15, 1}, {2, 3}, {4, 5}, {6, 7}
    };
    for (int i = 0; i < inputs.size(); i++) {
        _adders[_adders.size() - 1 - i]->setLink(1, *this, inputs[i].first);
        _adders[_adders.size() - 1 - i]->setLink(2, *this, inputs[i].second);
    }
    const std::vector<std::size_t> outputs = {
        13, 12, 11, 10
    };
    for (int i = 0; i < outputs.size(); i++) {
        this->setLink(outputs[i], *_adders[_adders.size() - i - 1], 3);
    }

    // set Last carry out
    this->setLink(14, *_adders[_adders.size() - 1], 5);
    // set First carry in
    _adders[0]->setLink(3, *this, 9);
    // set all carrys in adders
    for (int i = 0; i < _adders.size() - 1; i++) {
        _adders[_adders.size() - 1 - i]->setLink(3, *_adders[_adders.size() - 2 - i], 5);
    }
}

}  // namespace nts
