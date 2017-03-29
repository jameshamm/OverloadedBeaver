#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Contender {
    int score;
    string encoding;
    string input;

    bool operator<(const Contender& rhs) {
        if(this->score > rhs.score) {
            return true;
        } else if(this->score <= rhs.score) {
            return false;
        }
    }

    std::ostream& operator << (std::ostream &o) {
        o << "(" << this->encoding << ", " << this->input << ", " << this->score << ")";
        return o;
    }
};

class ResultMinder {
    public:
        ResultMinder(int size);
        ~ResultMinder(){delete[] champs;};
        int insert(int score, string encoding, string input);
        void print(string group_message);
    private:
        Contender* champs;
        int size;
};
