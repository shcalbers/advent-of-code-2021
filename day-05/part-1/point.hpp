#ifndef ADVENT_OF_CODE__POINT
#define ADVENT_OF_CODE__POINT

#include <iostream>

namespace advent_of_code {

inline namespace day_5 {

struct Point {
    int x = 0, y = 0;
};

inline constexpr bool operator==(const Point& a, const Point& b) noexcept {
    return (a.x == b.x) && (a.y == b.y);
}

inline constexpr bool operator!=(const Point& a, const Point& b) noexcept {
    return !(a == b);
}

inline std::ostream& operator<<(std::ostream& out, const Point& point) {
    return out << point.x << ',' << point.y;
}

inline std::istream& operator>>(std::istream& in, Point& point) {
    in >> point.x;
    in.ignore();
    in >> point.y;
    return in;
}

}

}

#endif
