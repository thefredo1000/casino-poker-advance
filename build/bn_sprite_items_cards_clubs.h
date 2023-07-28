#ifndef BN_SPRITE_ITEMS_CARDS_CLUBS_H
#define BN_SPRITE_ITEMS_CARDS_CLUBS_H

#include "bn_sprite_item.h"

//{{BLOCK(cards_clubs_bn_gfx)

//======================================================================
//
//	cards_clubs_bn_gfx, 16x256@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 32 + 2048 = 2080
//
//	Time-stamp: 2023-07-28, 09:46:59
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CARDS_CLUBS_BN_GFX_H
#define GRIT_CARDS_CLUBS_BN_GFX_H

#define cards_clubs_bn_gfxTilesLen 2048
extern const bn::tile cards_clubs_bn_gfxTiles[64];

#define cards_clubs_bn_gfxPalLen 32
extern const bn::color cards_clubs_bn_gfxPal[16];

#endif // GRIT_CARDS_CLUBS_BN_GFX_H

//}}BLOCK(cards_clubs_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item cards_clubs(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(cards_clubs_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(cards_clubs_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

