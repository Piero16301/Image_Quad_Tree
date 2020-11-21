#include <iostream>
#include <iomanip>

#define cimg_use_jpeg
#include "CImg.h"

using namespace cimg_library;
using namespace std;

struct Node{
    pair<pair<int, int>, pair<int, int>> quad;
    Node* m_pSon[4];
    bool color;
    Node(pair<int, int> a, pair<int, int>b){
        quad = {a, b};
        for(int i = 0; i < 4; i++){
            m_pSon[i] = nullptr;
        }
        color = false;
    }
};

class QuadTree{
private:
    Node* root;

    static bool isUniqueColor(Node* &qNode, CImg <char> &R){
        char color = R(qNode->quad.first.first,qNode->quad.first.second);
        for (int i = qNode->quad.first.first; i <= qNode->quad.second.first; i++) {
            for (int j = qNode->quad.first.second; j <= qNode->quad.second.second; j++) {
                if (R(i,j) != color) {
                    return false;
                }
            }
        }
        return true;
    }

    void insertRecursive(Node* &qNode, CImg <char> &R){
        if(isUniqueColor(qNode, R)){
            qNode->color = R(qNode->quad.first.first, qNode->quad.first.second) != '0';
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

    void loadImage(CImg <char> &R) {
        this->root->m_pSon[0] = new Node({0,0},{R.width()/2, R.height()/2});
        this->root->m_pSon[1] = new Node({R.width()/2+1,0},{R.width(), R.height()/2});
        this->root->m_pSon[2] = new Node({0,R.height()/2 + 1},{R.width()/2, R.height()});
        this->root->m_pSon[3] = new Node({R.width()/2 + 1,R.height() + 1},{R.width(), R.height()});
        insertRecursive(this->root->m_pSon[0],R);
        insertRecursive(this->root->m_pSon[1],R);
        insertRecursive(this->root->m_pSon[2],R);
        insertRecursive(this->root->m_pSon[3],R);
    }
};

CImg <char> Binarizar(CImg<float> & img, int umbral) {
    CImg <char> R(img.width(),img.height());
    for(int i=0;i< img.width();i++) {
        for (int j = 0; j < img.height(); j++) {
            int r = img(i, j, 0);
            int g = img(i, j, 1);
            int b = img(i, j, 2);
            if ((r + g + b) / 3 > umbral) {
                R(i, j) = 49;
            } else {
                R(i, j) = 48;
            }
        }
    }
    return R;
}

int main() {
    CImg <float> A("../imagen.jpeg");
    CImg <char> R =  Binarizar(A,40);
    /*for(int i = 0; i < R.width(); i++){
        for(int j = 0; j < R.height(); j++){
            cout << setw(2) << R(i, j);
        }
        cout << "\n";
    }
    */

    //A.display();
    //R.display();

    return 1;
}
