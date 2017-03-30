#include <algorithm>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

#ifndef ResultMinder_H
#define ResultMinder_H

struct Contender {
    int score;
    std::string encoding;
    std::string input;

    Contender() {
        this->score = 10;
        this->encoding = "None";
        this->input = "None";
    }

    Contender(int score, std::string encoding, std::string input) {
        this->score = score;
        this->encoding = encoding;
        this->input = input;
    }

    bool operator<(const Contender& rhs) const {
        if(this->score > rhs.score) {
            return true;
        } else if(this->score < rhs.score) {
            return false;
        }
        if(rhs.encoding == "None") {
            return true;
        }
        return false;
    }

    friend inline std::ostream& operator<<(std::ostream &o, const Contender& a) {
        o << "(" << a.encoding << ", " << a.input << ", " << a.score << ")";
        return o;
    }
};

class ResultMinder {
    public:
        ResultMinder();
        ResultMinder(int size, int group);
        ~ResultMinder(){};
        int lowest();
        int insert(int score, std::string encoding, std::string input);
        void print();
        ResultMinder& operator=(const ResultMinder& other);
    private:
        Contender* champs;
        int size;
        int group;
        mutable std::shared_timed_mutex mu;
};

#endif