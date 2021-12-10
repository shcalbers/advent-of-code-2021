#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

auto main(void) noexcept -> int {
    // The total amount of increments in depth measurement.
    auto measurement_increments = 0;

    { // Count the amount of measurement increases in file 'input.txt'.
        auto measurements = ifstream("input.txt");

        auto prev_measurement = numeric_limits<float>::infinity();
        for (auto measurement = 0; measurements >> measurement; ) {
            if (measurement > prev_measurement)
                measurement_increments++;

            prev_measurement = measurement;
        }
    } // Done counting

    // Print total increments.
    cout << "The depth measurement increased " << measurement_increments << " times in total." << endl;

    return 0;
}
