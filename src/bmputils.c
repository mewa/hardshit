#include <bmputils.h>

void bmp_draw(ALLEGRO_BITMAP* bmp, float x, float y, float w, float h) {
  al_draw_scaled_bitmap(bmp, 0, 0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp),
			x, y, w, h,
			0);
}
