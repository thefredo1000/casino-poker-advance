#ifndef BN_MUSIC_ITEMS_INFO_H
#define BN_MUSIC_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_music_item.h"
#include "bn_string_view.h"

namespace bn::music_items_info
{
    constexpr inline pair<music_item, string_view> array[] = {
        make_pair(music_item(0), string_view("amfa_2")),
        make_pair(music_item(1), string_view("erotic")),
        make_pair(music_item(2), string_view("hassans_spaceship")),
        make_pair(music_item(3), string_view("soda7_xcopy_ohc")),
    };

    constexpr inline span<const pair<music_item, string_view>> span(array);
}

#endif

