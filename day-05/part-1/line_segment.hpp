#ifndef ADVENT_OF_CODE__LINE_SEGMENT
#define ADVENT_OF_CODE__LINE_SEGMENT

#include <cmath>
#include <limits>

#include <cassert>
#include <exception>

#include <iostream>

#include <string>
#include <optional>

#include "point.hpp"

namespace advent_of_code {

inline namespace day_5 {

struct LineSegment {
    Point start = {0, 0}, end = {0, 0};
};

inline constexpr bool is_horizontal(const LineSegment& line) noexcept {
    return line.start.y == line.end.y;
}

inline constexpr bool is_vertical(const LineSegment& line) noexcept {
    return line.start.x == line.end.x;
}

inline constexpr bool is_diagonal(const LineSegment& line) noexcept {
    return !is_horizontal(line) && !is_vertical(line);
}

inline constexpr int min_x(const LineSegment& line) noexcept {
    return std::min(line.start.x, line.end.x);
}

inline constexpr int max_x(const LineSegment& line) noexcept {
    return std::max(line.start.x, line.end.x);
}

inline constexpr int min_y(const LineSegment& line) noexcept {
    return std::min(line.start.y, line.end.y);
}

inline constexpr int max_y(const LineSegment& line) noexcept {
    return std::max(line.start.y, line.end.y);
}

inline constexpr bool operator==(const LineSegment& a, const LineSegment& b) noexcept {
    return (a.start == b.start) && (a.end == b.end);
}

inline constexpr bool operator!=(const LineSegment& a, const LineSegment& b) noexcept {
    return !(a == b);
}

inline std::ostream& operator<<(std::ostream& out, const LineSegment& line) {
    return out << line.start << " -> " << line.end << '\n';
}

inline std::istream& operator>>(std::istream& in, LineSegment& line) {
    in >> line.start;
    in.ignore(4);
    in >> line.end;
    return in;
}

}

}

#endif
