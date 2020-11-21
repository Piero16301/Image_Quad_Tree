#include <iostream>
#define cimg_use_jpeg
#include "CImg.h"

using namespace cimg_library;
using namespace std;

CImg <char> Binarizar(CImg<float> & img, int umbral) {
    CImg <char> R(img.width(),img.height());
    for(int i=0;i< img.width();i++) {
        for (int j = 0; j < img.height(); j++) {
            int r = img(i, j, 0);
            int g = img(i, j, 1);
            int b = img(i, j, 2);
            if ((r + g + b) / 3 > umbral) {
                R(i, j) = 255;
            } else {
                R(i, j) = 0;
            }
        }
    }
    return R;
}

int main() {
    CImg <float> A("../imagen.jpeg");
    CImg <char> R =  Binarizar(A,40);
    //A.display();
    //R.display();

    return 1;
}
