#include "aoc.hpp"

bool valid_rectangle(const vector<vector<bool>> &tiles, i64 x, i64 y, i64 dx, i64 dy)
{
    for (i64 i = x; i <= dx; i++)
        for (i64 j = y; j <= dy; j++)
            if (!tiles[i][j])
                return false;
    return true;
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<pair<i64, i64>> tiles;
    for (string line : lines) {
        stringstream ss(line);
        string s;
        getline(ss, s, ',');
        i64 a = stol(s);
        getline(ss, s, ',');
        i64 b = stol(s);
        tiles.emplace_back(a, b);
    }

    i64 greatest = 0;
    size_t n = tiles.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            auto [x1, y1] = tiles[i];
            auto [x2, y2] = tiles[j];

            if (x2 < x1)
                swap(x1, x2);
            i64 x = x2 - x1 + 1;

            if (y2 < y1)
                swap(y1, y2);
            i64 y = y2 - y1 + 1;

            greatest = max(greatest, x * y);
        }
    }

    // ==== part two ====

    i64 maxx = 0;
    i64 maxy = 0;
    for (auto [x, y] : tiles) {
        maxx = max(maxx, x);
        maxy = max(maxy, y);
    }

    maxx += 1;
    maxy += 1;

    vector<vector<bool>> valid_tiles(maxx, vector<bool>(maxy, false));
    for (auto [x, y] : tiles)
        valid_tiles[x][y] = true;

    i64 greatest2 = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            auto [x1, y1] = tiles[i];
            auto [x2, y2] = tiles[j];

            i64 x = min(x1, x2);
            i64 y = min(y1, y2);
            i64 dx = max(x1, x2);
            i64 dy = max(y1, y2);

            if (valid_rectangle(valid_tiles, x, y, dx, dy))
                greatest2 = max(greatest2, (dx - x + 1) * (dy - y + 1));
        }
    }

    // ==================

    cout << "Part one: " << greatest << '\n';
    cout << "Part two: " << greatest2 << '\n';

    return 0;
}
