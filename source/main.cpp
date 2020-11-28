#include <iostream>

#include "QuadTree.h"

int main() {
    QuadTree quadTree;
    quadTree.loadImage("../../images/dragonball.jpg");
    quadTree.exportTree("../../binaries/quad_tree.dat");
    quadTree.buildImage("../../binaries/quad_tree.dat");
    cout << "SUCCESSFUL FINISH" << endl;
    return 0;
}
