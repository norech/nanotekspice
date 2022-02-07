namespace nts {
Trigate andGate(const Trigate a, const Trigate b)
{
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    return a && b;
}

Trigate nandGate(const Trigate a, const Trigate b)
{
    const Trigate res = and(a, b);
    return res == UNDEFINED ? res : !res;
}

Trigate xorGate(const Trigate a, const Trigate b)
{
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    return a ^ b;
}

Trigate orGate(const Trigate a, const Trigate b)
{
    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    return a | b;
}

}
