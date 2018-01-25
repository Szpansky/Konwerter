#ifndef KONWERTER_DEKODER_H
#define KONWERTER_DEKODER_H

#include "../Tools/Structs.h"


using namespace std;


void generateFileBMP(vector<Pixel> pixelVector, int width, int height);

vector<Pixel> readPixelsFromKS(char *filename);

unsigned char *readHeaderFromKS(char *filename);


#endif //KONWERTER_DEKODER_H
