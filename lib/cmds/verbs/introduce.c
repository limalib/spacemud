/* Do not remove the headers from this file! see /USAGE for more info. */

inherit VERB_OB;

void do_introduce_obj(object ob)
{
   this_body()->simple_action("$N $vare happy to introduce: $O!", ob);
}

void do_introduce()
{
   write("Introduce who?");
}

void do_introduce_wrd(string word)
{
   object *players = filter_array(all_inventory(environment(this_body())), ( : $1->is_body() && $1 != this_body() :));

   if (word != "yourself")
   {
      write("Introduce who?");
      return;
   }

   foreach (object p in players)
   {
      p->introduce(this_body());
   }
   this_body()->my_action("$N $vintroduce $r as \"$O1\".", this_body()->physical_appearance(),
                          this_body()->query_name());
   this_body()->other_action("$O $vintroduce $r as \"$O1\".", this_body()->physical_appearance(),
                             this_body()->query_name());
}

void create()
{
   add_rules(({
       "",
       "WRD",
       "OBJ",
   }));
}
