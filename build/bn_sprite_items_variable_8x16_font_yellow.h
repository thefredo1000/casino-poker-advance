#ifndef BN_SPRITE_ITEMS_VARIABLE_8X16_FONT_YELLOW_H
#define BN_SPRITE_ITEMS_VARIABLE_8X16_FONT_YELLOW_H

#include "bn_sprite_item.h"

//{{BLOCK(variable_8x16_font_yellow_bn_gfx)

//======================================================================
//
//	variable_8x16_font_yellow_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 32 + 128 = 160
//
//	Time-stamp: 2023-07-18, 13:34:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_VARIABLE_8X16_FONT_YELLOW_BN_GFX_H
#define GRIT_VARIABLE_8X16_FONT_YELLOW_BN_GFX_H

#define variable_8x16_font_yellow_bn_gfxTilesLen 128
extern const bn::tile variable_8x16_font_yellow_bn_gfxTiles[4];

#define variable_8x16_font_yellow_bn_gfxPalLen 32
extern const bn::color variable_8x16_font_yellow_bn_gfxPal[16];

#endif // GRIT_VARIABLE_8X16_FONT_YELLOW_BN_GFX_H

//}}BLOCK(variable_8x16_font_yellow_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item variable_8x16_font_yellow(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(variable_8x16_font_yellow_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(variable_8x16_font_yellow_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

