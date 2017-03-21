// Try generating encodings with strings as opposed to ints

#include "TMSim.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


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

void check_TM(string TM, int input_length) {
    /* Take a string encoding of a turing machine

    If the TM beats the previous best TM in some category, write it to the appropiate file.
    Else if the TM doesn't complete in the max number of steps, write it to a file to be checked later.
    Hopefully there are very few of these.*/
    int best_steps = 0;
    int best_ones = 0;
    int best_alt = 0;
    int best_any = 0;

    /*  TODO: Write the functions used below:
            bin
            check_for_loops
            fast_simulate
            matches_pattern
    */

    // TODO: Use 2**input_length
    for(int i = 0; i < 32; i++) {
        string input = "0" + bin(i);

        // Check if the TM loops quickly
        bool no_loops = check_for_loops(TM, input, 10000);

        if(no_loops) {
            // Simulate it for 1 billion steps.
            vector<int> res = fast_simulate(TM, input, 1000000000);

            int steps_taken = res[0];
            // TODO: Remove steps from the top of the tape
            vector<int> tape = res;

            if(steps_taken == -1) {
                // It didn't complete
                // TODO: Write (TM, input) to a file
            }

            if(steps_taken >= best_steps) {
                // Group 1 new contender
                // TODO: Output and write to file
            }

            int len = tape.size();
            if(len > best_ones && matches_pattern(tape, "1")) {
                // Group 2 new contender
                // TODO: Output and write to file
            } else if(len > best_alt && matches_pattern(tape, "01")) {
                // Group 3 new contender
                // TODO: Output and write to file
            } else if(len > best_any && matches_pattern(tape, "*")) {
                // Group 4 new contender
                // TODO: Output and write to file
            }
        }
    }
}

int main() {
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
