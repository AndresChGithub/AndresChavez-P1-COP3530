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
                    cout << "unsuccessful" << endl;
                    continue;
                }

                name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                ss.clear();
                ss.str(line.substr(lastQuote + 1));
                ss >> id;

                if (!isValidName(name) || !isValidUFID(id)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                cout << tree.insert(name, id) << endl;

            }

            else if (command == "remove") {
                string id;
                ss >> id;

                if (!isValidUFID(id)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                cout << tree.remove(id) << endl;

            }

            else if (command == "search") {
                string nextToken;
                ss >> nextToken;

                if (nextToken.front() == '"') {
                    // search NAME
                    size_t firstQuote = line.find('"');
                    size_t lastQuote = line.rfind('"');

                    if (firstQuote == string::npos || lastQuote == string::npos || firstQuote == lastQuote) {
                        cout << "unsuccessful" << endl;
                        continue;
                    }

                    string name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                    if (!isValidName(name)) {
                        cout << "unsuccessful" << endl;
                        continue;
                    }

                    vector<string> results = tree.searchByName(name);
                    if (results.empty()) {
                        cout << "unsuccessful" << endl;
                    } 

                    else {
                        for (const auto& id : results) {
                            cout << id << endl;
                        }
                    }
                } 

                else {
                    // search ID
                    string id = nextToken;

                    if (!isValidUFID(id)) {
                        cout << "unsuccessful" << endl;
                        continue;
                    }

                    cout << tree.searchByID(id) << endl;
                }
            }

            else if (command == "printInorder") {
                vector<string> names = tree.printInorder();

                for (size_t i = 0; i < names.size(); ++i) {
                    cout << names[i];
                    if (i != names.size() - 1)
                        cout << ", ";
                }

                cout << endl;

            }

            else if (command == "printPreorder") {
                vector<string> names = tree.printPreorder();

                for (size_t i = 0; i < names.size(); ++i) {
                    cout << names[i];
                    if (i != names.size() - 1)
                        cout << ", ";
                }

                cout << endl;
            }

            else if (command == "printPostorder") {
                vector<string> names = tree.printPostorder();

                for (size_t i = 0; i < names.size(); ++i) {
                    cout << names[i];
                    if (i != names.size() - 1)
                        cout << ", ";
                }

                cout << endl;
            }

            else if (command == "printLevelCount") {
                cout << tree.printLevelCount() << endl;
            }

            else if (command == "removeInorder") {
                int n;
                ss >> n;
                if (tree.removeInorder(n))
                    cout << "successful" << endl;
                else
                    cout << "unsuccessful" << endl;
            }

            else {
                cout << "unsuccessful\n";
            }

        }

    }

    return 0;
}
