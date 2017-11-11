#include "../include/bmp.h"
#include <ctype.h>
#define padding_zeros(c) ((4 - ((3 * (c)) % 4)) % 4)


int load_bmp(const char* name, PICTURE* pic) {
  FILE* fin = fopen(name, "rb");

  if (!fin)
    return 1;

  fread(&(pic->bitmapFile), sizeof(bITMAPFILEHEADER), 1, fin);
  fread(&(pic->bitmapInfo), sizeof(bITMAPINFOHEADER), 1, fin);

  int i = 0;
  int trash;

  int w = pic->bitmapInfo.biWidth, h = pic->bitmapInfo.biHeight;

  pic->bitmapImage = (BYTE*)malloc(3 * w * h * 1);

  if (!pic->bitmapImage)
    return 2;

  for (; i < h; i++) {
    fread(pic->bitmapImage + 3 * i * w, 1, 3 * w, fin);
    fread(&trash, 1, padding_zeros(w), fin);
  }

  fclose(fin);

  return 0;
}


int save_bmp(const char* name, PICTURE* pic) {
  FILE* fout = fopen(name, "wb");

  if (!fout)
    return 1;

  fwrite(&(pic->bitmapFile), sizeof(bITMAPFILEHEADER), 1, fout);
  fwrite(&(pic->bitmapInfo), sizeof(bITMAPINFOHEADER), 1, fout);

  int i = 0, trash = 0;

  int w = pic->bitmapInfo.biWidth, h = pic->bitmapInfo.biHeight;

  for (; i < h; i++) {
    fwrite(pic->bitmapImage + 3 * i * w, 1, 3 * w, fout);
    fwrite(&trash, 1, padding_zeros(w), fout);
  }

  fclose(fout);

  return 0;
}


int crop(PICTURE* pic, PICTURE* cropped, int x, int y, int w, int h) {
  if (x < 0 || y < 0 || w < 0 || h < 0 || x + w > pic->bitmapInfo.biWidth || y + h > pic->bitmapInfo.biHeight)
    return 3;

  memcpy(&(cropped->bitmapFile), &(pic->bitmapFile), sizeof(bITMAPFILEHEADER));
  memcpy(&(cropped->bitmapInfo), &(pic->bitmapInfo), pic->bitmapInfo.biSize);
  
  cropped->bitmapInfo.biHeight = h;
  cropped->bitmapInfo.biWidth = w;
  cropped->bitmapInfo.biSizeImage = w * h * 3 + padding_zeros(w) * h;
  cropped->bitmapFile.bfSize = w * h * 3 + cropped->bitmapInfo.biSize + sizeof(bITMAPFILEHEADER) + padding_zeros(w) * h;
  
  int starty = pic->bitmapInfo.biHeight - y - h, finishy = pic->bitmapInfo.biHeight - y - 1;
  int i, cnt = 0;
  int wpic = pic->bitmapInfo.biWidth;

  cropped->bitmapImage = (BYTE*)malloc(cropped->bitmapInfo.biSizeImage);  

  if (!cropped->bitmapImage)
    return 2;

  for (i = starty; i <= finishy; i++) {
    memcpy(cropped->bitmapImage + cnt * 3 * w, pic->bitmapImage + i * 3 * wpic + x * 3, 3 * w);
    cnt++;
  } 

  return 0;
}


int rotate(PICTURE* pic) {
  BYTE* new_bitmap = (BYTE*)malloc(pic->bitmapInfo.biSizeImage);  

  if (!new_bitmap)
    return 2;

  int w = pic->bitmapInfo.biWidth, h = pic->bitmapInfo.biHeight;

  pic->bitmapInfo.biSizeImage += padding_zeros(h) * w - padding_zeros(w) * h;
  pic->bitmapFile.bfSize += padding_zeros(h) * w - padding_zeros(w) * h;

  int i, j;

  for (i = 0; i < h; i++)
    for (j = 0; j < w; j++)
      memcpy(new_bitmap + 3 * ((w - 1 - j) * h + i), pic->bitmapImage + 3 * (i * w + j), 3);

  pic->bitmapInfo.biHeight = w;
  pic->bitmapInfo.biWidth = h;

  free(pic->bitmapImage);
  pic->bitmapImage = new_bitmap;

  return 0;
}


static int encoded_symbol(int ch) {
  if (isalpha(ch))
    return ch - 'A';
  else if (ch == ' ')
    return 26;
  else if (ch == '.')
    return 27;
  else
    return 28;
}


static int component(unsigned char comp) {
  if (comp == 'B')
    return 0;
  if (comp == 'G')
    return 1;
  return 2;
}


int insert(PICTURE* pic, const char* key, const char* msg) {
  FILE* fkey = fopen(key, "rt");
  FILE* fmsg = fopen(msg, "rt");

  if (!fkey || !fmsg)
    return 1;

  int smb, x, y;
  int w = pic->bitmapInfo.biWidth, h = pic->bitmapInfo.biHeight;
  unsigned char comp;

  while ((smb = getc(fmsg)) != EOF) {
    int i = 0;

    smb = encoded_symbol(smb);

    for (; i < 5; i++) {
      fscanf(fkey, "%i %i %c\n", &x, &y, &comp);
      y = h - y - 1;
      
      int bit = 1 & (smb >> i);
      int shift = component(comp);      
      
      if (bit)
      	*(pic->bitmapImage + 3 * (y * w + x) + shift) |= 1;
      else
        *(pic->bitmapImage + 3 * (y * w + x) + shift) &= 254;	
    }     
  }

  fclose(fkey);
  fclose(fmsg);

  return 0;
}


static unsigned char get_symbol(int num) {
  if (0 <= num && num <= 25)
    return 'A' + num;
  else if (num == 26)
    return ' ';
  else if (num == 27)
    return '.';
  else
    return ',';
}


int extract(PICTURE* pic, const char* key, char* msg) {
  FILE* fkey = fopen(key, "rt");
  FILE* fmsg = fopen(msg, "wt");

  if (!fkey || !fmsg)
    return 1;

  int smb = 0, x, y;
  int w = pic->bitmapInfo.biWidth, h = pic->bitmapInfo.biHeight;
  unsigned char comp;

  while (fscanf(fkey, "%i %i %c\n", &x, &y, &comp) == 3) {
    int i = 0;

    y = h - y - 1;
    int shift = component(comp);      
    int bit = *(pic->bitmapImage + 3 * (y * w + x) + shift) & 1;  
    smb = bit;

    for (i = 1; i < 5; i++) {
      fscanf(fkey, "%i %i %c\n", &x, &y, &comp);
      y = h - y - 1;
      shift = component(comp);
      bit = *(pic->bitmapImage + 3 * (y * w + x) + shift) & 1;
      smb += (bit << i);
    }

    fprintf(fmsg, "%c", get_symbol(smb));     
  }

  fclose(fkey);
  fclose(fmsg);

  return 0;
}

