#ifndef __BMP__
#define __BMP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;      
typedef unsigned int DWORD;    
typedef signed int LONG;

#pragma pack(push, 1)
struct tagBITMAPFILEHEADER
{
  WORD bfType;             
  DWORD bfSize;
  WORD bfReserved1;
  WORD bfReserved2;
  DWORD bfOffBits;        
} ;//__attrubute__((packed));    
#pragma pack(pop)

#pragma pack(push, 1)
struct tagBITMAPINFOHEADER
{
  DWORD biSize;
  LONG biWidth;
  LONG biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} ;//__attrubute__((__packed__));	 
#pragma pack(pop)

typedef struct tagBITMAPFILEHEADER bITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER bITMAPINFOHEADER;

typedef struct tagPICTURE {
  bITMAPINFOHEADER bitmapInfo;
  bITMAPFILEHEADER bitmapFile;
  BYTE* bitmapImage;
} PICTURE;
 
int load_bmp(const char* name, PICTURE* pic);
int save_bmp(const char* name, PICTURE* pic);
int crop(PICTURE* pic, PICTURE* cropped, int x, int y, int w, int h);
int rotate(PICTURE* pic);
int insert(PICTURE* pic, const char* key, const char* msg);
int extract(PICTURE* pic, const char* key, char* msg);

#endif
