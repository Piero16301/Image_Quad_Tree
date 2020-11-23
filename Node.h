#ifndef IMAGE_QUAD_TREE_NODE_H
#define IMAGE_QUAD_TREE_NODE_H

#include <utility>

using namespace std;

class QuadTree;

class Node {
private:
    pair <pair <int,int>,pair<int,int>> quad;
    Node* m_pSon[4]{};
    bool color{};

protected:
    void killSelf();

public:
    Node(pair<int, int> a, pair<int, int>b);

    friend class QuadTree;
};

#endif //IMAGE_QUAD_TREE_NODE_H