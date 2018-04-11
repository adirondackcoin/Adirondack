#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "crypto/sph_skein.h"
#include "crypto/sph_cubehash.h"
#include "crypto/sph_fugue.h"
#include "crypto/sph_gost.h"
#include "crypto/raptor.h"

#ifndef QT_NO_DEBUG
#include <string>
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_skein512_context     z_skein;
GLOBAL sph_cubehash512_context  z_cubehash;
GLOBAL sph_fugue512_context     z_fugue;
GLOBAL sph_gost512_context      z_gost;

#define fillz() do { \
    sph_skein512_init(&z_skein); \
    sph_cubehash512_init(&z_cubehash); \
    sph_fugue512_init(&z_fugue); \
    sph_gost512_init(&z_gost); \
} while (0) 

#define ZSKEIN (memcpy(&ctx_skein, &z_skein, sizeof(z_skein)))
#define ZFUGUE (memcpy(&ctx_fugue, &z_fugue, sizeof(z_fugue)))
#define ZGOST (memcpy(&ctx_gost, &z_gost, sizeof(z_gost)))

template<typename T1>
inline uint256 SkunkHash(const T1 pbegin, const T1 pend)

{
    sph_skein512_context     ctx_skein;
    sph_cubehash512_context   ctx_cubehash;
    sph_fugue512_context      ctx_fugue;
    sph_gost512_context      ctx_gost;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
    
    uint512 hash[17];

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[0]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[0]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[1]));
        
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, static_cast<const void*>(&hash[1]), 64);
    sph_fugue512_close(&ctx_fugue, static_cast<void*>(&hash[2]));

    sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, static_cast<const void*>(&hash[2]), 64);
    sph_gost512_close(&ctx_gost, static_cast<void*>(&hash[3]));

    return hash[3].trim256();
}


#endif // HASHBLOCK_H
