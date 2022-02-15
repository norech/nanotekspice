#pragma once

namespace nts {

enum Tristate { TRUE = true,
    FALSE = false,
    UNDEFINED = (-true) };

enum PinType { INPUT, OUTPUT };

}
