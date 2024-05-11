/* Do not remove the headers from this file! see /USAGE for more info. */

/*
 * uptime  -  reports how long the mud has been up.
 * copied from ideaexchange where it was originally
 * created by beek@nightmare
 * copied by zifnab@zorkmud
 */

//: PLAYERCOMMAND
//$$ see: timezone
// USAGE
//   ``time``
//
// Displays the current local time (where the mud server is located),
// and the GMT conversion of that, and player's local time (if the
// GMT offset has been entered using the ``timezone`` command)
// together with time the mud was last rebooted (on mud local time),
// and how long it has been up.
//
// .. TAGS: RST

#include <localtime.h>

inherit CMD;
inherit M_FRAME;

#define MIN 60
#define HOUR (60 * MIN)
#define DAY (24 * HOUR)
#define WEEK (7 * DAY)

private
string week_view()
{
   string day = EVENT_D->time_to_weekday();
   string out = "";
   TBUG(day);

   foreach (string d in EVENT_D->week_days())
   {
      out += "[" + (d == day ? "<190>" : "") + d + "<res>] ";
   }
   return out+"\n";
}

private
void main(string notused)
{
   int tm = uptime();
   int tm1 = time();
   string tm2 = ctime(tm1);
   int tm3 = tm1 - uptime();
   string tm4 = ctime(tm3);
   int tm5;
   string str = "";
   mixed local = localtime(tm1);
   int offset = local[LT_GMTOFF];
   string gmt;
   int x;
   string game_time = EVENT_D->time_to_str();
   mixed my_offset;

   my_offset = this_body()->query_tz();
   if (intp(my_offset) || floatp(my_offset))
   {
      my_offset = to_int(3600.0 * my_offset);
      tm5 = tm1 + my_offset;
   }
   gmt = ctime(tm1 - offset);
   str += sprintf("<190>%s<res>\n", game_time);
   str += week_view()+"\n";
   str += sprintf("%s.\n", tm2);
   str += sprintf("%s.\n", gmt);
   my_offset = this_body()->query_tz();
   if (intp(my_offset) || floatp(my_offset))
   {
      my_offset = to_int(3600.0 * my_offset);
      tm5 = tm1 + my_offset;
      str += sprintf("\n%s.\n", ctime(tm1 + my_offset));
   }
   str += sprintf("\n" + mud_name() + " restarted on " + tm4 + ". \n");
   str += mud_name() + " has been up for ";
   if (x = (tm / WEEK))
   {
      str += x + "w ";
      tm -= x * WEEK;
   }

   if (x = (tm / DAY))
   {
      str += x + "d ";
      tm -= x * DAY;
   }

   if (x = (tm / HOUR))
   {
      str += x + "h ";
      tm -= x * HOUR;
   }

   if (x = (tm / MIN))
   {
      str += x + "m ";
      tm -= x * MIN;
   }

   if (tm)
      str += tm + "s ";

   str = str[0.. < 2] + ".\n";
   frame_init_user();
   set_frame_left_header();
   set_frame_title("Game Time & Real Time");
   set_frame_content(str);
   set_frame_header("Game Time\n\n\nLocal MUD time\nGMT\n\nYour timezone\n\nUptime");
   out(frame_render());
}

void player_menu_entry(string str)
{
   bare_init();
   main(str);
   done_outputing();
}
