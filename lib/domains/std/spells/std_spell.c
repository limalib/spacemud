/* Do not remove the headers from this file! see /USAGE for more info. */

/*
    Superclass for all spells

*/

#include <assert.h>
#include <hooks.c>

inherit SPELL;

private
nosave int cast_time;
private
nosave int cooldown;
private
nosave int channeling;
private
nosave int channel_duration;
private
nosave int instant;
private
nosave string skill_used;
private
nosave int diff;
private
nosave int tag;

void setup()
{
   set_spell_name("standard spell");
}

void interrupt_cast();
function interupt_function = ( : interrupt_cast:);

int no_combat();
function no_combat_function = ( : no_combat:);

function channel_function = ( : channel:);

mixed no_combat()
{
   if (channeling)
      return "channeling";
   if (!instant)
      return "spell casting";
}

void set_skill_used(string val)
{
   skill_used = val;
}

void query_skill_used()
{
   return skill_used;
}

void set_cast_time(int t)
{
   ASSERT(t >= 0);
   cast_time = t;
}

void set_cooldown(int t)
{
   ASSERT(t > 0);
   cooldown = t;
}

void set_channel_duration(int t)
{
   ASSERT(t > 0);
   channel_duration = t;
}

void check_success(object target, object reagent)
{
   this_body()->remove_hook("interrupt", interrupt_function);
   this_body()->remove_hook("prevent_combat", no_combat_function);
#ifdef USE_SKILLS
   if (this_body()->test_skill(skill_used, diff))
      do_effects(target, reagent);
   else
      do_fail(target_reagent);
#endif
}

mixed valid_circumstances(object target, object reagent)
{
   return 1;
}

nomask void cast_spell(object target, object reagent)
{
   this_body()->simple_action("$N $vbegin to cast.");
}

nomask void channel_spell(object target, object reagent)
{
   this_body()->simple_action("$N $vbegn to channel.");
}

nomask void instant_spell(object target, object reagent)
{
   this_body()->simple_action("$N $vcast.");
}