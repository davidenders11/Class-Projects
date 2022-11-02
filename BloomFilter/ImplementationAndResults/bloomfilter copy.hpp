#ifndef BLOOMFILTER_HPP_INCLUDED
#define BLOOMFILTER_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class BloomFilter {
  public:
    BloomFilter(int n, double p);
    void insert(string x);
    bool lookup(string x);
    double probFP();
  private:
    string generateSuffix(int length);
    vector<bool> bitSet_; // the bloom filter data
    int numValues_; // count n of strings to be inputted
    double falseP_; // desired probability of false positive
    int numBits_; // how many bits to use to store n strings
    int numHashes_; // how many hash functions to use 
    vector<string> suffixes_; // for appending to each input string to simulate different hash functions
};

BloomFilter::BloomFilter(int n, double p) :
      numValues_{n},
      falseP_{p} {
        numHashes_ = ceil(log2(1/falseP_));
        numBits_ = ceil(1/log(2) * numHashes_ * numValues_);
        bitSet_ = vector<bool>(numBits_, 0);
        // fill suffixes array with random strings of different length
        for (int k = 0; k < numHashes_; ++k) {
          suffixes_.push_back(generateSuffix(k));
        }
}

void BloomFilter::insert(string x) {
  for (int hf = 0; hf < numHashes_; ++hf) { 
    string toHash = x.append(suffixes_[hf]);
    int bucket = hash<string>{}(toHash) % numBits_; // generate numHashes hashes
    bitSet_[bucket] = 1; // set numHashes bits for each string
  }
  
}

bool BloomFilter::lookup(string x) {
  for (int hf = 0; hf < numHashes_; ++hf) { 
    string toHash = x.append(suffixes_[hf]);
    int bucket = hash<string>{}(toHash) % numBits_; // generate numHashes hashes
    if (bitSet_[bucket] == 0) {
      return false; // if any of the buckets is not set, string not in filter
    }
  }
  return true; // if they're all set, string probably in filter
}

double BloomFilter::probFP() {
  int setCount = 0;
  for (int i = 0; i < numBits_; ++i) {
    setCount+=bitSet_[i];
  }
  double fractionSet = (double) setCount / (double) numBits_;
  return pow(fractionSet, numHashes_);
}


// Adaptation of https://inversepalindrome.com/blog/how-to-create-a-random-string-in-cpp
string BloomFilter::generateSuffix(int length) {
  const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  random_device random_device;
  mt19937 generator(random_device());
  uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

  string random_string;

  for (size_t i = 0; i < length; ++i) {
      random_string += CHARACTERS[distribution(generator)];
  }

  return random_string;
}

#endif
