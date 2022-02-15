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
    const Tristate res = andGate(a, b);
    if (res == TRUE)
        return FALSE;
    else if (res == FALSE)
        return TRUE;
    else
        return UNDEFINED;
}

Tristate xorGate(const Tristate a, const Tristate b) {
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    else if (a == TRUE && b == FALSE)
        return TRUE;
    else if (a == FALSE && b == TRUE)
        return TRUE;
    else if (a == TRUE && b == TRUE)
        return FALSE;
    else
        return FALSE;
}

Tristate orGate(const Tristate a, const Tristate b) {
    if (a == UNDEFINED || b == UNDEFINED) return UNDEFINED;
    if (a == TRUE || b == TRUE)
        return TRUE;
    else
        return FALSE;
}

}  // namespace nts
