# Assignment 7 — Binary Search Tree

## Overview

In this assignment, you will implement a **Binary Search Tree (BST)** as a recursive ADT.

This assignment brings together several major ideas from the course:

- recursion;
- dynamic memory;
- pointer ownership;
- interface versus implementation;
- private helper methods and overloads;
- algorithmic analysis;
- testing;
- tree structure and traversal.

The important challenge is not simply storing Nodes in sorted positions. You must learn to reason recursively about **subtrees**.

A recursive private helper may receive the true root of the entire tree on its first call, but after that, the parameter called `root` represents the root of the **current subtree**. Understanding that idea is central to this assignment.

---

# Background and Required References

Before beginning the assignment, review the following course material. These are the primary references for the design and algorithms used in this assignment:

- **Recursion lecture and notes, Part 1**
- **Recursion lecture and notes, Part 2**
- **Trees lecture and notes**
- **Binary Search Trees lecture and notes**
- **BST simple [example repo](https://github.com/alexander-katrompas/binary-search-tree-simple-example)**
- **BST Algorithms handout**

The example repository is intentionally simple. Use it to review basic BST structure and recursion, but do not treat it as a complete solution to this assignment.

The BST Algorithms handout gives conceptual algorithms and guidance. Remember:

> **Algorithm descriptions are not line-for-line source code.**

The handout may describe several conceptual return cases because that is often the clearest way to explain an algorithm. Your C++ implementation must still follow the course programming standards, including the **single-return policy for ordinary functions**.

---

# Files

The starter repository provides:

- `ASSIGNMENT.md`
- `ANALYSIS.md`
- `data.h`
- `main.cpp`
- `main.h`
- `test.cpp`
- `test.h`

You must create:

- `bintree.h`
- `bintree.cpp`
- `README.md`
- `.gitignore`

---

# Important: This Project Will Not Compile at First

The starter repository is intentionally incomplete.

That is not an error.

Your first development milestone should be:

1. inspect the supplied files;
2. determine the required `BinTree` interface;
3. create `bintree.h` and `bintree.cpp`;
4. write the required declarations;
5. create simple method stubs;
6. compile the entire project successfully;
7. **only then begin implementing the tree algorithms.**

Continue using the interface-first development process practiced throughout the course.

Your Git history will be inspected. It should show that you established the interface and achieved a complete compile before attempting the full algorithms.

---

# Data

The tree stores the supplied `Data` structure:

```cpp
struct Data {
    int id;
    std::string information;
};
```

Valid records require:

- `id > 0`
- non-empty `information`

Unlike several previous assignments, **duplicate IDs are allowed**.

Duplicate IDs must follow this rule:

> If the new ID is equal to the current Node's ID, insert the new Node into the **right subtree**.

Therefore the BST ordering rule for this assignment is:

```text
left subtree:  id < current id
right subtree: id >= current id
```

---

# Required Public Interface

Your `BinTree` class must provide **exactly** the following public interface:

```cpp
BinTree();
~BinTree();

bool isEmpty() const;
int getCount() const;
bool getRootData(Data&) const;

bool getNode(int, Data&) const;
bool contains(int) const;
int getHeight() const;

void clear();
bool addNode(int, const std::string&);
bool removeNode(int);

void displayPreOrder() const;
void displayPostOrder() const;
void displayInOrder() const;
void displayTree() const;
```

## No Other Public Methods

Do not add additional public methods.

Recursive implementation details belong in the private section of the class.

---

# Required Private Representation

`Node` must be a private structure inside `BinTree`.

```cpp
struct Node {
    Data data;
    Node* left;
    Node* right;
};
```

Your class must have **exactly** these two persistent attributes:

```cpp
Node* root;
int count;
```

Do not add:

- a parent pointer;
- a stored height;
- arrays;
- STL containers;
- additional persistent state.

The constructor must initialize:

```cpp
root = nullptr;
count = 0;
```

---

# Required Private Helpers

The recursive design requires private overloads of the public tree operations.

Your private section must include helpers equivalent to the following:

```cpp
void clear(Node*);

bool addNode(Node*, Node**);
// OR
bool addNode(Node*, Node*&);

Node* removeNode(int, Node*);

bool getNode(int, Data&, Node*) const;
bool contains(int, Node*) const;

int getHeight(Node*) const;

void displayPreOrder(Node*) const;
void displayPostOrder(Node*) const;
void displayInOrder(Node*) const;

Node* minValueNode(Node*) const;
```

For insertion, you may use either:

```cpp
Node**
```

or:

```cpp
Node*&
```

Both solve the same problem: allowing the recursive helper to modify the pointer that represents the root of a subtree.

The `removeNode()` overload uses a different technique. It returns the root pointer of the subtree after the removal attempt, and the caller assigns that result back into the appropriate subtree pointer.

You are expected to understand both approaches.

---

# Recursion Requirement

All operations that **traverse or structurally process the tree** must use recursion through the private overloads.

This includes:

- insertion;
- removal;
- search;
- retrieval;
- height calculation;
- clearing;
- preorder traversal;
- inorder traversal;
- postorder traversal.

Simple constant-time accessors such as `isEmpty()` and `getCount()` do not require recursion.

## Intentional Exception: `minValueNode()`

`minValueNode()` may remain iterative.

Its purpose is simply to follow one left-child path until the minimum Node is reached.

A recursive version is possible, but iteration is allowed and expected here because it performs the same `O(h)` work without adding `O(h)` recursive stack space.

You will analyze this design choice in `ANALYSIS.md`.

---

# Construction and Destruction

## Constructor

```cpp
BinTree();
```

Initialize:

```cpp
root = nullptr;
count = 0;
```

---

## Destructor

```cpp
~BinTree();
```

The destructor must call:

```cpp
clear();
```

The tree owns every Node that it dynamically allocates.

Every Node must be deleted exactly once.

---

# Required Behavior

## `isEmpty()`

```cpp
bool isEmpty() const;
```

Return whether `root` is null.

---

## `getCount()`

```cpp
int getCount() const;
```

Return the stored `count`.

Do not traverse the tree to calculate the count.

---

## `getRootData()`

```cpp
bool getRootData(Data&) const;
```

If the tree is not empty:

- copy the root's `Data` into the caller-owned object;
- return `true`.

If the tree is empty:

- return `false`;
- leave the caller's `Data` object unchanged.

---

# Insertion

## Public `addNode()`

```cpp
bool addNode(int, const std::string&);
```

The public method must:

1. validate the incoming data;
2. dynamically allocate and initialize a new Node;
3. call the private recursive overload;
4. increment `count` after successful insertion;
5. return the success status.

Return `false` when:

- `id <= 0`; or
- `information` is empty.

Duplicate IDs are valid.

---

## Private Recursive `addNode()`

Use either:

```cpp
bool addNode(Node*, Node**);
```

or:

```cpp
bool addNode(Node*, Node*&);
```

The recursive insertion algorithm must follow the BST rule:

```text
if new id < current id:
    recurse left
else:
    recurse right
```

The `else` includes duplicate IDs.

When the current subtree root is empty, attach the new Node there.

---

# Search and Retrieval

## `contains()`

```cpp
bool contains(int) const;
```

Validate the ID, then call the private recursive overload.

The recursive search should:

- return failure when the current subtree is empty;
- succeed when the ID matches the current Node;
- recurse left when the search ID is smaller;
- recurse right when the search ID is larger.

Only one root-to-leaf path should be searched.

---

## `getNode()`

```cpp
bool getNode(int, Data&) const;
```

This follows the same recursive search path as `contains()`.

If a matching Node is found:

- copy its `Data` into the caller-owned output object;
- return `true`.

If no matching Node is found:

- return `false`;
- leave the caller's `Data` object unchanged.

When duplicate IDs exist, `getNode()` returns the first matching Node encountered by the normal BST search.

---

# Height

## `getHeight()`

```cpp
int getHeight() const;
```

Height must be calculated dynamically each time this method is called.

Do not store height as an attribute.

Use this definition:

```text
empty tree height = 0
leaf height       = 1
```

The recursive relationship is:

```text
height(empty subtree) = 0

height(non-empty subtree) =
    max(height(left), height(right)) + 1
```

---

# Tree Traversals

You must implement all three recursive depth-first traversals.

## Preorder

```text
Node
Left
Right
```

## Inorder

```text
Left
Node
Right
```

Because duplicate IDs are always inserted right, inorder traversal must produce IDs in **nondecreasing order**.

## Postorder

```text
Left
Right
Node
```

Each displayed Node must use this format:

```text
id : information
```

Example:

```text
50 : fifty
```

---

# `displayTree()`

```cpp
void displayTree() const;
```

This method must display:

- tree count;
- tree height;
- root Data, or indicate that the tree is empty;
- preorder traversal;
- inorder traversal;
- postorder traversal.

`displayTree()` should delegate traversal work to the public traversal methods rather than duplicating traversal logic.

---

# Clearing the Tree

## Public `clear()`

```cpp
void clear();
```

The public method must:

1. call the private recursive `clear()` helper;
2. set `root` to `nullptr`;
3. set `count` to `0`.

The same `BinTree` object must remain reusable after clearing.

---

## Private Recursive `clear()`

```cpp
void clear(Node*);
```

Use postorder destruction:

```text
clear left subtree
clear right subtree
delete current Node
```

Children must be deleted before their parent.

---

# Removal

## Public `removeNode()`

```cpp
bool removeNode(int);
```

Return `false` for invalid or missing IDs.

A successful call removes **one** matching Node and decrements `count` exactly once.

When duplicate IDs exist, repeated calls to `removeNode(id)` should remove one matching Node at a time.

---

## Private Recursive `removeNode()`

```cpp
Node* removeNode(int, Node*);
```

The returned pointer represents:

> the root of this subtree after the removal attempt.

The caller must assign the result back into the appropriate subtree pointer.

Conceptually:

```cpp
root->left = removeNode(id, root->left);
```

or:

```cpp
root->right = removeNode(id, root->right);
```

and the public method ultimately updates the true tree root:

```cpp
root = removeNode(id, root);
```

---

## Deletion Cases

### Case 1 — No Children

Delete the Node.

The subtree becomes empty.

### Case 2 — One Child

Delete the Node.

Its child becomes the new root of that subtree.

### Case 3 — Two Children

Use the **inorder successor**.

The inorder successor is:

> the smallest Node in the current Node's right subtree.

The algorithm is:

1. find the inorder successor;
2. copy its `Data` into the Node being removed;
3. recursively remove the original successor Node from the right subtree.

The original successor cannot have a left child, so deleting it reduces to a zero-child or one-child case.

---

# `minValueNode()`

```cpp
Node* minValueNode(Node*) const;
```

This helper finds the minimum Node in a subtree by repeatedly following the left child.

It may be implemented iteratively.

Remember that because `Node` is a private nested type, the out-of-class definition will use the properly qualified return type:

```cpp
BinTree::Node* BinTree::minValueNode(Node* node) const
```

---

# Testing

There are **no autograding tests** because testing is part of the assignment.

The starter repository includes a testing architecture and a substantial set of completed tests.

The supplied tests cover:

- construction;
- empty-state behavior;
- insertion and retrieval;
- invalid operations;
- duplicate insertion and repeated duplicate removal;
- traversal output;
- `displayTree()`;
- clear and reuse;
- deterministic scaled stress behavior.

## Student-Written Tests

You must complete these two functions in `test.cpp`:

```cpp
void testDeletionCases(BinTree&, TestResult&);
void testTreeShapeAndHeight(BinTree&, TestResult&);
```

Their declarations are already provided in `test.h`.

### `testDeletionCases()`

Write meaningful tests that verify:

- leaf deletion;
- one-child deletion;
- two-child deletion;
- deletion that changes the root of the tree or a subtree;
- correct count maintenance;
- surviving data remains accessible after deletion.

### `testTreeShapeAndHeight()`

Write meaningful tests that demonstrate:

- insertion order changes tree shape;
- trees with the same number of Nodes can have different heights;
- a reasonably balanced tree has smaller height than a skewed tree;
- a deliberately skewed tree has the expected height.

### Testing Rules

For both student-written functions:

- establish the tree state needed by the test inside the function;
- do not depend on state left by an earlier test;
- initialize the supplied `TestResult&`;
- use the provided `recordTest()` helper;
- do not print test results from `test.cpp`;
- write a complete function comment block;
- remove the starter comments when your test is complete.

The supplied `main.cpp` will report a required student test as:

```text
INCOMPLETE
```

when that function records zero conditions.

If either required student test is incomplete, the final program summary will also report:

```text
Overall: INCOMPLETE
```

---

# Analysis

This assignment includes `ANALYSIS.md`.

Complete all ten questions.

Each question is worth **1 point**, for a total of **10 points**.

Partial credit may be awarded for incomplete answers that demonstrate correct understanding.

Your answers must analyze the actual `BinTree` design used in this assignment.

---

# Memory Verification

After the program works normally, build and run it with AddressSanitizer.

Example:

```bash
g++ -Wall -Wextra -pedantic -g -fsanitize=address \
    main.cpp test.cpp bintree.cpp -o bintree
```

Then run:

```bash
./bintree
```

The completed program must not produce:

- memory leaks;
- use-after-free errors;
- invalid reads or writes;
- double deletes.

Passing functional tests does not prove that dynamic memory ownership is correct.

---

# Git Requirements

Use Git throughout the assignment.

Your history should show meaningful development rather than one final bulk commit.

Commit as you reach real milestones: **small, smart, often**. and you must have at least **12 meaningful** code related commits.

Your commits should make the development sequence visible, including:

- interface creation;
- first complete compile;
- individual recursive operations;
- testing;
- debugging;
- completion of the two required student tests;
- completion of `ANALYSIS.md`.

**Your repository must contain at least 12 meaningful commits made during development.** Commits must represent real development milestones. Artificial commits created only to reach the minimum will not satisfy this requirement.

Do not manufacture meaningless commits merely to increase the count.

---

# Final Verification

Before submitting, verify all of the following:

- `bintree.h` and `bintree.cpp` exist;
- `README.md` and `.gitignore` exist;
- the project builds with the required compiler warnings enabled;
- all supplied and student-written tests pass;
- `testDeletionCases()` is complete and meaningful;
- `testTreeShapeAndHeight()` is complete and meaningful;
- `Node` is private;
- the only persistent attributes are `root` and `count`;
- constructor initializes `root` to `nullptr` and `count` to `0`;
- destructor calls `clear()`;
- invalid Data is rejected;
- duplicate IDs are accepted and routed right;
- traversal/search/structural operations use recursion as required;
- `minValueNode()` follows the required design;
- height is calculated dynamically;
- count is maintained correctly;
- deletion correctly handles zero-, one-, and two-child cases;
- `clear()` leaves the tree empty and reusable;
- output parameters remain unchanged on failed retrieval;
- AddressSanitizer reports no memory errors;
- `ANALYSIS.md` is complete;
- Git history shows meaningful interface-first development.

---

# Submission

Submit the URL of your completed GitHub repository in Blackboard.

Do not submit individual source files separately unless instructed to do so.
