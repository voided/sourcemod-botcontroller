
#if defined __botcontroller_included
	#endinput
#endif

#define __botcontroller_included


native BotController_CreateBot( const String:botName[] );


public Extension:__ext_botcontroller =
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
public __ext_botcontroller_SetNTVOptional()
{
	MarkNativeAsOptional( "BotController_CreateBot" );
}
