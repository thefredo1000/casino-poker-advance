#ifndef BN_SPRITE_ITEMS_CARDS_DIAMOND_H
#define BN_SPRITE_ITEMS_CARDS_DIAMOND_H

#include "bn_sprite_item.h"

//{{BLOCK(cards_diamond_bn_gfx)

//======================================================================
//
//	cards_diamond_bn_gfx, 16x256@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 32 + 2048 = 2080
//
//	Time-stamp: 2023-07-16, 21:56:53
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CARDS_DIAMOND_BN_GFX_H
#define GRIT_CARDS_DIAMOND_BN_GFX_H

#define cards_diamond_bn_gfxTilesLen 2048
extern const bn::tile cards_diamond_bn_gfxTiles[64];

#define cards_diamond_bn_gfxPalLen 32
extern const bn::color cards_diamond_bn_gfxPal[16];

#endif // GRIT_CARDS_DIAMOND_BN_GFX_H

//}}BLOCK(cards_diamond_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item cards_diamond(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(cards_diamond_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(cards_diamond_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

