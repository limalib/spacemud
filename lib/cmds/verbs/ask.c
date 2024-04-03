/* Do not remove the headers from this file! see /USAGE for more info. */

//: COMMAND
// USAGE
//
//  |  ``apply <something> to <something>``
//  |  ``apply bandage to left arm``
//  |  ``apply for drivers license``
//
// For applying things to things or for things.
//
// .. TAGS: RST

inherit VERB_OB;

mixed do_ask_liv_about_wrd(object liv, string item)
{
   string items = liv->ask_about_items(item);
   if (items)
   {
      write(items);
   }
   else
      write(liv->short() + " knows nothing about that item.");
}

mixed do_ask_liv_about_str(object liv, string item)
{
   string items = liv->ask_about_items(item);
   if (items)
   {
      write(items);
   }
   else
      write(liv->short() + " knows nothing about that item.");
}

void create()
{
   add_rules(({"LIV about WRD", "LIV about STR"}), ({}));
}
