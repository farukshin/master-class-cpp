#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

string toLower2(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main()
{
    string question;
    cout << "Hello, welcom to SUPER APP BOT 3000" << endl;
    getline(cin, question);

    question = toLower2(question);

    if (regex_match(question, regex(".*hello.*"))) {
        cout << "Hi, how are you?\n";
    }

    if (regex_match(question, regex(".*how are you.*"))) {
        cout << "I'm good!\n";
    }

    if (regex_match(question, regex(".*what is your name.*"))) {
        cout << "My name is SUPER APP BOT 3000!\n";
    }

    return 0;
}
