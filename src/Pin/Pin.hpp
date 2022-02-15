#pragma once

#include <memory>
#include <functional>

#include "../components/IComponent.hpp"

namespace nts
{
    class Pin
    {
    public:
        using Link = std::pair<std::shared_ptr<IComponent>, std::size_t>;

    protected:
        std::shared_ptr<IComponent> _component;
        std::size_t _pin;
        std::vector<Link> _links;

    public:
        Pin(std::shared_ptr<IComponent> &component, std::size_t pin);
        virtual ~Pin() = default;

        Pin(const Pin &) = delete;

        virtual void setLink(const std::shared_ptr<IComponent> &other, std::size_t otherPin) = 0;
        virtual Tristate compute() = 0;

        bool otherIsSelf(const std::shared_ptr<IComponent> &other) const;
        bool isLinkedTo(const std::shared_ptr<IComponent> &other, std::size_t pin) const;
    };

    class InputPin : public Pin
    {
    public:
        void setLink(const std::shared_ptr<IComponent> &other, std::size_t otherPin) override;
    };

    class OutputPin : public Pin
    {
    public:
        void setLink(const std::shared_ptr<IComponent> &other, std::size_t otherPin) override;
    };
}
