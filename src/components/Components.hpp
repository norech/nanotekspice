#pragma once

#include "GatesComponent.hpp"
#include <vector>

namespace nts {

/*
class HalfAdder : public Component {
private:
    std::unique_ptr<Xor> _output = std::make_unique<Xor>();
    std::unique_ptr<And> _carry = std::make_unique<And>();

public:
    HalfAdder(const std::string& name="HalfAdder") : Component(name) {
        addInputPin(1).addInputPin(2).addOutputPin(3).addOutputPin(4);
        setLink(1, *_output, 1);
        setLink(1, *_output, 2);
        setLink(1, *_carry, 1);
        setLink(2, *_carry, 2);
        _output->setLink(3, *this, 3);
        _output->setLink(4, *this, 4);
    }

    Tristate getCarry() { return compute(4); }
};

class FullAdder : public Component {
private:
    std::unique_ptr<Xor> _xorResult = std::make_unique<Xor>();
    std::unique_ptr<Or> _orResult = std::make_unique<Or>();

    std::unique_ptr<And> _linker1 = std::make_unique<And>();
    std::unique_ptr<And> _linker2 = std::make_unique<And>();
    std::unique_ptr<Xor> _inputLinker = std::make_unique<Xor>();

public:
    FullAdder(const std::string& name="FullAdder") : Component(name) {
        addInputPin(1).addInputPin(2).addInputPin(3).addOutputPin(4).addOutputPin(5);

        _inputLinker->setLink(1, *this, 1);
        _inputLinker->setLink(2, *this, 2);
        _inputLinker->setLink(3, *_xorResult, 1);
        _inputLinker->setLink(3, *_linker1, 1);

        _xorResult->setLink(1, *_inputLinker, 3);
        _xorResult->setLink(2, *this, 3);
        _xorResult->setLink(3, *this, 4);

        _linker1->setLink(1, *_inputLinker, 3);
        _linker1->setLink(2, *this, 3);
        _linker1->setLink(3, *_orResult, 1);

        _linker2->setLink(1, *this, 1);
        _linker2->setLink(2, *this, 2);
        _linker2->setLink(3, *_orResult, 2);

        _orResult->setLink(1, *_linker1, 3);
        _orResult->setLink(2, *_linker2, 3);
        _orResult->setLink(3, *this, 5);
    }
};

class FourBitsAdder : public Component {
private:
    // pin1 == in1
    // pin2 == in2
    // pin3 == carryin
    // pin4 == out
    // pin5 == carryout
    std::vector<std::unique_ptr<FullAdder>> _adders;

public:
    FourBitsAdder(const std::string& name="Adder") : Component(name) {
        // Setup full adders
        for (int i = 0; i < 4; i++)
            _adders.push_back(new FullAdder);

        // Setup pins
        for (int i = 1; i <= 9; i++) addInputPin(i);
        addInputPin(15);
        for (int i = 10; i <= 14; i++) addOutputPin(i);

        // First carry in
        setLink(9, *_adders[0], 3);
        // Last carry out
        _adders[_adders.size() - 1]->setLink(5, *this, 14);

        // each remaining Carry in/out
        for (int i = 0; i < _adders.size() - 2; i++)
            _adders[i]->setLink(5, *_adders[i + 1], 3);

        // in1, in2, out
        std::vector<std::vector<std::size_t>> links = {
            {7, 6, 10}, {5, 4, 11}, {3, 2, 12}, {1, 15, 13}
        };

        for (int i = 0; i < links.size(); i++) {
            this->setLink(links[i][0], *_adders[i], 1);
            this->setLink(links[i][1], *_adders[i], 2);
            this->setLink(links[i][2], *_adders[i], 4);
        }
    }
};

class FlipFlop : public Component {
private:
    std::unique_ptr<And> _r = std::make_unique<And>();
    std::unique_ptr<And> _s = std::make_unique<And>();
    std::unique_ptr<XNor> _qa = std::make_unique<XNor>();
    std::unique_ptr<XNor> _qb = std::make_unique<XNor>();

public:
    FlipFlop(const std::string& name="FlipFlop") : Component(name) {
        addInputPin(1).addInputPin(2).addInputPin(3)
            .addOutputPin(4).addOutputPin(5);
        this->setLink(1, *_r, 1);
        this->setLink(2, *_r, 2);
        this->setLink(2, *_s, 1);
        this->setLink(3, *_s, 2);
        _r->setLink(3, *_qa, 1);
        _s->setLink(3, *_qb, 2);
        _qa->setLink(2, *_qb, 3);
        _qb->setLink(3, *_qa, 2);
        _qa->setLink(3, *_qb, 1);
    }
};

*/

class Component4001 : public Component {
private:
    std::array<std::unique_ptr<Nor>, 4> _nors;

public:
    Component4001(const std::string& name="4001");
};

class Component4081 : public Component {
private:
    std::array<std::unique_ptr<And>, 4> _and;

public:
    Component4081(const std::string& name="4081");
};

}  // namespace nts
