#include <array>
#include <fstream>
#include <iostream>

using namespace std;

auto main(void) noexcept -> int {
    auto gamma_rate = 0;
    auto epsilon_rate = 0;
    auto power_consumption = 0;

    {
        auto diagnostic_report = ifstream("input.txt");

        constexpr auto bit_width = 12;
        array<int, bit_width> zero_count{0,0,0,0,0,0,0,0,0,0,0,0};
        array<int, bit_width> ones_count{0,0,0,0,0,0,0,0,0,0,0,0};
        
        for (string binary; diagnostic_report >> binary; ) {
            for (auto bit = 0; bit < bit_width; bit++) {
                const auto value = binary[bit] - '0';
                if (value == 0) zero_count[bit]++; else ones_count[bit]++;
            }
        }

        for (auto bit = 0; bit < bit_width; bit++) {
            if (ones_count[bit] >= zero_count[bit]) {
                gamma_rate   = (gamma_rate   << 1) | 1;
                epsilon_rate = (epsilon_rate << 1);
            } else {
                gamma_rate   = (gamma_rate   << 1);
                epsilon_rate = (epsilon_rate << 1) | 1;
            }
        }
        
        power_consumption = gamma_rate * epsilon_rate;
    }

    cout << "Gamma Rate: "   << gamma_rate << '\n'
         << "Epsilon Rate: " << epsilon_rate << '\n'
         << "Power Consumption: " << power_consumption << endl;

    return 0;
}
