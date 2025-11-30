#include <bits/stdc++.h>

using namespace std;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

int main(int argc, char *argv[])
{
    ifstream file("data/data.txt");
    string   s;
    string   data;

    while (getline(file, s)) {
        data += s;
        data.push_back('\n');
    }
    
    return 0;
}
