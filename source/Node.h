#ifndef IMAGE_QUAD_TREE_NODE_H
#define IMAGE_QUAD_TREE_NODE_H

#include <utility>

using namespace std;

class QuadTree;

class Node {
private:
    pair <pair <unsigned short int, unsigned short int>,pair<unsigned short int,unsigned short int>> quad;
    Node* m_pSon[4]{};
    unsigned char rcolor{};
    unsigned char gcolor{};
    unsigned char bcolor{};

protected:
    void killSelf();

public:
    Node(pair<int, int> a, pair<int, int>b);

    friend class QuadTree;
};

#endif //IMAGE_QUAD_TREE_NODE_H