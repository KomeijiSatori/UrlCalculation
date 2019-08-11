#include <fstream>
#include <unordered_map>
#include "consts.h"
using namespace std;

void getPartitionUrlCount(ifstream &, ofstream &);


unordered_map<string, long long> url_count_map;

void getCount() {
    // get count for each partition file
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        string const in_file_dir = string(PARTITION_DIR) + to_string(i);
        string const out_file_dir = string(COUNT_DIR) + to_string(i);
        ifstream in_file(in_file_dir);
        ofstream out_file(out_file_dir, ios::app);
        getPartitionUrlCount(in_file, out_file);
        // clean map to get another partition's info
        url_count_map.clear();
        in_file.close();
        out_file.close();
    }
}

void getPartitionUrlCount(ifstream &in_file, ofstream &out_file) {
    string url;
    while (getline(in_file, url) && !url.empty()) {
        url_count_map[url]++;
    }
    for (const auto &itr : url_count_map) {
        out_file << itr.first << " " << itr.second << endl;
    }
}
