#ifndef KONWERTER_STRUCTS_H
#define KONWERTER_STRUCTS_H


const unsigned char fileHeaderSizeKS = 14;    //rozmiar nagłówka pliku KS
const unsigned char infoHeaderSizeKS = 64;   // rozmiar informajcji o obrazie pliku KS
const unsigned char offsetKS = 78;            //początkowy adres bitów w tablicy pikseli.

const unsigned char fileHeaderSizeBMP = 14;    //rozmiar nagłówka pliku BMP
const unsigned char infoHeaderSizeBMP = 40;   // rozmiar informajcji o obrazie pliku BMP
const unsigned char offsetBMP = 54;            //początkowy adres bitów w tablicy pikseli.

struct Pixel {
    int R;
    int G;
    int B;
};

#endif //KONWERTER_STRUCTS_H
