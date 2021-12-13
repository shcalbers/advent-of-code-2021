#include <fstream>
#include <iostream>
#include <sstream>

#include <set>
#include <string>
#include <vector>

struct Point {
    int x, y;
};

constexpr auto fold_up(Point p, int y) noexcept -> Point {
    return (p.y > y) ? Point{p.x, y-(p.y-y)} : p;
}

constexpr auto fold_left(Point p, int x) noexcept -> Point {
    return (p.x > x) ? Point{x-(p.x-x), p.y} : p;
}

constexpr auto operator==(const Point lhs, const Point rhs) noexcept -> bool {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

constexpr auto operator<(const Point lhs, const Point rhs) noexcept -> bool {
    return (lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x));
}

auto operator<<(std::ostream& out, const Point& point) -> std::ostream& {
    return (out << point.x << ',' << point.y);
}

auto operator>>(std::istream& in, Point& point) -> std::istream& {
    return (in >> point.x, in.ignore(), in >> point.y);
}

constexpr auto ordinal_suffix(const int number) noexcept {
    const auto i = number%10, j = number%100;
    return i == 1 && j != 11 ? "st" :
           i == 2 && j != 12 ? "nd" :
           i == 3 && j != 13 ? "rd" : "th";
}

auto main(void) noexcept -> int {
    std::set<Point> points;

    {
        auto input = std::ifstream("input.txt");
        
        // Load all points on the transparent paper from the input.
        for (std::string line; std::getline(input, line); ) {
            if (line.empty()) break;

            auto input = std::istringstream(line);
            Point point;
            input >> point;

            points.insert(point);
        }

        // Load all the instruction from the input and apply them immediately.
        auto instruction_number = 1;
        for (std::string instruction; std::getline(input, instruction); ) {
            // First read the instruction...
            static constexpr char pattern[] = "fold along $=#";
            
            auto fold_on_x = true;
            auto folding_coord = -1;

            for (auto i = 0; pattern[i] != '\0'; i++) {
                switch (pattern[i]) {
                case '$':
                    fold_on_x = (instruction[i] == 'x');
                    break;
                case '#':
                    folding_coord = std::stoi(instruction.substr(i)); 
                    break;
                default:
                    if (instruction[i] != pattern[i]) {
                        std::cout << "Invalid instruction (" << instruction_number-1 << "," << i << "): " << instruction << std::endl;
                        std::exit(-1);
                    }
                }
            }
           
            // Then apply the instruction on all points.
            std::set<Point> new_points;
            for (const auto point : points) {
                if (fold_on_x) new_points.insert(fold_left(point, folding_coord));
                else new_points.insert(fold_up(point, folding_coord));
            }
            points = std::move(new_points);

            // Output the number of points after applying the current instruction and then continue.
            std::cout << "After applying the " << instruction_number << ordinal_suffix(instruction_number) << " instruction, there are " << points.size() << " points left!" << std::endl;
            instruction_number++;
        }
    }

    // Output instruction paper result
    std::vector<std::vector<bool>> instruction_paper(6, std::vector<bool>(100, false));
    for (auto point : points) instruction_paper[point.y][point.x] = true;

    for (auto y = 0; y < instruction_paper.size(); y++) {
        std::cout << " " << y << " | ";
        for (const auto point : instruction_paper[y]) std::wcout << (point ? '#' : '.');
        std::cout << std::endl;
    }

    return 0;
}
