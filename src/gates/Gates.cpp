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

Tristate addGate(const Tristate a, const Tristate b, Tristate &carry) {
    if (a == UNDEFINED || b == UNDEFINED) {
        carry = UNDEFINED;
        return UNDEFINED;
    }  else if (a == TRUE || b == TRUE) {
        if (a == FALSE || b == FALSE) {
            carry = FALSE;
            return TRUE;
        } else {
            carry = TRUE;
            return TRUE;
        }
    } else {
        carry = FALSE;
        return FALSE;
    }
}

Tristate addGate(const Tristate a, const Tristate b) {
    Tristate tmp;
    return addGate(a, b, tmp);
}

}  // namespace nts
