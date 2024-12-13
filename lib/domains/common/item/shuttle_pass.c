inherit OBJ;
inherit M_GETTABLE;

string capability;
string shuttle;
int level;

mapping payload = ([]);

void mudlib_setup(mapping p)
{
   set_id("space shuttle pass", "pass", "shuttle pass");
   payload = p || ([]);
}

mapping payload()
{
   return payload;
}

int set_payload(string key, mixed value)
{
   payload[key] = value;
}

int is_expired()
{
   return payload["expiry"] < time();
}

string shuttle_file()
{
   if (!shuttle)
      shuttle = payload["shuttle"] + "/server/" + time_ns();
   return shuttle;
}

mixed drop()
{
   if (!this_body())
      return 1;
   this_body()->simple_action("$N $vdrop " + short() + " which disappears in a puff of smoke.");

   this_object()->remove();
}

string short()
{
   if (is_expired() && member_array("expired", query_adj()) == -1)
      set_adj("expired");
   return ::short();
}

string long()
{
   string expiry;
   int expiry_count = payload["expiry"] - time();
   if (payload["expiry"] > time())
      expiry = time_to_string(expiry_count, 1);
   else
      expiry = "EXPIRED";

   return "A pass that can be inserted into a docking terminal to summon a space shuttle.\n"
          "This pass has a small digital date display next to the word %^DIGITAL_DISPLAY%^Expiry%^RESET%^, saying: " +
          "%^DIGITAL_DISPLAY%^" + expiry + "%^RESET%^.";
}

int is_docking_pass()
{
   return 1;
}

string query_module_name()
{
   return "shuttle pass";
}

// Can be put into things.
mixed direct_put_obj_wrd_obj(object ob1, string wrd, object ob2)
{
   return 1;
}
