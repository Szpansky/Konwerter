#ifndef KONWERTER_KODER_H
#define KONWERTER_KODER_H

#include <vector>
#include "../Tools/Functions.h"
#include "../Tools/Structs.h"


void generateFileKS(vector<Pixel>, int, int);

vector<Pixel> readPixelsFromBMP(char *);

unsigned char *readHeaderFromBMP(char *);

void generateFileKS(vector<Pixel>, int, int);


#endif //KONWERTER_KODER_H
