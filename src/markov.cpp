#include <iostream>
#include <unordered_map>
#include <pybind11/pybind11.h>

using namespace std;
namespace py = pybind11;

class MarkovChain {
private:
    unordered_map<double, unordered_map<double, long long>> chain;
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
        }

        chain[state1][state2] += 1;
    }

    double probableNextAggressive(double state) {
        if (chain.find(state) == chain.end()) {
            cout << "State doesn't exist in chain" << endl;
            return -1;
        } else {
            double res = 0;
            long long maxCount = 0;
            long long total = 0;

            for (auto &c: chain[state]) {
                maxCount = max(maxCount, c.second);
            }

            for (auto &c: chain[state]) {
                if (c.second == maxCount) {
                    res += (c.first);
                    total += 1;
                }
            }

            return res / total;
        }
    }

    double probableNextSafe(double state) {
        if (chain.find(state) == chain.end()) {
            cout << "State doesn't exist in chain" << endl;
            return -1;
        } else {
            double res = 0;
            double sum = 0;

            for (auto &c: chain[state]) {
                res += (c.first) * (c.second);
                sum += (c.second);
            }

            return res / sum;
        }
    }
};

PYBIND11_MODULE(markov, m) {
    py::class_<MarkovChain>(m, "MarkovChain")
        .def(py::init<>())
        .def("len", &MarkovChain::len)
        .def("insert", &MarkovChain::insert)
        .def("probableNextAggressive", &MarkovChain::probableNextAggressive)
        .def("probableNextSafe", &MarkovChain::probableNextSafe);
}