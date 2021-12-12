#include <iostream>

#include "cave_system.hpp"

using namespace advent_of_code::day_12;

auto main(void) -> int {
    CaveSystem cave_system = CaveSystem::load("input.txt");
    auto paths = cave_system.find_paths(true);
    
    //for (auto& path : paths) std::cout << path;

    std::cout << "There are " << paths.size() << " paths in this cave system that visit small caves at most once!" << std::endl;

    return 0;
}
