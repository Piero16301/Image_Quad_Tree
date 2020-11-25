#ifndef IMAGE_QUAD_TREE_QUADTREE_H
#define IMAGE_QUAD_TREE_QUADTREE_H

#include <fstream>
#include <vector>
#define cimg_use_jpeg
#include "CImg.h"
#include "Node.h"

using namespace cimg_library;
using namespace std;

class QuadTree {
private:
    Node* root;

protected:
    static bool isUniqueColor(Node* &qNode, CImg <int> &R);

    void insertRecursive(Node* &qNode, CImg <int> &R);

    void writeRecursive(ofstream &output, Node* &node);

    static void fillQuad(ifstream &input, Node &node, CImg <int> &image);

    static CImg <int> binarize(CImg <float> &img, int umbral);

public:
    QuadTree();

    void loadImage(const string& path);

    void exportTree(const string& path);

    void buildImage(const string& path);

    ~QuadTree();
};

#endif //IMAGE_QUAD_TREE_QUADTREE_H