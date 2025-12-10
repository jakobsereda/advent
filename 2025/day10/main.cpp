#include "aoc.hpp"

struct Machine
{
    u32         lights;
    u32         lights_cnt;
    vector<u32> buttons;
    vector<u32> joltage;
    vector<u32> joltage_cnts;
};

i64 find_min_presses(const Machine &m)
{
    vector<i32> dist(1 << m.lights_cnt, -1);
    dist[0] = 0;

    queue<i32> q;
    q.push(0);

    while (!q.empty()) {
        i32 state = q.front();
        q.pop();
        i32 d = dist[state];
        if (state == m.lights)
            return d;
        for (u32 b : m.buttons) {
            u32 n = state ^ b;
            if (dist[n] < 0) {
                dist[n] = d + 1;
                q.push(n);
            }
        }
    }

    return 0;
}

i64 find_min_presses2(const Machine &m)
{
    return 0;
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    i64 n = lines.size();

    vector<Machine> machines(n);
    for (size_t i = 0; i < n; i++) {
        vector<string> v;
        stringstream ss(lines[i]);
        string s;
        while (getline(ss, s, ' '))
            v.push_back(s);

        u32 lights = 0;
        string raw_lights = v[0];
        for (size_t j = 1; j < raw_lights.length() - 1; j++)
            lights |= (raw_lights[j] == '#' ? 1 : 0) << (j - 1);
        u32 lights_cnt = raw_lights.length() - 2;

        vector<u32> buttons;
        for (size_t j = 1; j < v.size() - 1; j++) {
            u32 wires = 0;
            stringstream ss2(v[j].substr(1, v[j].size() - 2));
            string s2;
            while (getline(ss2, s2, ','))
                wires |= 1 << stoi(s2);
            buttons.push_back(wires);
        }

        vector<u32> joltage;
        string raw_joltage = v[v.size() - 1];
        stringstream ss3(raw_joltage.substr(1, raw_joltage.size() - 2));
        string s3;
        while (getline(ss3, s3, ','))
            joltage.push_back(stoi(s3));
        vector<u32> joltage_cnts(joltage.size(), 0);

        machines[i] = Machine {
            .lights       = lights,
            .lights_cnt   = lights_cnt,
            .buttons      = buttons,
            .joltage      = joltage,
            .joltage_cnts = joltage_cnts
        };
    }

    i64 sum = 0;
    for (Machine m : machines)
        sum += find_min_presses(m);

    // ==== part two ====

    i64 sum2 = 0;
    for (Machine m : machines)
        sum2 += find_min_presses2(m);

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}
