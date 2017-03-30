// Try generating encodings with strings as opposed to ints

#include "TMSim.cpp"
#include <ResultMinder.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <thread>

using namespace std;

const int MAX_STEPS = 3000;

string bin(int len, int i) {
    return std::bitset<20>(i).to_string().substr(20 - len);
}

bool all_same(const vector<int> & tape) {
    // Expects a tape with no 2s at the end
    // There should only be a single 4 on the tape
    // Assumes the tape length is at least 2
    if(tape[0] == 2 || tape[1] == 2) {
        return false;
    }
    int expected = (tape[0] == 4) ? tape[1] : tape[0];

    for(int i = 2; i < tape.size(); i++) {
        if(tape[i] == 4) {
            continue;
        }
        else if(tape[i] != expected) {
            return false;
        }
    }
    return true;
}

bool all_alternating(const vector<int> & tape) {
    // Expects a tape with no 2s at the end)
    // Assumes the tape length is at least 3
    if(tape.size() % 2 == 1 || tape[0] == 2 || tape[2] == 2) {
        return false;
    }
    int expected = (tape[0] == 4) ? tape[2] : tape[0];
    for(int i = 0; i < tape.size(); i++) {
        if(tape[i] == 4){
            continue;
        }
        else if(tape[i] != (i + expected) % 2) {
            return false;
        }
    }
    return true;
}

bool all_not_blank(vector<int> & tape) {
    // Expects a tape with no 2s at the end)
    for(int i = 0; i < tape.size(); i++) {
        if(tape[i] == 2){
            return false;
        }
    }
    return true;
}

void check_TM(ResultMinder* best, ofstream& inf_tms_out, int input_length, string encoding) {
    /* Take a string encoding of a turing machine

    If the TM beats the previous best TM in some category, write it to the appropiate file.
    Else if the TM doesn't complete in the max number of steps, write it to a file to be checked later.
    Hopefully there are very few of these.*/
    int best_steps = best[0].lowest();
    int best_ones = best[1].lowest();
    int best_alt = best[2].lowest();
    int best_any = best[3].lowest();

    vector<vector<unsigned char> > TM = parse_TM(encoding);

    int limit = 1 << input_length;
    for(int i = 0; i < limit; i++) {
        string input = bin(input_length, i);

        // Check if the TM loops quickly
        bool no_loops = true;//check_for_loops(TM, input, 1000);

        if(no_loops) {
            // Simulate it for 1 billion steps.
            vector<int> res = fast_simulate(TM, input, MAX_STEPS);

            int len = res.size()-1;
            int steps_taken = res[len];

            if(steps_taken == 0) {
                // It didn't complete
                // TODO: Write (TM, input) to a file
                //inf_tms_out << encoding << " " << input << endl;
            }
            else{
                if(steps_taken >= best_steps) {
                    // Group 1 new contender
                    best_steps = best[0].insert(steps_taken, encoding, input);
                }

                res.pop_back();

                if(len >= best_ones && all_same(res)) {
                    // Group 2 new contender
                    if(len >= best_any){
                        best_any = best[3].insert(len, encoding, input);
                    }
                    best_ones = best[1].insert(len, encoding, input);
                } else if(len >= best_alt && all_alternating(res)) {
                    // Group 3 new contender
                    if(len >= best_any){
                        best_any = best[3].insert(len, encoding, input);
                    }
                    best_alt = best[2].insert(len, encoding, input);
                } else if(len >= best_any && all_not_blank(res)) {
                    // Group 4 new contender
                    best_any = best[3].insert(len, encoding, input);
                }
            }
        }
    }
}


void manage(ResultMinder* a, ResultMinder* b, ResultMinder* c, vector<string> encodings, int thread_id) {
    std::ofstream inf_tms_out("../data/unknown_nb_TMs.txt", std::ios_base::app);

    int j = 0;
    for(auto encoding : encodings) {
        check_TM(a, inf_tms_out, 3, encoding);
        check_TM(b, inf_tms_out, 4, encoding);
        check_TM(c, inf_tms_out, 5, encoding);
        j++;
        if(j % 1000 == 0) {
            cout << "thread-" << thread_id << " reached " << encoding << ", ";
            cout << j * 100.0 / encodings.size() << "%" << endl; 
        }
    }

    cout << "thread-" << thread_id << " is done!" << endl;
    a->print();
    b->print();

    inf_tms_out.close();
}

int main() {
    ifstream myReadFile;
    myReadFile.open("../data/trimmed_nb_TMs.txt");

    vector<string> encodings;
    string encoding;

    int prev_run = 0; // Which line to start from

    int j = 0;
    while(!myReadFile.eof()) {
        getline(myReadFile, encoding);
        if(encoding.length() < 3) {
            continue;
        }
        if(j < prev_run) {
            j++;
            continue;
        }

        encodings.push_back(encoding);
    }

    myReadFile.close();

    cout << "Starting" << endl;

    std::ofstream unknown("../data/unknown_nb_TMs.txt", std::ios_base::trunc);
    unknown.close();

    int thread_count = 8;
    std::thread *tt = new std::thread[thread_count];

    vector<vector<string> > encodings_split;
    for(int i = 0; i < thread_count; i++) {
        vector<string> encodings_s;
        encodings_split.push_back(encodings_s);
    }

    for(int i = 0; i < encodings.size(); i++) {
        string encoding = encodings[i];
        encodings_split[i%thread_count].push_back(encoding);
    }

    ResultMinder* a = new ResultMinder[4];
    ResultMinder* b = new ResultMinder[4];
    ResultMinder* c = new ResultMinder[4];

    for(int i = 0; i < 4; ++i) {
        a[i] = ResultMinder(15, i);
        b[i] = ResultMinder(15, i);
        c[i] = ResultMinder(15, i);
    }

    for(int i = 0; i < thread_count; i++) {
        tt[i] = std::thread(manage, a, b, c, encodings_split[i%thread_count], i+1);
    }

    // could do something here

    // nevermind
    for(int i = 0; i < thread_count; ++i) {
        tt[i].join();
    }
}
