#ifndef UTIL_H_
#define UTIL_H_

#ifdef __cplusplus
extern "C"
{
#endif

const char* mc2str(int mc);
int str2mc(const char *s);

const char *biome2str(int id);
void setBiomeColor(unsigned char biomeColor[256][3], int id,
        unsigned char r, unsigned char g, unsigned char b);
void initBiomeColors(unsigned char biomeColors[256][3]);
void initBiomeTypeColors(unsigned char biomeColors[256][3]);

int biomesToImage(unsigned char *pixels,
        unsigned char biomeColors[256][3], const int *biomes,
        const unsigned int sx, const unsigned int sy,
        const unsigned int pixscale, const int flip);

int savePPM(const char* path, const unsigned char *pixels,
        const unsigned int sx, const unsigned int sy);

#ifdef __cplusplus
}
#endif

#endif
