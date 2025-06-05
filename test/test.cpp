#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <set>

#include "../src/AVL.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Example Test Name - Change me!", "[flag]"){
	// instantiate any class members that you need to test here
	int one = 1;

	// anything that evaluates to false in a REQUIRE block will result in a failing test 
	REQUIRE(one == 1); // fix me!

	// all REQUIRE blocks must evaluate to true for the whole test to pass
	REQUIRE(true); // also fix me!
}

TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
	int one = 1;

	// testing again
	// committing something from vs code into the actual github
	//triple checking if committing works for reals

	SECTION("num is 2") {
		int num = one + 1;
		REQUIRE(num == 2);
	};

	SECTION("num is 3") {
		int num = one + 2;
		REQUIRE(num == 3);
	};

	// each section runs the setup code independently to ensure that they don't affect each other
}

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

// the provided test from the template is below.

TEST_CASE("Example BST Insert", "[flag]"){
	/*
		MyAVLTree tree;   // Create a Tree object
		tree.insert(3);
		tree.insert(2);
		tree.insert(1);
		std::vector<int> actualOutput = tree.inorder();
		std::vector<int> expectedOutput = {1, 2, 3};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
	*/
}

// THE GREAT DIVIDE

TEST_CASE("Invalid insert and command handling", "[validation]") {
    AVL tree;

    std::vector<std::pair<std::string, std::string>> invalidInputs = {
        {"A11y", "12345678"},   // Name with numbers
        {"John", "1234567"},    // UFID too short
        {"Jane", "123456789"},  // UFID too long
        {"", "12345678"},       // Empty name
        {"Mary@", "87654321"},  // Invalid character
        {"Alice", "abcdefg1"},  // UFID not numeric
        {"Bob", "1234567a"},    // UFID with letter
        {" Chris", "8765432@"}  // Space and special char in UFID
    };

    for (const auto& [name, ufid] : invalidInputs) {
        std::string result = tree.insert(name, ufid);
        REQUIRE(result == "unsuccessful");
    }
}

TEST_CASE("AVL insert with all rotations", "[rotation]") {
    AVL tree;

    SECTION("Right Rotation (LL)") {
        tree.insert("A", "33334444");
        tree.insert("B", "22223333");
        tree.insert("C", "11112222");
        auto inorder = tree.printInorder();
        std::vector<std::string> expected = {"C", "B", "A"};
        std::sort(expected.begin(), expected.end());
        std::sort(inorder.begin(), inorder.end());
        REQUIRE(inorder == expected);
    }

    SECTION("Left Rotation (RR)") {
        AVL tree2;
        tree2.insert("A", "11112222");
        tree2.insert("B", "22223333");
        tree2.insert("C", "33334444");
        auto inorder = tree2.printInorder();
        std::vector<std::string> expected = {"A", "B", "C"};
        REQUIRE(inorder == expected);
    }

    SECTION("Left-Right Rotation (LR)") {
        AVL tree3;
        tree3.insert("A", "33334444");
        tree3.insert("C", "11112222");
        tree3.insert("B", "22223333");
        auto inorder = tree3.printInorder();
        std::vector<std::string> expected = {"C", "B", "A"};
        std::sort(expected.begin(), expected.end());
        std::sort(inorder.begin(), inorder.end());
        REQUIRE(inorder == expected);
    }

    SECTION("Right-Left Rotation (RL)") {
        AVL tree4;
        tree4.insert("A", "11112222");
        tree4.insert("C", "33334444");
        tree4.insert("B", "22223333");
        auto inorder = tree4.printInorder();
        std::vector<std::string> expected = {"A", "B", "C"};
        REQUIRE(inorder == expected);
    }
}

TEST_CASE("Insert 100 nodes, remove 10, and verify in-order", "[bulk]") {
    AVL tree;
    std::set<std::string> ufidSet;
    std::vector<std::string> allNames;
    std::vector<std::string> allUFIDs;

    // Insert 100 unique students
    for (int i = 0; i < 100; ++i) {
        std::string name = "Student" + std::to_string(i);
        std::string ufid;

        do {
            int id = 10000000 + rand() % 90000000;
            ufid = std::to_string(id);
        } while (!ufidSet.insert(ufid).second); // ensure uniqueness

        tree.insert(name, ufid);
        allNames.push_back(name);
        allUFIDs.push_back(ufid);
    }

    // Pick 10 random UFIDs to delete
    std::vector<std::string> toRemove;
    std::sample(allUFIDs.begin(), allUFIDs.end(), std::back_inserter(toRemove), 10, std::mt19937{std::random_device{}()});

    for (const std::string& ufid : toRemove) {
        std::string result = tree.remove(ufid);
        REQUIRE(result == "successful");
        auto found = tree.searchByID(ufid);
        REQUIRE(found == "unsuccessful");
    }

    // Check total node count = 90
    REQUIRE(tree.printLevelCount() >= 1);  // just a check that the tree is still valid
    auto inorder = tree.printInorder();
    REQUIRE(inorder.size() == 90);
}
