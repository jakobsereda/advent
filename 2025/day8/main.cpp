#include "aoc.hpp"

struct JunctionBox {
    i64 x;
    i64 y;
    i64 z;
};

struct UnionFind {
    vector<i64> parent;
    vector<i64> size;

    UnionFind(i64 n) : parent(n), size(n, 1)
    {
        for (i64 i = 0; i < n; i++)
            parent[i] = i;
    }

    bool union_(i64 a, i64 b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    i64 find(i64 a)
    {
        if (parent[a] != a)
            parent[a] = find(parent[a]);
        return parent[a];
    }
};

i64 box_dist(JunctionBox a, JunctionBox b)
{
    i64 dx = a.x - b.x;
    i64 dy = a.y - b.y;
    i64 dz = a.z - b.z;
    return (dx * dx) + (dy * dy) + (dz * dz);
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    size_t n = lines.size();
    vector<JunctionBox> boxes(n);
    for (size_t i = 0; i < n; i++) {
        vector<i64> coords; 
        stringstream ss(lines[i]);
        string s;
        while (getline(ss, s, ','))
            coords.push_back(stol(s));
        boxes[i] = JunctionBox {
            .x = coords[0],
            .y = coords[1],
            .z = coords[2]
        };
    }

    vector<tuple<i64, size_t, size_t>> pairs;
    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n; j++)
            pairs.emplace_back(box_dist(boxes[i], boxes[j]), i, j);

    sort(pairs.begin(), pairs.end(), 
        [](auto a, auto b) {
            return get<0>(a) < get<0>(b);
        });
    
    UnionFind uf(n);

    for (size_t i = 0; i < 1000; i++) {
        auto [d, a, b] = pairs[i];
        uf.union_(a, b);
    }

    vector<i64> sizes;
    vector<bool> seen(n, false);
    for (size_t i = 0; i < n; i++) {
        i64 a = uf.find(i);
        if (!seen[a]) {
            seen[a] = true;
            sizes.push_back(uf.size[a]);
        }
    }

    sort(sizes.begin(), sizes.end(), greater<int>());

    i64 prod = sizes[0] * sizes[1] * sizes[2];

    // ==== part two ====

    UnionFind uf2(n);

    i64 total = n;
    i64 last_a = -1;
    i64 last_b = -1;

    for (auto [d, a, b] : pairs) {
        if (uf2.union_(a, b)) {
            total--;
            last_a = a;
            last_b = b;
            if (total == 1)
                break;
        }
    }

    i64 prod2 = boxes[last_a].x * boxes[last_b].x;

    // ==================

    cout << "Part one: " << prod << '\n';
    cout << "Part two: " << prod2 << '\n';

    return 0;
}
