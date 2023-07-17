#ifndef BN_SPRITE_ITEMS_RED_SPRITE_H
#define BN_SPRITE_ITEMS_RED_SPRITE_H

#include "bn_sprite_item.h"

//{{BLOCK(red_sprite_bn_gfx)

//======================================================================
//
//	red_sprite_bn_gfx, 64x64@8, 
//	+ palette 208 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 416 + 4096 = 4512
//
//	Time-stamp: 2023-07-16, 20:01:46
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RED_SPRITE_BN_GFX_H
#define GRIT_RED_SPRITE_BN_GFX_H

#define red_sprite_bn_gfxTilesLen 4096
extern const bn::tile red_sprite_bn_gfxTiles[128];

#define red_sprite_bn_gfxPalLen 416
extern const bn::color red_sprite_bn_gfxPal[208];

#endif // GRIT_RED_SPRITE_BN_GFX_H

//}}BLOCK(red_sprite_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item red_sprite(sprite_shape_size(sprite_shape::SQUARE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(red_sprite_bn_gfxTiles, 128), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(red_sprite_bn_gfxPal, 208), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

