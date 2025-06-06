#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <cstdlib>

#include "../src/AVL.h"

using namespace std;

// Andres Chavez, 26934004

TEST_CASE("Invalid insert and command handling", "[validation]") {
    AVL tree;

    vector<pair<string, string>> invalidInputs = {
        make_pair("Carl0s", "26934004"),     // Name with numbers
        make_pair("John", "2693400"),      // UFID too short
        make_pair("Jane", "269340044"),    // UFID too long
        make_pair("", "26934004"),         // Empty name
        make_pair("TheBest!", "26934004"),    // Invalid character
        make_pair("Suisei", "notnum24"),    // UFID not numeric
        make_pair("Okayu", "2693400a"),      // UFID with letter
        make_pair(" Chris", "269340@4")    // Space and special char in UFID
    };

    for (size_t i = 0; i < invalidInputs.size(); ++i) {
        string name = invalidInputs[i].first;
        string ufid = invalidInputs[i].second;
        string result = tree.insert(name, ufid);
        REQUIRE(result == "unsuccessful");
    }
}

TEST_CASE("AVL insert with all rotations", "[rotation]") {
    AVL tree;

    SECTION("Right Rotation (LL)") {
        tree.insert("A", "33334444");
        tree.insert("B", "22223333");
        tree.insert("C", "11112222");
        vector<string> inorder = tree.printInorder();
        vector<string> expected = {"C", "B", "A"};
        sort(expected.begin(), expected.end());
        sort(inorder.begin(), inorder.end());
        REQUIRE(inorder == expected);
    }

    SECTION("Left Rotation (RR)") {
        AVL tree2;
        tree2.insert("A", "11112222");
        tree2.insert("B", "22223333");
        tree2.insert("C", "33334444");
        vector<string> inorder = tree2.printInorder();
        vector<string> expected = {"A", "B", "C"};
        REQUIRE(inorder == expected);
    }

    SECTION("Left-Right Rotation (LR)") {
        AVL tree3;
        tree3.insert("A", "33334444");
        tree3.insert("C", "11112222");
        tree3.insert("B", "22223333");
        vector<string> inorder = tree3.printInorder();
        vector<string> expected = {"C", "B", "A"};
        sort(expected.begin(), expected.end());
        sort(inorder.begin(), inorder.end());
        REQUIRE(inorder == expected);
    }

    SECTION("Right-Left Rotation (RL)") {
        AVL tree4;
        tree4.insert("A", "11112222");
        tree4.insert("C", "33334444");
        tree4.insert("B", "22223333");
        vector<string> inorder = tree4.printInorder();
        vector<string> expected = {"A", "B", "C"};
        REQUIRE(inorder == expected);
    }
}

TEST_CASE("Insert 100 nodes, remove 10, and verify in-order", "[bulk]") {
    AVL tree;
    set<string> ufidSet;
    vector<string> allNames;
    vector<string> allUFIDs;

    // Inserting 100 unique students
    for (int i = 0; i < 100; ++i) {
        string name = "Student" + to_string(i);
        string ufid;

        do {
            int id = 10000000 + rand() % 90000000; // thank you cstdlib
            ufid = to_string(id);
        } while (!ufidSet.insert(ufid).second); // somehow found a way to make sure they are unique, a little excessive but o well

        tree.insert(name, ufid);
        allNames.push_back(name);
        allUFIDs.push_back(ufid);
    }

    // picking 10 specifics of the 100 unique students
    vector<string> toRemove;
    toRemove.push_back(allUFIDs[5]);
    toRemove.push_back(allUFIDs[12]);
    toRemove.push_back(allUFIDs[23]);
    toRemove.push_back(allUFIDs[34]);
    toRemove.push_back(allUFIDs[40]);
    toRemove.push_back(allUFIDs[51]);
    toRemove.push_back(allUFIDs[66]);
    toRemove.push_back(allUFIDs[72]);
    toRemove.push_back(allUFIDs[88]);
    toRemove.push_back(allUFIDs[95]);

    for (size_t i = 0; i < toRemove.size(); ++i) {
        string ufid = toRemove[i];
        string result = tree.remove(ufid);
        REQUIRE(result == "successful");
        string found = tree.searchByID(ufid);
        REQUIRE(found == "unsuccessful");
    }

    // Check that the total node count is 90
    REQUIRE(tree.printLevelCount() >= 1);  // just a check that the tree is still valid
    vector<string> inorder = tree.printInorder();
    REQUIRE(inorder.size() == 90);
}
