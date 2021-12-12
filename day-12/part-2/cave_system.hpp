#ifndef ADVENT_OF_CODE__CAVE_SYSTEM
#define ADVENT_OF_CODE__CAVE_SYSTEM

#include <fstream>

#include <map>
#include <string>
#include <vector>

#include "cave_node.hpp"

namespace advent_of_code {

inline namespace day_12 {

class CaveSystem {

public:

    static auto load(std::string file_name) -> CaveSystem;

    auto count_paths(void) const -> size_t;

private:
    
    std::map<std::string, CaveNode> nodes;

    CaveNode* start;
    CaveNode* end;

    auto count_paths(const CaveNode& current_node, std::map<const CaveNode*, bool> visited, bool can_revisit) const -> size_t;

};

inline auto CaveSystem::load(std::string file_name) -> CaveSystem {
    CaveSystem cave_system;

    {
        auto input = std::ifstream(file_name);

        for (std::string line; std::getline(input, line); ) {
            const auto split = line.find('-');
            if (split == std::string::npos) continue;

            const auto start_id = line.substr(0, split);
            const auto end_id = line.substr(split+1);

            auto [start_it, start_inserted] = cave_system.nodes.emplace(start_id, CaveNode(start_id));
            auto [end_it, end_inserted] = cave_system.nodes.emplace(end_id, CaveNode(end_id));

            CaveNode::connect(start_it->second, end_it->second);
        }
    }

    cave_system.start = &cave_system.nodes["start"];
    cave_system.end = &cave_system.nodes["end"];
    
    return cave_system;
}

inline auto CaveSystem::count_paths(void) const -> size_t {
    std::map<const CaveNode*, bool> visited;
    return this->count_paths(*this->start, visited, true);
}

inline auto CaveSystem::count_paths(const CaveNode& current_node, std::map<const CaveNode*, bool> visited, const bool can_revisit) const -> size_t {
    visited[&current_node] = true;

    auto path_count = size_t(0);
    for (const auto& [id, next_node] : current_node.get_connected_nodes()) {
        auto can_next_revisit = can_revisit;
        if (next_node->is_small() && visited[next_node]) {
            if (next_node == this->start || can_revisit == false) {
                continue;
            } else {
                can_next_revisit = false;
            }
        }
        
        if (next_node == this->end) path_count++;
        else path_count += this->count_paths(*next_node, visited, can_next_revisit);
    }

    return path_count;
}

}

}

#endif
