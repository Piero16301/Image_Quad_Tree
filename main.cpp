#include <iostream>

#include "QuadTree.h"

int main() {
    QuadTree quadTree;
    quadTree.loadImage("../imagenes/dragonball.jpg");
    quadTree.exportTree("../quad_tree.dat");
    quadTree.buildImage("../quad_tree.dat");
    cout << "FIN" << endl;
    return 0;
}
