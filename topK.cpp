#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include "consts.h"
#include "topK.h"

void getTopK() {
    // using priority queue to maintain heap
    auto cmp = [](pair<string, long long> &a, pair<string, long long> &b)-> bool { return a.second > b.second; };
    priority_queue<pair<string, long long>, vector<pair<string, long long> >, decltype(cmp) > que(cmp);
    for (int i = 0; i < PARTITION_NUMBER; i++) {
        string const in_file_dir = string(COUNT_DIR) + to_string(i);
        ifstream in_file(in_file_dir);

        string line, url;
        long long count;
        while (getline(in_file, line) && !line.empty()) {
            istringstream iss(line);
            iss >> url >> count;
            // not reach topK, then add
            if (que.size() < TOPK) {
                que.push(pair<string, long long>(url, count));
            } else if (count > que.top().second) {
                // if bigger than the smallest in heap, pop the smallest and add the number
                que.pop();
                que.push(pair<string, long long>(url, count));
            }
        }
        in_file.close();
    }

    // reverse the queue to sort by occurrence descend
    stack<pair<string, long long> > st;
    while (!que.empty()) {
        st.push(que.top());
        que.pop();
    }

    // write to file
    ofstream out_file(OUTPUT_DIR, ios::out);
    while (!st.empty()) {
        auto itr = st.top();
        out_file << itr.first << " " << itr.second << endl;
        st.pop();
    }
    out_file.close();
}
