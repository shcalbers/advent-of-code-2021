#ifndef ADVENT_OF_CODE__SIGNAL
#define ADVENT_OF_CODE__SIGNAL

#include <cassert>
#include <exception>

#include <fstream>
#include <iostream>

#include <array>
#include <bitset>
#include <map>
#include <string>
#include <vector>

namespace advent_of_code {

inline namespace day_8 {

union Signal {
    
    static constexpr auto max_length = 7;

    static constexpr uint8_t A { 0b0000'0001 };
    static constexpr uint8_t B { 0b0000'0010 };
    static constexpr uint8_t C { 0b0000'0100 };
    static constexpr uint8_t D { 0b0000'1000 };
    static constexpr uint8_t E { 0b0001'0000 };
    static constexpr uint8_t F { 0b0010'0000 };
    static constexpr uint8_t G { 0b0100'0000 };

    static constexpr uint8_t null { 0b0000'0000 };
    static constexpr uint8_t invalid { 0b1000'0000 };

    static constexpr uint8_t full_range = A | B | C | D | E | F | G;

    static constexpr uint8_t zero  = A | B | C | E | F | G;
    static constexpr uint8_t one   = C | F;
    static constexpr uint8_t two   = A | C | D | E | G;
    static constexpr uint8_t three = A | C | D | F | G;
    static constexpr uint8_t four  = B | C | D | F;
    static constexpr uint8_t five  = A | B | D | F | G;
    static constexpr uint8_t six   = A | B | D | E | F | G;
    static constexpr uint8_t seven = A | C | F;
    static constexpr uint8_t eight = A | B | C | D | E | F | G;
    static constexpr uint8_t nine  = A | B | C | D | F | G;

    static constexpr uint8_t signal[] = { A, B, C, D, E, F, G };
    static constexpr uint8_t digit[]  = { zero, one, two, three, four, five, six, seven, eight, nine };

    uint8_t byte = 0;
    struct {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t c : 1;
        uint8_t d : 1;
        uint8_t e : 1;
        uint8_t f : 1;
        uint8_t g : 1;
    } bit;

    constexpr Signal(void) noexcept;
    constexpr Signal(uint8_t value) noexcept;
    constexpr Signal(int value) noexcept;

    constexpr Signal(char c) noexcept;
    constexpr Signal(const char* pattern) noexcept;

    constexpr auto length(void) const noexcept -> int;
    constexpr auto to_digit(void) const noexcept -> int;

private:

    static constexpr auto validate(char c) noexcept -> bool;
    static constexpr auto validate(const char* pattern) noexcept -> bool;

};

constexpr Signal::Signal(void) noexcept : byte() {
    // Empty.
}

constexpr Signal::Signal(uint8_t value) noexcept : byte(value) {
    // Empty.
}

constexpr Signal::Signal(int value) noexcept : byte(value) {
    // Empty.
}

constexpr Signal::Signal(const char c) noexcept {
    assert(validate(c) && "Character 'c' out of range! 'c' must be either a, b, c, d, e, f or g to be converted to a Signal!");
    this->byte = signal[c - 'a'];
}

constexpr Signal::Signal(const char* pattern) noexcept {
    assert(validate(pattern) && "Invalid signal pattern supplied! The string must be at most 7 characters long and only consist of unique letters ranging from a to g!");
    for (auto i = 0; pattern[i] != '\0'; i++) {
        this->byte |= signal[pattern[i] - 'a']; 
    }
}

constexpr auto Signal::length(void) const noexcept -> int {
    auto length = 0;
    for (auto i = 0; i < max_length; i++) {
        if ((byte >> i) & 1) length++;
    }
    
    return length;
}

constexpr auto Signal::to_digit(void) const noexcept -> int {
    for (auto digit = 0; digit <= 9; digit++) {
        if (Signal::digit[digit] == byte) return digit;
    }

    return -1;
}

constexpr auto Signal::validate(char c) noexcept -> bool {
    return ('a' <= c) && (c <= 'g');
}

constexpr auto Signal::validate(const char* pattern) noexcept -> bool {
    bool valid = true;
    for (auto i = 0; i <= max_length; i++) {
        if (pattern[i] != '\0') {
            if (valid == false || i == max_length) return false;
            valid = valid && validate(pattern[i]);
        } else {
            break;
        }
    }

    return valid;
}

constexpr auto operator==(const Signal lhs, const Signal rhs) noexcept -> bool {
    return lhs.byte == rhs.byte;
}

constexpr auto operator!=(const Signal lhs, const Signal rhs) noexcept -> bool {
    return lhs.byte != rhs.byte;
}

constexpr auto operator<(const Signal lhs, const Signal rhs) noexcept -> bool {
    return lhs.byte < rhs.byte;
}

constexpr auto operator&(const Signal lhs, const Signal rhs) noexcept -> Signal {
    return lhs.byte & rhs.byte;
}

constexpr auto operator|(const Signal lhs, const Signal rhs) noexcept -> Signal {
    return lhs.byte | rhs.byte;
}

constexpr auto operator^(const Signal lhs, const Signal rhs) noexcept -> Signal {
    return lhs.byte ^ rhs.byte;
}

constexpr auto operator~(const Signal rhs) noexcept -> Signal {
    return ~rhs.byte;
}

constexpr auto operator&=(Signal& lhs, const Signal rhs) noexcept -> Signal& {
    lhs = lhs & rhs;
    return lhs;
}

constexpr auto operator|=(Signal& lhs, const Signal rhs) noexcept -> Signal& {
    lhs = lhs | rhs;
    return lhs;
}

constexpr auto operator^=(Signal& lhs, const Signal rhs) noexcept -> Signal& {
    lhs = lhs ^ rhs;
    return lhs;
}

auto operator<<(std::ostream& out, const Signal signal) noexcept -> std::ostream& {
    return out << std::bitset<8>(signal.byte);
}


inline auto overlapping_signals_for(const Signal signal_pattern) noexcept -> std::vector<Signal> {
    switch (signal_pattern.length()) {
    case 2: return { Signal::C, Signal::F };
    case 3: return { Signal::A, Signal::C, Signal::F };
    case 4: return { Signal::B, Signal::C, Signal::D, Signal::F };
    case 5: return { Signal::A, Signal::D, Signal::G };
    case 6: return { Signal::A, Signal::B, Signal::F, Signal::G };
    case 7: return { Signal::A, Signal::B, Signal::C, Signal::D, Signal::E, Signal::F, Signal::G };
    default:
        assert(signal_pattern.length() <= Signal::max_length && "Invalid Signal length! A signal can contain at most 7 on bits.");
        return std::vector<Signal>{};
    }
}

inline auto map_signals(const std::array<Signal, 10>& signal_patterns) noexcept -> std::map<Signal, Signal> {
    std::map<Signal, Signal> signal_map;
    for (auto i = 0; i < Signal::max_length; i++) {
        signal_map[Signal::signal[i]] = Signal::full_range;
    }

    for (const Signal& signal_pattern : signal_patterns) {
        for (Signal signal : overlapping_signals_for(signal_pattern)) {
            if (signal_map[signal].length() == 1) continue;
            //std::cout << signal << " = " << signal_map[signal] << " & " << signal_pattern << '\n';
            signal_map[signal] &= signal_pattern;

            if (signal_map[signal].length() == 1) {
               for (auto entry : signal_map) {
                    if (entry.first == signal) continue;
                    entry.second &= ~signal_map[signal];
                }
            }
        }
    }

    while (true) {
        auto solved = 0;
        for (auto& [signal, match] : signal_map) {
            if (match.length() == 1) {
                solved++;
                for (auto& [signal_other, match_other] : signal_map) {
                    if (signal_other == signal) continue;
                    match_other &= ~match;
                }
            }
        }
        if (solved == Signal::max_length) break;
    }

    return signal_map;
}

inline auto decode_signal(const Signal obscured_signal, std::map<Signal, Signal>& signal_map) {
    Signal decoded_signal = Signal::null;

    for (auto [signal, match] : signal_map)
        if ((obscured_signal & match) != Signal::null) decoded_signal |= signal;

    return decoded_signal;
}

}

}

#endif
