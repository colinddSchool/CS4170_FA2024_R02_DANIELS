#include <omp.h>
#include <random>

std::random_device rd;                           // only used once to initialise (seed) engine
std::mt19937 rng(rd());                          // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(0, 2000); // guaranteed unbiased

std::vector<int> generateList(int n){

    std::vector<int> retValue;
    srandom(time(NULL));
    for (int i = 0; i < n; i++){
        retValue.push_back(uni(rng));
    }

    return retValue;
}

int main(){

    return 0;
}


