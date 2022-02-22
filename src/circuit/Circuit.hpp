#pragma once

#include <memory>
#include <vector>

#include "../components/Component.hpp"

namespace nts {

class Circuit {
public:
    static std::unique_ptr<Circuit> circuit;

private:
    std::vector<std::unique_ptr<Component>> _components;
    std::size_t _tick;

protected:
public:
    Circuit(void);
    ~Circuit(void) = default;

    static Circuit& getInstance(void);

    static Component* addComponent(const std::string& type,
                                   const std::string& name);

    static Component* getFromName(const std::string& name);

    static void unvisit(void);
    static void simulate(void);
    static void dump(void);
    static void display(void);

    std::size_t getTick(void) const;
};

}  // namespace nts
