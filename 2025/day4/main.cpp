#include "aoc.hpp"

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<vector<bool>> rolls;
    for (string line : lines) {
        vector<bool> shelf;
        for (char& c : line)
            if (c == '.')
                shelf.push_back(false);
            else
                shelf.push_back(true);
        rolls.push_back(shelf);    
    }

    const vector<pair<i8, i8>> dirs {
        { 1, 0 },
        { 0, 1 },
        { 1, 1 },
        { 1, -1 },
        { 0, -1 },
        { -1, 0 },
        { -1, 1 },
        { -1, -1 }
    };

    i32 sum = 0;
    for (size_t i = 0; i < rolls.size(); i++) {
        for (size_t j = 0; j < rolls[0].size(); j++) {
            i32 cnt = 0;
            for (auto p : dirs) {
                i32 x = i + p.first;
                i32 y = j + p.second;
                if (x < 0 || x >= rolls.size())
                    continue;
                if (y < 0 || y >= rolls[0].size())
                    continue;
                if (rolls[x][y])
                    cnt++;
            }

            if (rolls[i][j] && cnt < 4)
                sum++;
        }
    }

    // ==== part two ====

    i32 sum2 = 0;
    i32 removed = 1;
    while (removed > 0) {
        removed = 0;
        for (size_t i = 0; i < rolls.size(); i++) {
            for (size_t j = 0; j < rolls[0].size(); j++) {
                i32 cnt = 0;
                for (auto p : dirs) {
                    i32 x = i + p.first;
                    i32 y = j + p.second;
                    if (x < 0 || x >= rolls.size())
                        continue;
                    if (y < 0 || y >= rolls[0].size())
                        continue;
                    if (rolls[x][y])
                        cnt++;
                }   

                if (rolls[i][j] && cnt < 4) {
                    rolls[i][j] = false;
                    sum2++;
                    removed++;
                }
            }
        }
    }

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}