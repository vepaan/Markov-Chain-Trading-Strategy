#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

class MarkovChain {
private:
    unordered_map<double, unordered_map<double, long long>> chain;
    long long size;

public:
    MarkovChain() {
        cout << "Created new chain" << endl;
        size = 0;
    }

    long long len() {
        return size;
    }

    void insert(double state1, double state2) {
        if (chain.find(state1) == chain.end()) {
            cout << "Inserted new state pair" << endl;
            size += 1;
        }
        chain[state1][state2] += 1;
    }

    double probableNext(double state) {
        if (chain.find(state) == chain.end()) {
            cout << "State doesn't exist in chain" << endl;
            return -1;
        } else {
            tuple<double, long long> runningMax = make_tuple(0, 0);
            for (auto &c: chain[state]) {
                if (c.second > get<1>(runningMax)) {
                    runningMax = make_tuple(c.first, c.second);
                }
            }
            return get<0>(runningMax);
        }
    }
};

int main() {
    MarkovChain chain;
    cout << chain.len() << endl;
    chain.insert(-2.5, 5.6);
    chain.insert(-2.5, 4.0);
    chain.insert(-2.5, 5.6);

    cout << chain.len() << endl;
    cout << chain.probableNext(-2.5) << endl;
    return 0;
}