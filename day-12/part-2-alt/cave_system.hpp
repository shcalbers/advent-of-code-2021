#ifndef ADVENT_OF_CODE__CAVE_SYSTEM
#define ADVENT_OF_CODE__CAVE_SYSTEM

#include <fstream>

#include <map>
#include <string>
#include <vector>

#include "cave_node.hpp"
#include "cave_path.hpp"

namespace advent_of_code {

inline namespace day_12 {

class CaveSystem {

public:

    static auto load(std::string file_name) -> CaveSystem;

    auto find_paths(bool can_revisit) const -> std::vector<CavePath>;

private:
    
    std::map<std::string, CaveNode> nodes;

    CaveNode* start;
    CaveNode* end;

    auto find_paths(const CaveNode& current_node, CavePath current_path, std::vector<CavePath>& paths_out, bool can_revisit) const -> void;

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

inline auto CaveSystem::find_paths(const bool can_revisit) const -> std::vector<CavePath> {
    std::vector<CavePath> paths;
    this->find_paths(*this->start, CavePath(), paths, can_revisit);

    return paths;
}

inline auto CaveSystem::find_paths(const CaveNode& current_node, CavePath current_path, std::vector<CavePath>& paths_out, const bool can_revisit) const -> void {
    current_path.add_node(current_node);
    if (&current_node == this->end) {
        paths_out.push_back(std::move(current_path));
        return;
    }

    for (const auto& [id, next_node] : current_node.get_connected_nodes()) {
        auto can_revisit_next = can_revisit;
        if (next_node->is_small() && current_path.visited(*next_node)) {
            if (next_node == this->start || can_revisit == false) continue;
            else can_revisit_next = false;
        }

        find_paths(*next_node, current_path, paths_out, can_revisit_next);
    }
}

}

}

#endif
