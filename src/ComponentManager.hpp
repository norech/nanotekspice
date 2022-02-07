#pragma once

#include <memory>
#include <string>

#include "./components/IComponent.hpp"

namespace nts {

class ComponentManager {
    class Error : public std::exception {
    public:
        Error(const std::string& msg)
            : _msg(msg)
        {
        }
        virtual ~Error() = default;
        virtual const char* what() const noexcept { return _msg.c_str(); }

    private:
        std::string _msg;
    };

public:
    ComponentManager();
    ~ComponentManager();
    ComponentManager(const ComponentManager& other) = default;
    ComponentManager& operator=(const ComponentManager& other) = default;

    std::unique_ptr<IComponent> createComponent(const std::string& type);

private:
    std::unique_ptr<IComponent> create4001() const;
    std::unique_ptr<IComponent> create4013() const;
    std::unique_ptr<IComponent> create4040() const;
};

} // namespace nts
