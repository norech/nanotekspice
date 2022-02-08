#pragma once

#include <pair>
#include "Graph.hpp"

namespace nts
{
    class PinManager
    {
    private:
        Graph<TriState> _states;

    public:

        void addPin(const std::string& pinName, TriState state)
        {
            _states.addNode(name, state);
        }

        auto& getLinks(const std::string& pinName)
        {
            return _states.getLinks(pinName);
        }

        const auto& getLinks(const std::string& pinName) const
        {
            return _states.getLinks(pinName);
        }

        TriState getValue(const std::string& pinName) const
        {
            const auto& links = _states.getLinks(pinName);
            TriState found = false;

            for (const auto& it : links) {
                if (it->data == UNDEFINED)
                    return UNDEFINED;
                found |= it->data;
            }
            return found;
        }

    }

    class Circuit
    {
    private:
        std::unordered_map<std::string, Pin>;

    };

};
