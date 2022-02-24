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

Component4069::Component4069(const std::string& name) : Component(name) {
    const std::size_t ins[] = {
        1, 3, 5, 9, 11, 13
    };
    const std::size_t outs[] = {
        2, 4, 6, 8, 10, 12
    };
    for (int i = 0; i < 6; i++) {
        addInputPin(ins[i]);
        addOutputPin(outs[i]);
        this->setLink(ins[i], *_nots[i], 1);
        this->setLink(outs[i], *_nots[i], 2);
    }
}

Component4008::Component4008(const std::string& name) : Component(name) {
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
    std::vector<std::array<std::size_t, 3>> left_links = {
        {7, 6, 10}, {5, 4, 11}, {3, 2, 12}, {1, 15, 13}
    };

    for (int i = 0; i < left_links.size(); i++) {
        this->setLink(left_links[i][0], *_adders[i], 1);
        this->setLink(left_links[i][1], *_adders[i], 2);
        this->setLink(left_links[i][2], *_adders[i], 4);
    }
}

}  // namespace nts
