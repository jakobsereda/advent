#include "aoc.hpp"

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    i32 cnt = 0;
    i32 cnt2 = 0;
    i32 dial = 50;

    for (string line : lines) {
        char dir = line[0];
        i32 ticks = stoi(line.substr(1));

        // ==== part two ====

        i32 dist;
        if (dir == 'R') {
            dist = (100 - dial) % 100;
        } else {
            dist = dial % 100;
        }

        if (dist == 0)
            dist = 100;

        if (dist <= ticks)
            cnt2 += 1 + (ticks - dist) / 100;

        // ==================

        if (dir == 'R') {
            dial = (dial + ticks) % 100;
        } else {
            dial = (dial - ticks) % 100;
            if (dial < 0) dial += 100;
        }

        if (dial == 0)
            cnt++;
    }
    
    cout << "Part one: " << cnt << '\n';
    cout << "Part two: " << cnt2 << '\n';

    return 0;
}
