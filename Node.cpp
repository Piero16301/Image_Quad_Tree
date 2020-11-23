#include "Node.h"

Node::Node(pair<int, int> a, pair<int, int> b) {
    this->quad = {a, b};
    for (auto &i : this->m_pSon) {
        i = nullptr;
    }
    this->color = false;
}

void Node::killSelf() {
    if (this->m_pSon[0] != nullptr) {
        for (auto &i : this->m_pSon) {
            i->killSelf();
        }
    }
    delete this;
}