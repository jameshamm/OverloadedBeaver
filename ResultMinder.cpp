#include <ResultMinder.h>

using namespace std;

const std::string message[4] = {"steps", "1s", "01s", "*s"};

ResultMinder::ResultMinder() {
    this->size = 0;
    this->group = 0;
    champs = nullptr;
}

ResultMinder::ResultMinder(int size, int group) {
    this->size = size;
    this->group = group;
    champs = new Contender[this->size];
}

int ResultMinder::insert(int score, std::string encoding, std::string input) {
    if(score >= champs[this->size-1].score) {
        // LOCK
        std::unique_lock<std::shared_timed_mutex> lock(mu);
        // UPDATE
        champs[this->size-1] = Contender(score, encoding, input);
        std::sort(&champs[0], &champs[this->size]);
        // UNLOCK
        lock.unlock();
        this->print();
    }
    return this->lowest();
}

int ResultMinder::lowest() {
    std::shared_lock<std::shared_timed_mutex> lock(mu);
    return champs[this->size-1].score;
}

void ResultMinder::print() {
    std::shared_lock<std::shared_timed_mutex> lock(mu);
    std::cout << "Current best " << message[group] << ", input length: " << champs[0].input.length() << std::endl;
    for(int i = 0; i < size; ++i) {
        std::cout << "\t" << champs[i];
        if(i % 3 == 2) {
            std::cout << std::endl;
        }
    }
    if(size % 3) {
        std::cout << std::endl;
    }
}

ResultMinder& ResultMinder::operator=(const ResultMinder& other) {
    std::unique_lock<std::shared_timed_mutex> lhs(mu, std::defer_lock);
    std::shared_lock<std::shared_timed_mutex> rhs(other.mu, std::defer_lock);
    std::lock(lhs, rhs);

    this->size = other.size;
    this->group = other.group;
    this->champs = other.champs;
    return *this;
}