#include <immintrin.h>
#include <sys/random.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int get_random_std() {
    return rand() % 200;
}

int get_random_rdrand() {
    unsigned int ret;

    int rc = _rdrand32_step(&ret);

    if (rc == 1)
        return ret;
    else
        return -1;
}

int get_random_dev_urandom() {
    int ret, read;

    FILE *urandom = fopen("/dev/urandom", "r");

    read = fread(&ret, sizeof(ret), 1, urandom);

    fclose(urandom);

    if (read > 0)
        return ret;
    else
        return -1;
}

int get_random_getrandom() {
    int ret, read;

    read = getrandom(&ret, sizeof(ret), 0);

    if (read > 0)
        return ret;
    else
        return read;
}

int get_random(int (*random_func)()) {
    return random_func() % 200;
}

typedef int (*fp)();

int main() {
    int n;

    cout << "Please enter a number" << endl;
    cin >> n;

    uint32_t rnd;

    srand((unsigned)time(NULL));

    vector<fp> randoms = {get_random_getrandom, get_random_dev_urandom, get_random_rdrand, get_random_std};

    for (int i = 0; i <= 5; i++) {
        if (get_random(randoms[i % 4]) == 150) {
            n += 1;
        } else {
            i--;
        }
    }

    cout << "Your number + 5 is: " << n << endl;

    return 0;
}
