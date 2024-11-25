#include <bits/stdc++.h>
using namespace std;

class StringSet {
public:
    vector<string> Tokens;

    static string processWord(const string& word) {
        string result;
        for (char c : word) {
            if (isalpha(c)) {
                result += tolower(c);
            }
        }
        return result;
    }

    static vector<string> stringFilter(vector<string>& oldVec) {
        vector<string> newVec;
        for (const auto& word : oldVec) {
            if (find(newVec.begin(), newVec.end(), word) == newVec.end()) {
                newVec.push_back(word);
            }
        }
        return newVec;
    }

    explicit StringSet(const string& input, bool isFile = false) {
        if (isFile) {
            ifstream file(input);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    tokenize(line);
                }
                file.close();
            } else {
                cout << "Error: Unable to open file " << input << endl;
            }
        } else {
            tokenize(input);
        }
        Tokens = stringFilter(Tokens);
    }

    void tokenize(const string& str) {
        istringstream stream(str);
        string word;
        while (stream >> word) {
            word = processWord(word);
            if (!word.empty()) Tokens.push_back(word);
        }
    }

    void print() const {
        cout << "Tokens' Number: " << Tokens.size() << endl;
        for (const auto& token : Tokens) {
            cout << "[" << token << "] ";
        }
        cout << endl;
    }

    void addStrings(const string& sentence) {
        istringstream stream(sentence);
        string word;
        while (stream >> word) {
            string processed = processWord(word);
            if (!processed.empty() && find(Tokens.begin(), Tokens.end(), processed) == Tokens.end()) {
                Tokens.push_back(processed);
            }
        }
    }

    void removeStrings(const string& sentence) {
        istringstream stream(sentence);
        string word;
        while (stream >> word) {
            string processed = processWord(word);
            Tokens.erase(remove(Tokens.begin(), Tokens.end(), processed), Tokens.end());
        }
    }

    void clearSet() {
        Tokens.clear();
    }

    StringSet operator+(const StringSet& other) const {
        vector<string> combined = Tokens;
        for (const auto& word : other.Tokens) {
            if (find(combined.begin(), combined.end(), word) == combined.end()) {
                combined.push_back(word);
            }
        }
        return StringSet(combined);
    }

    StringSet operator*(const StringSet& other) const {
        vector<string> common;
        for (const auto& word : other.Tokens) {
            if (find(Tokens.begin(), Tokens.end(), word) != Tokens.end()) {
                common.push_back(word);
            }
        }
        return StringSet(common);
    }

    double similarity(const StringSet& other) const {
        size_t intersectionSize = (*this * other).Tokens.size();
        size_t sizeThis = Tokens.size();
        size_t sizeOther = other.Tokens.size();
        if (sizeThis == 0 || sizeOther == 0) return 0.0;
        return static_cast<double>(intersectionSize) / (sqrt(sizeThis) * sqrt(sizeOther));
    }

private:
    explicit StringSet(const vector<string>& vec) : Tokens(vec) {}
};

int main() {
    StringSet set1(""), set2("");
    bool setsInitialized = false;

    cout << "=====================================================\n";
    cout << "       WELCOME TO DOCUMENT SIMILARITY PROGRAM\n";
    cout << "=====================================================\n";

    while (true) {
        cout << "Choose an initial option:\n"
             << "1. Load your files (enter two file names)\n"
             << "2. Enter your text (enter two strings)\n"
             << "3. Run demo test cases (with example texts)\n"
             << "4. Exit\n";

        string choiceStr;
        getline(cin, choiceStr);

        if (choiceStr.empty() || choiceStr.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid option. Please enter a number between 1 and 4.\n";
            continue;
        }

        int choice = stoi(choiceStr);

        if (choice == 1) {
            string file1, file2;
            cout << "Enter the first file name: ";
            getline(cin, file1);
            cout << "Enter the second file name: ";
            getline(cin, file2);
            set1 = StringSet(file1, true);
            set2 = StringSet(file2, true);
            setsInitialized = true;
        } else if (choice == 2) {
            string text1, text2;
            cout << "Enter the first string: ";
            getline(cin, text1);
            cout << "Enter the second string: ";
            getline(cin, text2);
            set1 = StringSet(text1);
            set2 = StringSet(text2);
            setsInitialized = true;
        } else if (choice == 3) {
            set1 = StringSet("example text for set one");
            set2 = StringSet("example text for set two");
            setsInitialized = true;

            // Run demo operations
            cout << "\nRunning demo operations on example sets:\n";

            cout << "\nInitial Set 1:\n";
            set1.print();
            cout << "\nInitial Set 2:\n";
            set2.print();

            cout << "\nAdding words to Set 1...\n";
            set1.addStrings("additional words for demo");
            set1.print();

            cout << "\nRemoving words from Set 2...\n";
            set2.removeStrings("text example");
            set2.print();

            cout << "\nClearing Set 2...\n";
            set2.clearSet();
            cout << "Set 2 after clearing:\n";
            set2.print();

            // Re-initialize set2 for further operations
            set2 = StringSet("restored text for set2 for demo");

            cout << "\nComputing similarity between Set 1 and Set 2:\n";
            double sim = set1.similarity(set2);
            cout << "Similarity: " << sim << endl;

            cout << "\nComputing union of Set 1 and Set 2:\n";
            StringSet unionSet = set1 + set2;
            unionSet.print();

            cout << "\nComputing intersection of Set 1 and Set 2:\n";
            StringSet intersectionSet = set1 * set2;
            intersectionSet.print();

            cout << "\nDemo completed.\n";
            continue; // Go back to the main menu
        } else if (choice == 4) {
            cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Please enter a number between 1 and 4.\n";
            continue;
        }

        // Main menu (available only if sets are initialized)
        if (setsInitialized) {
            while (true) {
                cout << "\nChoose an operation:\n"
                     << "1. Display Set 1\n"
                     << "2. Display Set 2\n"
                     << "3. Add words to a set\n"
                     << "4. Remove words from a set\n"
                     << "5. Clear a set\n"
                     << "6. Compute similarity between Set 1 and Set 2\n"
                     << "7. Compute union of Set 1 and Set 2\n"
                     << "8. Compute intersection of Set 1 and Set 2\n"
                     << "9. Exit to main menu\n";

                getline(cin, choiceStr);

                if (choiceStr.empty() || choiceStr.find_first_not_of("0123456789") != string::npos) {
                    cout << "Invalid option. Please enter a number between 1 and 9.\n";
                    continue;
                }

                int operationChoice = stoi(choiceStr);

                if (operationChoice == 1) {
                    cout << "Displaying Set 1:\n";
                    set1.print();
                } else if (operationChoice == 2) {
                    cout << "Displaying Set 2:\n";
                    set2.print();
                } else if (operationChoice == 3) {
                    cout << "Enter words to add: ";
                    string words;
                    getline(cin, words);
                    cout << "Choose the set (1 or 2): ";
                    getline(cin, choiceStr);
                    if (choiceStr == "1") {
                        set1.addStrings(words);
                    } else if (choiceStr == "2") {
                        set2.addStrings(words);
                    } else {
                        cout << "Invalid set choice.\n";
                    }
                } else if (operationChoice == 4) {
                    cout << "Enter words to remove: ";
                    string words;
                    getline(cin, words);
                    cout << "Choose the set (1 or 2): ";
                    getline(cin, choiceStr);
                    if (choiceStr == "1") {
                        set1.removeStrings(words);
                    } else if (choiceStr == "2") {
                        set2.removeStrings(words);
                    } else {
                        cout << "Invalid set choice.\n";
                    }
                } else if (operationChoice == 5) {
                    cout << "Choose the set to clear (1 or 2): ";
                    getline(cin, choiceStr);
                    if (choiceStr == "1") {
                        set1.clearSet();
                        cout << "Set 1 cleared.\n";
                    } else if (choiceStr == "2") {
                        set2.clearSet();
                        cout << "Set 2 cleared.\n";
                    } else {
                        cout << "Invalid set choice.\n";
                    }
                } else if (operationChoice == 6) {
                    double sim = set1.similarity(set2);
                    cout << "Similarity between Set 1 and Set 2: " << sim << endl;
                } else if (operationChoice == 7) {
                    StringSet unionSet = set1 + set2;
                    cout << "Union of Set 1 and Set 2:\n";
                    unionSet.print();
                } else if (operationChoice == 8) {
                    StringSet intersectionSet = set1 * set2;
                    cout << "Intersection of Set 1 and Set 2:\n";
                    intersectionSet.print();
                } else if (operationChoice == 9) {
                    break;
                } else {
                    cout << "Invalid option. Please enter a number between 1 and 9.\n";
                }
            }
        }
    }

    return 0;
}