/* Do not remove the headers from this file! see /USAGE for more info. */

#ifndef __MUDLIB_H__
#define __MUDLIB_H__
#pragma no_warnings

#include <daemons.h>
#include <dirs.h>
#include <size.h>
#include <setbit.h>
#include <msgtypes.h>
#include <classes.h>
#include <custom_mudlib.h>

#define BODY               "/std/body"
#define USER_OB            "/secure/user"
#define USER_OB_BAK        "/secure/user_bak"

#define SIMUL_OB           "/secure/simul_efun"

#define BASE_ROOM          "/std/base_room"
#define GRID_SERVER        "/std/grid_server"
#define INDOOR_ROOM        "/std/indoor_room"
#define NON_ROOM           "/std/non_room"
#define OUTDOOR_ROOM       "/std/outdoor_room"
#define WATER_ROOM         "/std/water_room"

#define HEAVEN             "/domains/std/room/Heaven"
#define LAB                "/domains/std/room/Laboratory"
#define VOID_ROOM          "/domains/std/room/Void"
#define WIZ_ROOM           "/domains/std/room/Wizroom"

#define	MENUS              "/std/menu"
#define	OLD_MENUS          "/std/menu_old"
#define ADVERSARY          "/std/adversary"
#define AGGRESSIVE_MONSTER "/std/aggressive_monster"
#define AMMUNITION         "/std/ammunition"
#define ARMOUR             "/std/armour"
#define BASE_OBJ           "/std/base_obj"
#define CHEST              "/std/chest"
#define CLIMB_CHALLENGE    "/std/climb_challenge"
#define COMBAT_SPELL       "/std/combat_spell"
#define CONTAINER          "/std/container"
#define CORPSE             "/std/corpse"
#define DOOR               "/std/door"
#define EXIT_OBJ           "/std/complex_exit_obj"
#define FLAME              "/std/flame"
#define FLUID              "/std/fluid"
#define FOLLOWING_MONSTER  "/std/following_monster"
#define FOOD               "/std/food"
#define FURNITURE          "/std/furniture"
#define GUILD_GUARD        "/std/guild_guard"
#define HIDDEN_DOOR        "/std/hidden_door"
#define HIDDEN_EXIT        "/std/hidden_exit"
#define KEY                "/std/key"
#define LIGHT_OBJECT       "/std/light_object"
#define LIVING             "/std/living"
#define MOUNT              "/std/mount"
#define MOVING_MONSTER     "/std/moving_monster"
#define MOVING_ROOM        "/std/moving_room"
#define NVERB_OB           "/std/nverb_ob"
#define OBJ                "/std/object"
#define PAPER              "/std/paper"
#define PARAM_OBJ          "/std/param_obj"
#define PELT               "/std/pelt"
#define RANGED_WEAPON      "/std/ranged_weapon"
#define SECRET_DOOR        "/std/secret_door"
#define SIGN               "/std/sign"
#define SPELL              "/std/spell"
#define STOCK_MASTER       "/std/stock_master"
#define VERB_OB            "/std/verb_ob"
#define WANDERING_MONSTER  "/std/wandering_monster"
#define WATER              "/std/water"
#define WEAPON             "/std/weapon"

/* used by the OBJ object */

/* for mudlib objects */
#define _MODULES           "/std/modules/"
#define M_COLOURS          _MODULES "m_colours"
#define M_COMPLETE         _MODULES "m_complete"
#define M_CONVERSATION     _MODULES "m_conversation"
#define M_DRINK_CONTAINER  _MODULES "m_drink_container"
#define M_DRINK_SOURCE     _MODULES "m_drink_source"
#define M_DRINKABLE        _MODULES "m_drinkable"
#define M_DURABILITY       _MODULES "m_durability"
#define M_EDIBLE           _MODULES "m_edible"
#define M_FLUID_CONTAINER  _MODULES "m_fluid_container"
#define M_FLUID_SOURCE     _MODULES "m_fluid_source"
#define M_FRAME            _MODULES "m_frame"
#define M_GLOB             _MODULES "m_glob"
#define M_GRAMMAR          _MODULES "m_grammar"
#define M_ITEMS            _MODULES "m_items"
#define M_PARSING          _MODULES "m_parsing"
#define M_RECONNECT        _MODULES "m_reconnect"
#define M_REGEX            _MODULES "m_regex"
#define M_SMARTMOVE        _MODULES "m_smartmove"
#define M_STATEFUL         _MODULES "m_stateful"
#define M_TEST_SUITE       _MODULES "m_test_suite"
#define M_WIDGETS          _MODULES "m_widgets"

/* for area objects */ 
#define M_ACCOUNTANT       _MODULES "m_accountant"
#define M_ACTIONS          _MODULES "m_actions"
#define M_AGGRESSIVE       _MODULES "m_aggressive"
#define M_ASSISTANCE       _MODULES "m_assistance"
#define M_BLOCKEXITS       _MODULES "m_blockexits"
#define M_BOSS             _MODULES "m_boss"
#define M_COMPANION        _MODULES "m_companion"
#define M_COMPLEX_EXIT     _MODULES "m_complex_exit"
#define M_CRAFTING         _MODULES "m_crafting"
#define M_DAMAGE_SINK      _MODULES "m_damage_sink"
#define M_DAMAGE_SOURCE    _MODULES "m_damage_source"
#define M_DECAY            _MODULES "m_decay"
#define M_DICE             _MODULES "m_dice"
#define M_DIGGABLE         _MODULES "m_diggable"
#define M_DIGGER           _MODULES "m_digger"
#define M_EXIT             _MODULES "m_exit"
#define M_FLOW_ROOM        _MODULES "m_flow_room"
#define M_FOLLOW           _MODULES "m_follow"
#define M_GETTABLE         _MODULES "m_gettable"
#define M_GUILD_MASTER     _MODULES "m_guild_master"
#define M_GUILD_MEMBER     _MODULES "m_guild_member"
#define M_HEALING          _MODULES "m_healing"
#define M_KNOCKABLE        _MODULES "m_knockable"
#define M_LIGHT_SOURCE     _MODULES "m_light_source"
#define M_LIGHTABLE        _MODULES "m_lightable"
#define M_LOCKABLE         _MODULES "m_lockable"
#define M_LOCKPICK         _MODULES "m_lockpick"
#define M_MDVIEW           _MODULES "m_mdview"
#define M_MESSAGES         _MODULES "m_messages"
#define M_MISSION_CTRL     _MODULES "m_mission_control"
#define M_MOUNTABLE        _MODULES "m_mountable"
#define M_NPCSCRIPT        _MODULES "m_npcscript"
#define M_OPENABLE         _MODULES "m_openable"
#define M_POWER            _MODULES "m_power"
#define M_REACT            _MODULES "m_react"
#define M_READABLE         _MODULES "m_readable"
#define M_READY            _MODULES "m_ready"
#define M_RSTVIEW          _MODULES "m_rstview"
#define M_SALVAGEABLE      _MODULES "m_salvageable"
#define M_SEARCHABLE       _MODULES "m_searchable"
#define M_SIBLING          _MODULES "m_sibling"
#define M_SPECIAL_WEAPON   _MODULES "m_special_weapon"
#define M_SWITCHABLE       _MODULES "m_switchable"
#define M_THROWABLE        _MODULES "m_throwable"
#define M_TRAINER          _MODULES "m_trainer"
#define M_TRIGGERS         _MODULES "m_triggers"
#define M_VENDOR           _MODULES "m_vendor"
#define M_WANDER           _MODULES "m_wander"
#define M_WANDER_OLD       _MODULES "m_wander_old"
#define M_WEARABLE         _MODULES "m_wearable"
#define M_WIELDABLE        _MODULES "m_wieldable"
#define M_WRITING_SURFACE  _MODULES "m_writing_surface"
 
/* secure _MODULES */
#define _SEC_MODULES       "/secure/modules/"
#define M_ACCESS           _SEC_MODULES "m_access"
#define M_DAEMON_DATA      _SEC_MODULES "m_daemon_data"
#define M_FILE             _SEC_MODULES "m_file"
#define M_INPUT            _SEC_MODULES "m_input"
#define M_SAVE             _SEC_MODULES "m_save"
#define M_SET              _SEC_MODULES "m_set"

#define M_LIB_LOCKABLE	  "/domains/std/lockable"
#define M_LIB_OPENABLE    "/domains/std/openable"

#define ADDTO_OB          "/trans/obj/addto_ob"
#define ADMTOOL           "/obj/admtool/admtool2"
#define ADMTOOL_BASE      "/obj/admtool/internal/base"
#define CONFIG_EDITOR     "/trans/obj/config_editor"
#define DATAEDIT          "/trans/obj/dataedit"
#define ED_SESSION        "/trans/obj/ed_session"
#define TASKTOOL          "/obj/tasktool/tasktool"
#define TELNET_OB         "/trans/obj/telnet_ob"
#define USER_MENU         "/obj/usermenu/usermenu"
#define WIZ_SHELL         "/trans/obj/wish"

#define ALIASMENU         "/obj/mudlib/aliasmenu"
#define ANNO_MENU         "/obj/mudlib/annotationmenu"
#define HELPSYS           "/obj/mudlib/helpsys"
#define HINT_MENU         "/obj/mudlib/hintmenu"
#define IFTP_OB           "/obj/mudlib/iftp_ob"
#define NEWSREADER        "/obj/mudlib/newsreader"
#define NNTP_OB           "/obj/mudlib/nntp"
#define ARTEFACT_MENU     "/obj/mudlib/artefact_menu"
#define PARTY_MENU        "/obj/mudlib/party_menu"
#define PLAYER_MENU       "/obj/mudlib/plmenu"
#define PLAYER_SHELL      "/obj/mudlib/pshell"
#define SIMPLE_OB         "/obj/mudlib/simple_ob"
#define TEMP_WORKROOM     "/obj/mudlib/TWorkroom"

#define CMD               "/obj/secure/cmd"
#define SPECIAL           "/obj/secure/special"
#define MAILBOX           "/obj/secure/mailbox"
#define MAILER_DIR        "/obj/secure/mailers"
#define MAILER            MAILER_DIR "/mailer"
#define SOCKET            "/obj/secure/socket"
#define BEHAVIOUR_TREE    "/std/behaviour/behaviour_tree"

#define SHELL             "/obj/secure/shell"
#define M_ALIAS           "/obj/secure/shell/alias"
#define M_HISTORY         "/obj/secure/shell/history"
#define M_SCROLLBACK      "/obj/secure/shell/scrollback"
#define M_SHELLFUNCS      "/obj/secure/shell/shellfuncs"

/* used by 'wish';  M_GETOPT also used in CMD_D */
#define M_GETOPT          "/obj/secure/shell/getopt"
#define M_PROMPT          "/obj/secure/shell/prompt"
#define M_SHELLVARS       "/obj/secure/shell/shellvars"

// These next few are 'high level' inheritables and probably should have
// their own dir.
#define ACCOUNTANT        "/std/accountant"
#define ART_OBJECT        "/std/art_object"
#define BANDAGE           "/std/bandage"
#define BATTERY           "/std/battery"
#define BED               "/std/bed"
#define BOOK              "/std/book"
#define COINS             "/std/coins"
#define CRAFTING_STATION  "/std/crafting_station"
#define DRINK             "/std/drink"
#define ELEVATOR          "/std/elevator"
#define GEM               "/std/gem"
#define HOLE              "/std/hole"
#define INF_SUPPLY        "/std/inf_supply"
#define JUNK              "/std/junk"
#define LADDER            "/std/ladder"
#define LANTERN           "/std/lantern"
#define LOOT_CHEST        "/std/loot_chest"
#define MATERIAL          "/std/material"
#define MATERIAL_SPAWNER  "/std/material_spawner"
#define MEAT              "/std/meat"
#define MONEY             "/std/money"
#define PELT              "/std/pelt"
#define PORTAL            "/std/portal"
#define SLOWHEAL          "/std/slowheal"
#define STAIRS            "/std/stairs"
#define TAMING_COLLAR     "/std/taming_collar"
#define TORCH             "/std/torch"
#define TRANSIENT         "/std/transient"
#define VEHICLE           "/std/vehicle"

#endif /* __MUDLIB_H__ */
