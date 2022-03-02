#pragma once

#include <array>

#include "GatesComponent.hpp"

namespace nts {

// Specific Components

class Logger : public Component {
public:
    Logger(const std::string& name = "Logger");

    void simulate(void) override;
};

class HalfAdder : public Component {
private:
    std::unique_ptr<Xor> _s = std::make_unique<Xor>();
    std::unique_ptr<And> _c = std::make_unique<And>();

public:
    HalfAdder(const std::string& name = "HalfAdder");
};

class FullAdder : public Component {
// FullAdder logic
// 1: in1, 2: in2
// 3: cin, 4: sum
// 5: cout
private:
    std::array<std::unique_ptr<HalfAdder>, 2> _hadders = {
        std::make_unique<HalfAdder>(), std::make_unique<HalfAdder>()};
    std::unique_ptr<Or> _cresult = std::make_unique<Or>();

public:
    FullAdder(const std::string& name = "FullAdder");
};

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
            .addInputPin(6)
            .addInputPin(8)
            .addInputPin(9)
            .addOutputPin(10)
            .addOutputPin(11)
            .addInputPin(12)
            .addInputPin(13);

        // O -> I
        _gates[0]->setLink(1, *this, 1);
        _gates[0]->setLink(2, *this, 2);
        this->setLink(3, *_gates[0], 3);
        this->setLink(4, *_gates[1], 3);
        _gates[1]->setLink(1, *this, 5);
        _gates[1]->setLink(2, *this, 6);
        this->setLink(10, *_gates[2], 3);
        _gates[2]->setLink(1, *this, 8);
        _gates[2]->setLink(2, *this, 9);
        this->setLink(11, *_gates[3], 3);
        _gates[3]->setLink(1, *this, 12);
        _gates[3]->setLink(2, *this, 13);
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

class Component4071 : public GenericComponent7In5OutInternal<Or> {
public:
    Component4071(const std::string& name = "4071");
};

class Component4081 : public GenericComponent7In5OutInternal<And> {
public:
    Component4081(const std::string& name = "4081");
};

class Component4008 : public Component {
private:
    std::array<std::unique_ptr<FullAdder>, 4> _adders = {
        std::make_unique<FullAdder>(), std::make_unique<FullAdder>(),
        std::make_unique<FullAdder>(), std::make_unique<FullAdder>()};

public:
    Component4008(const std::string& name = "4008");
};

class DFlipFlopWithSetAndReset : public Component {
private:
    std::unique_ptr<Nand> _q = std::make_unique<Nand>();
    std::unique_ptr<Nand> _nq = std::make_unique<Nand>();

    std::array<std::unique_ptr<Nand>, 4> _ins = {
        std::make_unique<Nand>(), std::make_unique<Nand>(),
        std::make_unique<Nand>(), std::make_unique<Nand>()
    };

public:
    // Pin1: Set, Pin2: Clock
    // Pin3: Data, Pin4: Reset
    // Pin5: Q, Pin6: ~Q
    DFlipFlopWithSetAndReset(const std::string& name = "DFlipFlopWithSetAndReset");
};

class Component4013 : public Component {
private:
    std::array<std::unique_ptr<DFlipFlopWithSetAndReset>, 2> _latches = {
        std::make_unique<DFlipFlopWithSetAndReset>(),
        std::make_unique<DFlipFlopWithSetAndReset>()
    };
public:
    Component4013(const std::string& name = "Component4013");
};

}  // namespace nts
