#include "../include/bmp.h"


int main (int argc, char** argv) {
  if (strcmp(argv[1], "crop-rotate") == 0) {
    PICTURE pic, cropped;
    int x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);
    int result;

    result = load_bmp(argv[2], &pic);    
    if (result != 0)
      return result;

    result = crop(&pic, &cropped, x, y, w, h);
    if (result != 0)
      return result;

    result = rotate(&cropped);
    if (result != 0)
      return result;

    result = save_bmp(argv[3], &cropped);  
    if (result != 0)
      return result;

    free(pic.bitmapImage);  
    free(cropped.bitmapImage);
  }

  if (strcmp(argv[1], "insert") == 0) {
    PICTURE pic;

    int result;

    result = load_bmp(argv[2], &pic);
    if (result != 0)
      return result;

    result = insert(&pic, argv[4], argv[5]);
    if (result != 0)
      return result;

    result = save_bmp(argv[3], &pic);  
    if (result != 0)
      return result;
    
    free(pic.bitmapImage);  
  }

  if (strcmp(argv[1], "extract") == 0) {
    PICTURE pic;

    int result;

    result = load_bmp(argv[2], &pic);
    if (result != 0)
      return result;

    result = extract(&pic, argv[3], argv[4]);
    if (result != 0)
      return result;

    free(pic.bitmapImage);
  }

  return 0;
}
