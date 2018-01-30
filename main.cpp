#include <iostream>
#include <vector>

#include "Dekoder/Dekoder.h"
#include "Koder/Koder.h"
#include "lz77.h"


int main() {
    unsigned char *info;
    vector<Pixel> pixelVector;

    char *option;
    option = readChars("Wybierz opcje:\n1:Kodowanie\n2:Dekodowanie\n");

    char *grey;
    char *filenameIn, *filenameOut;
    char *fileTMP = const_cast<char *>("tempFile");

    filenameIn = readChars("Podaj nazwe pliku Wejsciowego, eg. test.bmp / test.ks\n");

    filenameOut = readChars("Podaj nazwe pliku Wyjsciowego\n");

    switch (*option) {
        case 49: {
            info = readHeaderFromBMP(filenameIn);
            int width = *(int *) &info[18];
            int height = *(int *) &info[22];
            pixelVector = readPixelsFromBMP(filenameIn);
            grey = readChars("\nWybierz opcje:\n1:Skala szarosci\n2:Kolor\n");
            if (*grey == 49) {
                pixelVector = convertToGrey(pixelVector);
            }
            generateFileKS(pixelVector, width, height, fileTMP);
            inicialFiles(fopen(fileTMP, "rb"), fopen(filenameOut, "wb"));
            Encode();
        }
            break;
        case 50: {
            inicialFiles(fopen(filenameIn, "rb"), fopen(fileTMP, "wb"));
            Decode();
            info = readHeaderFromKS(fileTMP);
            int width = *(int *) &info[18];
            int height = *(int *) &info[22];
            pixelVector = readPixelsFromKS(fileTMP);
            generateFileBMP(pixelVector, width, height, filenameOut);
        }
            break;
        default:
            printf("Bledna opcja\n");
    }

    return 0;
}







