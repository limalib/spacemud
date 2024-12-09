/* Do not remove the headers from this file! see /USAGE for more info. */

#include <spells.h>

inherit SPELL;

void setup()
{
   set_name("shield");
   set_targets(TARGET_ROOM);
   extra_reflex_cost(1);
}

void cast_spell(object ob, object reagent)
{
   this_body()->simple_action("A semi-transparent blue shield appears infront of $n.");
   transient("shield", 1, 10, "A shimmering shield protects $n.")->move(this_body());
}