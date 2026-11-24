
#if defined _botcontroller_included
	#endinput
#endif

#define _botcontroller_included

/**
 * Creates a fake client and returns its client index.
 *
 * The bot receives an empty user command every game frame. SourcePawn hooks
 * may change that command to provide movement and actions.
 */
native int BotController_CreateBot(const char[] botName);

public Extension __ext_botcontroller =
{
	name = "BotController",
	file = "botcontroller.ext",

#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif

#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif

};


#if !defined REQUIRE_EXTENSIONS
public void __ext_botcontroller_SetNTVOptional()
{
	MarkNativeAsOptional("BotController_CreateBot");
}
