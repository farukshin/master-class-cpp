#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <unordered_map>

using namespace std;

string toLower2(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string user() {
    string question;
    cout << "[USER]: ";
    getline(cin, question);
    question = toLower2(question);
    return question;
}

void bot(string text) {
    cout << "[BOT]: " << text << endl;;
}

int main()
{
    unordered_map<string, string> database = {
        {"hello", "oh, hello to you, human"},
        {"how are you", "i'm good"},
        {"what is your name", "My name is SUPER APP BOT 3000!"}
    };

    string question;
    bot("Hello, welcom to AUTOMATED SUPERBOT 3000, please ask any questions:");

    while (question.compare("exit")) {
        question = user();

        for (auto entry : database)
            if (regex_match(question, regex(".*" + entry.first + ".*"))) {
                bot(entry.second);
            }
    }
    bot("okey, by!");
    return 0;
}
