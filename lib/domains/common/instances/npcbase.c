// inherit something;

string *base;
string instance_name;
string base_name;
int x, y;
int setup_done;

void setup()
{
}

object base_controller()
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

   if (sscanf(arg, "%s/%d/%d/%d", instance_name, new_size, x, y) != 4)
      if (sscanf(arg, "%s/%d", instance_name, new_size) != 2)
         return 0;

   set_base_size(new_size);
   instance_name = instance_name + "/" + new_size;
   ::create();
}

string *base_design()
{
   if (base_controller() == this_object())
   {
      if (!base)
         base = generate_base(query_base_size());
      return base;
   }
   return base_controller()->base_design();
}

int *random_room()
{
   int x = random(sizeof(base_design()) - 2) + 1;
   int y = random(sizeof(base_design()) - 2) + 1;
   if (base_design()[x][y] != ' ')
      return ({x, y});
   else
      return random_room();
}

string size_name()
{
    switch (query_base_size()))
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

string base_name()
{
    if (base_controller() == this_object())
    {
        if(!base_name)
        //some code here to reference a daemon?
        return base_name;
    }
    return base_controller()->base_name();
}

int *coords()
{
    return ({x,y});
}

string query_instance_name()
{
    return instance_name;
}

varargs int room_type(int *coords)
{
    if arrayp(coords))
        return base_design()[coords[0]][coords[1]];
    if (x >= sizeof(base_design()) || y >= strlen(base_design()[0]))
        return ' ';
    return base_design()[x][y];
}