#include <iostream>

#include "cave_system.hpp"

using namespace advent_of_code::day_12;

auto main(void) -> int {
    CaveSystem cave_system = CaveSystem::load("input.txt");
    auto path_count = cave_system.count_paths();
    
    std::cout << "There are " << path_count << " paths in this cave system that visit a single small cave at most twice!" << std::endl;

    return 0;
}
