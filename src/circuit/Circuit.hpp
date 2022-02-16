#pragma once

#include <vector>
#include <memory>

#include "../components/IComponent.hpp"

namespace nts {

class Component;

class Circuit {
public:
    static Circuit* circuit;

private:
    std::vector<std::unique_ptr<Component>> _components;

public:
    Circuit(void);
    ~Circuit(void) = default;

    static Circuit* getInstance(void);

    static Component* addComponent(const std::string& type, const std::string& name);

    static Component* getFromName(const std::string& name);
};
}  // namespace nts
