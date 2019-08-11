#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "partition.h"
#include "count.h"
#include "topK.h"
using namespace std;

int main() {
    // prepare input file
    vector<string> s_vec;
    for (int i = 1; i <= 26; i++) {
        for (int j = 1; j <= i; j++) {
            s_vec.push_back("https://" + to_string(i) + "/");
        }
    }
    
    auto rng = default_random_engine {};
    std::shuffle(begin(s_vec), end(s_vec), rng);

    ofstream out_file("input/input.txt", ios::out);
    for (string const &s : s_vec) {
        out_file << s << endl;
    }

    // run main logic
    getPartitions();
    getCount();
    getTopK();

    // check the result
    ifstream in_file("output/output.txt");
    string line;
    int num = 26;
    while (getline(in_file, line) && !line.empty()) {
        string desire = "https://" + to_string(num) + "/ " + to_string(num);
        num--;
        if (desire != line) {
            exit(-1);
        }
    }
    return 0;
}
