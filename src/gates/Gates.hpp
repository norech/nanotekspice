#pragma once

#include "../Trigate.hpp"

namespace nts {

    Trigate andGate(const Trigate a, const Trigate b);

    Trigate nandGate(const Trigate a, const Trigate b);

    Trigate xorGate(const Trigate a, const Trigate b);

    Trigate orGate(const Trigate a, const Trigate b);

}
