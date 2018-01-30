#ifndef KONWERTER_FUNCTIONS_H
#define KONWERTER_FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Structs.h"


using namespace std;

vector<Pixel> revertPixelMirrorHorisontal(vector<Pixel> pixels, int width, int height);

char *readChars(string info);

unsigned char *createIMG(vector<Pixel> pixels, int width, int height);

int getPartedNumber(int value);


#endif //KONWERTER_FUNCTIONS_H
