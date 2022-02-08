#pragma once

#include "./IComponent.hpp"

namespace nts {

    class Component : public IComponent {
        private:
            std::vector<std::size_t> _inputs;
            std::vector<std::size_t> _outputs;

        protected:
            Component(const std::vector<std::size_t>& inputs, const std::vector<std::size_t>& outputs) const
                : _inputs(inputs), _outputs(outputs)
                {

                }

        public:
            bool isInput(std::size_t pin) const
            {
                return _inputs.find(pin) != _inputs.end();
            }

            bool isOutput(std::size_t pin) const
            {
                return _outputs.find(pin) != _outputs.end();
            }

            void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) final
            {
                Component& otherDynC = dynamic_cast<Component&>(other);

                if (this->isInput(pin) == otherDynC->isInput(otherPin)) {
                    throw Error("Both are Input or Output");
                }
            }
    };
}

