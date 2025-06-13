#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <cctype>
#include "AVL.h"

using namespace std;

// need this functions to validate inputs
bool isValidName(const string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ')
            return false;
    }

    return true;
}

bool isValidUFID(const string& id) {
    if (id.length() != 8)
        return false;

    for (char ch : id) {
        if (!isdigit(ch))
            return false;
    }

    return true;
}

int main() {
    AVL tree;
    int commandCount;
    vector<string> outputLines; // need to print all my outputs at the end to pass the autograder

    while (cin >> commandCount) {
        
        cin.ignore(); // To skip the newline after the number
    

        for (int i = 0; i < commandCount; ++i) {
            string line;
            getline(cin, line);

            istringstream ss(line);
            string command;
            ss >> command;

            if (command == "insert") {
                string name;
                string id;

                // Parse name (surrounded by quotes)
                size_t firstQuote = line.find('"');
                size_t lastQuote = line.rfind('"');
                if (firstQuote == string::npos || lastQuote == string::npos || firstQuote == lastQuote) {
                    outputLines.push_back("unsuccessful");
                    continue;
                }

                name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                ss.clear();
                ss.str(line.substr(lastQuote + 1));
                ss >> id;

                if (!isValidName(name) || !isValidUFID(id)) {
                    outputLines.push_back("unsuccessful");
                    continue;
                }

                outputLines.push_back(tree.insert(name, id));

            }

            else if (command == "remove") {
                string id;
                ss >> id;

                if (!isValidUFID(id)) {
                    outputLines.push_back("unsuccessful");
                    continue;
                }

                outputLines.push_back(tree.remove(id));

            }

            else if (command == "search") {
                string nextToken;
                ss >> nextToken;

                if (nextToken.front() == '"') {
                    // search NAME
                    size_t firstQuote = line.find('"');
                    size_t lastQuote = line.rfind('"');

                    if (firstQuote == string::npos || lastQuote == string::npos || firstQuote == lastQuote) {
                        outputLines.push_back("unsuccessful");
                        continue;
                    }

                    string name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                    if (!isValidName(name)) {
                        outputLines.push_back("unsuccessful");
                        continue;
                    }

                    vector<string> results = tree.searchByName(name);
                    if (results.empty()) {
                        outputLines.push_back("unsuccessful");
                    } 

                    else {

                        for (const auto& id : results) {
                            outputLines.push_back(id);
                        }

                    }
                } 

                else {
                    // search ID
                    string id = nextToken;

                    if (!isValidUFID(id)) {
                        outputLines.push_back("unsuccessful");
                        continue;
                    }

                    outputLines.push_back(tree.searchByID(id));

                }
            }

            else if (command == "printInorder") {
                vector<string> names = tree.printInorder();
                string result;

                for (size_t i = 0; i < names.size(); ++i) {
                    result += names[i];
                    if (i != names.size() - 1)
                        result += ", ";
                }

                outputLines.push_back(result);

            }

            else if (command == "printPreorder") {
                vector<string> names = tree.printPreorder();
                string result;

                for (size_t i = 0; i < names.size(); ++i) {
                    result += names[i];
                    if (i != names.size() - 1)
                        result += ", ";
                }

                outputLines.push_back(result);

            }

            else if (command == "printPostorder") {
                vector<string> names = tree.printPostorder();
                string result;

                for (size_t i = 0; i < names.size(); ++i) {
                    result += names[i];
                    if (i != names.size() - 1)
                        result += ", ";
                }

                outputLines.push_back(result);

            }

            else if (command == "printLevelCount") {
                outputLines.push_back(to_string(tree.printLevelCount()));
            }

            else if (command == "removeInorder") {
                int n;
                ss >> n;
                if (tree.removeInorder(n))
                    outputLines.push_back("successful");
                else
                    outputLines.push_back("unsuccessful");
            }

            else {
                outputLines.push_back("unsuccessful");
            }

        }

    }

    for (const string& line : outputLines) {
        cout << line << endl;
    }

    return 0;
}
