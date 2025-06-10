#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <cctype>

bool isValidName(const std::string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ')
            return false;
    }
    return true;
}

bool isValidUFID(const std::string& id) {
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
    std::cin >> commandCount;
    std::cin.ignore();  // To consume the newline after the number

    for (int i = 0; i < commandCount; ++i) {
        std::string line;
        getline(std::cin, line);

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "insert") {
            std::string name;
            std::string id;

            // Parse name (surrounded by quotes)
            size_t firstQuote = line.find('"');
            size_t lastQuote = line.rfind('"');
            if (firstQuote == std::string::npos || lastQuote == std::string::npos || firstQuote == lastQuote) {
                std::cout << "unsuccessful\n";
                continue;
            }

            name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

            ss.clear();
            ss.str(line.substr(lastQuote + 1));
            ss >> id;

            if (!isValidName(name) || !isValidUFID(id)) {
                std::cout << "unsuccessful\n";
                continue;
            }

            // insert(name, id); <-- implement this later
            std::cout << "successful\n";

        } else if (command == "remove") {
            std::string arg;
            ss >> arg;

            if (!isValidUFID(arg)) {
                std::cout << "unsuccessful\n";
                continue;
            }

            // remove(arg); <-- implement this later
            std::cout << "successful\n";

        } else if (command == "search") {
            std::string remaining;
            getline(ss, remaining);
            size_t quoteStart = remaining.find('"');
            if (quoteStart != std::string::npos) {
                size_t quoteEnd = remaining.rfind('"');
                if (quoteEnd == std::string::npos || quoteEnd == quoteStart) {
                    std::cout << "unsuccessful\n";
                    continue;
                }
                std::string name = remaining.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                if (!isValidName(name)) {
                    std::cout << "unsuccessful\n";
                    continue;
                }
                // searchByName(name); <-- implement this later
                std::cout << "successful\n";
            } else {
                std::string id;
                ss >> id;
                if (!isValidUFID(id)) {
                    std::cout << "unsuccessful\n";
                    continue;
                }
                // searchByID(id); <-- implement this later
                std::cout << "successful\n";
            }

        } else if (command == "printInorder" || command == "printPreorder" || 
                   command == "printPostorder" || command == "printLevelCount") {
            // Call corresponding function later
            std::cout << "successful\n";

        } else if (command == "removeInorder") {
            int n;
            if (!(ss >> n)) {
                std::cout << "unsuccessful\n";
                continue;
            }
            // removeInorder(n); <-- implement this later
            std::cout << "successful\n";

        } else {
            std::cout << "unsuccessful\n";
        }
    }

    return 0;
}
