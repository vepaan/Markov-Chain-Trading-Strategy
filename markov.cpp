#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

class MarkovChain {
private:
    unordered_map<double, unordered_map<double, long long>> chain;
    unordered_map<double, tuple<double, long long>> next; // stores the most probable next state
    unordered_map<double, long long> sums; // sums for weighted average
    long long size;

public:
    MarkovChain() {
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

        sums[state1] += 1;
    }

    double probableNextAggresive(double state) {
        if (chain.find(state) == chain.end()) {
            cout << "State doesn't exist in chain" << endl;
            return -1;
        }
        return get<0>(next[state]);
    }

    double probableNextSafe(double state) {
        if (chain.find(state) == chain.end()) {
            cout << "State doesn't exist in chain" << endl;
            return -1;
        } else {
            double res;
            for (auto &c: chain[state]) {
                res += (c.first) * (c.second) / (sums[state]);
            }
            return res;
        }
    }
};

int main() {
    MarkovChain chain;
    cout << chain.len() << endl;
    chain.insert(-2.5, 5.6);
    chain.insert(-2.5, 4.0);
    chain.insert(-2.5, 4.0);
    chain.insert(-2.5, 4.0);
    chain.insert(-2.5, 5.6);

    cout << chain.len() << endl;
    cout << chain.probableNextAggresive(-2.5) << endl;
    cout << chain.probableNextSafe(-2.5) << endl;
    return 0;
}