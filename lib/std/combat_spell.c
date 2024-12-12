/* Do not remove the headers from this file! see /USAGE for more info. */

// combat_spell.c - Base object for damage-causing magic spells. Whenever
//                  your spells cause the damage, call do_spell_damage().
//                  Combat will automatically start between the caster and
//                  the target.
// Iizuka, 4-28-98: Created.

inherit SPELL;
inherit M_DAMAGE_SOURCE;

void do_spell_damage(object target, function damage_func)
{
   this_body()->add_event(target, this_object(), "torso", evaluate(damage_func));
   this_body()->start_fight(target);
}

int is_combat_spell()
{
   return 1;
}

string short()
{
   return add_article(query_name());
}

void create()
{
   set_damage_type("force");

   // Generic spell messages that uses the damage type for description.
   set_combat_messages("combat-generic-spell");
#ifdef USE_SKILLS
   set_magic_skill_used("magic/technique/casting");
#endif
   // Call create down here so the defaults above can be overwritten.
   ::create();
}
