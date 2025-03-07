/* Do not remove the headers from this file! see /USAGE for more info. */

inherit VERB_OB;

//: COMMAND
// USAGE
//
//  |  ``pull <something>``
//  |  ``pull <in some way> <something>``
//  |  ``pull <something> <in some way>``
//  |  ``pull <something> with <something>``
//
//  Pull or yank a rope, pull it hard, pull the wagon with the horse.
//
// .. TAGS: RST

void do_pull_obj(object ob, string name)
{
   ob->do_pull(name);
}

void do_pull_obj_with_obj(object ob1, object ob2)
{
   ob2->use("pull", ob1);
}

void do_pull_obj_str(object ob, string str)
{
   ob->do_pull_str(str);
}

void do_pull_str_obj(string str, object ob)
{
   ob->do_pull_str(str);
}

void create()
{
   add_rules(({"OBJ", "OBJ STR", "STR OBJ", "OBJ with OBJ"}), ({"yank"}));
}
