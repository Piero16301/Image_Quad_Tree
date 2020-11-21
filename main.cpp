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

    bool isUniqueColor(Node* &qNode){}

    void insertRecursive(Node* &qNode){
        if(isUniqueColor(qNode)){
            return;
        }
        qNode->m_pSon[0] = new Node({qNode->quad.first});
    }

public:
    QuadTree() : root{nullptr} {};
    void loadImage(CImg <char> &R){
        auto q0Node = new Node({0,0},{R.width()/2, R.height()/2});
        auto q1Node = new Node({R.width()/2+1,0},{R.width(), R.height()/2});
        auto q2Node = new Node({0,R.height()/2 + 1},{R.width()/2, R.height()});
        auto q3Node = new Node({R.width()/2 + 1,R.height() + 1},{R.width(), R.height()});
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
