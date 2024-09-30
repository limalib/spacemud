/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** naming.c -- functions for naming and description of the player body
**
** 960603, Deathblade: created.
*/

#include <commands.h>    /* for CMD_OB_xxx */
#include <playerflags.h> /* for F_INACTIVE */

private
string describe;
private
string invis_name;
private
string nickname;

#ifdef USE_INTRODUCTIONS
private
string *introduced = ({});
#endif

void save_me();
void remove_id(string *id...);
void add_id_no_plural(string *id...);

string number_of(int num, string what);
string in_room_desc();
string living_query_name();
string query_name();
string query_race();
string query_pronoun();
string query_reflexive();

int is_visible();
int test_flag(int which);
int query_ghost();
int query_prone();
int query_sitting();

object query_link();

#ifdef USE_INTRODUCTIONS
string physical_appearance();
#endif

#ifdef USE_TITLES
string query_title();
#endif

#ifdef USE_INTRODUCTIONS
int is_introduced(object body)
{
   return member_array(body->query_link()->query_userid() + ":" + body->query_name(), introduced) != -1;
}

void introduce(object body)
{
   if (!is_introduced(body))
      introduced += ({body->query_link()->query_userid() + ":" + body->query_name()});
}

string *query_introduced()
{
   return introduced;
}

void clear_introduced()
{
   introduced=({});
}

string query_description()
{
   string state = query_prone() ? "is lying on the ground" : (query_sitting() ? "is sitting here" : "is standing here");
   return physical_appearance() + " " + state + ".";
}
#endif

string query_long_name()
{
#ifdef USE_INTRODUCTIONS
   if (query_ghost())
      return "A ghostly outline of " + add_article(query_race());
#ifdef USE_TITLES
   // If the onlooker is introduced to use, give them our title, otherwise give them our description.
   return this_body()->is_introduced(this_object()) ? query_title() : query_description();
#else
   return this_body()->is_introduced(this_object()) ? query_description() + "[" + query_name() + "]" +)
       : query_description();
#endif
   return;
#else
   if (query_ghost())
      return "The ghost of " + capitalize(living_query_name());
#ifdef USE_TITLES
   return query_title();
#else
   return capitalize(living_query_name());
#endif
#endif
}

nomask string query_userid()
{
   if (!query_link())
      return 0;
   return query_link()->query_userid();
}

nomask string query_invis_name()
{
   return invis_name;
}

string query_idle_string()
{
   object link = query_link();
   int idle_time;
   string result = "";

   if (test_flag(F_INACTIVE))
      result += " [INACTIVE] ";

   if (interactive(link))
      idle_time = query_idle(link);
   if (idle_time < 60)
      return result;

   result += " [idle " + convert_time(idle_time, 2) + "]";
   return result;
}

// This is used by in_room_desc and by who, one of which truncates,
// one of which doesnt.  Both want an idle time.
string base_in_room_desc()
{
   string result;
   object link = query_link();

   result = query_long_name();

   /* if they are link-dead, then prepend something... */
   if (!link || !interactive(link))
      result = "The lifeless body of " + result;

   return result;
}

string query_formatted_desc(int num_chars)
{
   string idle_string;
   int i;

   idle_string = query_idle_string();
   if (i = strlen(idle_string))
   {
      num_chars -= (i + 1);
      idle_string = " " + idle_string;
   }
   return M_COLOURS->colour_truncate(base_in_room_desc(), num_chars) + idle_string;
}

string adjust_name(string name)
{
   if (!name)
      return "Nothing";
   if (invis_name == capitalize(name) || !invis_name)
      invis_name = "Someone";
   if (!is_visible())
      return invis_name;
   return capitalize(name);
}

void set_description(string str)
{
   if (base_name(previous_object()) == CMD_OB_DESCRIBE)
      describe = str;
   save_me();
}

string our_description()
{
   if (describe)
      return in_room_desc() + "\n" + describe + "\n";

   return in_room_desc() + "\n" +
#ifdef USE_INTRODUCTIONS
          capitalize(query_pronoun())
#else
          capitalize(query_name())
#endif
          + " is boring and hasn't described " + query_reflexive() + ".\n";
}

void set_nickname(string arg)
{
   if (file_name(previous_object()) != CMD_OB_NICKNAME)
      error("Illegal call to set_nickname\n");

   if (nickname)
      remove_id(nickname);

   nickname = arg;
   add_id_no_plural(nickname);
   parse_refresh();
}

string query_nickname()
{
   return nickname;
}

protected
void naming_init_ids()
{
   if (nickname)
      add_id_no_plural(nickname);
}
