#include "aoc.hpp"

struct JunctionBox
{
    i64 x;
    i64 y;
    i64 z;
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

    vector<set<i64>> circuits;
    vector<i64> mapping(n, -1);
    for (size_t i = 0; i < 1000; i++) {
        size_t idx_a = get<1>(pairs[i]);
        size_t idx_b = get<2>(pairs[i]);
        bool a_not_mapped = mapping[idx_a] < 0;
        bool b_not_mapped = mapping[idx_b] < 0;

        if (a_not_mapped && b_not_mapped) {
            set<i64> s;
            s.insert(idx_a);
            s.insert(idx_b);
            i64 map = circuits.size();
            mapping[idx_a] = map;
            mapping[idx_b] = map;
            circuits.push_back(s);
        } else if (a_not_mapped) {
            i64 idx_s = mapping[idx_b];
            mapping[idx_a] = idx_s;
            circuits[idx_s].insert(idx_a);
        } else if (b_not_mapped) {
            i64 idx_s = mapping[idx_a];
            mapping[idx_b] = idx_s;
            circuits[idx_s].insert(idx_b);
        } else {
            i64 idx_sa = mapping[idx_a];
            i64 idx_sb = mapping[idx_b];
            if (idx_sa == idx_sb)
                continue;
            if (circuits[idx_sa].size() < circuits[idx_sb].size())
                swap(idx_sa, idx_sb);
            for (i64 j : circuits[idx_sb]) {
                circuits[idx_sa].insert(j);
                mapping[j] = idx_sa;
            }
            circuits[idx_sb].clear();
        }
    }

    vector<i64> sizes;
    for (set<i64> s : circuits)
        sizes.push_back(s.size());

    sort(sizes.begin(), sizes.end(), greater<int>());

    i64 prod = sizes[0] * sizes[1] * sizes[2];

    // ==== part two ====

    size_t last_a = 0;
    size_t last_b = 0;
    for (size_t i = 1000; i < pairs.size(); i++) {
        size_t idx_a = get<1>(pairs[i]);
        size_t idx_b = get<2>(pairs[i]);
        bool a_not_mapped = mapping[idx_a] < 0;
        bool b_not_mapped = mapping[idx_b] < 0;

        if (a_not_mapped && b_not_mapped) {
            set<i64> s;
            s.insert(idx_a);
            s.insert(idx_b);
            i64 map = circuits.size();
            mapping[idx_a] = map;
            mapping[idx_b] = map;
            circuits.push_back(s);
        } else if (a_not_mapped) {
            i64 idx_s = mapping[idx_b];
            mapping[idx_a] = idx_s;
            circuits[idx_s].insert(idx_a);
        } else if (b_not_mapped) {
            i64 idx_s = mapping[idx_a];
            mapping[idx_b] = idx_s;
            circuits[idx_s].insert(idx_b);
        } else {
            i64 idx_sa = mapping[idx_a];
            i64 idx_sb = mapping[idx_b];
            if (idx_sa == idx_sb)
                continue;
            if (circuits[idx_sa].size() < circuits[idx_sb].size())
                swap(idx_sa, idx_sb);
            for (i64 j : circuits[idx_sb]) {
                circuits[idx_sa].insert(j);
                mapping[j] = idx_sa;
            }
            circuits[idx_sb].clear();
        }

        i64 non_empty = 0;
        i64 last_non_empty = -1;
        for (size_t j = 0; j < circuits.size(); j++) {
            if (!circuits[j].empty()) {
                non_empty++;
                last_non_empty = j;
            }
        }

        if (non_empty == 1) {
            last_a = idx_a;
            last_b = idx_b;
            break;
        }
    }

    i64 prod2 = boxes[last_a].x * boxes[last_b].x;

    // ==================

    cout << "Part one: " << prod << '\n';
    cout << "Part two: " << prod2 << '\n';

    return 0;
}