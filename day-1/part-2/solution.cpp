#include <deque>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

auto main(void) noexcept -> int {
    // The total amount of increments in depth measurement.
    auto measurement_increments = 0;

    { // Count the amount of measurement increases in file 'input.txt'.
        auto measurements = ifstream("input.txt");

        constexpr auto window_size = 3;
        auto window = deque<int>();

        auto prev_measurement = numeric_limits<float>::infinity();
        for (auto measurement = 0; measurements >> measurement; ) {
            if (window.size() == window_size) window.pop_front();
            window.push_back(measurement);

            if (window.size() == window_size) {
                auto window_sum = 0;
                for (auto measurement : window) window_sum += measurement;
                
                if (window_sum > prev_measurement) measurement_increments++;
                
                prev_measurement = window_sum;
            }
        }
    } // Done counting

    // Print total increments.
    cout << "The depth measurement increased " << measurement_increments << " times in total." << endl;

    return 0;
}
