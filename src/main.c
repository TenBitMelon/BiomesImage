#include "../cubiomes/generator.h"
#include "../cubiomes/util.h"
#include "../cubiomes/finders.h"
#include <stdio.h>

// Function declaration for setBiomeColor because it is not in util.h for some reason
void setBiomeColor(unsigned char biomeColor[256][3], int id, unsigned char r, unsigned char g, unsigned char b);

// Function for converting string to uint_64t
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
    // Initialize the generator.
    Generator g;
    // Enable large biomes if command line argument used
    if (argc > 2) {
      if (!strcmp(argv[2], "--largeBiomes")) {
        setupGenerator(&g, MC_1_18, 1);
      } else {
        setupGenerator(&g, MC_1_18, 0);
      }
    } else {
      setupGenerator(&g, MC_1_18, 0);
    }

    // Set the seed.
    uint64_t seed = S64(argv[1]);
    applySeed(&g, 0, seed);

    // Set the parameters for the area generated
    Range r;

    r.scale = 4;
    Pos worldSpawn = getSpawn(&g); // Center the image at world spawn
    r.x = (worldSpawn.x / 4) - 64, r.z = (worldSpawn.z / 4) - 64;
    r.sx = 128, r.sz = 128;
    r.y = 80, r.sy = 0;

    // Generate Biomes
    int *biomeIds = allocCache(&g, r);
    genBiomes(&g, biomeIds, r);
    
    // Initialize a color map for biomes.
    unsigned char biomeColors[256][3];

    initBiomeColors(biomeColors);
    
    setBiomeColor(biomeColors, sunflower_plains, 111, 152, 0);
    setBiomeColor(biomeColors, deep_ocean, 43, 65, 153);
    setBiomeColor(biomeColors, swamp, 40, 43, 21);
    setBiomeColor(biomeColors, taiga_hills, 12, 126, 134);
    
    // Map the biomes to a color buffer and generate an image.
    int imgWidth = r.sx, imgHeight = r.sz;
    unsigned char *rgb = (unsigned char *) malloc(3*imgWidth*imgHeight);
    biomesToImage(rgb, biomeColors, biomeIds, r.sx, r.sz, 1, 2);

    // Print Image RGB Values
    #ifndef DEBUG
    for(int i=0; i<imgWidth*imgHeight; i++) {
      printf("%d,%d,%d\n", rgb[i*3], rgb[(i*3)+1], rgb[(i*3)+2]);
    }
    #else
    // Save to file instead of printing for debug
      savePPM("biomes_at_layer.ppm", rgb, imgWidth, imgHeight);
    #endif

    // Clean up.
    free(biomeIds);
    free(rgb);

    return 0;
}
