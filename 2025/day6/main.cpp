#include "aoc.hpp"

enum Op { plus, mult };

bool not_done(const vector<char> &v)
{
    for (char c : v)
        if (c != ' ')
            return true;
    return false;
}

i32 convert_to_num(const vector<char> &v)
{
    i32 ret = 0;
    i32 mul = 1;
    for (i32 i = v.size() - 1; i >= 0; i--) {
        if (v[i] != ' ') {
            ret += mul * (v[i] - '0');
            mul *= 10;
        }
    }
    return ret;
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<vector<string>> broken;
    for (string line : lines) {
        vector<string> b;
        istringstream iss(line);
        string s;
        while (iss >> s)
            b.push_back(s);
        broken.push_back(b);
    }

    i32 r = broken.size();
    i32 c = broken[0].size();
    vector<vector<string>> rotated(c);
    for (size_t dc = 0; dc < c; dc++)
        for (size_t dr = 0; dr < r; dr++)
            rotated[dc].push_back(broken[dr][dc]);
    
    i32 n = rotated.size();

    vector<pair<vector<i32>, Op>> problems(n);
    for (size_t i = 0; i < n; i++) {
        Op o = rotated[i][r - 1] == "*"
            ? Op::mult
            : Op::plus;
        vector<i32> v(r - 1);
        for (size_t j = 0; j < r - 1; j++)
            v[j] = stoi(rotated[i][j]);
        problems[i] = { v, o };
    }

    i64 sum = 0;
    for (auto p : problems) {
        if (p.second == Op::plus) {
            for (i32 i : p.first)
                sum += i;
        } else {
            i64 tmp = 1;
            for (i32 i : p.first)
                tmp *= i;
            sum += tmp;
        }
    }

    // ==== part two ====

    i32 rows = lines[0].length();
    i32 cols = lines.size() - 1;

    vector<Op> ops;
    vector<vector<char>> grid(rows, vector<char>(cols));

    for (string s : broken[broken.size() - 1]) {
        if (s == "*")
            ops.push_back(Op::mult);
        else
            ops.push_back(Op::plus);
    }

    for (i32 i = rows - 1; i >= 0; i--)
        for (i32 j = 0; j < cols; j++)
            grid[i][j] = lines[j][i];

    vector<vector<i32>> nums;
    i32 i = 0;
    while (i < rows) {
        vector<i32> v;
        while (i < rows && not_done(grid[i])) {
            v.push_back(convert_to_num(grid[i]));
            i++;
        }
        nums.push_back(v);
        i++;
    }

    i64 sum2 = 0;
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] == Op::plus) {
            for (i32 num : nums[i])
                sum2 += num;
        } else {
            i64 tmp = 1;
            for (i32 num : nums[i])
                tmp *= num;
            sum2 += tmp;
        }
    }

    // ==================

    cout << "Part one: " << sum << '\n';
    cout << "Part two: " << sum2 << '\n';

    return 0;
}
