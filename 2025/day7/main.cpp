#include "aoc.hpp"

map<pair<size_t, size_t>, i64> dp;

i64 find_timelines(size_t idx, size_t depth, const vector<vector<char>> &g)
{
    // if (idx >= g[0].size())
    //     return 0;
    while (g[depth][idx] != '^') {
        if (depth == g.size() - 1)
            return 1;
        depth++;
    }
    auto key = make_pair(idx, depth);
    if (dp.contains(key))
        return dp[key];
    i64 l = 0;
    i64 r = 0;
    if (idx > 0)
        l = find_timelines(idx - 1, depth + 1, g);
    if (idx + 1 < g[0].size())
        r = find_timelines(idx + 1, depth + 1, g);
    return dp[key] = l + r;
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<vector<char>> grid(lines.size(), vector<char>(lines[0].length()));
    for (size_t i = 0; i < lines.size(); i++)
        for (size_t j = 0; j < lines[0].length(); j++)
            grid[i][j] = lines[i][j];
    
    size_t s_idx = 0;
    set<size_t> lanes;
    for (size_t i = 0; i < grid[0].size(); i++) {
        if (grid[0][i] == 'S') {
            lanes.insert(i);
            s_idx = i;
        }
    }

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

    // ==== part two ====

    i64 sum2 = find_timelines(s_idx, 1, grid);

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << "\n";

    return 0;
}