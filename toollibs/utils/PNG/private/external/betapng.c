#include <png.h>
#include <stdlib.h>
#include <math.h>
#include "betaimage.h"
#include "betapng.h"

#define NoSuchFileError  1
#define WrongFormatError 2
#define MemoryError      3




int BetaReadPNG(char *name, BetaImage *image)
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
  png_uint_32   i;


  int alpha;
  

  /*
   * Open file and check that it is in PNG format
   */
  
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
  
  if (!info_ptr) {
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

  printf("color_type = %d, bit_depth = %d\n", (int) color_type, (int) bit_depth);
  
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_expand(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand(png_ptr);
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)){
    png_set_expand(png_ptr);
    alpha = 1;
  } else {
    png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
    alpha = 0;
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

  for (i = 0;  i < height;  ++i) {
        rows[i] = pixels + i*rowbytes;
  }

  /*
   * Now read the image data
   */

  png_read_image(png_ptr, rows);

  /*
   * We are done with the png engine
   */

  png_read_end(png_ptr, NULL);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  free(rows);
  fclose(fp);


  /* Process the pixel data */

  printf("width = %d, height = %d, rowbytes = %d\n", width, height, rowbytes);

  printf("channels = %d\n", (int) channels);

  image->alpha = alpha;
  image->width = width;
  image->height = height;
  image->data = pixels;
  image->rowbytes = rowbytes;
  
  return 0;
  
}

int BetaReadPNGToBetaImage(char *name, BetaImage *image)
{
  FILE *fp;
  char header[8];

  png_byte color_type;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowbytes;
  png_uint_32 depth;

  long pixel_size;
  
  double gamma, screen_gamma;

  
  png_structp png_ptr;
  png_infop   info_ptr;
  png_infop   end_info;

  png_bytep pixels;
  png_bytep iter;
  png_uint_32 index;

  png_bytep *rowpointers;

  png_colorp palette;
  int num_palette;
  
  Color *betapalette = NULL;
  
  fp = fopen(name, "rb");
  
  if(!fp) {
    return NoSuchFileError;
  }
  
  fread(header, 1, 8, fp);
  
  if (!png_check_sig(header, 8)) {
    fclose(fp);
    return WrongFormatError;
  }
  

  png_ptr = png_create_read_struct
    (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  
  info_ptr = png_create_info_struct(png_ptr);

  if (!info_ptr) {
     fclose(fp);
     png_destroy_read_struct(&png_ptr, NULL, NULL);
     return MemoryError;
  }
  end_info = png_create_info_struct(png_ptr);
  
  if (!info_ptr) {
     fclose(fp);
     png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
     return MemoryError;
  }

  png_init_io(png_ptr, fp);

  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);


  color_type = png_get_color_type(png_ptr, info_ptr);
  depth = png_get_bit_depth(png_ptr, info_ptr);


  /* NOTE: If the color_type is RGB (truecolor) then
   * depth refers to the number of bits per component
   * The following code ensures that a component is
   * always 8 bit. PNG supports 1, 2, 4, 8 and 16.
   * 
   * Each pixel is expanded to 32 bit with a filler
   * byte.
   */
  
  if (color_type == PNG_COLOR_TYPE_RGB) {
    pixel_size = 24;
    if (depth < 8) {
      png_set_packing(png_ptr);
    }
    else if (depth == 16) {
      png_set_strip_16(png_ptr);
    }
    //png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);
    png_set_bgr(png_ptr);
  }

  /* The following code converts grayscale to paletted
   * image
   */

  if (color_type == PNG_COLOR_TYPE_GRAY && depth <= 8) {
    png_set_expand(png_ptr);
    pixel_size = 8;
  }

  /* The following code makes sure that paletted images
   * are always 8-bit
   */
   
  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    pixel_size = 8;
    if(depth < 8)
      png_set_packing(png_ptr);
  }
  
  /* The following code removes the alpha information
   * since we dont handle that yet.
   */

  if (color_type & PNG_COLOR_MASK_ALPHA)
    png_set_strip_alpha(png_ptr);

  /* PNG performs gamma-correction, we choose 2.2 as
   * the screen gamma.
   */
  
  screen_gamma = 2.2;
  
  if (png_get_gAMA(png_ptr, info_ptr, &gamma)) {
    png_set_gamma(png_ptr, screen_gamma, gamma);
  }
  else {
    png_set_gamma(png_ptr, screen_gamma, 1.0 / 2.2);
  }

  /* Recompute information based on the settings. */
  
  png_read_update_info(png_ptr, info_ptr);

  
  /* Allocate the pixmap data */
  
  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  rowbytes = ((rowbytes + 3) >> 2) << 2;

  pixels = malloc(rowbytes*height);

  if (pixels == NULL) {
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return MemoryError;
  }

  /* Set up a row pointer array needed by the read function. */
  rowpointers = malloc(height*sizeof(png_bytep));

  if (rowpointers == NULL) {
    free(pixels);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return MemoryError;
  }
  
  iter = pixels;
  index = 0;
  
  while(index < height) {
    rowpointers[index] = iter;
    iter += rowbytes;
    index++;
  }

  /* Read the image */
  
  png_read_image(png_ptr, rowpointers);
  
  
  
  /* Read the palette if it is there */
  
  if (png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette)) {
    index = 0;
    betapalette = malloc(num_palette * sizeof(Color));
    if (betapalette == NULL) {
      free(pixels);
      png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
      fclose(fp);
      return MemoryError;
    }
    else while (index < num_palette) {
      betapalette[index].red = palette[index].red;
      betapalette[index].green = palette[index].green;
      betapalette[index].blue = palette[index].blue;
      index++;
    };
  }
  
  image->width = width;
  image->height = height;
  image->data = pixels;
  image->rowbytes = rowbytes;
  image->pixel_size = pixel_size;
  image->palette = betapalette;
  image->palette_size = num_palette;

  png_read_end(png_ptr, end_info);
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  free(rowpointers);
  fclose(fp);
  
  return 0;
}


