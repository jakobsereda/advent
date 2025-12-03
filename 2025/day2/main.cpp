#include "aoc.hpp"

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<string> data;
    string s;
    for (stringstream ss(lines[0]); getline(ss, s, ',');)
        data.push_back(s);

    vector<pair<i64, i64>> ranges;
    for (string d : data) {
        size_t dash = d.find('-');
        i64 i = stol(d.substr(0, dash));
        i64 j = stol(d.substr(dash + 1));
        ranges.emplace_back(i, j);
    }

    i64 sum = 0;
    for (auto p : ranges) {
        for (i64 i = p.first; i <= p.second; i++) {
            string s = to_string(i);

            i32 len = s.length();
            if (len % 2 != 0)
                continue;

            string l = s.substr(0, len / 2);
            string r = s.substr(len / 2);

            if (l == r)
                sum += i;
        }
    }

    // ==== part two ====

    i64 sum2 = 0;
    for (auto p : ranges) {
        for (i64 i = p.first; i <= p.second; i++) {
            string s = to_string(i);

            string t = s + s;
            t = t.substr(1, 2 * s.length() - 2);

            if (t.find(s) != string::npos)
                sum2 += i;
        }
    }

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}
