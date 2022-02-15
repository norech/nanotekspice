#pragma once

#include "../Tristate.hpp"

namespace nts {

Tristate andGate(const Tristate a, const Tristate b);

Tristate nandGate(const Tristate a, const Tristate b);

Tristate xorGate(const Tristate a, const Tristate b);

Tristate orGate(const Tristate a, const Tristate b);

}  // namespace nts
