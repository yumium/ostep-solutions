/* 
Program exploring TLB levels of your machine
Usage:
- Compile with optimisation disabled
    g++ -O0 ./vm-tlb.cpp
- Run by pinning the thread to a single core
    taskset 1 ./a.ou 10 1000000000

TODO:
- Have a think on precision of timer
- Explore why there's no jump on my machine (poke around on TLB size, coverage etc.)
*/

#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int PAGESIZE = sysconf(_SC_PAGESIZE);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Please provide exactly 2 arguments" << endl;
        return 1;
    }

    cout << "Page size: " << PAGESIZE << endl;

    int jump = PAGESIZE / sizeof(int);
    
    int page_cnt = atoi(argv[1]);
    int trial_cnt = atoi(argv[2]);
    int repeat = trial_cnt / page_cnt;

    int N = page_cnt * jump;
    int a [N] = {};

    timeval start;
    timeval end;

    gettimeofday(&start, NULL);
    for (int cnt = 0; cnt < repeat; cnt++) 
        for (int i = 0; i < N; i += jump)
            a[i] += 1;
    gettimeofday(&end, NULL);

    double diff_micros = (end.tv_sec - start.tv_sec) * 1'000'000 + (end.tv_usec - start.tv_usec);
    cout << diff_micros * 1'000 / trial_cnt << endl; // result in ns
}