#ifndef ADVENT_OF_CODE__CAVE_PATH
#define ADVENT_OF_CODE__CAVE_PATH

#include <iostream>

#include <vector>

#include "cave_node.hpp"

namespace advent_of_code {

inline namespace day_12 {

class CavePath {

    friend auto operator<<(std::ostream&, const CavePath&) -> std::ostream&;

    using Container = std::vector<const CaveNode*>;

public:

    CavePath(void);

    auto length(void) const noexcept -> decltype(Container().size());

    auto visited(const CaveNode& node) const noexcept -> bool;
    auto add_node(const CaveNode& node) -> void;

private:

    Container nodes;

};

inline CavePath::CavePath(void) {
    this->nodes.reserve(13);
}

inline auto CavePath::length(void) const noexcept -> decltype(Container().size()) {
    return this->nodes.size();
}

inline auto CavePath::visited(const CaveNode& node) const noexcept -> bool {
    for (const auto& other_node : this->nodes)
        if (node.get_id() == other_node->get_id()) return true;

    return false;
}

inline auto CavePath::add_node(const CaveNode& node) -> void {
    this->nodes.push_back(&node);
}

inline auto operator<<(std::ostream& out, const CavePath& path) -> std::ostream& {
    if (path.length() == 0) return out;

    auto node_it = path.nodes.cbegin();
    out << (*node_it)->get_id();

    for (node_it++; node_it != path.nodes.cend(); node_it++) {
        out << ',' << (*node_it)->get_id();
    }
    
    out << '\n';

    return out;
}

}

}

#endif
