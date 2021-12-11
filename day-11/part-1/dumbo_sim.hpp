#ifndef ADVENT_OF_CODE__DUMBO_SIMULATION
#define ADVENT_OF_CODE__DUMBO_SIMULATION

#include <fstream>
#include <iostream>

#include <string>
#include <vector>

#include "dumbo_pus.hpp"

namespace advent_of_code {

inline namespace day_11 {

class DumboSim final {

public:

    static auto load(std::string file_name) -> DumboSim;

    auto run() -> void;

private:
    
    std::vector<std::vector<DumboPus>> dumbopuses;

    DumboSim(std::vector<std::vector<DumboPus>>&& dumbopuses) noexcept;

};

DumboSim::DumboSim(std::vector<std::vector<DumboPus>>&& dumbopuses) noexcept {
    this->dumbopuses = std::move(dumbopuses);
}

auto DumboSim::load(std::string file_name) -> DumboSim {
    std::vector<std::vector<DumboPus>> dumbopuses;
    dumbopuses.reserve(10);

    {
        auto input = std::ifstream(file_name);
        for (std::string line; std::getline(input, line); ) {
            if (line.empty()) continue;

            std::vector<DumboPus> new_dumbopuses;
            new_dumbopuses.reserve(10);

            for (const char c : line) new_dumbopuses.emplace_back(c - '0');
            
            dumbopuses.push_back(new_dumbopuses);
        }
    }

    for (auto y = 0; y < 10; y++) {
        for (auto x = 0; x < 10; x++) {
            auto& dumbopus = dumbopuses[y][x];

            auto x0 = std::max(x-1, 0), xE = std::min(x+2, 10);
            auto y0 = std::max(y-1, 0), yE = std::min(y+2, 10);
            for (auto y_n = y0; y_n < yE; y_n++) {
                for (auto x_n = x0; x_n < xE; x_n++) {
                    if (x_n == x && y_n == y) continue;
                    dumbopus.add_neighbour(dumbopuses[y_n][x_n]);
                }
            }
        }
    }

    return DumboSim(std::move(dumbopuses));
}

auto DumboSim::run(void) -> void {
    auto total_flashes = 0;

    for (auto cycle = 0; cycle < 100; cycle++) {
        for (auto& dumbopuses : dumbopuses) {
            for (auto& dumbopus : dumbopuses) {
                dumbopus.charge();
            }
        }

        for (auto& dumbopuses : dumbopuses) {
            for (auto& dumbopus : dumbopuses) {
                if (dumbopus.is_overcharged()) {
                    dumbopus.release_charge();
                    total_flashes++;
                }
            }
        }
    }

    std::cout << "After 100 cycles, there have been a total of " << total_flashes << " flashes! X_X" << std::endl;
    
    return;
}

}

}

#endif
