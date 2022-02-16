#pragma once

#include <vector>
#include <memory>

#include "../components/Component.hpp"

namespace nts {

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
