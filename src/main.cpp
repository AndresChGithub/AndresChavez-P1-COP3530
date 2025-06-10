#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <cctype>

using namespace std;

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
    int commandCount;
    cin >> commandCount;
    cin.ignore();  // To skip the newline after the number

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
            int firstQuote = line.find('"');
            int lastQuote = line.rfind('"');
            if (firstQuote == string::npos || lastQuote == string::npos || firstQuote == lastQuote) {
                cout << "unsuccessful\n";
                continue;
            }

            name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

            ss.clear();
            ss.str(line.substr(lastQuote + 1));
            ss >> id;

            if (!isValidName(name) || !isValidUFID(id)) {
                cout << "unsuccessful\n";
                continue;
            }

            // insert(name, id); <-- implement this later
            cout << "successful\n";

        }
		else if (command == "remove") {
            string id;
            ss >> id;

            if (!isValidUFID(id)) {
                cout << "unsuccessful\n";
                continue;
            }

            // remove(arg); <-- implement this later
            cout << "successful\n";

        }
		else if (command == "search") {
            string remaining;
            getline(ss, remaining);
            int quoteStart = remaining.find('"');
            if (quoteStart != string::npos) {
                int quoteEnd = remaining.rfind('"');
                if (quoteEnd == string::npos || quoteEnd == quoteStart) {
                    cout << "unsuccessful\n";
                    continue;
                }
                string name = remaining.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                if (!isValidName(name)) {
                    cout << "unsuccessful\n";
                    continue;
                }
                // searchByName(name); <-- implement this later
                cout << "successful\n";
            } 
			else {
                string id;
                ss >> id;
                if (!isValidUFID(id)) {
                    cout << "unsuccessful\n";
                    continue;
                }
                // searchByID(id); <-- implement this later
                cout << "successful\n";
            }

        }
		else if (command == "printInorder" || command == "printPreorder" || 
                   command == "printPostorder" || command == "printLevelCount") {
            // Call corresponding function later
            cout << "successful\n";

        } 
		else if (command == "removeInorder") {
            int n;
            if (!(ss >> n)) {
                cout << "unsuccessful\n";
                continue;
            }
            // removeInorder(n); <-- implement this later
            cout << "successful\n";

        } 
		else {
            cout << "unsuccessful\n";
        }
    }

    return 0;
}
