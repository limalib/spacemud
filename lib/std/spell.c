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
nosave int level = 1;
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

//: FUNCTION set_level
// Sets the level of the spell.
// Parameters:
// - l: The level of the spell.
protected
void set_level(int l)
{
   level = l;
}

//: FUNCTION query_level
// Returns the level of the spell.
int query_level()
{
   return level;
}

//: FUNCTION set_name
// Sets the name of the spell.
// Parameters:
// - s: The name of the spell.
protected
void set_name(string s)
{
   spell_name = s;
}

//: FUNCTION query_name
// Returns the name of the spell.
string query_name()
{
   return spell_name;
}

//: FUNCTION extra_reflex_cost
// Sets the extra reflex cost of the spell. A spell
// always costs level + reflex_cost to cast.
// Parameters:
// - c: The reflex cost of the spell.
protected
void extra_reflex_cost(int c)
{
   ASSERT(c > 0);
   reflex_cost = c;
}

//: FUNCTION query_reflex_cost
// Returns the reflex cost of the spell.
int query_reflex_cost()
{
   return reflex_cost + level;
}

//: FUNCTION check_reflex
// Checks if the caster has enough reflex to cast the spell.
// Parameters:
// - b: The caster object.
// Returns: 1 if the caster has enough reflex, 0 otherwise.
protected
int check_reflex(object b)
{
   return b->query_reflex() >= reflex_cost;
}

//: FUNCTION spend_reflex
// Spends the reflex cost for casting the spell.
// Parameters:
// - b: The caster object.
// Returns: 1 if the reflex cost was successfully spent, 0 otherwise.
protected
int spend_reflex(object b)
{
   return b->use_reflex(query_reflex_cost());
}

//: FUNCTION set_instant_cast
// Sets whether the spell is an instant cast.
// Parameters:
// - c: 1 if the spell is an instant cast, 0 otherwise.
protected
void set_instant_cast(int c)
{
   if (c == 1)
      instant_cast = 1;
   else
      instant_cast = 0;
}

//: FUNCTION query_instant_cast
// Returns whether the spell is an instant cast.
// Returns: 1 if the spell is an instant cast, 0 otherwise.
int query_instant_cast()
{
   return instant_cast;
}

//: FUNCTION valid_target
// Checks if the target is valid for the spell.
// Parameters:
// - target: The target object.
// Returns: 1 if the target is valid, 0 otherwise.
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

//: FUNCTION valid_spell_components
// Checks if the spell components are valid.
// Parameters:
// - sc: The spell components mapping.
// Returns: 1 if the spell components are valid, 0 otherwise.
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

//: FUNCTION valid_circumstances
// Checks if the circumstances are valid for casting the spell.
// Parameters:
// - target: The target object.
// - sc: The spell components mapping.
// Returns: 1 if the circumstances are valid, 0 otherwise.
protected
mixed valid_circumstances(mixed target, mixed sc)
{
   return 1;
}

//: FUNCTION check_valid_spell
// Checks if the spell is valid to cast.
// Parameters:
// - has_target: 1 if the spell has a target, 0 otherwise.
// - has_sc: 1 if the spell has spell components, 0 otherwise.
// Returns: 1 if the spell is valid to cast, an error message otherwise.
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

//: FUNCTION set_targets
// Sets the valid targets for the spell.
// Parameters:
// - targets: The valid targets for the spell.
nomask void set_targets(int targets)
{
   valid_targets = targets;
}

//: FUNCTION check_valid_target
// Checks if the target is valid for the spell.
// Parameters:
// - target: The target object.
// - has_sc: 1 if the spell has spell components, 0 otherwise.
// Returns: 1 if the target is valid, an error message otherwise.
nomask mixed check_valid_target(object target, mixed has_sc)
{
   mixed result;

   result = valid_circumstances(target, has_sc);
   if (!result)
      return result;

   TBUG("check_valid_target(" + target + ")");
   return valid_target(target);
}

//: FUNCTION check_valid_spell_components
// Checks if the spell components are valid for the spell.
// Parameters:
// - sc: The spell components mapping.
// - has_target: 1 if the spell has a target, 0 otherwise.
// Returns: 1 if the spell components are valid, an error message otherwise.
nomask mixed check_valid_spell_components(mapping sc, mixed has_target)
{
   mixed result;

   result = valid_circumstances(has_target, sc);
   if (!result)
      return result;

   return valid_spell_components(sc);
}

//: FUNCTION set_skill_used
// Sets the skill used for casting the spell.
// Parameters:
// - val: The skill used for casting the spell.
void set_skill_used(string val)
{
   skill_used = val;
}

//: FUNCTION query_skill_used
// Returns the skill used for casting the spell.
string query_skill_used()
{
   return skill_used;
}

//: FUNCTION set_magic_skill_used
// Sets the magic skill used for casting the spell.
// Parameters:
// - val: The magic skill used for casting the spell.
void set_magic_skill_used(string val)
{
   magic_skill_used = val;
}

//: FUNCTION query_magic_skill_used
// Returns the magic skill used for casting the spell.
string query_magic_skill_used()
{
   return magic_skill_used;
}

//: FUNCTION set_channeling_time
// Sets the channeling time for the spell.
// Parameters:
// - t: The channeling time in seconds.
void set_channeling_time(int t)
{
   ASSERT(t > 0);
   channeling = t;
}

//: FUNCTION set_channeling_interval
// Sets the interval between channeling actions for the spell.
// Parameters:
// - t: The interval time in seconds.
void set_channeling_interval(int t)
{
   ASSERT(t > 0);
   channeling_interval = t;
}

//: FUNCTION set_cast_time
// Sets the cast time for the spell.
// Parameters:
// - t: The cast time in seconds.
void set_cast_time(int t)
{
   ASSERT(t >= 0);
   cast_time = t;
}

//: FUNCTION delayed_cast_spell
// Initiates a delayed cast for the spell.
// Parameters:
// - target: The target object.
// - sc: The spell components object.
nomask void delayed_cast_spell(object target, object sc)
{
   this_body()->other_action("$N $vbegin casting a spell.");
   this_body()->busy_with(this_object(), "casting " + query_name(), "cast_action", ({target, sc}));
}

//: FUNCTION cast_action
// Executes the casting action for the spell.
// Parameters:
// - args: An array containing the target and spell components.
void cast_action(mixed *args)
{
   object target = args[0];
   object sc = args[1];
   this_object()->cast_spell(target, sc);
}

//: FUNCTION transient
// Creates a transient spell object.
// Parameters:
// - name: The name of the transient spell.
// - args: Additional arguments for the transient spell.
// Returns: The created transient spell object.
object transient(string name, mixed *args...)
{
   object t = new ("/domains/std/spell/transient/" + name, args...);
   return t;
}

//: FUNCTION internal_cast_spell
// Internally handles the casting of the spell.
// Parameters:
// - target: The target object.
// - sc: The spell components object.
void internal_cast_spell(object target, object sc)
{
   object caster = this_body();

   if (!check_reflex(caster))
   {
      write("You cannot focus on casting spells right now.");
      return;
   }

   spend_reflex(caster);
   if (!caster->test_skill("magic/technique/casting", level * 100))
   {
      write("You fail to cast the spell.");
      return;
   }

   if (cast_time > 0)
      delayed_cast_spell(target, sc);
   else
      this_object()->cast_spell(target, sc);
}

string stat_me()
{
   return "Spell: " + query_name() + "\n" + "Spell Level: " + query_level() + "\n" +
          "Reflex Cost: " + query_reflex_cost() + "\n" + "Skill Used: " + query_skill_used() + "\n" +
          "Magic Skill Used: " + query_magic_skill_used() + "\n" + "Cast Time: " + cast_time + "\n" +
          "Channeling Time: " + channeling + "\n" + "Channeling Interval: " + channeling_interval + "\n" +
          "Valid Targets: " + valid_targets + "\n" + "Spell Components: " + identify(spell_components) + "\n" +
          "Casting String: " + casting_string + "\n" + "Channeling String: " + channeling_string + "\n";
}