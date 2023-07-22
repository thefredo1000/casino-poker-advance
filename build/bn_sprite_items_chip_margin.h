#ifndef BN_SPRITE_ITEMS_CHIP_MARGIN_H
#define BN_SPRITE_ITEMS_CHIP_MARGIN_H

#include "bn_sprite_item.h"

//{{BLOCK(chip_margin_bn_gfx)

//======================================================================
//
//	chip_margin_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 32 + 512 = 544
//
//	Time-stamp: 2023-07-22, 16:58:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CHIP_MARGIN_BN_GFX_H
#define GRIT_CHIP_MARGIN_BN_GFX_H

#define chip_margin_bn_gfxTilesLen 512
extern const bn::tile chip_margin_bn_gfxTiles[16];

#define chip_margin_bn_gfxPalLen 32
extern const bn::color chip_margin_bn_gfxPal[16];

#endif // GRIT_CHIP_MARGIN_BN_GFX_H

//}}BLOCK(chip_margin_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item chip_margin(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(chip_margin_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(chip_margin_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

