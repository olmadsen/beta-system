#include "png.h"
#include <stdlib.h>
#include <math.h>
#include "betaimage.h"
#include "betapng.h"


int BetaReadPNG(char *name, BetaImage *image, int row_order)
{
  FILE *fp;
  char header[8];

  png_structp png_ptr;
  png_infop   info_ptr;
  png_infop   end_info;

  png_byte    color_type;
  png_uint_32 bit_depth;

  double gamma;
  double screen_gamma = 2.2;
  

  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowbytes;
  png_byte    channels;

  
  unsigned char *pixels;
  png_bytep     *rows;
  int           i;

  int alpha;


  /*
   * Open file and check that it is in PNG format
   */
 
  printf("beta read png %s\n", name);

  fp = fopen(name, "rb");

  if(!fp) {
    return NoSuchFileError;
  }

  
  fread(header, 1, 8, fp);
  
  if (!png_check_sig(header, 8)) {
    fclose(fp);
    return WrongFormatError;
  }


  /*
   * Initialize the PNG reading engine
   */
  
  png_ptr = png_create_read_struct
    (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  
  info_ptr = png_create_info_struct(png_ptr);

  if (!info_ptr) {
     fclose(fp);
     png_destroy_read_struct(&png_ptr, NULL, NULL);
     return MemoryError;
  }
  end_info = png_create_info_struct(png_ptr);
  
  if (!end_info) {
     fclose(fp);
     png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
     return MemoryError;
  }

  png_init_io(png_ptr, fp);

  png_set_sig_bytes(png_ptr, 8);


  /*
   * Read the PNG info.
   */

  png_read_info(png_ptr, info_ptr);
  
  /*
   * Setup to always read in RGB[A] format where each
   * component is 8 bit
   */
  

  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);  /* If color_type is RGB[A]
                                                      * the bit_depth refers to
                                                      * the size of the components
                                                      */


  alpha = 0;

  
  if (color_type & PNG_COLOR_MASK_ALPHA) {
    alpha = 1;
  }
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_expand(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand(png_ptr);
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)){
    png_set_expand(png_ptr);
    alpha = 1;
  } else {
    png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
  }
 
  if (bit_depth == 16)
    png_set_strip_16(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);


  /*
   * Handle gamma correction if this is supplied in the file
   */

  if (png_get_gAMA(png_ptr, info_ptr, &gamma))
    png_set_gamma(png_ptr, screen_gamma, gamma);

  
  /*
   * Now update the read info struct
   */

  png_read_update_info(png_ptr, info_ptr);

  /*
   * Set up the rowpointer array for reading
   */

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);

  
  pixels = (unsigned char *) malloc(rowbytes * height);

  if (pixels == NULL) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return MemoryError;
  }

  rows = (png_bytep *) malloc(height * sizeof(png_bytep));

  if(rows == NULL) {
    free(pixels);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return MemoryError;
  }


  switch(row_order) {
  case TOP_DOWN:
    for(i = 0;  i < height;  ++i) {
      rows[i] = pixels + i*rowbytes;
    }
    break;
  case BOTTOM_UP:
    for(i = 0;  i < height;  ++i) {
      rows[height - i - 1] = pixels + i*rowbytes;
    }
    break;
  }
  /*
   * Now read the image data
   */

  png_read_image(png_ptr, rows);

  /*
   * We are done with the png engine
   */

  png_read_end(png_ptr, NULL);
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  free(rows);
  fclose(fp);


  /* Process the pixel data */


  image->alpha = alpha;
  image->width = width;
  image->height = height;
  image->data = pixels;
  image->rowbytes = rowbytes;
  image->palette_size = 0;
  image->palette = NULL;
  image->pixel_size = 24;
  return 0;
  
}

