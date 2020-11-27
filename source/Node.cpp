#include "Node.h"

Node::Node(pair<int, int> a, pair<int, int> b) {
    this->quad = {a, b};
    for (auto &i : this->m_pSon) {
        i = nullptr;
    }
#ifdef black_and_white_image
    this->color = false;
#else
    this->rcolor = 0;
    this->gcolor = 0;
    this->bcolor = 0;
#endif
}

void Node::killSelf() {
    if (this->m_pSon[0] != nullptr) {
        for (auto &i : this->m_pSon) {
            i->killSelf();
        }
    }
    delete this;
}