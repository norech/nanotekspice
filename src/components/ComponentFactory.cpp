#include "ComponentFactory.hpp"

#include "../circuit/Circuit.hpp"
#include "../components/Board.hpp"

namespace nts {

Board *ComponentFactory::do4071() {
    Circuit *circuit = new Circuit("4071");

    circuit->addComponent("input", "in_1");
    circuit->addComponent("input", "in_2");
    circuit->addComponent("output", "out_3");

    circuit->addComponent("output", "out_4");
    circuit->addComponent("input", "in_5");
    circuit->addComponent("input", "in_6");

    circuit->addComponent("input", "in_8");
    circuit->addComponent("input", "in_9");
    circuit->addComponent("output", "out_10");

    circuit->addComponent("output", "out_11");
    circuit->addComponent("input", "in_12");
    circuit->addComponent("input", "in_13");

    circuit->addComponent("_or", "or1");
    circuit->addComponent("_or", "or2");
    circuit->addComponent("_or", "or3");
    circuit->addComponent("_or", "or4");

    circuit->setLink("in_1", 1, "or1", 1);
    circuit->setLink("in_2", 1, "or1", 2);
    circuit->setLink("out_3", 1, "or1", 3);

    circuit->setLink("in_5", 1, "or2", 1);
    circuit->setLink("in_6", 1, "or2", 2);
    circuit->setLink("out_4", 1, "or2", 3);

    circuit->setLink("in_8", 1, "or3", 1);
    circuit->setLink("in_9", 1, "or3", 2);
    circuit->setLink("out_10", 1, "or3", 3);

    circuit->setLink("in_13", 1, "or4", 1);
    circuit->setLink("in_12", 1, "or4", 2);
    circuit->setLink("out_11", 1, "or4", 3);

    return new Board(circuit);
}

}  // namespace nts
