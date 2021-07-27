// generate an image of the world
#include "../include/generator.h"
#include "../include/util.h"
#include "../include/finders.h"
#include <stdio.h>
#include <string.h>

int64_t S64(const char *s) {
  int64_t i;
  char c ;
  int scanned = sscanf(s, "%" SCNd64 "%c", &i, &c);
  if (scanned == 1) return i;
  if (scanned > 1) {
    // TBD about extra data found
    return i;
    }
  // TBD failed to scan;
  return 0;
}

int main(int argc, char **argv)
{
    unsigned char biomeColors[256][3];

    // Initialize a color map for biomes.
    initBiomeColors(biomeColors);

    // Initialize a stack of biome layers.
    LayerStack g;
    Layer *layer;
    if (argc > 2) {
      if (!strcmp(argv[2], "--largeBiomes")) {
        setupGeneratorLargeBiomes(&g, MC_1_17, 1);
      } else {
        setupGenerator(&g, MC_1_17);
      }
    } else {
      setupGenerator(&g, MC_1_17);
    }
    // Extract the desired layer.
    layer = &g.layers[L_RIVER_MIX_4];

    uint64_t seed = S64(argv[1]);
    applySeed(&g, seed);
    Pos worldSpawn = getSpawn(MC_1_17, &g, NULL, seed);
    int areaX = (worldSpawn.x / 4) - 64, areaZ = (worldSpawn.z / 4) - 64;
    unsigned int areaWidth = 128, areaHeight = 128;
    unsigned int scale = 1;
    unsigned int imgWidth = areaWidth*scale, imgHeight = areaHeight*scale;

    // Allocate a sufficient buffer for the biomes and for the image pixels.
    int *biomeIds = allocCache(layer, areaWidth, areaHeight);
    unsigned char *rgb = (unsigned char *) malloc(3*imgWidth*imgHeight);

    // Apply the seed only for the required layers and generate the area.

    genArea(layer, biomeIds, areaX, areaZ, areaWidth, areaHeight);

    // Map the biomes to a color buffer and save to an image.
    biomesToImage(rgb, biomeColors, biomeIds, areaWidth, areaHeight, scale, 2);

    // Print Image RGB Values
    for(int i=0; i<imgWidth*imgHeight; i++) {
      printf("%d,%d,%d\n", rgb[i*3], rgb[(i*3)+1], rgb[(i*3)+2]);
    }

    // savePPM("biomes_at_layer.ppm", rgb, imgWidth, imgHeight);

    // Clean up.
    free(biomeIds);
    free(rgb);

    return 0;
}
