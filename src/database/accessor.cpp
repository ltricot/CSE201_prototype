#include "driver.hpp"

EdgeAccessor::EdgeAccessor(std::string directory, unsigned int size)
    : driver(Driver(directory)), bufferSize(size) {

    updateBuffer(1.0); // initialize buffer

    this->someAuthors = this->driver.getKeys<Author>();
}

void EdgeAccessor::updateBuffer(float proportion) {

    int i = 0;
    while (i <= int(proportion * bufferSize)) {
        i++;
        // we remove a random edge from the buffer
        int k = rand() % this->replayBuffer.size(); // random int between 0 and replayBuffer.size()
        this->replayBuffer.erase(this->replayBuffer.begin() + k);

        // we add a random edge to the buffer
        int j = rand() % this->someAuthors.size(); // random int between 0 and someAuthors.size()
        Author au = someAuthors[j];
        std::vector<Edge> edges = this->driver.getFrom(au);
        int m = rand() % edges.size();          // random int between 0 and edges.size()
        this->replayBuffer.push_back(edges[m]); // or do we want to add all of them?
    }
}

EdgeAccessor::iterator EdgeAccessor::iterator::operator++() {
    this->cursor = rand() % this->parent->replayBuffer.size();
    return *this;
}

Edge EdgeAccessor::iterator::operator*() { return this->parent->replayBuffer[this->cursor]; }
