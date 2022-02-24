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

}  // namespace nts
