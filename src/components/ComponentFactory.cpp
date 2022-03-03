#include "ComponentFactory.hpp"

#include "../circuit/Circuit.hpp"
#include "../components/Board.hpp"

namespace nts {

Board *ComponentFactory::do4071() {
    Circuit *circuit = new Circuit("4071");

    circuit->addComponent("input", "in_1", "or1_a");
    circuit->addComponent("input", "in_2", "or1_b");
    circuit->addComponent("output", "out_3", "or1_s");

    circuit->addComponent("output", "out_4", "or2_a");
    circuit->addComponent("input", "in_5", "or2_b");
    circuit->addComponent("input", "in_6", "or2_s");

    circuit->addComponent("input", "in_8", "or3_a");
    circuit->addComponent("input", "in_9", "or3_b");
    circuit->addComponent("output", "out_10", "or3_s");

    circuit->addComponent("output", "out_11", "or4_a");
    circuit->addComponent("input", "in_12", "or4_b");
    circuit->addComponent("input", "in_13", "or4_s");

    circuit->addComponent("_or", "or1");
    circuit->addComponent("_or", "or2");
    circuit->addComponent("_or", "or3");
    circuit->addComponent("_or", "or4");

    circuit->setLink("or1_a", 1, "or1", 1);
    circuit->setLink("or1_b", 1, "or1", 2);
    circuit->setLink("or1_s", 1, "or1", 3);

    circuit->setLink("or2_a", 1, "or2", 1);
    circuit->setLink("or2_b", 1, "or2", 2);
    circuit->setLink("or2_s", 1, "or2", 3);

    circuit->setLink("or3_a", 1, "or3", 1);
    circuit->setLink("or3_b", 1, "or3", 2);
    circuit->setLink("or3_s", 1, "or3", 3);

    circuit->setLink("or4_a", 1, "or4", 1);
    circuit->setLink("or4_b", 1, "or4", 2);
    circuit->setLink("or4_s", 1, "or4", 3);

    return new Board(circuit);
}

Board *ComponentFactory::do4069() {
    Circuit *circuit = new Circuit("4069");

    circuit->addComponent("input", "in_1", "not1_i");
    circuit->addComponent("output", "out_2", "not1_o");

    circuit->addComponent("input", "in_3", "not2_i");
    circuit->addComponent("output", "out_4", "not2_o");

    circuit->addComponent("input", "in_5", "not3_i");
    circuit->addComponent("output", "out_6", "not3_o");

    circuit->addComponent("input", "in_9", "not4_i");
    circuit->addComponent("output", "out_8", "not4_o");

    circuit->addComponent("input", "in_11", "not5_i");
    circuit->addComponent("output", "out_10", "not5_o");

    circuit->addComponent("input", "in_13", "not6_i");
    circuit->addComponent("output", "out_12", "not6_o");

    circuit->addComponent("_not", "not1");
    circuit->addComponent("_not", "not2");
    circuit->addComponent("_not", "not3");
    circuit->addComponent("_not", "not4");
    circuit->addComponent("_not", "not5");
    circuit->addComponent("_not", "not6");

    circuit->setLink("not1_i", 1, "not1", 1);
    circuit->setLink("not1_o", 1, "not1", 2);

    circuit->setLink("not2_i", 1, "not2", 1);
    circuit->setLink("not2_o", 1, "not2", 2);

    circuit->setLink("not3_i", 1, "not3", 1);
    circuit->setLink("not3_o", 1, "not3", 2);

    circuit->setLink("not4_i", 1, "not4", 1);
    circuit->setLink("not4_o", 1, "not4", 2);

    circuit->setLink("not5_i", 1, "not5", 1);
    circuit->setLink("not5_o", 1, "not5", 2);

    circuit->setLink("not6_i", 1, "not6", 1);
    circuit->setLink("not6_o", 1, "not6", 2);

    return new Board(circuit);
}

}  // namespace nts
