/**
 * @file test.h
 * @author Alex Katrompas
 * @assignment Binary Search Tree
 * @brief Declares the BinTree testing module.
 */

#ifndef TEST_H
#define TEST_H

#include <sstream>
#include <string>
#include "bintree.h"

struct TestResult {
    int passed;
    int total;
};

// instructor test functions
void recordTest(bool, TestResult&);
bool matchesRecord(const BinTree&, int, const std::string&);

void testConstruction(TestResult&);
void testInitialState(BinTree&, TestResult&);
void testBasicInsertionAndRetrieval(BinTree&, TestResult&);
void testRejectedOperations(BinTree&, TestResult&);
void testDuplicateInsertion(BinTree&, TestResult&);
void testTraversals(BinTree&, TestResult&);
void testClearAndReuse(BinTree&, TestResult&);
void testScaledStress(BinTree&, TestResult&);

// student test functions
// COMPLETE THE FOLLOWING TEST FUNCTIONS IN test.cpp
void testDeletionCases(BinTree&, TestResult&);
void testTreeShapeAndHeight(BinTree&, TestResult&);

#endif // TEST_H
