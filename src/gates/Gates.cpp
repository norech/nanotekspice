#include "Gates.hpp"

namespace nts {
Tristate andGate(const Tristate a, const Tristate b) {
    if (a == FALSE || b == FALSE)
        return FALSE;
    else if (a == TRUE && b == TRUE)
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
    else
        return FALSE;
}

Tristate orGate(const Tristate a, const Tristate b) {
    if (a == TRUE || b == TRUE)
        return TRUE;
    else if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    else
        return FALSE;
}

Tristate notGate(const Tristate a) {
    if (a == UNDEFINED)
        return UNDEFINED;
    else if (a == TRUE)
        return FALSE;
    else
        return TRUE;
}

}  // namespace nts
