// Try generating encodings with strings as opposed to ints

#include "TMSim.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <thread>

using namespace std;

void print(vector<vector<int> > vss) {
    for (auto i = vss.begin(); i != vss.end(); ++i) {
        for (auto j = (*i).begin(); j != (*i).end(); ++j) {
            int num = *j;
            std::cout << num/10 << num%10;
        }
    }
    cout << endl;
}

string bin(int len, int i) {
    return std::bitset<20>(i).to_string().substr(20 - len);
}

bool all_ones(const vector<int> & tape) {
    // Expects a tape with no 2s at the end
    for(int i = 0; i < tape.size(); i++) {
        if(tape[i] == 4) {
            continue;
        }
        else if(tape[i] != 1) {
            return false;
        }
    }
    return true;
}

bool all_zero_ones(const vector<int> & tape) {
    // Expects a tape with no 2s at the end)
    if(tape.size() % 2 == 1) {
        return false;
    }
    for(int i = 0; i < tape.size(); i++) {
        if(tape[i] == 4){
            continue;
        }
        else if(tape[i] != i % 2) {
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

void check_TM(string encoding, int input_length, int * bests) {
    /* Take a string encoding of a turing machine

    If the TM beats the previous best TM in some category, write it to the appropiate file.
    Else if the TM doesn't complete in the max number of steps, write it to a file to be checked later.
    Hopefully there are very few of these.*/
    int best_steps = bests[0];
    int best_ones = bests[1];
	int best_alt = bests[2];
	int best_any = bests[3];

    vector<vector<int> > TM = parse_TM(encoding);

    int limit = 1 << input_length-1;
    for(int i = 0; i < limit; i++) {
        string input = "1" + bin(input_length-1, i);

        // Check if the TM loops quickly
        bool no_loops = check_for_loops(TM, input, 10000);

        if(no_loops) {
            // Simulate it for 1 billion steps.
            vector<int> res = fast_simulate(TM, input, 1000000000);

            int len = res.size()-1;
            int steps_taken = res[len];
            res.pop_back();

            if(steps_taken == -1) {
                // It didn't complete
                // TODO: Write (TM, input) to a file
            }
            else{
                if(steps_taken >= best_steps) {
                    // Group 1 new contender
                    // TODO: Output and write to file
                    best_steps = steps_taken;
                    cout << "NEW CHAMPION G1: took " << steps_taken << " steps, " << encoding << ", " << input << endl;
                }

                if(len > best_ones && all_ones(res)) {
                    // Group 2 new contender
                    // TODO: Output and write to file
                	if(len>best_any){
                		best_any = len;
                		cout << "NEW VICTOR G4: " << len << " *s, " << encoding << ", " << input << endl;
                	}
                    best_ones = len;
                    cout << "NEW HERO G2: " << len << " 1s, " << encoding << ", " << input << endl;
                } else if(len > best_alt && all_zero_ones(res)) {
                    // Group 3 new contender
                    // TODO: Output and write to file
                	if(len>best_any){
    					best_any = len;
    					cout << "NEW VICTOR G4: " << len << " *s, " << encoding << ", " << input << endl;
    				}
                    best_alt = len;
                    cout << "NEW LEADER G3: " << len << " 01s, " << encoding << ", " << input << endl;
                } else if(len > best_any && all_not_blank(res)) {
                    // Group 4 new contender
                    // TODO: Output and write to filenew
                    best_any = len;
                    cout << "NEW VICTOR G4: " << len << " *s, " << encoding << ", " << input << endl;
                }
            }
        }
    }
    bests[0] = best_steps;
    bests[1] = best_ones;
    bests[2] = best_alt;
    bests[3] = best_any;
}


void manage(vector<string> encodings) {
    int * a = new int[4];
    int * b = new int[4];

    for(int i = 0; i < 4; i++) {
    	a[i] = 2;
    	b[i] = 2;
    }

    int j = 0;
    for(auto i : encodings) {
        check_TM(i, 6, a);
        check_TM(i, 7, b);
        j++;
        if(j % 100 == 0) {
            cout << "Reached " << i << ", ";
            cout << j * 100.0 / encodings.size() << "%" << endl; 
        }
    }
    delete[] a;
    delete[] b;
}

int main() {
    ifstream myReadFile;
    myReadFile.open("data/nb_TMs.txt");

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

    cout << "Starting from " << j;
    cout << ", encoding " << encodings[0] << endl; 

    int thread_count = 4;
    std::thread *tt = new std::thread[thread_count];

    vector<vector<string> > encodings_split;
    for(int i = 0; i < thread_count; i++) {
        vector<string> encodings_s;
        encodings_split.push_back(encodings_s);
    }

    for(int i = 0; i < encodings.size(); i++) {
        string encoding = encodings[i];
        encodings_split[i%4].push_back(encoding);
    }

    for(int i = 0; i < thread_count; i++) {
        tt[i] = std::thread(manage, encodings_split[i%4]);
    }

    // could do something here

    // nevermind
    for(int i = 0; i < thread_count; ++i) {
        tt[i].join();
    }
}
/*
int old_main() {
    string encoding;

    int lim = 9999;
    int best_steps = 5;
    int i = 0;
    vector<vector<int> > best_TM;
    string input = "1111111111111111111";

    ofstream no_loop_file("no_loop_" + std::to_string(lim) + "_" + input + ".txt");
    ofstream loop_file("loop" + std::to_string(lim) + "_" + input + ".txt");

    ifstream myReadFile;
    myReadFile.open("no_loop_999_1111111111111111111.txt");

    while(!myReadFile.eof()) {
        getline(myReadFile, encoding);
        if(encoding.length() < 12) {
            continue;
        }

        vector<vector<int> > TM_encoding = parse_TM(encoding);
        int steps = simulate2(TM_encoding, input, lim);
        if(steps == 0) {
            no_loop_file << encoding << endl;
        } else if(steps == -1) {
            loop_file << encoding << endl;
        }
        if(steps >= best_steps) {
            best_steps = steps;
            best_TM = TM_encoding;
            print(best_TM);
            cout << "new champion: " << best_steps << " steps" << endl;
        }
        if(i % 10000 == 0) {
            cout << "  currently at: " << i << endl;
        }
        i++;
    }
    myReadFile.close();
    cout << "DONE" << endl;
    cout << i << endl;
}
*/
