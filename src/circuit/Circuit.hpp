#pragma once

#include <memory>
#include <map>

#include "../components/Components.hpp"

namespace nts {

class Circuit {
public:
    static std::unique_ptr<Circuit> circuit;

private:
    std::map<std::string, std::unique_ptr<Component>> _components;
    std::size_t _tick;

    std::unordered_map<
        std::string,
        std::function<std::unique_ptr<Component>(const std::string&)>
    > _factory = {}; 

protected:
public:
    Circuit(void);
    ~Circuit(void) = default;

    static Circuit& getInstance(void);

    static void addComponent(const std::string& type,
                                   const std::string& name);

    static Component& getFromName(const std::string& name);
    void setLink(const std::string& leftComponent, std::size_t pinLeft,
        const std::string& rightComponent, std::size_t left);
    
    static bool alreadyHasName(const std::string& name);

    static void unvisit(void);
    static void simulate(void);
    static void dump(void);
    static void display(void);

    std::size_t getTick(void) const;
};

}  // namespace nts
