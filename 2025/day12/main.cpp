#include "aoc.hpp"

struct Present {
    vector<vector<bool>> shape;
};

struct Region {
    i64         width;
    i64         height;
    vector<i64> quantities;
};

bool can_fit_presents(Region r, vector<Present> p)
{
    i64 sum = 0;
    for (i64 i : r.quantities)
        sum += i;
    i64 wd = r.width / 3;
    i64 hd = r.height / 3;
    return sum <= (wd * hd);
}

int main(void)
{
    vector<string> lines = read_lines("data/data.txt");

    vector<Present> presents;
    vector<Region>  regions;
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i].find('x') == string::npos) {
            i++;
            vector<vector<bool>> shape;
            while (!lines[i].empty()) {
                vector<bool> vb;
                for (size_t j = 0; j < lines[i].length(); j++)
                    vb.push_back(lines[i][j] == '#');
                shape.push_back(vb);
                i++;
            }
            presents.emplace_back(shape);
        } else {
            i64 w = stoi(lines[i].substr(0, 2));
            i64 h = stoi(lines[i].substr(3, 2));
            string rest = lines[i].substr(7);
            vector<i64> q;
            stringstream ss(rest);
            string s;
            while (getline(ss, s, ' '))
                q.push_back(stoi(s));
            regions.emplace_back(w, h, q);
        }
    }

    i64 sum = 0;
    for (Region r : regions)
        if (can_fit_presents(r, presents))
            sum++;
    
    cout << "Part one: " << sum << '\n';

    return 0;
}
