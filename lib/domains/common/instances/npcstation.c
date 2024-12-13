// inherit something;

string *station;
string instance_name;
string station_name;
int x, y, z;
int setup_done;

void setup()
{
}

object station_controller()
{
   return load_object(__FILE__[0.. < 3] + "/" + instance_name);
}

void create(string arg)
{
   int new_size;
   if (!arg)
   {
      ::create();
      return;
   }

   if (sscanf(arg, "%s/%d/%d/%d/%d", instance_name, new_size, x, y, z) != 5)
      if (sscanf(arg, "%s/%d", instance_name, new_size) != 2)
         return 0;

   set_station_size(new_size);
   instance_name = instance_name + "/" + new_size;
   ::create();
}

string *station_design()
{
   if (station_controller() == this_object())
   {
      if (!station)
         station = generate_station(query_station_size());
      return station;
   }
   return station_controller()->station_design();
}

int *random_room()
{
   int x = random(sizeof(station_design()) - 2) + 1;
   int y = random(sizeof(station_design()) - 2) + 1;
   int z = random(sizeof(station_design()) - 2) + 1;
   if (station_design()[x][y][z] != ' ')
      return ({x, y, z});
   else
      return random_room();
}

string size_name()
{
   switch (query_station_size()))
      {
      case 0..3:
         return "small";
      case 4..6:
         return "large";
      case 7..9:
         return "quite large";
      case 10..15:
         return "huge";
      default:
         return "gigantic";
      }
}

string station_name()
{
   if (station_controller() == this_object())
   {
      if (!station_name)
         // some code here to reference a daemon?
         return station_name;
   }
   return station_controller()->station_name();
}

int *coords()
{
   return ({x, y, z});
}

string query_instance_name()
{
   return instance_name;
}

varargs int room_type(int *coords)
{
   if arrayp (coords))
        return station_design()[coords[0]][coords[1]][coords[2]];
   if (x >= sizeof(station_design()) || y >= strlen(station_design()[0]) || z >= strlen(station_design()[0]))
      return ' ';
   return station_design()[x][y][z];
}

void add_exits()
{
   if (room_type(({x - 1, y, z})) != ' ')
      add_exit("south", __FILE__[0.. < 4] + "/" + instance_name + "/" + (x - 1) + "/" + y + "/" + z);
   if (room_type(({x + 1, y, z})) != ' ')
      add_exit("north", __FILE__[0.. < 4] + "/" + instance_name + "/" + (x + 1) + "/" + y + "/" + z);
   if (room_type(({x, y + 1, z})) != ' ')
      add_exit("east", __FILE__[0.. < 4] + "/" + instance_name + "/" + x + "/" + (y + 1) + "/" + z);
   if (room_type(({x, y - 1, z})) != ' ')
      add_exit("west", __FILE__[0.. < 4] + "/" + instance_name + "/" + x + "/" + (y - 1) + "/" + z);
   if (room_type(({x, y, z + 1})) != ' ')
      add_exit("up", __FILE__[0.. < 4] + "/" + instance_name + "/" + x + "/" + y + "/" + (z + 1));
   if (room_type(({x, y, z - 1})) != ' ')
      add_exit("down", __FILE__[0.. < 4] + "/" + instance_name + "/" + x + "/" + y + "/" + (z - 1));
}

int *find_rooms_of_type(int type)
{
}

void generate_room()
{
}

string room_type_name(int short_code)
{
   string type_name;
   switch (short_code)
   {
   case 'A':
      type_name = "airlock";
      break;
   case 'O':
      type_name = "outer ring";
      break;
   case 'I':
      type_name = "inner ring";
      break;
   case 'H':
      type_name = "hallway";
      break;
   case 'R':
      type_name = "room";
      break;
   case 'S':
      type_name = "central spindle";
      break;
   }
   return type_name;
}

void object_arrived(object ob)
{
   if (!setup_done)
   {
      string long;
      ABUG(ob->short() + " arrived.  Setting up new room.");
      add_exits();
      long = room_type_name("A");
      generate_room();
      set_brief(station_name() + " - " + capitalize(long));
      setup_done = 1;
   }
}

object virtual_create(string arg)
{
   return new (__FILE__, arg);
}

void stat_me()
{
   for (int l = sizeof(station_design()) - 1; l >= 0; l--)
   {
      string line = station_design()[l];
      if (x == 1)
         line = line[0..y - 1] + "<120>" + line[y..y] + "<res>" + line[y + 1..];
      write(line);
   }
}