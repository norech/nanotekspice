#pragma once

#include <map>

#include "Chip.hpp"

namespace nts {
class Circuit {
public:
    static Circuit* circuit;

private:
    std::unordered_map<std::shared_ptr<IComponent>, std::unique_ptr<Chip> >
        _chips;

public:
    Circuit(void);
    ~Circuit(void) = default;

    static Circuit* getInstance(void);

    static Chip& addChip(IComponent* component);

    static Chip& getChip(IComponent* component);
};
}  // namespace nts