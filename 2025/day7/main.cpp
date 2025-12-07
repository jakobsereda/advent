#include "aoc.hpp"

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<vector<char>> grid(lines.size(), vector<char>(lines[0].length()));
    for (size_t i = 0; i < lines.size(); i++)
        for (size_t j = 0; j < lines[0].length(); j++)
            grid[i][j] = lines[i][j];
    
    set<size_t> lanes;
    for (size_t i = 0; i < grid[0].size(); i++)
        if (grid[0][i] == 'S')
            lanes.insert(i);

    i64 sum = 0;
    for (size_t i = 1; i < grid.size(); i++) {
        set<size_t> curr = lanes;
        for (size_t j : curr) {
            if (grid[i][j] == '^') {
                sum++;
                lanes.erase(j);
                if (j + 1 < grid[0].size())
                    lanes.insert(j + 1);
                if (j - 1 >= 0)
                    lanes.insert(j - 1);
            }
        }
    }

    i64 sum2 = 0;

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << "\n";

    return 0;
}