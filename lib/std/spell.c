/* Do not remove the headers from this file! see /USAGE for more info. */

// T: You need some variables to hold all these:
/*
    What are the things that all spells/abilities have in common
    - Name - string?
    - reflex Cost - cost how? int?
    - Damage Type - string that can be verified towards DAMAGE_D?  query_valid_damage_type(string str)
    - Casting type - int ? Perhaps spell.h to define different casting types?
    - Skills used - string?
    - Components - mapping perhaps? (["black powder":2,"piece of rope":1]) ? So you could specify how
                   much is used?
    - target - int ? perhaps also target types defined in spell.h? TARGET_LIVING TARGET_ITEM etc?
                     So let the spell specify what type of target it expects?
*/

// T: Materials: Could it be the ones also used for crafting? I think two different material sets
//    might be a bit much for  a MUD?
//  When on lima calls:
//  @CRAFTING_D->query_material_categories()
//  Then for each of those do:
//  @CRAFTING_D->query_materials("textile") e.g.
//
//  Further categories and materials could easily be added, like a magical category etc.
//  I'm just mindfil to keep LIMA somewhat generic so it can be spun into Rifts, DND and a sci-fi MUD.

#include <assert.h>
#include <spells.h>

private
nosave string spell_name;
private
nosave int reflex_cost = 1;
private
nosave int cast_time;
private
nosave string skill_used;
private
nosave int instant_cast;
private
nosave string magic_skill_used;
private
nosave int channeling;
private
nosave int channeling_interval;
private
nosave int valid_targets;

mapping spell_components = ([]);
string casting_string;
string channeling_string = "channeling";

void do_effects(object target, object sc);

void create()
{
   this_object()->setup();
}

protected
void set_name(string s)
{
   spell_name = s;
}

string query_name()
{
   return spell_name;
}

protected
void set_reflex_cost(int c)
{
   ASSERT(c > 0);
   reflex_cost = c;
}

int query_reflex_cost()
{
   return reflex_cost;
}

protected
int check_reflex(object b)
{
   return b->query_reflex() >= reflex_cost;
}

protected
int spend_reflex(object b)
{
   return b->use_reflex(reflex_cost);
}

protected
void set_instant_cast(int c)
{
   if (c == 1)
      instant_cast = 1;
   else
      instant_cast = 0;
}

int query_instant_cast()
{
   return instant_cast;
}

protected
mixed valid_target(object target)
{
   /*DEFAULT: if there is a target, then it is invalid*/
   if (target)
   {
      return 0;
   }
   return 1;
}

protected
mixed valid_spell_components(mapping sc)
{
   /*DEFAULT: if there is a spell component, then it cant be used*/
   if (sc)
   {
      return 0;
   }
   return 1;
}

protected
mixed valid_circumstances(mixed target, mixed sc)
{
   return 1;
}

nomask mixed check_valid_spell(int has_target, int has_sc)
{
   // Did we define only specific valid targets?
   // Do we not have a target? Then we need to have TARGET_ROOM
   // defined as a valid target.
   TBUG(valid_targets);
   if (valid_targets && !has_target)
      return valid_targets & TARGET_ROOM ? 1 : "The spell requires a target.";

   return valid_circumstances(has_target, has_sc);
}

nomask void set_targets(int targets)
{
   valid_targets = targets;
}

nomask mixed check_valid_target(object target, mixed has_sc)
{
   mixed result;

   result = valid_circumstances(target, has_sc);
   if (!result)
      return result;

   TBUG("check_valid_target(" + target + ")");
   return valid_target(target);
}

nomask mixed check_valid_spell_components(mapping sc, mixed has_target)
{
   mixed result;

   result = valid_circumstances(has_target, sc);
   if (!result)
      return result;

   return valid_spell_components(sc);
}

void set_skill_used(string val)
{
   skill_used = val;
}

string query_skill_used()
{
   return skill_used;
}

void set_magic_skill_used(string val)
{
   magic_skill_used = val;
}

string query_magic_skill_used()
{
   return magic_skill_used;
}

// Timer for how long the spell is channeled (ongoing) in the room
void set_channeling_time(int t)
{
   ASSERT(t > 0);
   channeling = t;
}

// Timer for how long between actions
void set_channeling_interval(int t)
{
   ASSERT(t > 0);
   channeling_interval = t;
}

// Timer that is relevant to the spells, either cast time, cooldown, or channeling duration
void set_cast_time(int t)
{
   ASSERT(t >= 0);
   cast_time = t;
}

nomask void delayed_cast_spell(object target, object sc)
{
   this_body()->other_action("$N $vbegin casting a spell.");
   this_body()->busy_with(this_object(), "casting " + query_name(), "cast_action", ({target, sc}));
}

void cast_action(mixed *args)
{
   object target = args[0];
   object sc = args[1];
   this_object()->cast_spell(target, sc);
}

object transient(string name, mixed *args...)
{
   object t = new ("/domains/std/spell/transient/" + name, args...);
   return t;
}

// Different versions of how a spell would be cast
void internal_cast_spell(object target, object sc)
{
   if (!check_reflex(this_body()))
   {
      write("You cannot focus on casting spells right now.");
      return;
   }
   spend_reflex(this_body());

   if (cast_time > 0)
      delayed_cast_spell(target, sc);
   else
      this_object()->cast_spell(target, sc);
}
