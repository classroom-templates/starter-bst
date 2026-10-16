# Assignment 7 — Binary Search Tree Analysis

## Instructions

Complete all ten questions.

Each question is worth **1 point** for a total of **10 points**.

Partial credit may be awarded for answers that are incomplete but demonstrate correct understanding.

Your answers must be based on the **actual `BinTree` design and implementation used in this assignment**, not generic definitions copied from another source.

Use your code, the supplied tests, the Binary Tree Algorithms handout, and the Recursion and Tree lectures as references.

Answer directly below each question.

---

## 1. The Meaning of `root` in Recursion — 1 point

In the public methods, `root` refers to the root of the entire tree.

In the private recursive overloads, the parameter representing `root` may instead refer to the root of a subtree.

Explain why this distinction matters.

Your answer should describe what happens to the meaning of `root` as a recursive call moves left or right through the tree.

### Answer



---

## 2. Algorithm Description vs. C++ Implementation — 1 point

The Binary Tree Algorithms handout sometimes describes an algorithm using several conceptual return points, such as:

- return false if the subtree is empty;
- return true if the value is found;
- otherwise return the result of a recursive call.

Your C++ implementation is still expected to follow the course single-return policy.

Explain why these two ideas are not contradictory.

### Answer



---

## 3. Why BST Operations Are `O(h)` — 1 point

For this assignment, search, insertion, and removal follow the Binary Search Tree ordering rule.

Explain why the time complexity of these operations is more accurately described as:

\[
O(h)
\]

where `h` is the height of the tree.

Then explain when that behaves like:

\[
O(\log n)
\]

and when it degrades to:

\[
O(n)
\]

### Answer



---

## 4. Insertion Order, Shape, and Height — 1 point

Your `testTreeShapeAndHeight()` function is intended to demonstrate that two trees can contain the same number of Nodes but have very different shapes and heights.

Explain how insertion order affects tree shape.

Compare the expected height of:

- a reasonably balanced tree; and
- a completely skewed tree containing the same number of Nodes.

Then explain how that difference affects search performance.

### Answer



---

## 5. Duplicate IDs — 1 point

This assignment allows duplicate IDs.

The required rule is:

> if the new ID is equal to the current Node's ID, insert it into the right subtree.

Explain why a consistent duplicate-placement rule is necessary.

Then explain what effect this rule has on:

- inorder traversal order;
- `contains()`;
- `getNode()`; and
- repeated calls to `removeNode()` for the same ID.

### Answer



---

## 6. Two Ways to Change a Subtree Root — 1 point

This assignment uses two different techniques for recursive subtree modification.

Insertion may use:

```cpp
bool addNode(Node*, Node*&);
```

while deletion uses:

```cpp
Node* removeNode(int, Node*);
```

Explain how each technique allows a recursive operation to change the root pointer of a subtree.

Then explain the main conceptual difference between:

- modifying the caller's pointer through `Node*&`; and
- returning the new subtree root and assigning it in the caller.

### Answer



---

## 7. Two-Child Deletion — 1 point

Deleting a Node with two children requires more work than deleting a leaf or a Node with one child.

Explain the algorithm used in this assignment for the two-child case.

Your answer must explain:

- what the inorder successor is;
- where it is found;
- why its Data can replace the Data in the Node being deleted; and
- why deleting the original successor Node is guaranteed to reduce to a simpler deletion case.

### Answer



---

## 8. Why `minValueNode()` Is Iterative — 1 point

Most of the important tree operations in this assignment use recursion, but `minValueNode()` is intentionally iterative.

Explain why an iterative implementation is reasonable for this helper.

Compare iterative and recursive versions in terms of:

- time complexity;
- auxiliary space / call-stack use; and
- readability or engineering simplicity.

### Answer



---

## 9. Traversal Order and Purpose — 1 point

Preorder, inorder, and postorder traversals all visit every Node in the tree, but they visit the current Node at different points relative to the recursive calls.

For each traversal:

- state the visit order;
- explain one useful property or use case.

Your answer must also explain why inorder traversal of this Binary Search Tree produces IDs in nondecreasing order.

### Answer



---

## 10. What Your Two Student-Written Tests Demonstrate — 1 point

You were required to complete:

```cpp
testDeletionCases()
testTreeShapeAndHeight()
```

Explain what each test is intended to demonstrate about Binary Search Tree behavior.

Your answer should explain why these are specifically **BST / tree-structure tests**, rather than merely generic ADT tests.

### Answer
