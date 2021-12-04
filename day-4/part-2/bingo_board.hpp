#ifndef ADVENT_OF_CODE__BINGO_BOARD
#define ADVENT_OF_CODE__BINGO_BOARD

#include <cassert>

#include <iomanip>
#include <ostream>

#include <vector>

namespace advent_of_code {

inline namespace day4 {

class BingoBoard final {

    friend std::ostream& operator<<(std::ostream& out, const BingoBoard& board);

public:

    BingoBoard(int size = 5) noexcept;
    BingoBoard(const std::vector<std::vector<int>>& numbers) noexcept;

    auto has_bingo(void) const noexcept -> bool;
    auto score(void) const noexcept -> int;

    auto mark(int number) noexcept -> bool; 

private:

    struct BingoNumber {
        int value = 0;
        bool marked = false;
    };

    using Grid = std::vector<std::vector<BingoNumber>>;

    Grid numbers;

    bool bingo = false;
    int winning_number = -1;

    auto is_row_complete(int row) const noexcept -> bool;
    auto is_col_complete(int col) const noexcept -> bool;

};

inline BingoBoard::BingoBoard(int size) noexcept {
    this->numbers = std::vector<std::vector<BingoNumber>>(size, std::vector<BingoNumber>(size));
}

inline BingoBoard::BingoBoard(const std::vector<std::vector<int>>& numbers) noexcept {
    assert(numbers.size() == numbers[0].size() && "The vector 'numbers' should form a grid with an equal amount of rows and columns!");

    const int size = numbers.size();

    this->numbers = std::vector<std::vector<BingoNumber>>(size, std::vector<BingoNumber>(size));
    for (auto row = 0; row < size; row++) {
        for (auto col = 0; col < size; col++) {
            this->numbers[row][col].value = numbers[row][col];
        }
    }
}

inline auto BingoBoard::has_bingo(void) const noexcept -> bool {
    return this->bingo;
}

inline auto BingoBoard::score(void) const noexcept -> int {
    assert(this->has_bingo() && "Attempted to calculate the score of an incomplete board!");
    
    auto score = 0;

    for (auto row = 0; row < numbers.size(); row++) {
        for (auto col = 0; col < numbers.size(); col++) {
            score += (numbers[row][col].marked == false) ? numbers[row][col].value : 0;
        }
    }

    score *= winning_number;

    return score;
}

inline auto BingoBoard::mark(int number) noexcept -> bool {
    auto number_found = false;

    for (auto row = 0; row < numbers.size(); row++) {
        for (auto col = 0; col < numbers.size(); col++) {
            auto& current_number = numbers[row][col];
            if (current_number.value == number) {
                current_number.marked = true;
                if (!this->has_bingo() && (this->is_row_complete(row) || this->is_col_complete(col))) {
                    this->bingo = true;
                    this->winning_number = number;
                }
            }
        }
    }

    return number_found;
}

inline auto BingoBoard::is_row_complete(int row) const noexcept -> bool {
    auto row_complete = true;
    for (auto col = 0; col < numbers.size(); col++) {
        row_complete = row_complete && numbers[row][col].marked;
    }

    return row_complete;
}

inline auto BingoBoard::is_col_complete(int col) const noexcept -> bool {
    auto col_complete = true;
    for (auto row = 0; row < numbers.size(); row++) {
        col_complete = col_complete && numbers[row][col].marked;
    }

    return col_complete;
}

inline std::ostream& operator<<(std::ostream& out, const BingoBoard& board) {
    for (auto row = 0; row < board.numbers.size(); row++) {
        for (auto col = 0; col < board.numbers.size(); col++) {
            auto check_mark = board.numbers[row][col].marked ? 'x' : 'o';
            out << std::setw(2) << board.numbers[row][col].value << check_mark << ' ';
        }
        out << '\n';
    }

    return out;
}

}

}

#endif
