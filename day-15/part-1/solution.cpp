#include <fstream>
#include <iostream>

#include <list>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

struct Point {
    int x = 0, y = 0;
};

constexpr auto operator==(const Point lhs, const Point rhs) noexcept -> bool {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr auto operator<(const Point lhs, const Point rhs) noexcept -> bool {
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}

auto find_neighbours(const Point point, const Point max, std::vector<Point>& neighbours_out) noexcept -> void {
    if (point.x != 0)       neighbours_out.push_back({point.x-1, point.y+0});
    if (point.x != max.x)   neighbours_out.push_back({point.x+1, point.y+0});
    if (point.y != 0)       neighbours_out.push_back({point.x+0, point.y-1});
    if (point.y != max.y)   neighbours_out.push_back({point.x+0, point.y+1});
}

auto h(const Point point, const Point end) noexcept -> int {
    return int(std::sqrt((end.x-point.x)*(end.x-point.x) + (end.y-point.y)*(end.y-point.y)));
}

auto reconstruct_path(std::map<Point, Point>& came_from, Point current, const std::vector<std::vector<int>>& risk_map) noexcept -> std::list<int> {
    std::list<int> path;

    while (came_from.count(current)) {
        path.push_front(risk_map[current.y][current.x]);
        current = came_from[current];
    }

    return path;
}

auto lowest_risk(const Point start, const Point end, const std::vector<std::vector<int>>& risk_map) noexcept -> std::optional<std::list<int>> {
    const Point max = Point{int(risk_map.size()-1), int(risk_map.size()-1)};

    std::set<std::pair<int, Point>> open_set;
    open_set.insert({h(start, end), start});

    std::map<Point, Point> came_from;

    std::map<Point, int> g_scores;
    g_scores[start] = 0;

    std::map<Point, int> f_scores;
    f_scores[start] = h(start, end);

    std::vector<Point> neighbours;
    neighbours.reserve(4);

    while (open_set.empty() == false) {
        auto [_, current] = *open_set.begin();
        if (current == end) return reconstruct_path(came_from, current, risk_map);

        open_set.erase(open_set.begin());
        
        neighbours.clear();
        find_neighbours(current, max, neighbours);
        for (auto neighbour : neighbours) {
            g_scores.insert({neighbour, std::numeric_limits<int>::max()});

            const auto tentative_g_score = g_scores[current] + risk_map[neighbour.y][neighbour.x];
            if (tentative_g_score < g_scores[neighbour]) {
                came_from[neighbour] = current;
                g_scores[neighbour] = tentative_g_score;
                f_scores[neighbour] = tentative_g_score + h(neighbour, end);

                open_set.insert({f_scores[neighbour], neighbour});
            }
        }
    }

    return std::nullopt;
}

auto main(void) -> int {
    static constexpr auto risk_map_size = 100;

    std::vector<std::vector<int>> risk_map;
    risk_map.reserve(risk_map_size);

    {
        auto input = std::ifstream("input.txt");
        for (std::string line; std::getline(input, line); ) {
            std::vector<int> risk_map_row;
            risk_map_row.reserve(risk_map_size);

            for (auto c : line) risk_map_row.push_back(c - '0');

            risk_map.push_back(std::move(risk_map_row));
        }
    }

    auto safest_path = lowest_risk({0,0}, {99, 99}, risk_map);
    auto risk_factor = 0;
    for (auto node : *safest_path) {
        std::cout << node << ", ";
        risk_factor += node;
    }
    std::cout << '\n';

    std::cout << "Total risk factor: " << risk_factor << std::endl;

    return 0;
}
