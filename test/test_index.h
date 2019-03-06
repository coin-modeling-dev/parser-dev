//
// Created by kingaj on 3/5/19.
//

#include <iostream>
#include <cassert>

#include "../src/utils/utils.h"
#include "../src/simplemodel/SimpleIndex.h"


using namespace std;
using namespace spdlog;

void testIndex(SimpleIndex &tensorIndex, const VectorUInt &t_indx, unsigned int DISPLAY = 0) {
    unsigned int n = tensorIndex.index(t_indx);
    auto v = tensorIndex.invIndex(n);
    for (int i = 0; i < t_indx.size(); ++i) {
        assert(v[i] == t_indx[i]);
    }
    if (!DISPLAY) return;
    int i = 0;
    cout << "[";
    for (; i < t_indx.size() - 1; ++i) {
        cout << t_indx[i] << ",";
    }
    cout << t_indx[t_indx.size() - 1];
    cout << "]";
    cout << " equals index " << n << "\n";
    cout << "index " << n << " equals ";
    string display = tensorIndex.display(n);
    cout << display;
    cout << "\n";
}

void testInvIndex(SimpleIndex &tensorIndex, unsigned int n, unsigned int DISPLAY = 0) {
    auto v = tensorIndex.invIndex(n);
    unsigned int m = tensorIndex.index(v);
    assert(m == n);

    if (!DISPLAY) return;
    cout << "index " << n << " equals ";
    cout << "[" << v[0];
    for (int i = 1; i < v.size() - 1; i++) {
        cout << "," << v[i];
    }
    cout << v[v.size() - 1];
    cout << "]\n";
    cout << tensorIndex.display(n);
    cout << " equals index " << n << "\n";

}

int testSimpleIndex(unsigned int DISPLAY = 0, shared_ptr<logger> logger = get("console")) {
    VectorUInt dims = {3, 5};
    SimpleIndex tensorIndex(dims);

    VectorUInt testVector = {2, 1};
    testIndex(tensorIndex, testVector);
    testInvIndex(tensorIndex, 14);

    bool success = false;

    try {
        testInvIndex(tensorIndex, 25);  // should fail
        success = false;
    }
    catch (runtime_error &error) {
        if (DISPLAY) cout << error.what() << endl;
        success = true;
    }

    try {
        VectorUInt vectorUInt = {2, 1, 4};
        testIndex(tensorIndex, vectorUInt); // should fail
        success = false;
    }
    catch (runtime_error &error1) {
        if (DISPLAY) cout << error1.what() << endl;
        success = true;
    }

    if (success) {
        logger->info("testSimpleIndex succeeded");
        return 0;
    } else {
        logger->critical("testSimpleIndex failed");
        return 1;
    }
}

