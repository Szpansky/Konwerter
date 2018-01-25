#include <iostream>
#include <vector>

#include "Dekoder/Dekoder.h"
#include "Koder/Koder.h"


int main() {
    unsigned char *info;
    vector<Pixel> pixelVector;

    char *filename;
    filename = readFileName("Podaj nazwe pliku eg: img.ks");

    info = readHeaderFromKS(filename);
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

    pixelVector = readPixelsFromKS(filename);

    generateFileBMP(pixelVector, width, height);

    generateFileKS(pixelVector, width, height);


    return 0;
}







