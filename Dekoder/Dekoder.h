#ifndef KONWERTER_DEKODER_H
#define KONWERTER_DEKODER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "Dekoder.h"
#include "../Tools/Functions.h"
#include "../Tools/Structs.h"

void generateFileBMP(vector<Pixel> pixelVector, int width, int height, char *filenameOut);

vector<Pixel> readPixelsFromKS(char *filename);

unsigned char *readHeaderFromKS(char *filename);


#endif //KONWERTER_DEKODER_H
