#ifndef KONWERTER_KODER_H
#define KONWERTER_KODER_H

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "../Tools/Functions.h"
#include "../Tools/Structs.h"


vector<Pixel> readPixelsFromBMP(char *);

unsigned char *readHeaderFromBMP(char *);

void generateFileKS(vector<Pixel>, int width, int height, char *filenameOut);

vector<Pixel> convertToGrey(vector<Pixel> vectorPixels);


#endif //KONWERTER_KODER_H
