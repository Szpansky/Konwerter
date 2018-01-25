#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "Dekoder.h"
#include "../Tools/Functions.h"


using namespace std;


void generateFileBMP(vector<Pixel> pixelVector, int width, int height) {

    unsigned char bmpfileheader[fileHeaderSizeBMP] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, offsetBMP, 0, 0, 0};
    unsigned char bmpinfoheader[infoHeaderSizeBMP] = {infoHeaderSizeBMP, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};    //padding do konca lini

    int filesize = offsetBMP + 3 * width * height;

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    bmpinfoheader[4] = (unsigned char) (width);
    bmpinfoheader[5] = (unsigned char) (width >> 8);
    bmpinfoheader[6] = (unsigned char) (width >> 16);
    bmpinfoheader[7] = (unsigned char) (width >> 24);
    bmpinfoheader[8] = (unsigned char) (height);
    bmpinfoheader[9] = (unsigned char) (height >> 8);
    bmpinfoheader[10] = (unsigned char) (height >> 16);
    bmpinfoheader[11] = (unsigned char) (height >> 24);

    FILE *f;
    f = fopen("img.bmp", "wb");
    fwrite(bmpfileheader, 1, fileHeaderSizeBMP, f);
    fwrite(bmpinfoheader, 1, infoHeaderSizeBMP, f);

    unsigned char *img = createIMG(pixelVector, width, height);

    for (int i = 0; i < height; i++) {
        fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
    }
    free(img);

    fclose(f);
}


vector<Pixel> readPixelsFromKS(char *filename) {
    vector<Pixel> pixelVector;
    FILE *f = fopen(filename, "rb");

    if (f == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[offsetKS];
    fread(info, sizeof(unsigned char), offsetKS, f); // read the 78-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];
    char fileType[2];
    fileType[0] = *(char *) &info[0];
    fileType[1] = *(char *) &info[1];

    if (fileType[0] != 75 || fileType[1] != 83) {
        cout << "Plik nie jest typu KS ";
        exit(1);
    }

    int row_padded = (width * 3 + 3) & (~3);
    unsigned char *data = new unsigned char[row_padded];
    unsigned char tmp;

    Pixel pixel;

    for (int i = 0; i < height; i++) {
        fread(data, sizeof(unsigned char), row_padded, f);
        for (int j = 0; j < width * 3; j += 3) {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j + 2];
            data[j + 2] = tmp;

            // cout << "R: " << (int) data[j] << " G: " << (int) data[j + 1] << " B: " << (int) data[j + 2] << endl;
            pixel.R = (int) data[j];
            pixel.G = (int) data[j + 1];
            pixel.B = (int) data[j + 2];
            pixelVector.push_back(pixel);
        }
    }
    fclose(f);
    pixelVector = revertPixelMirrorHorisontal(pixelVector, width, height);
    return pixelVector;
}


unsigned char *readHeaderFromKS(char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[offsetKS];
    fread(info, sizeof(unsigned char), offsetKS, file); // read the 78-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

    char fileType[2];

    fileType[0] = *(char *) &info[0];
    fileType[1] = *(char *) &info[1];

    if (fileType[0] != 75 || fileType[1] != 83) {
        cout << "Plik nie jest typu KS ";
        exit(1);
    }

    cout << endl;
    cout << "  Type: " << fileType[0] << fileType[1] << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

    fclose(file);
    return info;
}

