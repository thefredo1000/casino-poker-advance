#ifndef BN_REGULAR_BG_ITEMS_TITLE_SCREEN_H
#define BN_REGULAR_BG_ITEMS_TITLE_SCREEN_H

#include "bn_regular_bg_item.h"

//{{BLOCK(title_screen_bn_gfx)

//======================================================================
//
//	title_screen_bn_gfx, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 384 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 24576 + 2048 = 27136
//
//	Time-stamp: 2023-07-23, 14:11:35
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TITLE_SCREEN_BN_GFX_H
#define GRIT_TITLE_SCREEN_BN_GFX_H

#define title_screen_bn_gfxTilesLen 24576
extern const bn::tile title_screen_bn_gfxTiles[768];

#define title_screen_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell title_screen_bn_gfxMap[1024];

#define title_screen_bn_gfxPalLen 512
extern const bn::color title_screen_bn_gfxPal[256];

#endif // GRIT_TITLE_SCREEN_BN_GFX_H

//}}BLOCK(title_screen_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item title_screen(
            regular_bg_tiles_item(span<const tile>(title_screen_bn_gfxTiles, 768), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(title_screen_bn_gfxPal, 256), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(title_screen_bn_gfxMap[0], size(32, 32), compression_type::NONE));
}

#endif

