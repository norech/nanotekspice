#pragma once

#include <array>

#include "GatesComponent.hpp"

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
*/

class Component4008 : public Component {
private:
    // pin1 == in1
    // pin2 == in2
    // pin3 == carryin
    // pin4 == out
    // pin5 == carryout
    std::array<std::unique_ptr<FullAdder>, 4> _adders = {
        std::unique_ptr<FullAdder>(),
        std::unique_ptr<FullAdder>(),
        std::unique_ptr<FullAdder>(),
        std::unique_ptr<FullAdder>()
    };

public:
    Component4008(const std::string& name="4008");
};

/*
class FlipFlop : public Component {
private:
    std::unique_ptr<And> _r = std::make_unique<And>();
    std::unique_ptr<And> _s = std::make_unique<And>();
    std::unique_ptr<Xnor> _qa = std::make_unique<Xnor>();
    std::unique_ptr<Xnor> _qb = std::make_unique<Xnor>();

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

template <typename T>
class GenericComponent7In5OutInternal : public Component {
private:
    std::array<std::unique_ptr<T>, 4> _gates = {
        std::make_unique<T>(), std::make_unique<T>(), std::make_unique<T>(),
        std::make_unique<T>()};

protected:
    GenericComponent7In5OutInternal(const std::string& name) : Component(name) {
        addInputPin(1)
            .addInputPin(2)
            .addOutputPin(3)
            .addOutputPin(4)
            .addInputPin(5)
            .addOutputPin(6)
            .addInputPin(8)
            .addInputPin(9)
            .addOutputPin(10)
            .addOutputPin(11)
            .addInputPin(12)
            .addInputPin(13);

        this->setLink(1, *_gates[0], 1);
        this->setLink(2, *_gates[0], 2);
        this->setLink(3, *_gates[0], 3);

        this->setLink(4, *_gates[1], 3);
        this->setLink(5, *_gates[1], 1);
        this->setLink(6, *_gates[1], 2);

        this->setLink(8, *_gates[2], 2);
        this->setLink(9, *_gates[2], 1);
        this->setLink(10, *_gates[2], 3);

        this->setLink(11, *_gates[3], 3);
        this->setLink(12, *_gates[3], 2);
        this->setLink(13, *_gates[3], 1);
    }
};

class Component4001 : public GenericComponent7In5OutInternal<Nor> {
public:
    Component4001(const std::string& name = "4001");
};

class Component4011 : public GenericComponent7In5OutInternal<Nand> {
public:
    Component4011(const std::string& name = "4011");
};

class Component4030 : public GenericComponent7In5OutInternal<Xor> {
public:
    Component4030(const std::string& name = "4030");
};

class Component4069 : public Component {
private:
    std::array<std::unique_ptr<Not>, 6> _nots = {
        std::make_unique<Not>(), std::make_unique<Not>(),
        std::make_unique<Not>(), std::make_unique<Not>(),
        std::make_unique<Not>(), std::make_unique<Not>()
    };
public:
    Component4069(const std::string& name = "4069");
};

class Component4071 : public GenericComponent7In5OutInternal<Or> {
public:
    Component4071(const std::string& name = "4071");
};

class Component4081 : public GenericComponent7In5OutInternal<And> {
public:
    Component4081(const std::string& name = "4081");
};

}  // namespace nts
