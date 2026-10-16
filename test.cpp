/**
 * @file test.cpp
 * @author Alex Katrompas
 * @assignment Binary Search Tree
 * @brief Implements the BinTree testing module.
 */

#include "test.h"

/**
 * @brief Records the result of one test condition.
 * @param condition The condition being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note This function does not print test results.
 */
void recordTest(bool condition, TestResult& result) {

    result.total++;

    if (condition) {
        result.passed++;
    }
}

/**
 * @brief Checks whether a stored BinTree record matches expected data.
 * @param tree A reference to the BinTree being tested.
 * @param id The expected id.
 * @param information The expected information.
 * @exception none
 * @return true when one matching record is found with the expected data.
 * @note When duplicate ids exist, getNode returns the first matching record
 *       encountered by the BST search.
 */
bool matchesRecord(const BinTree& tree, int id, const std::string& information) {

    bool matches = false;
    Data result = {-1, "unchanged"};

    if (tree.getNode(id, result)) {
        matches = result.id == id && result.information == information;
    }

    return matches;
}

/**
 * @brief Tests constructor behavior using local BinTree objects.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note Each newly constructed tree should be empty with count and height zero.
 */
void testConstruction(TestResult& result) {

    result.passed = 0;
    result.total = 0;

    BinTree first;
    recordTest(first.isEmpty(), result);
    recordTest(first.getCount() == 0, result);
    recordTest(first.getHeight() == 0, result);

    Data unchanged = {-1, "unchanged"};
    recordTest(!first.getRootData(unchanged), result);
    recordTest(unchanged.id == -1 && unchanged.information == "unchanged", result);

    BinTree second;
    recordTest(second.isEmpty(), result);
    recordTest(second.getCount() == 0, result);
    recordTest(second.getHeight() == 0, result);
}

/**
 * @brief Tests the initial empty state and failure behavior.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note This test establishes its own empty starting state.
 */
void testInitialState(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    Data rootData = {-1, "unchanged"};
    Data data = {-1, "unchanged"};

    recordTest(tree.isEmpty(), result);
    recordTest(tree.getCount() == 0, result);
    recordTest(tree.getHeight() == 0, result);
    recordTest(!tree.getRootData(rootData), result);
    recordTest(rootData.id == -1 && rootData.information == "unchanged", result);

    recordTest(!tree.contains(10), result);
    recordTest(!tree.contains(0), result);
    recordTest(!tree.contains(-10), result);

    recordTest(!tree.getNode(10, data), result);
    recordTest(data.id == -1 && data.information == "unchanged", result);

    recordTest(!tree.removeNode(10), result);
    recordTest(!tree.removeNode(0), result);

    tree.clear();
    recordTest(tree.isEmpty(), result);
    recordTest(tree.getCount() == 0, result);
}

/**
 * @brief Tests balanced insertion, retrieval, search, count, root data, and height.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note This test leaves the seven-Node tree 50,25,75,10,30,60,90.
 */
void testBasicInsertionAndRetrieval(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    std::string fifty = "fifty";
    std::string twentyFive = "twenty-five";
    std::string seventyFive = "seventy-five";
    std::string ten = "ten";
    std::string thirty = "thirty";
    std::string sixty = "sixty";
    std::string ninety = "ninety";

    recordTest(tree.addNode(50, fifty), result);
    recordTest(tree.addNode(25, twentyFive), result);
    recordTest(tree.addNode(75, seventyFive), result);
    recordTest(tree.addNode(10, ten), result);
    recordTest(tree.addNode(30, thirty), result);
    recordTest(tree.addNode(60, sixty), result);
    recordTest(tree.addNode(90, ninety), result);

    recordTest(!tree.isEmpty(), result);
    recordTest(tree.getCount() == 7, result);
    recordTest(tree.getHeight() == 3, result);

    Data rootData = {-1, "unchanged"};
    recordTest(tree.getRootData(rootData), result);
    recordTest(rootData.id == 50 && rootData.information == fifty, result);

    recordTest(tree.contains(50), result);
    recordTest(tree.contains(25), result);
    recordTest(tree.contains(75), result);
    recordTest(tree.contains(10), result);
    recordTest(tree.contains(30), result);
    recordTest(tree.contains(60), result);
    recordTest(tree.contains(90), result);

    recordTest(matchesRecord(tree, 50, fifty), result);
    recordTest(matchesRecord(tree, 25, twentyFive), result);
    recordTest(matchesRecord(tree, 75, seventyFive), result);
    recordTest(matchesRecord(tree, 10, ten), result);
    recordTest(matchesRecord(tree, 30, thirty), result);
    recordTest(matchesRecord(tree, 60, sixty), result);
    recordTest(matchesRecord(tree, 90, ninety), result);

    Data unchanged = {-1, "unchanged"};
    recordTest(!tree.getNode(999, unchanged), result);
    recordTest(unchanged.id == -1 && unchanged.information == "unchanged", result);
}

/**
 * @brief Tests invalid insertions and invalid or missing operations.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note Duplicate ids are valid and are tested separately.
 */
void testRejectedOperations(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    std::string fifty = "fifty";
    std::string valid = "valid";
    std::string empty = "";

    recordTest(tree.addNode(50, fifty), result);
    recordTest(tree.getCount() == 1, result);

    recordTest(!tree.addNode(0, valid), result);
    recordTest(!tree.addNode(-10, valid), result);
    recordTest(!tree.addNode(20, empty), result);

    recordTest(tree.getCount() == 1, result);
    recordTest(tree.getHeight() == 1, result);
    recordTest(matchesRecord(tree, 50, fifty), result);

    Data unchanged = {-1, "unchanged"};
    recordTest(!tree.getNode(0, unchanged), result);
    recordTest(!tree.getNode(-1, unchanged), result);
    recordTest(!tree.getNode(999, unchanged), result);
    recordTest(unchanged.id == -1 && unchanged.information == "unchanged", result);

    recordTest(!tree.contains(0), result);
    recordTest(!tree.contains(-1), result);
    recordTest(!tree.contains(999), result);

    recordTest(!tree.removeNode(0), result);
    recordTest(!tree.removeNode(-1), result);
    recordTest(!tree.removeNode(999), result);
    recordTest(tree.getCount() == 1, result);
}

/**
 * @brief Tests duplicate-id insertion and repeated removal of duplicate keys.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note Equal ids are expected to be inserted into the right subtree.
 */
void testDuplicateInsertion(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    std::string fiftyA = "fifty-a";
    std::string twentyFive = "twenty-five";
    std::string seventyFive = "seventy-five";
    std::string fiftyB = "fifty-b";
    std::string fiftyC = "fifty-c";

    recordTest(tree.addNode(50, fiftyA), result);
    recordTest(tree.addNode(25, twentyFive), result);
    recordTest(tree.addNode(75, seventyFive), result);
    recordTest(tree.addNode(50, fiftyB), result);
    recordTest(tree.addNode(50, fiftyC), result);

    recordTest(tree.getCount() == 5, result);
    recordTest(tree.getHeight() == 4, result);
    recordTest(matchesRecord(tree, 50, fiftyA), result);

    std::ostringstream capture;
    std::streambuf* original = std::cout.rdbuf(capture.rdbuf());
    tree.displayInOrder();
    std::cout.rdbuf(original);

    std::string expected =
        "25 : twenty-five\n"
        "50 : fifty-a\n"
        "50 : fifty-b\n"
        "50 : fifty-c\n"
        "75 : seventy-five\n";

    recordTest(capture.str() == expected, result);

    recordTest(tree.removeNode(50), result);
    recordTest(tree.getCount() == 4, result);
    recordTest(tree.contains(50), result);
    recordTest(matchesRecord(tree, 50, fiftyB), result);

    recordTest(tree.removeNode(50), result);
    recordTest(tree.getCount() == 3, result);
    recordTest(tree.contains(50), result);
    recordTest(matchesRecord(tree, 50, fiftyC), result);

    recordTest(tree.removeNode(50), result);
    recordTest(tree.getCount() == 2, result);
    recordTest(!tree.contains(50), result);
    recordTest(!tree.removeNode(50), result);
}

/**
 * @brief Tests preorder, inorder, postorder, and displayTree output.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note The test captures std::cout so the test module itself does not report results.
 */
void testTraversals(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    std::string fifty = "fifty";
    std::string twentyFive = "twenty-five";
    std::string seventyFive = "seventy-five";
    std::string ten = "ten";
    std::string thirty = "thirty";
    std::string sixty = "sixty";
    std::string ninety = "ninety";

    tree.addNode(50, fifty);
    tree.addNode(25, twentyFive);
    tree.addNode(75, seventyFive);
    tree.addNode(10, ten);
    tree.addNode(30, thirty);
    tree.addNode(60, sixty);
    tree.addNode(90, ninety);

    std::ostringstream capture;
    std::streambuf* original = std::cout.rdbuf(capture.rdbuf());

    tree.displayPreOrder();
    std::cout.rdbuf(original);

    std::string preorder =
        "50 : fifty\n"
        "25 : twenty-five\n"
        "10 : ten\n"
        "30 : thirty\n"
        "75 : seventy-five\n"
        "60 : sixty\n"
        "90 : ninety\n";

    recordTest(capture.str() == preorder, result);

    capture.str("");
    capture.clear();
    original = std::cout.rdbuf(capture.rdbuf());
    tree.displayInOrder();
    std::cout.rdbuf(original);

    std::string inorder =
        "10 : ten\n"
        "25 : twenty-five\n"
        "30 : thirty\n"
        "50 : fifty\n"
        "60 : sixty\n"
        "75 : seventy-five\n"
        "90 : ninety\n";

    recordTest(capture.str() == inorder, result);

    capture.str("");
    capture.clear();
    original = std::cout.rdbuf(capture.rdbuf());
    tree.displayPostOrder();
    std::cout.rdbuf(original);

    std::string postorder =
        "10 : ten\n"
        "30 : thirty\n"
        "25 : twenty-five\n"
        "60 : sixty\n"
        "90 : ninety\n"
        "75 : seventy-five\n"
        "50 : fifty\n";

    recordTest(capture.str() == postorder, result);

    capture.str("");
    capture.clear();
    original = std::cout.rdbuf(capture.rdbuf());
    tree.displayTree();
    std::cout.rdbuf(original);

    std::string output = capture.str();
    recordTest(output.find("Tree count: 7\n") != std::string::npos, result);
    recordTest(output.find("Tree height: 3\n") != std::string::npos, result);
    recordTest(output.find("Root: 50 : fifty\n") != std::string::npos, result);
    recordTest(output.find("Preorder:\n") != std::string::npos, result);
    recordTest(output.find("Inorder:\n") != std::string::npos, result);
    recordTest(output.find("Postorder:\n") != std::string::npos, result);
}

/**
 * @brief Tests clear on populated and empty trees and reuse after clearing.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note This test establishes its own starting state.
 */
void testClearAndReuse(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    std::string forty = "forty";
    std::string twenty = "twenty";
    std::string sixty = "sixty";

    tree.addNode(40, forty);
    tree.addNode(20, twenty);
    tree.addNode(60, sixty);

    recordTest(tree.getCount() == 3, result);
    recordTest(tree.getHeight() == 2, result);

    tree.clear();

    recordTest(tree.isEmpty(), result);
    recordTest(tree.getCount() == 0, result);
    recordTest(tree.getHeight() == 0, result);
    recordTest(!tree.contains(40), result);
    recordTest(!tree.contains(20), result);
    recordTest(!tree.contains(60), result);

    Data unchanged = {-1, "unchanged"};
    recordTest(!tree.getRootData(unchanged), result);
    recordTest(unchanged.id == -1 && unchanged.information == "unchanged", result);

    tree.clear();

    recordTest(tree.isEmpty(), result);
    recordTest(tree.getCount() == 0, result);

    std::string fifteen = "fifteen";
    std::string five = "five";
    std::string twentyFive = "twenty-five";

    recordTest(tree.addNode(15, fifteen), result);
    recordTest(tree.addNode(5, five), result);
    recordTest(tree.addNode(25, twentyFive), result);

    recordTest(tree.getCount() == 3, result);
    recordTest(tree.getHeight() == 2, result);
    recordTest(matchesRecord(tree, 15, fifteen), result);
    recordTest(matchesRecord(tree, 5, five), result);
    recordTest(matchesRecord(tree, 25, twentyFive), result);
}

/**
 * @brief Performs deterministic large-scale insertion, retrieval, removal, and reuse tests.
 * @param tree A reference to the BinTree being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note This test establishes an empty starting state and finishes empty.
 */
void testScaledStress(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    tree.clear();

    const int TEST_SIZE = 200;

    recordTest(tree.isEmpty(), result);
    recordTest(tree.getCount() == 0, result);

    for (int i = 0; i < TEST_SIZE; i++) {
        int id = ((i * 73) % TEST_SIZE) + 1;
        std::string information = "record-" + std::to_string(id);
        recordTest(tree.addNode(id, information), result);
    }

    recordTest(tree.getCount() == TEST_SIZE, result);
    recordTest(tree.getHeight() > 0, result);
    recordTest(tree.getHeight() <= TEST_SIZE, result);

    for (int id = 1; id <= TEST_SIZE; id++) {
        std::string information = "record-" + std::to_string(id);
        recordTest(tree.contains(id), result);
        recordTest(matchesRecord(tree, id, information), result);
    }

    std::string valid = "valid";
    std::string empty = "";

    recordTest(!tree.addNode(0, valid), result);
    recordTest(!tree.addNode(-1, valid), result);
    recordTest(!tree.addNode(TEST_SIZE + 1, empty), result);
    recordTest(tree.getCount() == TEST_SIZE, result);

    for (int i = 0; i < TEST_SIZE; i++) {
        int id = ((i * 97) % TEST_SIZE) + 1;
        recordTest(tree.removeNode(id), result);
        recordTest(!tree.contains(id), result);
    }

    recordTest(tree.isEmpty(), result);
    recordTest(tree.getCount() == 0, result);
    recordTest(tree.getHeight() == 0, result);
    recordTest(!tree.removeNode(1), result);

    std::string five = "five";
    recordTest(tree.addNode(5, five), result);
    recordTest(tree.getCount() == 1, result);
    recordTest(tree.contains(5), result);

    tree.clear();
    recordTest(tree.isEmpty(), result);
}


// write your comment function block here
void testDeletionCases(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    // Write your own tests here. Establish the tree state you need inside this
    // function. Verify deletion of a leaf, a one-child Node, and a two-child
    // Node. Include at least one case where deleting a Node changes the root of
    // the tree or of a subtree. Verify count and surviving data after deletion.
    // Erase this comment when you are done.
}


// write your comment function block here
void testTreeShapeAndHeight(BinTree& tree, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    // Write your own tests here. Establish the tree state you need inside this
    // function. Build trees with the same number of Nodes but different insertion
    // orders. Demonstrate that insertion order changes tree shape and height.
    // Include a deliberately skewed tree and verify its expected height.
    // Erase this comment when you are done.
}
