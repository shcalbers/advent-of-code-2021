#ifndef ADVENT_OF_CODE__HTVENT_SUBSYSTEM
#define ADVENT_OF_CODE__HTVENT_SUBSYSTEM

#include <cmath>

#include <fstream>
#include <iostream>

#include <map>
#include <string>
#include <vector>

#include "point.hpp"
#include "line_segment.hpp"

namespace advent_of_code {

inline namespace day_5 {

class HTVentSubsystem final {

public:

    ~HTVentSubsystem(void) noexcept = delete;

    static auto run(std::string file_name) -> void;

private:

    static auto parse(std::string file_name, std::vector<LineSegment>& lines) -> void;

};

inline auto HTVentSubsystem::run(std::string file_name) -> void {
    std::vector<LineSegment> lines;
    lines.reserve(500);
    
    std::vector<std::vector<int>> htvent_map(1000, std::vector<int>(1000, 0));
    parse(file_name, lines);
   
    auto overlaps = 0;
    for (auto& line : lines) {
        if (is_horizontal(line)) {
            for (auto x = min_x(line); x <= max_x(line); x++) {
                if (++htvent_map[line.start.y][x] == 2) overlaps++;
            }
        } else if (is_vertical(line)) {
            for (auto y = min_y(line); y <= max_y(line); y++) {
                if (++htvent_map[y][line.start.x] == 2) overlaps++;
            }
        }
    }

    std::cout << "There were a total of " << overlaps << " overlaps across all thermal vents\n";
    return;
}

inline auto HTVentSubsystem::parse(std::string file_name, std::vector<LineSegment>& lines) -> void {
    auto input = std::ifstream(file_name);

    for (LineSegment line; input >> line; ) {
        lines.push_back(line); 
    }
}

}

}

#endif
