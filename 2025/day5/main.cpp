#include "aoc.hpp"

bool fresh(i64 s, const vector<pair<i64, i64>> &ranges)
{
    for (auto p : ranges)
        if (s >= p.first && s <= p.second)
            return true;
    return false;
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    auto nl = find(lines.begin(), lines.end(), "");

    vector<string> raw_ranges(lines.begin(), nl);
    vector<string> raw_stock(nl + 1, lines.end());

    vector<pair<i64, i64>> ranges;
    for (string r : raw_ranges) {
        size_t dash = r.find('-');
        i64 i = stol(r.substr(0, dash));
        i64 j = stol(r.substr(dash + 1));
        ranges.emplace_back(i, j);
    }

    vector<i64> stock;
    for (string s : raw_stock)
        stock.push_back(stol(s));

    i64 sum = 0;
    for (i64 s : stock)
        if (fresh(s, ranges))
            sum++;
    
    // ==== part two ====

    sort(ranges.begin(), ranges.end(),
        [](const pair<i64, i64> &a, const pair<i64, i64> &b) {
            return a.first < b.first;
        });

    vector<pair<i64, i64>> merged;
    for (size_t i = 0; i < ranges.size(); i++) {
        pair<i64, i64> m = ranges[i];

        while (i + 1 < ranges.size() && ranges[i + 1].first <= m.second) {
            i++;
            m.second = max(ranges[i].second, m.second);
        }
    
        merged.push_back(m);
    }

    i64 sum2 = 0;
    for (auto p : merged)
        sum2 += p.second - p.first + 1;

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}
