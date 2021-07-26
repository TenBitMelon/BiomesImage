// generate an image of the world
#include "../include/generator.h"
#include "../include/util.h"
#include "../include/finders.h"

int main()
{
    unsigned char biomeColors[256][3];

    // Initialize a color map for biomes.
    initBiomeColors(biomeColors);

    // Initialize a stack of biome layers.
    LayerStack g;
    setupGenerator(&g, MC_1_17);
    // Extract the desired layer.
    Layer *layer = &g.layers[L_SHORE_16];
    uint64_t seed = -2974007333565199888LL;

    // setLayerSeed(layer, seed);

    // Pos worldSpawn = getSpawn(MC_1_17, layer, NULL, seed);
    // int areaX = worldSpawn.x, areaZ = worldSpawn.z;

    int areaX = -64, areaZ = -64;
    unsigned int areaWidth = 128, areaHeight = 128;
    unsigned int scale = 1;
    unsigned int imgWidth = areaWidth*scale, imgHeight = areaHeight*scale;

    // Allocate a sufficient buffer for the biomes and for the image pixels.
    int *biomeIds = allocCache(layer, areaWidth, areaHeight);
    unsigned char *rgb = (unsigned char *) malloc(3*imgWidth*imgHeight);

    // Apply the seed only for the required layers and generate the area.
    setLayerSeed(layer, seed);
    genArea(layer, biomeIds, areaX, areaZ, areaWidth, areaHeight);

    // Map the biomes to a color buffer and save to an image.
    biomesToImage(rgb, biomeColors, biomeIds, areaWidth, areaHeight, scale, 2);
    savePPM("biomes_at_layer.ppm", rgb, imgWidth, imgHeight);

    // Clean up.
    free(biomeIds);
    free(rgb);

    return 0;
}
