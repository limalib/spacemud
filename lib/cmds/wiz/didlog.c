/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** didlog.c -- print out a portion of the DID_D log
**
** 950821, Deathblade: created
*/

//: COMMAND
//$$ see: I, lima
// USAGE: didlog
//       didlog <value>
//       didlog /on
//       didlog /off
//       didlog /help (more info here!)
//       didlog /versions
//       didlog /version <name>
//       didlog /version <name> <pattern> <days>
//       dudlog /newversion
//
// Shows you the "did" log (ie log of changes recorded by wizards).
// With no arguments it shows the log for the past day.
// With an integer argument it will show the log for that many days back.
// didlog /off turns didlog notification on login off.
// didlog /on turns it back on again.

#include <daemons.h>

inherit CMD;

private
void main(string str)
{
   int ndays;
   string header;
   string pattern;
   string version;

   if (str && sscanf(str, "/version %s %s", pattern, str) == 2)
   {
      if (member_array(pattern, DID_D->versions()) != -1)
         version = pattern;
      else
         out("Unknown version '" + pattern + "'.");
      pattern = 0;
   }

   if (!str)
      ndays = 1;
   else if (str == "help" || str == "/help" && this_body())
   {
      out("didlog:\n"
          "  didlog <days>|all                     - Show didlog since <days> or all.\n"
          "  didlog /version <name>                - Show all changes in <version>.\n"
          "  didlog /on|/off                       - Turn didlog on login on/off.\n"
          "  didlog /newversion                    - Set a new version (admin only).\n"
          "  didlog /versions                      - Show the versions stored.\n"
          "  didlog /version <name> <pat> <days>   - Show changes in version matching pattern since days.");
      return;
   }
   else if (str == "/off" && this_body())
   {
      this_user()->set_didlog_off(1);
      out("You will no longer receive didlog notifications.\n");
      return;
   }
   else if (str == "/on" && this_body())
   {
      this_user()->set_didlog_off(0);
      out("You will now receive didlog notifications.\n");
      return;
   }
   else if (str == "/versions" && this_body())
   {
      out("The following versions are known: \n\t" + implode(sort_array(DID_D->versions(), 1), "\n\t") + "\n");
      return;
   }
   else if (strlen(str) > 8 && str[0..10] == "/newversion" && this_body() && adminp(this_body()))
   {
      if (sscanf(str, "/newversion %s", pattern) == 1)
      {
         if (mud_name() == "LIMA")
         {
            out("Error: Set version in secure/simul_efun/misc.c for LIMA library.");
            DID_D->set_version(0);
            return;
         }
         DID_D->set_version(pattern);
         out("Version set to '" + pattern + "'.");
         return;
      }
      else
      {
         out("Usage: didlog /version number");
         return;
      }
   }
   else if (!(ndays = to_int(str)))
   {
      if (str == "all")
         ndays = -1;
      else if (sscanf(str, "%s %d", pattern, ndays) != 2)
      {
         pattern = str;
         ndays = 1;
      }
   }

   if (ndays == 1)
      header = "DID_D report for the past day" + (version ? " for " + version : "");
   if (ndays == -1)
   {
      header = "Complete DID_D report" + (version ? " for " + version : "");
   }
   else
      header = sprintf("DID_D report for the past %d days" + (version ? " for " + version : ""), ndays);

   out(DID_D->get_did_info(time() - ndays * 24 * 60 * 60, ({header, repeat_string("-", sizeof(header)), ""}), pattern,
                           0, version));
}
