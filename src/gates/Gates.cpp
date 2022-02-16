#include "Gates.hpp"

namespace nts {
Tristate andGate(const Tristate a, const Tristate b) {
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    else if (a == TRUE && b == TRUE)
        return TRUE;
    else
        return FALSE;
}

Tristate nandGate(const Tristate a, const Tristate b) {
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    else if (a == TRUE && b == TRUE)
        return FALSE;
    else
        return TRUE;
}

Tristate xorGate(const Tristate a, const Tristate b) {
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    else if (a == TRUE && b == FALSE)
        return TRUE;
    else if (a == FALSE && b == TRUE)
        return TRUE;
    else
        return FALSE;
}

Tristate orGate(const Tristate a, const Tristate b) {
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    else if (a == TRUE || b == TRUE)
        return TRUE;
    else
        return FALSE;
}

}  // namespace nts
