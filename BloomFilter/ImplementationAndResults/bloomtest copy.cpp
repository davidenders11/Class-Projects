
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
#include "bloomfilter.hpp"
using namespace std;


int main(int argc, char** argv) {
    // Parse command-line arguments
    if (argc != 4)
    {
        // Wrong number of command-line arguments. Print message and quit
        cout << "usage: " << argv[0] << "  <numInserts> <falseProb> <numTrials>]\n";
        return -1;
    }
    // Convert argument n from ascii string to a number (using base 10)
    int numStr = stoi(argv[1]);

    // Convert argument fp from ascii string to a number (using base 10).
    double falseP = stod(argv[2]);

    // Convert arg. numTrials to int
    int numTri = stoi(argv[3]);


    // Create array of numStr strings to insert into the bloom filter
    vector<string> strs;
    for (int i = 0; i < numStr; ++i) {
        strs.push_back(to_string(i));
    }

    // Initialize bloom filter numTri times
    for (int tri = 0; tri < numTri; ++tri) {
        BloomFilter filt(numStr, falseP);
        for (int i = 0; i < numStr; ++i) {
            filt.insert(to_string(i)); // insert numStr strings (just integers converted to strings)
        }
        // Inserts done for this filter: print how many inserts, how long it should've taken, how long it took
        cout << "Inserts: \t" << numStr << "\t Desired FP: \t" << falseP << "\t True FP: \t" << filt.probFP() << endl;
    }
}