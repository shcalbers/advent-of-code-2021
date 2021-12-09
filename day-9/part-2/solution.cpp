#include <cassert>

#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include <set>

using HeightMap = std::vector<std::vector<int>>;
using VisitedMap = std::vector<std::vector<bool>>;

static constexpr auto height_map_size = 100;

auto in_range(int x, int y) noexcept -> bool {
    return (0 <= x && x < height_map_size) && (0 <= y && y < height_map_size);
}

auto find_basin_size(int x, int y, const HeightMap& height_map, VisitedMap& visited) noexcept -> int {
    if (!in_range(x, y) || height_map[y][x] == 9 || visited[y][x]) return 0;
    visited[y][x] = true;
    return 1 + find_basin_size(x-1, y+0, height_map, visited)  // Check left...
             + find_basin_size(x+1, y+0, height_map, visited)  // Check right...
             + find_basin_size(x+0, y-1, height_map, visited)  // Check up...
             + find_basin_size(x+0, y+1, height_map, visited); // Check down
}

auto find_basin_sizes(const HeightMap& height_map) noexcept {
    assert(height_map.size() == height_map[0].size() && "Invalid Height Map! Height maps must form a NxN square!");
    
    std::multiset<int, std::greater<int>> basin_sizes;
    VisitedMap visited(height_map_size, std::vector<bool>(height_map_size, false)); 

    for (auto y = 0; y < height_map_size; y++) {
        for (auto x = 0; x < height_map_size; x++) {
            auto basin_size = find_basin_size(x, y, height_map, visited);
            if (basin_size != 0) basin_sizes.insert(basin_size);
        }
    }

    return basin_sizes;
}

auto main(void) noexcept -> int {
    HeightMap height_map;
    height_map.reserve(height_map_size);

    {
        auto input = std::ifstream("input.txt");

        for (std::string line; std::getline(input, line); ) {
            std::vector<int> height_map_row;
            height_map_row.reserve(height_map_size);

            for (char c : line) height_map_row.push_back(c - '0');

            height_map.push_back(std::move(height_map_row));
        }
    }

    const auto basin_sizes = find_basin_sizes(height_map);
    auto result = 1;

    auto it = basin_sizes.cbegin();
    for (auto i = 0; i < 3; i++, std::advance(it, 1)) {
        result *= *it;
    }

    std::cout << "Multiplying the size of the three largest basins gives " << result << " :o" << std::endl;

    return 0;
}
