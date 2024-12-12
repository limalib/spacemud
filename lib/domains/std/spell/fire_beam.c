/* Do not remove the headers from this file! see /USAGE for more info. */

#include <spells.h>

inherit COMBAT_SPELL;

void setup()
{
   set_level(1);
   set_cast_time(1);
   set_name("fire beam");
   set_category("evocation");
   set_targets(TARGET_LIVING);
   set_channeling_interval(5);
   set_description("This spell creates an ongoing beam of fire that flies at the target.");
}

int calculate_damage(int success)
{
   return random(6) * (success + 1) + 1 + spell_skill_rank());
}

void cast_spell(object ob, object reagent, int success)
{
   if (!ob || !present(ob, environment(this_body())))
   {
      channel_failure("Your target has disappeared.");
      return;
   }

   if (success)
      this_body()->targetted_action("$N $vchannel a <221>fire beam<res> at $t1.", ob);
   else
      this_body()->targetted_action("$N $vchannel a wavering fire beam at $t1.", ob);
   do_spell_damage(ob, ( : calculate_damage:));
}