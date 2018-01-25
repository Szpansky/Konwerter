#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;



struct Pixel {
    int R;
    int G;
    int B;
};



unsigned char *readHeaderFromBMP(char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, file); // read the 54-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;


    fclose(file);
    return info;

}

unsigned char *readDataFromBMP(char *filename) {
  vector<Pixel> pixelVector;
    FILE *f = fopen(filename, "rb");

    if (f == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

    int row_padded = (width * 3 + 3) & (~3);
    unsigned char *data = new unsigned char[row_padded];
    unsigned char tmp;

    Pixel pixel;
    int k = 0;

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
            k++;
        }
    }
    cout << "ilosc3 = " << k;
    fclose(f);
    return data;
}

vector<Pixel> revertPixelMirrorHorisontal(vector<Pixel> pixels, int width, int height) {
    vector<Pixel> pixelVectorTMP;
    for (int i = 1; i < height + 1; i++) {
        for (int j = 0; j < width; j++) {

            pixelVectorTMP.push_back(pixels[(pixels.size() - (width * i)) + (j)]);        //odwrocenie lustrzane w pionie

            //   cout << " " << (pixelVector.size() - (width * i)) + (j);
        }
    }
    // pixels = pixelVectorTMP;
    //pixelVectorTMP.clear();

    return pixelVectorTMP;
}

vector<Pixel> generatePixelsVector(char *filename) {
    vector<Pixel> pixelVector;
    FILE *f = fopen(filename, "rb");

    if (f == NULL) {
        cout << "Blad odczytu pliku";
        exit(1);
    }

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

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


char *readFileName(string info) {
    string input;

    cout << info << endl;
    cin >> input;

    char *filename = new char[input.length() + 1];
    strcpy(filename, input.c_str());

    return filename;
}


unsigned char *createIMG(vector<Pixel> pixels, int width, int height) {
    int x, y;
    unsigned char *img = NULL;
    img = (unsigned char *) malloc(3 * width * height);
    memset(img, 0, 3 * width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            x = i;
            y = (height - 1) - j;

            img[(x + y * width) * 3 + 2] = (unsigned char) (pixels[(x + y * width)].R);
            img[(x + y * width) * 3 + 1] = (unsigned char) (pixels[(x + y * width)].G);
            img[(x + y * width) * 3 + 0] = (unsigned char) (pixels[(x + y * width)].B);

        }
    }
    return img;
}


void generateFileBMP(vector<Pixel> pixelVector, int width, int height){

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    int filesize = 54 + 3 * width * height;

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
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);

    unsigned char *img = createIMG(pixelVector, width, height);

    for (int i = 0; i < height; i++) {
        fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);

    }
    free(img);

    fclose(f);
}


int main() {
    unsigned char *info; //header from bmp
    vector<Pixel> pixelVector; //pixels data

    char *filename;
    filename = readFileName("Podaj nazwe pliku eg: test.bmp");

    info = readHeaderFromBMP(filename);
    int width = *(int *) &info[18];
    int height = *(int *) &info[22];

    pixelVector = generatePixelsVector(filename);

    generateFileBMP(pixelVector,width,height);

    return 0;
}







