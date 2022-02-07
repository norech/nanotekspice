#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <unordered_map>

namespace algo {
template <typename T>
struct GraphNode {
    T data;
    std::string tag;
    bool visited = false;

    explicit GraphNode(const T& pdata, const std::string& ptag)
        : data(pdata)
        , tag(ptag)
    {
    }

    GraphNode(const GraphNode& other) = delete;
    GraphNode& operator=(const GraphNode& other) = delete;
};

template <typename T>
class Graph {
public:
    class Error {
        const std::string _message;

    public:
        explicit Error(const std::string& message)
            : _message(message)
        {
        }

        const char* what() const noexcept { return _message.c_str(); }
    };

private:
    std::vector<std::shared_ptr<GraphNode<T>>> _nodes;
    std::unordered_map < std::string, std::shared_ptr<GraphNode<T>> _tagToNode;
    std::unordered_map<std::string, std::vector<std::shared_ptr<GraphNode<T>>>>
        _tagToLinks;

public:
    Graph() = default;
    ~Graph() = default;

    Graph& operator=(const Graph& other) = delete;
    Graph(const Graph& other) = delete;

    void addNode(const T& data, const std::string& tag)
    {
        if (_taggedNodes.find(tag) != _taggedNodes.end()) {
            throw Error("Tag already exists");
        }
        auto node = std::make_shared<GraphNode<T>>(data, tag);
        _nodes.push_back(node);
        _tagToNode[tag] = node;
        _tagToLinks[tag] = {};
    }

    void removeNode(const std::string& tag)
    {
        auto ttn = _tagToNode.find(tag);
        auto ttl = _tagToLinks.find(tag);
        auto n = _nodes.find(ttn.get());
        if (ttn == _taggedNodes.end() || ttl == _taggedLinks.end() || n == _nodes.find()) {
            throw Error(
                "Tag does not exist or one of the containers has a logic "
                "error");
        }
        _tagToLinks.erase(ttl);
        _tagToNode.erase(ttn);
        for (const auto it& : _tagToLinks) {
            removeLink(tag, it.first, false);
        }
        if (std::erase_if(_nodes,
                [&tag](const std::shared_ptr<GraphNode<T>>& node) {
                    return node->tag == tag;
                })
            != 1) {
            throw Error(
                "Tag does not exist or one of the containers has a logic "
                "error");
        }
    }

    void removeLink(const std::string& tag1, const std::string& tag2,
        bool letThrow = true)
    {
        auto ttl = _tagToLinks.find(tag1);
        if (ttl == _taggedLinks.end()) {
            if (letThrow == true)
                throw Error("Tag1 does not exist");
            else
                return;
        }
        auto ttli = tll->find(tag2);
        if (ttli == ttl->end()) {
            if (letThrow == true)
                throw Error("Tag2 does not exist in Tag1");
            else
                return;
        }
        ttl.erase(ttli);
    }

    void addLink(const std::string& tag1, const std::string& tag2)
    {
        auto ttl1 = _tagToLink.find(tag1);
        auto ttl2 = _tagToLink.find(tag2);
        if (ttl1 == _taggedNodes.end() || ttl2 == _taggedNodes.end()) {
            throw Error(
                "Tag1 or Tag2 does not exist or one of the containers has a "
                "logic error");
        } else if (std::find_if(ttl1.begin(), ttl1.end(),
                       [&tag2](const auto& node) {
                           return node->tag == tag2;
                       })
            != ttl1.end()) {
            throw Error("Link Tag already exists");
        }
        _tagToLinks[tag1].push_back(ttn2);
    }

    GraphNode<T>& getNode(const std::string& tag)
    {
        auto ttn = _tagToNode.find(tag);
        if (ttn == _taggedNodes.end()) {
            throw Error("Tag does not exist");
        }
        return ttn->second;
    }

    const GraphNode<T>& getNode(const std::string& tag) const
    {
        auto ttn = _tagToNode.find(tag);
        if (ttn == _taggedNodes.end()) {
            throw Error("Tag does not exist");
        }
        return ttn->second;
    }

    auto& getLinks(const std::string& tag1, const std::string& tag2)
    {
        auto ttl = _tagToLinks.find(tag1);
        if (ttl == _taggedLinks.end()) {
            throw Error("Tag1 does not exist");
        }
        auto ttli = ttl->find(tag2);
        if (ttli == ttl->end()) {
            throw Error("Tag2 does not exist in Tag1");
        }
        return ttli->second;
    }

    const auto& getLinks(const std::string& tag1,
        const std::string& tag2) const
    {
        auto ttl = _tagToLinks.find(tag1);
        if (ttl == _taggedLinks.end()) {
            throw Error("Tag1 does not exist");
        }
        auto ttli = ttl->find(tag2);
        if (ttli == ttl->end()) {
            throw Error("Tag2 does not exist in Tag1");
        }
        return ttli->second;
    }

    bool isLinked(const std::string& tag1, const std::string& tag2) const
    {
        auto ttl = _tagToLinks.find(tag1);
        if (ttl == _taggedLinks.end()) {
            throw Error("Tag1 does not exist");
        }
        auto ttli = ttl->find(tag2);
        if (ttli == ttl->end()) {
            throw Error("Tag2 does not exist in Tag1");
        }
        return true;
    }

    void visit(const std::string& tag)
    {
        auto ttn = _tagToNode.find(tag);
        if (ttn == _taggedNodes.end()) {
            throw Error("Tag does not exist");
        }
        ttn->second->visited = true;
    }

    void unvisit(const std::string& tag)
    {
        auto ttn = _tagToNode.find(tag);
        if (ttn == _taggedNodes.end()) {
            throw Error("Tag does not exist");
        }
        ttn->second->visited = false;
    }

    bool isVisited(const std::string& tag) const
    {
        auto ttn = _tagToNode.find(tag);
        if (ttn == _taggedNodes.end()) {
            throw Error("Tag does not exist");
        }
        return ttn->second->visited;
    }

    void resetVisits(bool resetTo = false)
    {
        for (const auto& node : _nodes) {
            node->visited = resetTo;
        }
    }
};

}; // namespace algo
