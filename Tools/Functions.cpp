#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Functions.h"


vector<Pixel> revertPixelMirrorHorisontal(vector<Pixel> pixels, int width, int height) {
    vector<Pixel> pixelVectorTMP;
    for (int i = 1; i < height + 1; i++) {
        for (int j = 0; j < width; j++) {
            pixelVectorTMP.push_back(
                    pixels[(pixels.size() - (width * i)) + (j)]);        //odwrocenie lustrzane w pionie
            //   cout << " " << (pixelVector.size() - (width * i)) + (j);
        }
    }
    return pixelVectorTMP;
}


char *readFileName(string info) {
    string input;

    cout << info << endl;
    cin >> input;

    char *filename = new char[input.length() + 1];
    strcpy(filename, input.c_str());

    return filename;
}


unsigned char *createIMG(vector<Pixel> pixels, int width, int height) {
    int x, y;
    unsigned char *img = NULL;
    img = (unsigned char *) malloc(3 * width * height);
    memset(img, 0, 3 * width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            x = i;
            y = (height - 1) - j;

            img[(x + y * width) * 3 + 2] = (unsigned char) (pixels[(x + y * width)].R);
            img[(x + y * width) * 3 + 1] = (unsigned char) (pixels[(x + y * width)].G);
            img[(x + y * width) * 3 + 0] = (unsigned char) (pixels[(x + y * width)].B);
        }
    }
    return img;
}

