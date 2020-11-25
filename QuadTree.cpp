#include "QuadTree.h"

QuadTree::QuadTree() {
    this->root = nullptr;
}

bool QuadTree::isUniqueColor(Node *&qNode, CImg<int> &R) {
    int color = R(qNode->quad.first.first,qNode->quad.first.second);
    for (int i = qNode->quad.first.first; i <= qNode->quad.second.first; i++) {
        for (int j = qNode->quad.first.second; j <= qNode->quad.second.second; j++) {
            if (R(i,j) != color) {
                return false;
            }
        }
    }
    return true;
}

void QuadTree::insertRecursive(Node *&qNode, CImg<int> &R) {
    if(isUniqueColor(qNode, R)){
        qNode->color = R(qNode->quad.first.first, qNode->quad.first.second) != 0;
        return;
    }
    int midX = (qNode->quad.second.first-qNode->quad.first.first)/2;
    int midY = (qNode->quad.second.second - qNode->quad.first.second)/2;
    qNode->m_pSon[0] = new Node({qNode->quad.first,{qNode->quad.first.first+midX,qNode->quad.first.second+midY}});
    qNode->m_pSon[1] = new Node({qNode->quad.first.first+midX+1,qNode->quad.first.second},{qNode->quad.second.first,qNode->quad.first.second+midY});
    qNode->m_pSon[2] = new Node({qNode->quad.first.first,qNode->quad.first.second+midY+1},{qNode->quad.first.first+midX,qNode->quad.second.second});
    qNode->m_pSon[3] = new Node({qNode->quad.first.first+midX+1,qNode->quad.first.second+midY+1},qNode->quad.second);
    insertRecursive(qNode->m_pSon[0],R);
    insertRecursive(qNode->m_pSon[1],R);
    insertRecursive(qNode->m_pSon[2],R);
    insertRecursive(qNode->m_pSon[3],R);
}

void QuadTree::writeRecursive(ofstream &output, Node* &node) {
    if (node->m_pSon[0] == nullptr) {
        Node temp = Node(*node);
        output.write((char*)&temp, sizeof(Node));
        return;
    }
    for (auto &i : node->m_pSon) {
        writeRecursive(output, i);
    }
}

void QuadTree::fillQuad(ifstream &input, Node &node, CImg <int> &image) {
    for (int i = node.quad.first.first; i <= node.quad.second.first; i++) {
        for (int j = node.quad.first.second; j <= node.quad.second.second; j++) {
            image(i,j) = ((node.color) ? 1 : 0);
        }
    }
}

CImg<int> QuadTree::binarize(CImg<float> &img, int umbral) {
    CImg <int> R(img.width(),img.height());
    for(int i=0;i< img.width();i++) {
        for (int j = 0; j < img.height(); j++) {
            // Extrae color rojo (posicion 0 de la 3ra dimension)
            int r = img(i, j, 0);
            // Extrae color verde (posicion 1 de la 3ra dimension)
            int g = img(i, j, 1);
            // Extrae color azul (posicion 2 de la 3ra dimension)
            int b = img(i, j, 2);
            if ((r + g + b) / 3 > umbral) {
                R(i, j) = 1;
            } else {
                R(i, j) = 0;
            }
        }
    }
    return R;
}

void QuadTree::loadImage(const string& path) {
    CImg <float> A(path.c_str());
    CImg <int> R = binarize(A,20);
    this->root = new Node({0,0},{R.width()-1,R.height()-1});
    insertRecursive(this->root, R);
}

void QuadTree::exportTree(const string &path) {
    ofstream output;
    output.open(path, ios::out);
    // Write image width
    unsigned int width = this->root->quad.second.first+1;
    output.write((char*)&width, sizeof(unsigned int));

    // Write image heigth
    unsigned int heigth = this->root->quad.second.second+1;
    output.write((char*)&heigth, sizeof(unsigned int));

    // Write only leafs recursively
    writeRecursive(output, this->root);
    output.close();
}

void QuadTree::buildImage(const string &path) {
    ifstream input;
    input.open(path, ios::in);

    // Read width and height from file
    unsigned int width;
    unsigned int height;
    input.read((char*)&width, sizeof(unsigned int));
    input.read((char*)&height, sizeof(unsigned int));

    // Vector to save all nodes from file
    vector <Node> nodes;

    // Node to iterate through file
    Node current({0,0},{0,0});

    // Read nodes until end of file
    while (input.read((char*)&current, sizeof(Node))) {
        nodes.push_back(current);
    }
    input.close();

    // Construct CImg from readed nodes
    CImg <int> image(width,height);
    for (auto it : nodes) {
        fillQuad(input, it, image);
    }

    // Display image
    image.display();
}

QuadTree::~QuadTree() {
    if(this->root){
        this->root->killSelf();
    }
}