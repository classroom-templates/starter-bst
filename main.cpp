/**
 * @file main.cpp
 * @author Alex Katrompas
 * @assignment Binary Search Tree
 * @brief Application driver for the BinTree test suite.
 */

#include "main.h"

int main() {

    int status = 0;
    bool incomplete = false;
    TestResult result = {0, 0};
    TestResult overall = {0, 0};
    BinTree tree;

    std::cout << "Binary Search Tree Tests" << std::endl;
    std::cout << "========================" << std::endl;

    testConstruction(result);
    std::cout << "Construction: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testInitialState(tree, result);
    std::cout << "Initial state: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testBasicInsertionAndRetrieval(tree, result);
    std::cout << "Insertion and retrieval: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    std::cout << std::endl;
    std::cout << "Visual tree verification" << std::endl;
    std::cout << "Expected count: 7" << std::endl;
    std::cout << "Expected height: 3" << std::endl;
    std::cout << "Expected root: 50 : fifty" << std::endl;
    std::cout << std::endl;
    tree.displayTree();
    std::cout << std::endl;

    testRejectedOperations(tree, result);
    std::cout << "Rejected operations: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testDuplicateInsertion(tree, result);
    std::cout << "Duplicate insertion: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testTraversals(tree, result);
    std::cout << "Traversals and display: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testDeletionCases(tree, result);

    if (result.total == 0) {
        std::cout << "Deletion cases: INCOMPLETE" << std::endl;
        incomplete = true;
        status = 1;
    } else {
        std::cout << "Deletion cases: "
                  << result.passed << "/" << result.total
                  << " passed" << std::endl;
        overall.passed += result.passed;
        overall.total += result.total;
    }

    testClearAndReuse(tree, result);
    std::cout << "Clear and reuse: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testTreeShapeAndHeight(tree, result);

    if (result.total == 0) {
        std::cout << "Tree shape and height: INCOMPLETE" << std::endl;
        incomplete = true;
        status = 1;
    } else {
        std::cout << "Tree shape and height: "
                  << result.passed << "/" << result.total
                  << " passed" << std::endl;
        overall.passed += result.passed;
        overall.total += result.total;
    }

    testScaledStress(tree, result);
    std::cout << "Scaled stress: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    std::cout << std::endl;

    if (incomplete) {
        std::cout << "Overall: INCOMPLETE" << std::endl;
        std::cout << "Completed tests: "
                  << overall.passed << "/" << overall.total
                  << " passed" << std::endl;
    } else {
        std::cout << "Overall: "
                  << overall.passed << "/" << overall.total
                  << " passed" << std::endl;
    }

    if (overall.passed != overall.total) {
        status = 1;
    }

    return status;
}
