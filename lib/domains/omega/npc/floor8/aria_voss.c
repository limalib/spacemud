/* Do not remove the headers from this file! see /USAGE for more info. */

inherit LIVING;
inherit M_CONVERSATION;
inherit M_STATEFUL;

#define MAX_MISSIONS 3
#define RENEW_MISSIONS_MINUTES 120
#define PUSHY_CUSTOMER_PENALTY 10
#define PASS_EXPIRY 60

private
mapping missions = ([]);
private
mapping volunteers = ([]);

mapping volunteers()
{
   return volunteers;
}

void generate_key(string key)
{
   object pass;
   int expiry = time() + (60 * PASS_EXPIRY);
   if (volunteers[this_body()->query_name()] && volunteers[this_body()->query_name()] > time())
   {
      this_object()->targetted_action(
          "$N $vsay to $t, \"HEY! You already got a mission! Finish that first, see me when done.\"", this_body());
      // More penalty box for asking. 10 more minutes.
      volunteers[this_body()->query_name()] += (60 * PUSHY_CUSTOMER_PENALTY);
      return;
   }
   missions[key]["expiry"] = expiry;
   volunteers[this_body()->query_name()] = expiry;
   pass = new ("/domains/common/item/shuttle_pass", missions[key]);
   pass->move(this_body());
   this_object()->targetted_action("$N $vhand the $o to $t.", this_body(), pass);
   map_delete(missions, key);
}

void complete_mission(string who)
{
   map_delete(volunteers, who || this_body()->query_name());
}

void generate_missions()
{
   string *problems =
       ({"Core Failure|<bld>Power Core Failure:<res> The ship's primary power source has malfunctioned, leading to a "
         "complete "
         "systems shutdown.",
         "Comm Array Dmg|<bld>Communication Array Damage:<res> The ship's antennas or communication systems have been "
         "damaged, "
         "rendering them unable to send or receive signals.",
         "Navi Error|<bld>Navigational System Malfunction:<res> A critical error in the navigational systems has left "
         "the "
         "ship "
         "adrift and unable to correct its course or send distress signals.",
         "Hull Breach|<bld>Hull Breach:<res> A breach in the hull has caused an emergency lockdown, sealing off "
         "sections of "
         "the "
         "ship and disabling communication.",
         "Virus|<bld>Computer Virus:<res> A malicious software attack has crippled the ship's onboard computers, "
         "preventing "
         "any form of communication.",
         "Engine|<bld>Engine Overload:<res> The ship's engines have experienced a catastrophic failure, resulting in "
         "an "
         "emergency shutdown of all systems.",
         "Life Support|<bld>Life Support System Failure:<res> The life support systems have failed, putting the crew "
         "in "
         "immediate "
         "danger and prioritizing internal emergency protocols over external communication.",
         "Hostiles|<bld>Hostile Boarding:<res> The ship has been boarded by hostile forces, who have disabled "
         "communication to "
         "avoid detection.",
         "Asteroid|<bld>Asteroid Collision:<res> An unexpected collision with an asteroid or space debris has caused "
         "significant damage, disrupting all communication channels.",
         "Interference|<bld>Electromagnetic Interference:<res> A nearby cosmic anomaly or enemy device is emitting "
         "strong "
         "electromagnetic waves, blocking all outgoing and incoming signals."});
   missions = ([]);
   for (int i = 0; i < MAX_MISSIONS; i++)
   {
      string ship_type = SHIP_D->random_large_ship();
      int size = random(6) + 3;
      string *problem = explode(choice(problems), "|");
      missions["mission" + i] =
          (["ship type":ship_type,
                 "size":size, "mission":problem[0], "problem":problem[1], "shuttle":"/domains/common/ship/shuttle"]);
   }
}

void setup_chats()
{
   mapping responses = (["hello":"Sorry, I do not have time to chat. Did you have a question?@@help"]);
   mapping options =
       (["hello":"Hello, Chief Voss.", "help":"Can I assist the landing operations of Omega Station in some way?"]);
   string *confirmations =
       ({"My team and I will handle the", "We'll attempt to help the", "I decided on the", "I've picked the",
         "We are going for the", "Let's do the", "The", "Umm.. the", "The team has decided that we go for the"});
   string mission_txt = "I have the following \"dark ships\" right now - check back later for other missions:\n\n";
   string mission_list = "";

   foreach (string key in keys(missions))
   {
      mission_list += key + ",";
   }
   mission_list = mission_list[0.. < 1];

   foreach (string key, mapping mish in missions)
   {
      mission_txt += "       <148>" + capitalize(mish["ship type"]) + " category " + mish["size"] + "<res>:\n       " +
                     mish["problem"] + "\n\n";
      options[key] = choice(confirmations) + " <148>" + mish["ship type"] + " category " + mish["size"] + "<res>!";
      responses[key] =
          ({"Okay, the " + mish["ship type"] + " it is then.@@@@nothanks," + mission_list, (
                                                                                               : generate_key, key:)});
   }

   responses["help"] =
       ({mission_txt + "...",
         "Let me know if you want to help with one of these and I'll give you a terminal key to summon a "
         "shuttle.",
         "Higher category of ship means more people needed to handle the situation.",
         "So what will it be?@@nothanks," + mission_list});
   options["nothanks"] = "Nevermind, not right now then. My team is not quite ready.";
   responses["nothanks"] = "Stop wasting my time.@@@@" + mission_list;
   set_responses(responses);
   set_options(options);
}

void begin_conversation()
{
   // Generate missions just in time
   if (!sizeof(keys(missions)))
      generate_missions();
   setup_chats();
   set_start(({"hello"}));

   ::begin_conversation();
}

void setup()
{
   set_gender(2);
   set_name("Aria Voss");
   add_id("aria", "voss", "aria voss", "chief");
   set_proper_name("Aris Voss");
   set_in_room_desc("Chief landing controller Aria Voss");
   set_long("Behind the main counter stands the chief landing controller, Aria Voss, a seasoned veteran with sharp "
            "eyes and an air of authority. She wears a crisp uniform adorned with insignias of her rank and years of "
            "service. Her short-cropped hair is streaked with silver, hinting at her vast experience, and her focused "
            "expression reveals a mind always at work, juggling multiple tasks at once. A headset is permanently "
            "affixed to her ear, connecting her to various ship channels and station personnel.");

   // Refresh the missions every RENEW_MISSIONS_MINUTES
   set_call_interval(RENEW_MISSIONS_MINUTES);
}

int state_update()
{
   if (arrayp(missions))
      exit_conversations();
   missions = ([]);
   return 1;
}

string query_location()
{
   return "Omega Terminal";
}

string query_starsystem()
{
   return "Omega";
}

string *query_variants(string main_mish)
{
   if (!sizeof(keys(missions)))
      generate_missions();
   return clean_array(map(values(missions), ( : $1["mission"] :)));
}

string query_hint(int level)
{
   return "Aria Voss provides missions in space around Omega Terminal.";
}