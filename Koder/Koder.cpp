#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Koder.h"


using namespace std;


vector<Pixel> convertToGrey(vector<Pixel> vectorPixels) {
    vector<Pixel> vectorTMP;
    Pixel pixelTMP;
    int greyColor;

    for (int i = 0; i <= vectorPixels.size(); i++) {
        pixelTMP = vectorPixels[i];
        greyColor = (int) (pixelTMP.R * 0.299 + pixelTMP.G * 0.587 + pixelTMP.B * 0.114);
        pixelTMP.R = greyColor;
        pixelTMP.G = greyColor;
        pixelTMP.B = greyColor;
        vectorTMP.push_back(pixelTMP);
    }
    return vectorTMP;
}


vector<Pixel> readPixelsFromBMP(char *filename) {
    vector<Pixel> pixelVector;
    FILE *f = fopen(filename, "rb");

    if (f == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[offsetBMP];
    fread(info, sizeof(unsigned char), offsetBMP, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];
    char fileType[2];
    fileType[0] = *(char *) &info[0];
    fileType[1] = *(char *) &info[1];

    if (fileType[0] != 66 || fileType[1] != 77) {
        cout << "Plik nie jest typu BM ";
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


            pixel.R = getPartedNumber((int) data[j]);
            pixel.G = getPartedNumber((int) data[j + 1]);
            pixel.B = getPartedNumber((int) data[j + 2]);
/*
            pixel.R = (int) data[j];
            pixel.G = (int) data[j + 1];
            pixel.B = (int) data[j + 2];*/

            pixelVector.push_back(pixel);
        }
    }
    fclose(f);
    pixelVector = revertPixelMirrorHorisontal(pixelVector, width, height);
    return pixelVector;
}


unsigned char *readHeaderFromBMP(char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[54];
    fread(info, sizeof(unsigned char), offsetBMP, file); // read the 54-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

    char fileType[2];

    fileType[0] = *(char *) &info[0];
    fileType[1] = *(char *) &info[1];

    if (fileType[0] != 66 || fileType[1] != 77) {
        cout << "Plik nie jest typu BM ";
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


void generateFileKS(vector<Pixel> pixelVector, int width, int height, char *filenameOut) {

    unsigned char bmpfileheader[fileHeaderSizeKS] = {'K', 'S', 0, 0, 0, 0, 0, 0, 0, 0, offsetKS, 0, 0, 0};
    unsigned char bmpinfoheader[infoHeaderSizeKS] = {infoHeaderSizeKS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    int filesize = offsetKS + 3 * width * height;

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    bmpinfoheader[0] = (unsigned char) (infoHeaderSizeKS);
    bmpinfoheader[1] = (unsigned char) (infoHeaderSizeKS >> 8);
    bmpinfoheader[2] = (unsigned char) (infoHeaderSizeKS >> 16);
    bmpinfoheader[3] = (unsigned char) (infoHeaderSizeKS >> 24);

    bmpinfoheader[4] = (unsigned char) (width);
    bmpinfoheader[5] = (unsigned char) (width >> 8);
    bmpinfoheader[6] = (unsigned char) (width >> 16);
    bmpinfoheader[7] = (unsigned char) (width >> 24);

    bmpinfoheader[8] = (unsigned char) (height);
    bmpinfoheader[9] = (unsigned char) (height >> 8);
    bmpinfoheader[10] = (unsigned char) (height >> 16);
    bmpinfoheader[11] = (unsigned char) (height >> 24);


    bmpinfoheader[12] = (unsigned char) (1);


    FILE *f;
    f = fopen(filenameOut, "wb");
    fwrite(bmpfileheader, 1, fileHeaderSizeKS, f);
    fwrite(bmpinfoheader, 1, infoHeaderSizeKS, f);

    unsigned char *img = createIMG(pixelVector, width, height);

    for (int i = 0; i < height; i++) {
        fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
    }
    free(img);

    fclose(f);

}
