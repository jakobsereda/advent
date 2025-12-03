#include "aoc.hpp"

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<vector<u8>> banks;
    for (string line : lines) {
        vector<u8> bank;
        for (char& c : line)
            bank.push_back(c - '0');
        banks.push_back(bank);
    }

    i64 sum = 0;
    for (auto bank : banks) {
        i64 best = 0;

        for (size_t i = 0; i < bank.size(); i++) {
            for (size_t j = i + 1; j < bank.size(); j++) {
                i64 val = (bank[i] * 10) + bank[j];
                if (val > best)
                    best = val;
            }
        }

        sum += best;
    }

    // ==== part two ====

    i64 sum2 = 0;
    for (auto bank : banks) {
        size_t idx = 0;
        string best_str;

        for (size_t i = 12; i > 0; i--) {
            i32 best_digit = -1;
            size_t best_idx = idx;

            for (size_t j = idx; j < bank.size() - i + 1; j++) {
                if (bank[j] > best_digit) {
                    best_digit = bank[j];
                    best_idx = j;
                }
            }

            best_str += to_string(best_digit);
            idx = best_idx + 1;
        }

        sum2 += stol(best_str);
    }

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}
