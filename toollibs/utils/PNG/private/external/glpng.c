#include <png.h>
#include <stdlib.h>
#include <math.h>

#define Success          0
#define NoSuchFileError  1
#define WrongFormatError 2
#define MemoryError      3

#define DEBUG 1
#undef DEBUG

#ifdef DEBUG
#define TRACE(txt) fprintf(stderr, "%s\n", txt); fflush(stderr)
#else
#define TRACE(txt) 
#endif

int GlReadPNGFile(char *name, long *width_return, long *height_return, unsigned char **data, int *has_palette)
{
  FILE *fp;
  char header[8];

  png_byte color_type;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowbytes;
  png_uint_32 depth;

  double gamma, screen_gamma;
  png_structp png_ptr;
  png_infop   info_ptr;
  png_infop   end_info;

  png_bytep pixels;
  png_bytep iter;
  png_uint_32 index;

  png_bytep *rowpointers;

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

#ifdef DEBUG
  fprintf(stderr, "color_type: 0x%x, depth: %d\n", (int)color_type, (int)depth);
  fflush(stderr);
#endif

  if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
    if (depth < 8) {
      png_set_packing(png_ptr);
    }
    else if (depth == 16) {
      png_set_strip_16(png_ptr);
    }
    /*png_set_strip_alpha(png_ptr);*/
    /* png_set_invert_alpha(png_ptr);*/
  } else {
    if (color_type == PNG_COLOR_TYPE_PALETTE){
      TRACE("Expand Palette");
      png_set_expand(png_ptr);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY ||
	color_type == PNG_COLOR_TYPE_GRAY_ALPHA){
      TRACE("graytorgb");
      png_set_gray_to_rgb(png_ptr);
    }
  }

  TRACE("gamma");

  /* PNG performs gamma-correction, we choose 2.2 as
   * the screen gamma.
   */
  
  screen_gamma = 2.2;
  
  if (png_get_gAMA(png_ptr, info_ptr, &gamma)) {
    png_set_gamma(png_ptr, screen_gamma, gamma);
  } else {
    png_set_gamma(png_ptr, screen_gamma, 1.0 / 2.2);
  }

  TRACE("recompute");
  /* Recompute information based on the settings. */
  
  png_read_update_info(png_ptr, info_ptr);
  
  TRACE("alloc");
  /* Allocate the pixmap data */
  
  *width_return = width = png_get_image_width(png_ptr, info_ptr);
  *height_return = height = png_get_image_height(png_ptr, info_ptr);
  rowbytes = png_get_rowbytes(png_ptr, info_ptr);
#ifdef DEBUG
  fprintf(stderr, "width: %d\n", (int)width);
  fflush(stderr);
  fprintf(stderr, "height: %d\n", (int)height);
  fflush(stderr);
  fprintf(stderr, "rowbytes: %d\n", (int)rowbytes);
  fflush(stderr);
#endif

  /*rowbytes = (rowbytes + 3) & ~3;*/
#ifdef DEBUG
  fprintf(stderr, "rowbytes: %d\n", (int)rowbytes);
  fflush(stderr);
#endif

  *data = pixels = malloc(rowbytes*height);

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
    rowpointers[height-1-index] = iter;
    iter += rowbytes;
    index++;
  }

  /* Read the image */
  
  png_read_image(png_ptr, rowpointers);

  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    *has_palette = 1;
  } else {
    *has_palette = 0;
  }

  png_read_end(png_ptr, end_info);

  png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
  free(rowpointers);
  fclose(fp);
  
  return Success;
}


