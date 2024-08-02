/* Do not remove the headers from this file! see /USAGE for more info. */

// party_menu.c - Menu object accessible through the 'party' command
//                for all players. Includes all party-related
//                functions.
// March 1, 1997: Iizuka@Lima Bean created.
// August 15, 1999: Iizuka@Lima Bean ripped creation process out of the
//                  party player command and moved it here.

#define MAX_ATTEMPTS 3

#include <mudlib.h>

inherit "/std/menu2";
inherit M_FRAME;
inherit CLASS_PARTY;

private
varargs void enter_password(string owner, string party_name, int failures, string response);

class menu toplevel;
class menu maint;

class menu_item quit_item;
class menu_item main_seperator;
class menu_item help_item;
private
string party_name;

void who_current()
{
   int online;
   class party party = PARTY_D->query_party(party_name);
   string c = "";
   mapping members = party.members;
   mapping kills = party.kills;
   frame_init_user();
   set_frame_title("Party: " + party_name);
   set_frame_header(sprintf("%-15.15s %-10.10s %-10.10s %-10.10s", "Player", "Level", "Role", "Kills"));

   foreach (string name in keys(members))
   {
      object body = find_body(lower_case(name));
      if (body)
      {
         c += sprintf(" %-15.15s %-10.10s %-10.10s %-10.10s\n", body->query_name(), "" + body->query_level(),
                      members[name] == 1 ? "Lead" : "Member", "" + kills[name]);
         online++;
      }
      else
         c += sprintf(warning(" %-15.15s %-10.10s %-10.10s %-10.10s") + "\n", name, "Offline",
                      members[name] == 1 ? "Lead" : "Member", "" + kills[name]);
   }
   set_frame_footer(sprintf("%d member%s, %d online right now. Total kills for the party: %d", sizeof(members),
                            sizeof(members) == 1 ? "" : "s", online, party.total_kills));
   set_frame_content(c);
   write(frame_render());
}

void party_maint()
{
   return;
}

void party_help()
{
   return;
}

void last_ten_kills()
{
   string *list = PARTY_D->query_kill_list(party_name);
   int count = sizeof(list);
   printf("Last 10 kills in the party");
   printf("--------------------------");
   foreach (string kill in list)
   {
      printf("%-3.3s %s", "" + count, kill);
      count--;
   }
   printf("--------------------------\n\n");

   return;
}

void list_active()
{
   string c = "";
   mapping active = PARTY_D->list_all_parties();
   frame_init_user();
   set_frame_title("Party: " + party_name);
   set_frame_header(sprintf("%-25.25s %-12.12s %-12.12s", "Party Name", "Kill count", "Members"));

   foreach (string name, int *data in active)
   {
      c += sprintf(" %-25.25s %-12.12s %-12.12s", name, "" + data[0], "" + data[1]);
   }
   set_frame_content(c);
   write(frame_render());
}

void quit_party()
{
   printf("Removing you from %s.. %%^RED%%^done.%%^RESET%%^\n\n", party_name);
   if (sizeof(PARTY_D->query_party_members(party_name)) == 1)
      PARTY_D->remove_party(party_name);
   else
      PARTY_D->remove_member(this_body()->query_name(), party_name);
   quit_menu_application();
}

void start_menu()
{
   party_name = PARTY_D->locate_user(this_body()->query_name());
   toplevel = new_menu(party_name + " Party Menu");
   maint = new_menu(party_name + " Maintenance Menu");

   quit_item = new_menu_item("Quit", ( : quit_menu_application:), "q");

   add_menu_item(toplevel, new_menu_item("Members in " + party_name, ( : who_current:), "m"));

   add_menu_item(toplevel, new_menu_item("Active parties", ( : list_active:), "a"));

   add_menu_item(toplevel, new_menu_item("Last ten kills", ( : last_ten_kills:), "k"));
   TBUG(PARTY_D->query_owner(party_name));
   TBUG(this_body()->query_name());

   if (PARTY_D->query_owner(party_name) == this_body()->query_name())
      add_menu_item(toplevel, new_menu_item("Party maintenance", ( : party_maint:), "p"));

   add_menu_item(toplevel, new_menu_item("QUIT " + party_name + " permanently.", ( : quit_party:), "X"));

   add_menu_item(toplevel, new_menu_item("Help!", ( : party_help:), "h"));

   add_menu_item(toplevel, quit_item);

   init_menu_application(toplevel);
}

void confirm_create(string owner, string party_name, string response)
{
   switch (response)
   {
   case "n":
   case "no":
      destruct();
   case "y":
   case "yes":
      modal_simple(( : enter_password, owner, party_name, 0 :), "   Enter password: ", 1);
      return;
   default:
      modal_simple(( : confirm_create, owner, party_name:), "Enter 'yes' or 'no' please: ", 0);
      return;
   }
}

private
void confirm_password(string owner, string party_name, string password, int failures, string response)
{
   if (response != password)
   {
      write("\nPasswords do not match!\n");
      if (++failures == MAX_ATTEMPTS)
      {
         write("Sorry..\n");
         destruct();
      }
      modal_simple(( : enter_password, owner, party_name, failures:), "   Enter password: ", 1);
      return;
   }

   PARTY_D->register_party(party_name, owner, password);
   write("\n");
   start_menu();
}

private
varargs void enter_password(string owner, string party_name, int failures, string response)
{
   if (!response || response == "")
   {
      write("You must enter a password. And don't forget it!\n");
      if (++failures == MAX_ATTEMPTS)
      {
         write("Sorry.\n");
         destruct();
      }
      modal_simple(( : enter_password, owner, party_name, failures:), "   Enter password: ", 1);
      return;
   }

   if (PARTY_D->party_exists(party_name))
   {
      if (!PARTY_D->add_member(owner, party_name, response))
      {
         write("Incorrect password.\n");
         if (++failures == MAX_ATTEMPTS)
         {
            write("Sorry.\n");
            destruct();
         }
         modal_simple(( : enter_password, owner, party_name, failures:), "   Enter password: ", 1);
         return;
      }
      failures = 0;
      printf("Joined %s.\n", party_name);
   }
   else
   {
      modal_simple(( : confirm_password, owner, party_name, response, failures:), "\n   Confirm password: ", 1);
      return;
   }

   start_menu();
}

private
varargs void enter_party_password(string owner, string party_name, int failures, string response)
{
   write("\n"); // Since we were in secure entry
   if (failures == MAX_ATTEMPTS)
   {
      write("Sorry, you just didn't make the cut.\n");
      destruct();
   }

   if (!PARTY_D->add_member(owner, party_name, response))
   {
      write("Password is incorrect.\n");
      modal_simple(( : enter_party_password, owner, party_name, ++failures:), "Try again. Enter password: ");
   }
   else
   {
      write("Congratulations! You've been added to the party!\n");
   }
}

private
void enter_party_name(string owner, string response)
{
   response = trim(response);
   if (!response || response == "" || !regexp(response, "^[a-zA-Z 0-9]+$"))
   {
      write("Invalid name, only letters, numbers and spaces.\n");
      modal_simple(( : enter_party_name, owner:), "   Enter party name: ");
      return;
   }

   if (PARTY_D->party_exists(response))
   {
      printf("%s exists.\n", response);
      modal_simple(( : enter_party_password, owner, response, 0 :), "   Enter password: ", 1);
   }
   else
   {
      printf("Party '%s' does not exist. ", response);
      modal_simple(( : confirm_create, owner, response:), "Create it? ");
   }
}

private
void confirm_join_party(string owner, string response)
{
   response = lower_case(response);

   if (response == "n" || response == "no")
      destruct(this_object());

   if (response == "y" || response == "yes")
   {
      modal_simple(( : enter_party_name, owner:), "  Enter party name: ");
   }
}

void join_party()
{
   string owner = this_body()->query_name();

   if (!PARTY_D->locate_user(owner))
   {
      write("You are not a member of any party.\n");
      modal_simple(( : confirm_join_party, owner:), "Would you like to join one? ");
   }
   else
   {
      start_menu();
   }
}
