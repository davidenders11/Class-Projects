#include "treestringset.hpp"
#include <iostream>
#include <cs70/testinglogger.hpp>
#include <sstream>

using namespace std;

bool testSizeNonEmpty() {
    TestingLogger log("Testing size() member function on non-empty tree");
    TreeStringSet testTree;
    testTree.insert("a");
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("d");
    affirm_expected(testTree.size(), 4);
    return log.summarize();
}

bool testSizeEmpty() {
    TestingLogger log("Testing size() member function on empty tree");
    TreeStringSet testTree;
    affirm_expected(testTree.size(), 0);
    return log.summarize();
}

bool testExistsEmpty() {
    TestingLogger log("Testing exists() member function on empty tree");
    TreeStringSet testTree;
    affirm_expected(testTree.exists("a"), false);
    return log.summarize();
}

bool testExistsFourElemTrue() {
    TestingLogger log("Testing exists() member function on tree w/ elem");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("d");
    testTree.insert("a");
    affirm(testTree.exists("a"));
    return log.summarize();
}

bool testExistsFourElemFalse() {
    TestingLogger log("Testing exists() member function on tree w/o elem");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("d");
    testTree.insert("a");
    affirm_expected(testTree.exists("e"), false);
    return log.summarize();
}

bool testPrintToStreamEmptyTree() {
    TestingLogger log("Testing print member functions on empty tree");
    TreeStringSet testTree;
    stringstream ss;
    ss << testTree;
    affirm_expected(testTree.size(), 0);
    affirm_expected(ss.str(), "-");
    return log.summarize();
}

bool testPrintToStreamOneElemTree() {
    TestingLogger log("Testing print member functions on tree with 1 elem");
    TreeStringSet testTree;
    testTree.insert("b");
    stringstream ss;
    ss << testTree;
    affirm_expected(testTree.size(), 1);
    affirm_expected(ss.str(), "(-, b, -)");
    return log.summarize();
}

bool testPrintToStreamNonEmptyTree() {
    TestingLogger log("Testing print member functions on tree with 4 elems");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("d");
    testTree.insert("a");
    affirm_expected(testTree.size(), 4);
    stringstream ss;
    ss << testTree;
    affirm_expected(ss.str(), "((-, a, -), b, (-, c, (-, d, -)))");
    return log.summarize();
}

bool testIteratorBegin() {
    TestingLogger log("Testing iterator constructor and begin()");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("d");
    testTree.insert("a");
    TreeStringSet::const_iterator iter = testTree.begin();
    affirm_expected(*iter, "a");
    return log.summarize();
}

bool testIteratorEnd() {
    TestingLogger log("Testing iterator end() and operator==");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    TreeStringSet::const_iterator iter = testTree.begin();
    TreeStringSet::const_iterator endIter = testTree.end();
    ++iter;
    ++iter;
    affirm(iter == endIter);
    return log.summarize();
}

bool testIteratorAssignment() {
    TestingLogger log("Testing iterator assignment");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    TreeStringSet::const_iterator iter = testTree.begin();
    TreeStringSet::const_iterator assignIter = testTree.end();
    assignIter = iter;
    // assignIter should now also be at begin
    affirm_expected(*assignIter, "b");
    return log.summarize();
}

bool testIteratorOperatorStar() {
    TestingLogger log("Testing iterator dereference");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    TreeStringSet::const_iterator iter = testTree.begin();
    affirm_expected(*iter, "b");
    ++iter;
    affirm_expected(*iter, "c");
    return log.summarize();
}

bool testIteratorEquals() {
    TestingLogger log("Testing iterator operator== and !=");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    TreeStringSet::const_iterator iter = testTree.begin();
    TreeStringSet::const_iterator notEqualsIter = testTree.end();
    TreeStringSet::const_iterator equalsIter = testTree.begin();
    affirm(iter != notEqualsIter);
    affirm(iter == equalsIter);
    ++iter;
    ++equalsIter;
    affirm(iter == equalsIter);
    return log.summarize();
}

bool testEqualsSameTree() {
    TestingLogger log("Testing operator== and != on same shape (equal) trees");
    TreeStringSet firstTree;
    firstTree.insert("b");
    firstTree.insert("c");
    TreeStringSet secondTree;
    secondTree.insert("b");
    secondTree.insert("c");
    affirm(firstTree == secondTree);
    return log.summarize();
}

bool testEqualsDiffShapeSameVals() {
    TestingLogger log("Testing operator== and != on diff shape (equal) trees");
    TreeStringSet firstTree;
    firstTree.insert("b");
    firstTree.insert("c");
    TreeStringSet secondTree;
    secondTree.insert("c");
    secondTree.insert("b");
    affirm(firstTree == secondTree);
    return log.summarize();
}

bool testNotEquals() {
    TestingLogger log("Testing operator== and != on different trees");
    TreeStringSet firstTree;
    firstTree.insert("b");
    firstTree.insert("c");
    TreeStringSet secondTree;
    secondTree.insert("d");
    secondTree.insert("a");
    affirm(firstTree != secondTree);
    return log.summarize();
}

bool avgDepthEmpty() {
    TestingLogger log("Testing avgDepth() on empty tree");
    TreeStringSet testTree;
    affirm(testTree.averageDepth() == 0.0);
    return log.summarize();
}

bool avgDepthOneNode() {
    TestingLogger log("Testing avgDepth() on one node tree");
    TreeStringSet testTree;
    testTree.insert("a");
    affirm(testTree.averageDepth() == 0.0);
    return log.summarize();
}

bool avgDepthMultiNode() {
    TestingLogger log("Testing avgDepth() on full tree");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("a");
    testTree.insert("d");
    testTree.insert("e");
    affirm(testTree.averageDepth() == 1.4);
    return log.summarize();
}

bool heightEmpty() {
    TestingLogger log("Testing height() on empty tree");
    TreeStringSet testTree;
    affirm_expected(testTree.height(), -1);
    return log.summarize();
}

bool heightOneNode() {
    TestingLogger log("Testing height() on one node tree");
    TreeStringSet testTree;
    testTree.insert("b");
    affirm_expected(testTree.height(), 0);
    return log.summarize();
}

bool heightStick() {
    TestingLogger log("Testing height() on stick tree");
    TreeStringSet testTree;
    testTree.insert("b");
    testTree.insert("c");
    testTree.insert("d");
    testTree.insert("e");
    affirm_expected(testTree.height(), 3);
    return log.summarize();
}

bool heightBalanced() {
    TestingLogger log("Testing height() on full tree");
    TreeStringSet testTree;
    testTree.insert("d");
    testTree.insert("b");
    testTree.insert("a");
    testTree.insert("c");
    testTree.insert("g");
    testTree.insert("f");
    testTree.insert("e");
    affirm_expected(testTree.height(), 3);
    return log.summarize();
}

bool testShowStatistics() {
    TestingLogger log("Testing showStatistics() on full tree");
    TreeStringSet testTree;
    testTree.insert("d");
    testTree.insert("b");
    testTree.insert("a");
    testTree.insert("c");
    testTree.insert("h");
    testTree.insert("g");
    testTree.insert("f");
    testTree.insert("e");
    affirm_expected(testTree.height(), 4);
    affirm_expected(testTree.averageDepth(), 1.875);
    stringstream ss;
    testTree.showStatistics(ss);
    affirm_expected(ss.str(), "8 nodes, height 4, average depth 1.875\n");
    return log.summarize();
}

int main() {
    TestingLogger alltests("All tests");
    // test size() member function
    testSizeNonEmpty();
    testSizeEmpty();

    // test exists() member func
    testExistsEmpty();
    testExistsFourElemTrue();
    testExistsFourElemFalse();

    // test printToStream() member func with insert() member func
    testPrintToStreamEmptyTree();
    testPrintToStreamOneElemTree();
    testPrintToStreamNonEmptyTree();

    // test iterator member funcs
    testIteratorBegin();
    testIteratorEnd();
    testIteratorAssignment();
    testIteratorOperatorStar();
    testIteratorEquals();

    // test operator== and != member funcs
    testEqualsSameTree();
    testEqualsDiffShapeSameVals();
    testNotEquals();

    // test avgDepth() and height()
    avgDepthEmpty();
    avgDepthOneNode();
    avgDepthMultiNode();
    heightEmpty();
    heightOneNode();
    heightStick();
    heightBalanced();
    testShowStatistics();

    if (alltests.summarize(true)) {
        return 0;  // Error code of 0 == Success!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
    }
}
