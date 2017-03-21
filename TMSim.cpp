#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

vector<vector<int>> parse_TM(string TM_encoding) {
    vector<vector<int>> TM;
    int offset = 6;
    for(int i = 0; i < TM_encoding.length(); i += offset) {
        string s = TM_encoding.substr(i, offset);
        vector<int> state;
        for(int j = 0; j < offset; j += 2) {
            state.push_back(stoi(s.substr(j, 2)));
        }
        TM.push_back(state);
    }
    return TM;
}

vector<int> itotape(string TM_input) {
    vector<int> tape;
    for(char &c : TM_input) {
        tape.push_back(c - '0');
    }
    return tape;
}

void print(vector<int> tape) {
    for (auto i = tape.begin(); i != tape.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;
}

int simulate(vector<vector<int> > TM, string TM_input, int steps) {
    /* Return the state reached after supplied steps */

    vector<int> tape = itotape(TM_input);

    int head = 0;
    int current_state = 0;
    int halt_state = 2;

    for(int i = 0; i < steps; i++){

        // Read from tape
        if(head >= tape.size()) {
            tape.push_back(2);
        }
        int cell = tape[head];
        int data = TM[current_state][cell];  // get transition for this state/input

        int move = data % 2;
        int write = (data % 10) % 3;
        current_state = data / 10;

        // Write to tape
        tape[head] = write;

        if(current_state == halt_state) {
            // This highlights the last place that is written to in the tape
            tape[head] = 4;  
            return i+1;
        }

        // move head
        if(move == 0) {
            if(head != 0) {
                head--;
            }
        } else {
            head++;
        }
    }
    return 0;
}

int simulate2(vector<vector<int> > TM, string TM_input, int steps) {
    /*  Return the state reached after supplied steps
        If the TM has not finished by the number of steps, returns 0
        If the TM has looped, return -1
    */

    std::set<vector<int> > seen;

    vector<int> tape = itotape(TM_input);
    int head = 0;
    int current_state = 0;
    int halt_state = 2;

    for(int i = 0; i < steps; i++){

        // Read from tape
        if(head >= tape.size()) {
            tape.push_back(2);
        }
        int cell = tape[head];
        int data = TM[current_state][cell];  // get transition for this state/input

        int move = data % 2;
        int write = (data % 10) % 3;
        current_state = data / 10;

        // Write to tape
        tape[head] = write;

        if(current_state == halt_state) {
            return i+1;  // steps taken
        }

        // move head
        if(move == 0) {
            if(head != 0) {
                head--;
            }
        } else {
            head++;
        }

        vector<int> statis = tape;
        statis.insert(statis.begin(), head);
        statis.insert(statis.begin(), current_state);

        if(seen.find(statis) != seen.end()) {
            return -1;
        } else {
            seen.insert(statis);
        }
    }
    return 0;  // hasn't looped, or halted
}