#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "No argument" << endl;
        return 1;
    }
    else {
        for (int i = 0; i < argc; ++i) {
            cout << "argv[" << i << "]= " << argv[i] << endl;
        }
        cout << "\n";
    }

    fstream fin(argv[1]);
    if (!fin) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    string line;
    string tape;
    int start;

    while (getline(fin, line)) {
        if (line != "") {
            tape = line;
            break;
        }
    }

    while (getline(fin, line)) {
        if (line != "") {
            int pos = line.find("//");
            if (pos != string::npos) line = line.substr(0, pos);
            start = stoi(line);
            break;
        }
    }

    struct tm_rule {
        string state;
        char symb;
        char symb2;
        char dir;
        string state2;
    };

    vector<tm_rule> rules;
    tm_rule temp;

    while (fin >> temp.state >> temp.symb >> temp.symb2 >> temp.dir >> temp.state2) {
        rules.push_back(temp);
    }

    string tape_now = tape;
    int head = start - 1;
    char blank = '_';
    string state = "0";

    long long steps = 0;

    // If it moves in the same direction 10000 times in a row, ask whether to continue
    long long dirCount = 0;
    char last = '0';

    while (true) {

        if (_kbhit()) {
            char c = _getch();
            if (c == 'p' || c == 'P') {
                cout << "Stopped" << endl;
                break;
            }
        }

        if (head < 0) {
            tape_now = blank + tape_now;
            head = 0;
        }
        if (head >= tape_now.size()) {
            tape_now = tape_now + blank;
        }

        char read = tape_now[head];

        int idx = -1;
        for (int i = 0; i < rules.size(); i++) {
            if (rules[i].state == state &&
                rules[i].symb == read) {
                idx = i;
                break;
            }
        }

        system("cls");

        cout << "Press P to stop the machine" << endl;

        cout << "Step: " << steps << endl;
        cout << "State: " << state << endl;

        if (idx != -1)
            cout << "Looking for: " << rules[idx].symb << endl;

        cout << endl;

        cout << tape_now << endl;

        int arrow = head - 1;
        if (arrow < 0) arrow = 0;

        for (int i = 0; i < arrow; i++)
            cout << " ";
        cout << "^" << endl;

        Sleep(10);

        if (idx == -1) break;

        if (rules[idx].dir == 'L' || rules[idx].dir == 'R') {
            if (last == rules[idx].dir) dirCount++;
            else {
                last = rules[idx].dir;
                dirCount = 1;
            }
        }
        else {
            last = '0';
            dirCount = 0;
        }

        if (dirCount >= 10000) {
            system("cls");
            cout << "Infinite expansion detected. Continue? Y or N" << endl;
            char ans = 0;
            while (true) {
                ans = _getch();
                if (ans == 'Y' || ans == 'y' || ans == 'N' || ans == 'n') break;
            }
            if (ans == 'N' || ans == 'n') break;
            last = '0';
            dirCount = 0;
        }

        tape_now[head] = rules[idx].symb2;

        if (rules[idx].dir == 'L') head--;
        else if (rules[idx].dir == 'R') head++;

        state = rules[idx].state2;
        steps++;
    }

    if (head < 0) {
        tape_now = blank + tape_now;
        head = 0;
    }
    if (head >= tape_now.size()) {
        tape_now = tape_now + blank;
    }

    cout << "Tapes: 1" << endl;
    cout << "Steps: " << steps << endl;
    cout << "State: " << state << endl;
    cout << "Head: " << head << endl;
    cout << "Tape: " << tape_now << endl;
    cout << "Symbol: " << tape_now[head] << endl;

    return 0;
}