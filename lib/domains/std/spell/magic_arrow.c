/* Do not remove the headers from this file! see /USAGE for more info. */

#include <spells.h>

inherit COMBAT_SPELL;

void setup()
{
   set_level(0);
   set_name("magic arrow");
   set_category("evocation");
   set_targets(TARGET_LIVING);
   set_cast_time(1);
   set_description("This spell creates a magical arrow that flies at the target.");
}

int calculate_damage()
{
   return random(8) + 1 + spell_skill_rank();
}

void cast_spell(object ob, object reagent, int success)
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