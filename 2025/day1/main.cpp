#include "aoc.hpp"

int main(int argc, char *argv[])
{
    vector<string> lines = read_lines("data/data.txt");

    for (string line : lines)
        cout << line << '\n';

    return 0;
}
