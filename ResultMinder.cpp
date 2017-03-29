#include <ResultMinder.h>

using namespace std;

ResultMinder::ResultMinder(int size) {
    champs = new Contender[size];
    this.size = size;
}

int ResultMinder::insert(int score, string encoding, string input) {
    champs[10] = Contender(score, encoding, input);
    sort(begin(champs), end(champs));
    return champs[10].score;
}

void ResultMinder::print(string group_message) {
    cout << "Current best at " << group_message << endl;
    for(int i = 0; i < size; ++i) {
        cout << "  " << champs[i] << endl;
    }
}
