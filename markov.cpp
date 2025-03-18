#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

class MarkovChain {
private:
    unordered_map<double, unordered_map<double, long long>> chain;
    unordered_map<double, tuple<double, long long>> next; // stores the most probable next state
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

            tuple<double, long long> tpl = make_tuple(state2, 1);
            next[state1] = tpl;
        }

        chain[state1][state2] += 1;
        long long curr = chain[state1][state2];
        tuple<double, long long> tpl = next[state1];

        if (curr > get<1>(tpl)) {
            tpl = make_tuple(state2, curr);
            next[state1] = tpl;
        }
    }

    double probableNext(double state) {
        if (chain.find(state) == chain.end()) {
            cout << "State doesn't exist in chain" << endl;
            return -1;
        } else {
            tuple<double, long long> curr = next[state];
            return get<0>(curr);
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