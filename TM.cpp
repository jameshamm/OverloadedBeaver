#include "TMSim.cpp"
#include <ResultMinder.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

int main(){
    cout << "Start" << endl;
    string encoding = "000110011121";
    string input = "1111111";
    vector<vector<unsigned char> > tm = parse_TM(encoding);

    vector<int> res = fast_simulate(tm, input, 1000);
    cout << res[res.size()-1] << endl;

    ResultMinder r(10, 0);
    r.print();
    r.insert(10, "0010", "2");
    r.insert(10, "10", "2");
    r.insert(1, "1", "2");
    r.insert(2, "0110", "2");
    r.insert(11, "10", "2");
    r.insert(10, "0", "2");
    r.insert(2, "10", "1");
    r.insert(9, "100", "1");
    r.insert(8, "110", "2");
    r.insert(9, "110", "1");
    r.insert(9, "11110", "1");
    r.insert(1, "011110", "2");

    cout << "--- Final results ---" << endl;
    r.print();
}
