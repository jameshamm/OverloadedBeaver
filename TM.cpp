#include "TMSim.cpp"
#include "ResultMinder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

int main(){
	string encoding = "000110011121";
	string input = "1111111";
	vector<vector<unsigned char> > tm = parse_TM(encoding);

	vector<int> res = fast_simulate(tm, input, 1000000000);
	cout << res[res.size()-1] << endl;

	ResultMinder r(10);
	r.insert(10, "10", "2");
	r.print("all 1s");
}
