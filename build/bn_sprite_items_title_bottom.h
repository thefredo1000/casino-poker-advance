#ifndef BN_SPRITE_ITEMS_TITLE_BOTTOM_H
#define BN_SPRITE_ITEMS_TITLE_BOTTOM_H

#include "bn_sprite_item.h"

//{{BLOCK(title_bottom_bn_gfx)

//======================================================================
//
//	title_bottom_bn_gfx, 16x96@8, 
//	+ palette 112 entries, not compressed
//	+ 24 tiles not compressed
//	Total size: 224 + 1536 = 1760
//
//	Time-stamp: 2023-08-05, 15:15:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TITLE_BOTTOM_BN_GFX_H
#define GRIT_TITLE_BOTTOM_BN_GFX_H

#define title_bottom_bn_gfxTilesLen 1536
extern const bn::tile title_bottom_bn_gfxTiles[48];

#define title_bottom_bn_gfxPalLen 224
extern const bn::color title_bottom_bn_gfxPal[112];

#endif // GRIT_TITLE_BOTTOM_BN_GFX_H

//}}BLOCK(title_bottom_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item title_bottom(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(title_bottom_bn_gfxTiles, 48), bpp_mode::BPP_8, compression_type::NONE, 3), 
            sprite_palette_item(span<const color>(title_bottom_bn_gfxPal, 112), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

