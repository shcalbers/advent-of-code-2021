#ifndef ADVENT_OF_CODE__CAVE_NODE
#define ADVENT_OF_CODE__CAVE_NODE

#include <cctype>

#include <map>
#include <string>

namespace advent_of_code {

inline namespace day_12 {

class CaveNode {

public:

    CaveNode(void) noexcept = default;
    CaveNode(std::string id) noexcept;

    static auto connect(CaveNode& node_a, CaveNode& node_b) -> void; 

    auto get_id(void) const noexcept -> const std::string&;
    auto is_small(void) const noexcept -> bool;

    auto get_connected_nodes(void) const noexcept -> const std::map<std::string, CaveNode*>&;

    ~CaveNode(void) noexcept;

private:

    std::string id;
    bool small;

    std::map<std::string, CaveNode*> connected_nodes;

};

inline CaveNode::CaveNode(std::string id) noexcept {
    this->id = id;
    this->small = islower(id[0]);
}

inline auto CaveNode::connect(CaveNode& node_a, CaveNode& node_b) -> void {
    node_a.connected_nodes.emplace(node_b.get_id(), &node_b);
    node_b.connected_nodes.emplace(node_a.get_id(), &node_a);
}

inline auto CaveNode::get_id(void) const noexcept -> const std::string& {
    return this->id;
}

inline auto CaveNode::is_small(void) const noexcept -> bool {
    return this->small;
}

inline auto CaveNode::get_connected_nodes(void) const noexcept -> const std::map<std::string, CaveNode*>& {
    return this->connected_nodes;
}

inline CaveNode::~CaveNode(void) noexcept {
    for (auto& [id, connected_node] : connected_nodes)
        connected_node->connected_nodes.erase(this->id);
}

}

}

#endif
