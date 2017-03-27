#include "TMSim.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <thread>

using namespace std;

int main(){
    string encoding, input;
    cin >> encoding >> input;
    vector<vector<int> > tm = parse_TM(encoding);

    int steps = 10000;
    bool no_loop = check_for_loops(tm, input, steps);
    if(no_loop) {
        // Up the steps so we can see what the tm does
        steps = 1000000000;
    }

    vector<int> res = fast_simulate(tm, input, steps);

    int len = res.size()-1;
    int steps_taken = res[len];
    res.pop_back();
    
    cout << "Ran " << encoding << " for " << steps_taken << " steps." << endl;

    if(!no_loop) {
        cout << "It looped." << endl;
    }
    print_tape(res);
}