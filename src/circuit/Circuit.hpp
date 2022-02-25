#pragma once

#include <map>
#include <memory>
#include <queue>

#include "../components/Components.hpp"

namespace nts {

#define NTS_COMPONENT_FACTORY(name, type)                                    \
    {                                                                        \
        name, [](const std::string& n) { return std::make_unique<type>(n); } \
    }

class Circuit {
public:
private:
    std::map<std::string, std::unique_ptr<Component>> _components;
    std::size_t _tick = 0;

    std::unordered_map<std::string, std::function<std::unique_ptr<Component>(
                                        const std::string&)>>
        _factory;

protected:
public:
    Circuit(void);
    ~Circuit(void) = default;

    void addComponent(const std::string& type, const std::string& name);

    const std::map<std::string, std::unique_ptr<Component>>& getComponents(
        void) const;

    Component& getFromName(const std::string& name);
    void setLink(const std::string& leftComponent, std::size_t pinLeft,
                 const std::string& rightComponent, std::size_t left);

    bool alreadyHasName(const std::string& name);

    void unvisit(void);
    void simulate(void);
    void dump(void);
    void display(void);

    std::size_t getTick(void);
};

}  // namespace nts
