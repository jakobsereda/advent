#include "aoc.hpp"

map<string, vector<string>> g;
map<tuple<string, bool, bool>, i64> dp;

i64 dfs(const string& s, bool seen_dac, bool seen_fft)
{
    bool sd = seen_dac || (s == "dac");
    bool sf = seen_fft || (s == "fft");

    if (s == "out")
        return (sd && sf) ? 1 : 0;

    auto k = make_tuple(s, sd, sf);
    if (dp.count(k))
        return dp[k];

    i64 ret = 0;

    for (string e : g[s])
        ret += dfs(e, sd, sf);

    return dp[k] = ret;
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    for (string line : lines) {
        vector<string> parts;
        stringstream ss(line);
        string s;
        while (getline(ss, s, ':'))
            parts.push_back(s);
        
        vector<string> e;
        stringstream ss2(parts[1].substr(1));
        string s2;
        while (getline(ss2, s2, ' '))
            e.push_back(s2);
        
        g[parts[0]] = e;
    }

    i64 sum = 0;

    queue<string> q;
    q.push("you");

    while (!q.empty()) {
        string s = q.front();
        q.pop();

        if (s == "out") {
            sum++;
            continue;
        }

        for (string e : g[s])
            q.push(e);
    }

    // ==== part two ====

    i64 sum2 = dfs("svr", false, false);

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}
