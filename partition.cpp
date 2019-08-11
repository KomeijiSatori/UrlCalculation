#include <fstream>
#include <vector>
#include "consts.h"
#include "partition.h"

using namespace std;


int const getMaxUrlCount();
int getPartitionNumber(string &);
void savePartitions(ofstream *);
void clearPartitions();


vector<string> partitions[PARTITION_NUMBER];

void getPartitions() {
    ifstream in_file(INPUT_DIR);
    // create output objects
    ofstream out_files[PARTITION_NUMBER];
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        string const file_dir = string(PARTITION_DIR) + to_string(i);
        out_files[i].open(file_dir, ios_base::app);
    }

    string url;
    int cur_count = 0;
    int const max_count = getMaxUrlCount();
    // read every line of the origin file
    while (getline(in_file, url) && !url.empty()) {
        // use hash function to get the partition number
        int partition_ind = getPartitionNumber(url);
        partitions[partition_ind].push_back(url);
        cur_count++;
        // if url count reach near the memory limit, shuffle to disk
        if (cur_count >= max_count) {
            savePartitions(out_files);
            // clear memory to avoid memory limit exceeds
            clearPartitions();
            cur_count = 0;
        }
    }
    // save the remain urls
    if (cur_count > 0) {
        savePartitions(out_files);
        clearPartitions();
    }

    // close all outputs
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        out_files[i].close();
    } 

}

// assume the max url count is the max memory divide max url length, can be even smaller to avoid memory limit exceed
int const getMaxUrlCount() {
    return MAX_MEMORY / MAX_URL_LENGTH;
}

// the hash function to determine which partition the url belongs to
int getPartitionNumber(string &s) {
    int number = 0;
    // if number overflows, it doesn't matter, it will mode partition number
    for (const char &ch : s) {
        number += ch * ch;
    }
    return number % PARTITION_NUMBER;
}

// save parition files to disk
void savePartitions(ofstream *out_files) {
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        for (string const &s: partitions[i]) {
            out_files[i] << s << endl;
        }
    }
}

// clear memory
void clearPartitions() {
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        partitions[i].clear();
    }
}
