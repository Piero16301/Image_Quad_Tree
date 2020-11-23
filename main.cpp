#include <iostream>

#define cimg_use_jpeg
#include "CImg.h"

using namespace cimg_library;
using namespace std;

struct Node{
    pair<pair<int, int>, pair<int, int>> quad;
    Node* m_pSon[4]{};
    bool color;

    Node(pair<int, int> a, pair<int, int>b) {
        quad = {a, b};
        for (auto &i : m_pSon) {
            i = nullptr;
        }
        color = false;
    }

    void killSelf() {
        if (this->m_pSon[0] != nullptr) {
            for (auto &i : m_pSon) {
                i->killSelf();
            }
        }
        delete this;
    }
};

class QuadTree{
private:
    Node* root;

    static bool isUniqueColor(Node* &qNode, CImg <int> &R) {
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

    void insertRecursive(Node* &qNode, CImg <int> &R){
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

public:
    QuadTree() : root{nullptr} {};

    void loadImage(CImg <int> &R) {
        this->root = new Node({0,0},{R.width()-1,R.height()-1});
        insertRecursive(this->root, R);
    }

    ~QuadTree() {
        this->root->killSelf();
    }
};

CImg <int> Binarizar(CImg <float> &img, int umbral) {
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

int main() {
    CImg <float> A("../imagenes/imagen_2.jpg");
    CImg <int> R =  Binarizar(A,20);
    R.display();
    QuadTree quadTree;
    quadTree.loadImage(R);
    cout << "FIN" << endl;
    return 0;
}
