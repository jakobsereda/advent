#include "aoc.hpp"

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

    set<i64> xs;
    set<i64> ys;
    for (auto [x, y] : tiles) {
        xs.insert(x);
        ys.insert(y);
    }

    auto insert_with_neighbors = [&](i64 i, set<i64> &s) {
        s.insert(i);
        s.insert(i - 1);
        s.insert(i + 1);
    };

    for (size_t i = 0; i < n; i++) {
        auto [x1, y1] = tiles[i];
        auto [x2, y2] = tiles[(i + 1) % n];

        if (x1 == x2) {
            insert_with_neighbors(x1, xs);
            insert_with_neighbors(y1, ys);
            insert_with_neighbors(y2, ys);
        } else {
            insert_with_neighbors(y1, ys);
            insert_with_neighbors(x1, xs);
            insert_with_neighbors(x2, xs);
        }
    }

    xs.insert(*xs.begin() - 1);
    xs.insert(*xs.rbegin() + 1);
    ys.insert(*ys.begin() - 1);
    ys.insert(*ys.rbegin() + 1);

    vector<i64> xv(xs.begin(), xs.end());
    vector<i64> yv(ys.begin(), ys.end());

    map<i64, i64> xm;
    for (size_t i = 0; i < xv.size(); i++)
        xm[xv[i]] = i;

    map<i64, i64> ym;
    for (size_t i = 0; i < yv.size(); i++)
        ym[yv[i]] = i;
    
    i64 x_comp = xv.size();
    i64 y_comp = yv.size();

    vector<vector<bool>> valid_tiles(x_comp, vector<bool>(y_comp, false));

    for (auto [x, y] : tiles)
        valid_tiles[xm[x]][ym[y]] = true;

    for (size_t i = 0; i < n; i++) {
        auto [x1, y1] = tiles[i];
        auto [x2, y2] = tiles[(i + 1) % n];

        if (x1 == x2) {
            i64 cx = xm[x1];
            i64 y  = ym[min(y1, y2)];
            i64 dy = ym[max(y1, y2)];
            for (i64 j = y + 1; j <= dy; j++)
                valid_tiles[cx][j] = true;
        } else {
            i64 cy = ym[y1];
            i64 x  = xm[min(x1, x2)];
            i64 dx = xm[max(x1, x2)];
            for (i64 j = x + 1; j <= dx; j++)
                valid_tiles[j][cy] = true;
        }
    }
    
    vector<vector<bool>> outside(x_comp, vector<bool>(y_comp, false));
    queue<pair<i64, i64>> q;

    auto q_bfs = [&](i64 x, i64 y) {
        if (x < 0 || x >= x_comp || y < 0 || y >= y_comp)
            return;
        if (valid_tiles[x][y])
            return;
        if (outside[x][y])
            return;
        outside[x][y] = true;
        q.emplace(x, y);
    };

    const vector<pair<i8, i8>> dirs {
        { 1, 0 },
        { 0, 1 },
        { 0, -1 },
        { -1, 0 }
    };

    for (size_t i = 0; i < x_comp; i++) {
        q_bfs(i, 0);
        q_bfs(i, y_comp - 1);
    }

    for (size_t i = 0; i < y_comp; i++) {
        q_bfs(0, i);
        q_bfs(x_comp - 1, i);
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto [dx, dy] : dirs)
            q_bfs(x + dx, y + dy);
    }

    for (size_t i = 0; i < x_comp; i++)
        for (size_t j = 0; j < y_comp; j++)
            if (!outside[i][j])
                valid_tiles[i][j] = true;

    vector<vector<i64>> prefix(x_comp + 1, vector<i64>(y_comp + 1, 0));
    for (i64 i = 1; i <= x_comp; i++) {
        for (i64 j = 1; j <= y_comp; j++) {
            prefix[i][j] = (valid_tiles[i - 1][j - 1] ? 1 : 0)
                + prefix[i - 1][j]
                + prefix[i][j - 1]
                - prefix[i - 1][j - 1];
        }
    }

    auto valid_rectangle = [&](i64 x, i64 y, i64 dx, i64 dy) -> bool {
        i64 cx  = xm[x];
        i64 cy  = ym[y];
        i64 cdx = xm[dx];
        i64 cdy = ym[dy];

        i64 w = cdx - cx + 1;
        i64 h = cdy - cy + 1;
        i64 expected = w * h;

        i64 sum = prefix[cdx + 1][cdy + 1]
            - prefix[cx][cdy + 1]
            - prefix[cdx + 1][cy]
            + prefix[cx][cy];
        
        return sum == expected;
    };

    i64 greatest2 = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            auto [x1, y1] = tiles[i];
            auto [x2, y2] = tiles[j];

            i64 x  = min(x1, x2);
            i64 y  = min(y1, y2);
            i64 dx = max(x1, x2);
            i64 dy = max(y1, y2);
            i64 area = (dx - x + 1) * (dy - y + 1);

            if (area <= greatest2)
                continue;

            if (valid_rectangle(x, y, dx, dy))
                greatest2 = area;
        }
    }

    // ==================

    cout << "Part one: " << greatest << '\n';
    cout << "Part two: " << greatest2 << '\n';

    return 0;
}
