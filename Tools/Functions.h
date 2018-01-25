#ifndef KONWERTER_FUNCTIONS_H
#define KONWERTER_FUNCTIONS_H

#include <vector>
#include <string>
#include "Structs.h"

using namespace std;

vector<Pixel> revertPixelMirrorHorisontal(vector<Pixel> pixels, int width, int height);

char *readFileName(string info);

unsigned char *createIMG(vector<Pixel> pixels, int width, int height);


#endif //KONWERTER_FUNCTIONS_H
