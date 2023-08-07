#ifndef BN_SPRITE_ITEMS_TITLE_MIDDLE_H
#define BN_SPRITE_ITEMS_TITLE_MIDDLE_H

#include "bn_sprite_item.h"

//{{BLOCK(title_middle_bn_gfx)

//======================================================================
//
//	title_middle_bn_gfx, 16x96@8, 
//	+ palette 256 entries, not compressed
//	+ 24 tiles not compressed
//	Total size: 512 + 1536 = 2048
//
//	Time-stamp: 2023-08-05, 15:33:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TITLE_MIDDLE_BN_GFX_H
#define GRIT_TITLE_MIDDLE_BN_GFX_H

#define title_middle_bn_gfxTilesLen 1536
extern const bn::tile title_middle_bn_gfxTiles[48];

#define title_middle_bn_gfxPalLen 512
extern const bn::color title_middle_bn_gfxPal[256];

#endif // GRIT_TITLE_MIDDLE_BN_GFX_H

//}}BLOCK(title_middle_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item title_middle(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(title_middle_bn_gfxTiles, 48), bpp_mode::BPP_8, compression_type::NONE, 3), 
            sprite_palette_item(span<const color>(title_middle_bn_gfxPal, 256), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

