#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <windows.h>

struct tm_rule {
    std::string state;
    char symb;
    char symb2;
    char dir;
    std::string state2;
};

int main(int argc, char* argv[]) {

    // Check command line arguments
    if (argc < 2) {
        std::cout << "No argument" << std::endl;
        return 1;
    }
    else {
        for (int i = 0; i < argc; ++i) {
            std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
        }

        std::cout << "\n";
    }

    // Open input file
    std::fstream fin(argv[1]);

    if (!fin) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    std::string tape;
    int start;

    // Read the initial tape
    while (std::getline(fin, line)) {
        if (line != "") {
            tape = line;
            break;
        }
    }

    // Read starting position
    while (std::getline(fin, line)) {
        if (line != "") {
            int pos = line.find("//");

            if (pos != std::string::npos)
                line = line.substr(0, pos);

            start = std::stoi(line);
            break;
        }
    }

    // Read machine rules
    std::vector<tm_rule> rules;
    tm_rule temp;

    while (fin >> temp.state
               >> temp.symb
               >> temp.symb2
               >> temp.dir
               >> temp.state2) {

        rules.push_back(temp);
    }

    std::string tape_now = tape;
    int head = start - 1;
    char blank = '_';
    std::string state = "0";

    long long steps = 0;

    // Used to detect long movement in one direction
    long long dirCount = 0;
    char last = '0';

    while (true) {

        if (_kbhit()) {
            char c = _getch();

            if (c == 'p' || c == 'P') {
                std::cout << "Stopped" << std::endl;
                break;
            }
        }

        // Expand tape when the head reaches an edge
        if (head < 0) {
            tape_now = blank + tape_now;
            head = 0;
        }

        if (head >= tape_now.size()) {
            tape_now = tape_now + blank;
        }

        char read = tape_now[head];

        int idx = -1;

        // Find a rule for the current state and symbol
        for (int i = 0; i < rules.size(); i++) {
            if (rules[i].state == state &&
                rules[i].symb == read) {

                idx = i;
                break;
            }
        }

        system("cls");

        std::cout << "Press P to stop the machine" << std::endl;

        std::cout << "Step: " << steps << std::endl;
        std::cout << "State: " << state << std::endl;

        if (idx != -1)
            std::cout << "Looking for: " << rules[idx].symb << std::endl;

        std::cout << std::endl;

        std::cout << tape_now << std::endl;

        int arrow = head - 1;

        if (arrow < 0)
            arrow = 0;

        for (int i = 0; i < arrow; i++)
            std::cout << " ";

        std::cout << "^" << std::endl;

        Sleep(10);

        if (idx == -1)
            break;

        // Count consecutive moves in the same direction
        if (rules[idx].dir == 'L' || rules[idx].dir == 'R') {

            if (last == rules[idx].dir)
                dirCount++;
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

            std::cout << "Infinite expansion detected. Continue? Y or N" << std::endl;

            char ans = 0;

            while (true) {
                ans = _getch();

                if (ans == 'Y' || ans == 'y' ||
                    ans == 'N' || ans == 'n') {

                    break;
                }
            }

            if (ans == 'N' || ans == 'n')
                break;

            last = '0';
            dirCount = 0;
        }

        tape_now[head] = rules[idx].symb2;

        if (rules[idx].dir == 'L')
            head--;
        else if (rules[idx].dir == 'R')
            head++;

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

    std::cout << "Tapes: 1" << std::endl;
    std::cout << "Steps: " << steps << std::endl;
    std::cout << "State: " << state << std::endl;
    std::cout << "Head: " << head << std::endl;
    std::cout << "Tape: " << tape_now << std::endl;
    std::cout << "Symbol: " << tape_now[head] << std::endl;

    return 0;
}