#include "Node.h"

Node::Node(pair<int, int> a, pair<int, int> b) {
    this->quad = {a, b};
    for (auto &i : this->m_pSon) {
        i = nullptr;
    }
    this->rcolor = 0;
    this->gcolor = 0;
    this->bcolor = 0;
}

void Node::killSelf() {
    if (this->m_pSon[0] != nullptr) {
        for (auto &i : this->m_pSon) {
            i->killSelf();
        }
    }
    delete this;
}