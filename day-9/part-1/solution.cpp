#include <fstream>
#include <iostream>

#include <string>
#include <vector>

auto main(void) noexcept -> int {
    static constexpr auto height_map_size = 100;
    std::vector<std::vector<int>> height_map;
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

    auto total_risk_level = 0;
    for (auto y = 0; y < height_map_size; y++) {
        for (auto x = 0; x < height_map_size; x++) {
            bool is_lowest = true;
            for (auto n = 0; n < 4; n++) {
                // Some unnecessary madness >:D
                const auto x_n = x+(((n+1)&1)*(1+(n/2*-2)));
                const auto y_n = y+(((n+0)&1)*(1+(n/2*-2)));
                const auto d_n = (x_n*((n+1)&1)|y_n*((n+0)&1));
                if (0 <= d_n && d_n < height_map_size) {
                    is_lowest = is_lowest && height_map[y][x] < height_map[y_n][x_n];
                }
            }
            if (is_lowest) total_risk_level += 1+height_map[y][x];
        }
    }

    std::cout << "The total risk level is " << total_risk_level << ". Risky!" << std::endl;

    return 0;
}
