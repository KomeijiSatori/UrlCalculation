#include <fstream>
#include <unordered_map>
#include "consts.h"
#include "heap.h"
using namespace std;

void getPartitionUrlCount(ifstream &);
void savePartitionUrlCount(ofstream &, vector<pair<string, long long> > &);


unordered_map<string, long long> url_count_map;

void getCount() {
    // get count for each partition file
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        string const in_file_dir = string(PARTITION_DIR) + to_string(i);
        string const out_file_dir = string(COUNT_DIR) + to_string(i);
        ifstream in_file(in_file_dir);
        ofstream out_file(out_file_dir, ios::out);
        getPartitionUrlCount(in_file);

        auto cmp = [](pair<string, long long> const &a, pair<string, long long> const &b)-> bool { return a.second > b.second; };
        heap<pair<string, long long> > h(TOPK, cmp);
        for (auto const &itr : url_count_map) {
            auto cur = pair<string, long long>(itr.first, itr.second);
            h.add(cur);
        }
        vector<pair<string, long long> > res = h.clearHeap();
        savePartitionUrlCount(out_file, res);
        // clean map to get another partition's info
        url_count_map.clear();
        in_file.close();
        out_file.close();
    }
}

void getPartitionUrlCount(ifstream &in_file) {
    string url;
    while (getline(in_file, url) && !url.empty()) {
        url_count_map[url]++;
    }
}

void savePartitionUrlCount(ofstream &out_file, vector<pair<string, long long> > &res) {
    for (const auto &itr : res) {
        out_file << itr.first << " " << itr.second << endl;
    }
}
