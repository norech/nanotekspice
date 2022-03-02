#pragma once

#include "../Tristate.hpp"

namespace nts {

Tristate andGate(const Tristate a, const Tristate b);

Tristate xorGate(const Tristate a, const Tristate b);

Tristate orGate(const Tristate a, const Tristate b);

Tristate notGate(const Tristate a);

}  // namespace nts
