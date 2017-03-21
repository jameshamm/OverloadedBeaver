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
