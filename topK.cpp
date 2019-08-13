#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include "consts.h"
#include "heap.h"
#include "topK.h"

void getTopK() {
    // using priority queue to maintain heap
    auto cmp = [](pair<string, long long> const &a, pair<string, long long> const &b)-> bool { return a.second > b.second; };

    heap<pair<string, long long> > h(TOPK, cmp);
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        string const in_file_dir = string(COUNT_DIR) + to_string(i);
        ifstream in_file(in_file_dir);

        string line, url;
        long long count;
        while (getline(in_file, line) && !line.empty()) {
            istringstream iss(line);
            iss >> url >> count;
            auto cur = pair<string, long long>(url, count);
            h.add(cur);
        }
        in_file.close();
    }
    vector<pair<string, long long> > res = h.clearHeap();

    // write to file
    ofstream out_file(OUTPUT_DIR, ios::out);
    for (auto reco : res) {
        out_file << reco.first << " " << reco.second << endl;
    }
    out_file.close();
}
