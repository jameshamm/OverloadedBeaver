#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

vector<vector<unsigned char>> parse_TM(string TM_encoding) {
    vector<vector<unsigned char>> TM;
    int offset = 6;
    for(int i = 0; i < TM_encoding.length(); i += offset) {
        string s = TM_encoding.substr(i, offset);
        vector<unsigned char> state;
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

void print_tape(vector<int> tape) {
    for(auto& el: tape) std::cout << el << ' ';
    cout << endl;
}

void print_tm(vector<vector<unsigned char> > vss) {
    for (auto i = vss.begin(); i != vss.end(); ++i) {
        for (auto j = (*i).begin(); j != (*i).end(); ++j) {
            int num = *j;
            std::cout << num/10 << num%10;
        }
    }
    cout << endl;
}

vector<int> shorten_tape(vector<int> tape) {
    /*  Shorten the tape by removing unnecessary 2's (blanks) from the end of it.
    */
    int i = tape.size()-1;
    for(; i >= 0; --i) {
        if(tape[i] != 2) {
            tape.resize(i+1);
            return tape;
        }
    }
    return tape;
}

vector<int> fast_simulate(const vector<vector<unsigned char> > TM, const string TM_input, int steps) {
    /* Return the state reached after supplied steps */
    vector<int> tape = itotape(TM_input);

    int head = 0;
    int current_state = 0;
    int halt_state = 2;

    for(int i = 0; i < steps; i++){
        // Read from tape
        int data = TM[current_state][tape[head]];  // get transition for this state/input

        current_state = data / 10;
        if(current_state == halt_state) {
            // This highlights the last place that is written to in the tape
            tape[head] = 4;
            vector<int> res = shorten_tape(tape);
            res.push_back(i+1);
            return res;
        }

        // Write to tape
        tape[head] = (data % 10) % 3;

        // move head
        if(data & 1) {
            if(++head == tape.size()) {
                tape.push_back(2);
            }
        } else {
            if(head) {
                --head;
            }
        }
    }

    vector<int> res {0};
    return res;
}

bool check_for_loops(vector<vector<unsigned char> > TM, string TM_input, int steps) {
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
        int data = TM[current_state][tape[head]];  // get transition for this state/input

        current_state = data / 10;
        if(current_state == halt_state) {
            // Doesn't loop if it halts
            return true;
        }

        // Write to tape
        tape[head] = (data % 10) % 3;

        // move head
        if(data & 1) {
            if(++head == tape.size()) {
                tape.push_back(2);
            }
        } else {
            if(head) {
                --head;
            }
        }

        vector<int> stasis = shorten_tape(tape);
        stasis.push_back(current_state);
        stasis.push_back(head);

        if(seen.find(stasis) != seen.end()) {
            return false;
        }
        seen.insert(stasis);
    }
    return true;  // hasn't looped, or halted
}
