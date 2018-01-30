//
// Created by Marcin on 2018-01-28.
//

#ifndef KONWERTER_LZ77_H
#define KONWERTER_LZ77_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void SendBits(unsigned int bits, unsigned int numbits);

unsigned int ReadBits(unsigned int numbits);

void SendMatch(unsigned int matchlen, unsigned int matchdistance);

void SendChar(unsigned int character);

void InitEncode(void);

unsigned int LoadDict(unsigned int dictpos);

void DeleteData(unsigned int dictpos);

void HashData(unsigned int dictpos, unsigned int bytestodo);

void FindMatch(unsigned int dictpos, unsigned int startlen);

void DictSearch(unsigned int dictpos, unsigned int bytestodo);

void Encode(void);

void Decode(void);

void inicialFiles(FILE *infileTMP, FILE *outfileTMP);


#endif //KONWERTER_LZ77_H
