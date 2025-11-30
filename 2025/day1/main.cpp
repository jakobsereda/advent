#include <bits/stdc++.h>

using namespace std;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

int main(int argc, char *argv[])
{
    if (argc > 2) {
        cout << "failure" << '\n';
        return 1;
    }

    for (u16 i = 0; i < atoi(argv[1]); i++)
        cout << i << '\n';
    
    return 0;
}
