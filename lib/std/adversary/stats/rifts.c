/* Do not remove the headers from this file! see /USAGE for more info. */

//: MODULE
// rifts.c -- body statistics (characteristics)
//
// Very rough version 0.1 by Tsath 2024.
//
// .. TAGS: RST

#include <hooks.h>

inherit "/std/adversary/stats/base";
private
inherit CLASS_STATMODS;

mixed call_hooks(string, int);
void refresh_stats();
int skill_stat_sum(string stat);

private
mapping stats = ([]);

mapping query_stats()
{
   return copy(stats);
}

nomask int query_stat_pure(string stat)
{
   return stats["stat_" + stat];
}

nomask int query_stat(string stat)
{
   return stats["cur_" + stat];
}

void set_mod_stat(string stat, int s)
{
   stats["mod_" + stat] = s;
}

int query_mod_stat(string stat)
{
   return stats["mod_" + stat];
}

void inc_mod_stat(string stat)
{
   stats["mod_" + stat]++;
}

int spare_points()
{
   int total_pts = (this_object()->query_level() / 4) * 2;
   total_pts -= stats["mod_iq"] + stats["mod_me"] + stats["mod_ma"] + stats["mod_ps"] + stats["mod_pp"] +
                stats["mod_pe"] + stats["mod_pb"] + stats["mod_spd"];
   return total_pts;
}

nomask void set_stat(string stat, int c)
{
   stats["stat_" + stat] = c;
}

/*
** Character creation stuff
**
** query_roll_mods() may be overriden by subclasses to provide for changes
**   in the statistics generation.
**
** init_stats() may only be called once (admins may call whenever)
*/
class stat_roll_mods query_roll_mods()
{
   // should be overloaded
   return new (class stat_roll_mods);
}

private
int exceptional()
{
   int r = random(6) + 1;
   return r + (r == 6 ? exceptional() : 0);
}

private
nomask int roll_stat()
{
   int base = random(6) + random(6) + random(6) + 3;
   if (base > 15)
      return base + exceptional();
   else
      return base;
}

//: FUNCTION init_stats
// Rolls the stats for the first time, based on the proper racial adjustments.
// Admins can call this to reinitialize a player's stats (for example, in the
// case of abysmally horrific (near minimum) rolls.
nomask void init_stats()
{
   ::init_stats();

   stats["stat_iq"] = roll_stat();
   stats["stat_me"] = roll_stat();
   stats["stat_ma"] = roll_stat();
   stats["stat_ps"] = roll_stat();
   stats["stat_pp"] = roll_stat();
   stats["stat_pe"] = roll_stat();
   stats["stat_pb"] = roll_stat();
   stats["stat_spd"] = roll_stat();

   reset_stat_increases();

   refresh_stats();
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_carrying_stat()
{
   return query_stat("ps");
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_health_stat()
{
   return query_stat("pe");
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_physical_dmg_stat()
{
   return query_stat("ps");
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_agility_stat()
{
   return query_stat("pp");
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_social_stat()
{
   return query_stat("pb");
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_mental_stat()
{
   return query_stat("iq");
}

/*
** Must be defined for the mudlib inteface. Put in the stat you want.
*/
int query_reflex_stat()
{
   return query_stat("pp");
}

mapping stat_abrev()
{
   return (["Intelligence Quotient (I.Q.)":"iq",
                 "Mental Endurance (M.E.)":"me", "Mental Affinity (M.A.)":"ma", "Physical Strength (P.S.)":"ps",
                 "Physical Prowess (P.P.)":"pp", "Physical Endurance (P.E.)":"pe", "Physical Beauty (P.B.)":"pb",
                             "Speed (Spd)":"spd"]);
}

// Always returns a strlen 6.
string pretty_bonus(int b)
{
   string out = "      ";
   if (b > 0)
      out = "(<002>+" + b + "<res>)";
   else if (b < 0)
      out = "(<001>" + b + "<res>)";

   if (colour_strlen(out) < 6)
      out += repeat_string(" ", 6 - colour_strlen(out));

   return out;
}

string show_stats()
{
   return sprintf("<bld>I.Q.<res> %2d    <bld>M.E.<res> %2d    <bld>M.A.<res> %2d    <bld>P.S.<res> %2d \n" +      //
                      "<bld>P.P.<res> %2d    <bld>P.E.<res> %2d    <bld>P.B.<res> %2d    <bld>Spd.<res> %2d \n\n", //
                  query_stat("iq"),                                                                                //
                  query_stat("me"),                                                                                //
                  query_stat("ma"),                                                                                //
                  query_stat("ps"),                                                                                //
                  query_stat("pp"),                                                                                //
                  query_stat("pe"),                                                                                //
                  query_stat("pb"),                                                                                //
                  query_stat("spd"),                                                                               //
   );
}

/*
** Object inheriting this module should be sure to call this.
*/
void internal_setup(mixed args...)
{
}
