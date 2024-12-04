/* Do not remove the headers from this file! see /USAGE for more info. */

#include <spells.h>

inherit COMBAT_SPELL;

void setup()
{
   set_name("magic arrow");
   set_targets(TARGET_LIVING);
}

int calculate_damage()
{
   return random(8) + 1;
}

void cast_spell(object ob, object reagent)
{
   if (!ob)
   {
      write("Your target has disappeared.");
   }
   else
   {
      this_body()->targetted_action("$N $vcast a magic arrow at $t1.", ob);
      do_spell_damage(ob, ( : calculate_damage:));
   }
}