/* Do not remove the headers from this file! see /USAGE for more info. */

inherit LIGHT_OBJECT;
inherit M_GETTABLE;

void setup()
{
   set_id("candle");
   set_adj("wax", "red");
   set_long("A red wax candle");
   set_fuel(10);
   set_die_msg("The $o burns up and a small pillar of smoke rises from the wick.");
   set_decay_action("The "+this_object()->short()+" flickers and sputters a little.");
}