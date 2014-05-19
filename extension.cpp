/**
 * vim: set ts=4 :
 * =============================================================================
 * BotController Extension
 * Copyright (C) 2014 Ryan Stecker
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */



#include "extension.h"

#include "botmanager.h"
#include "bot.h"


/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

BotController g_BotController;		/**< Global singleton for extension's main interface */

SMEXT_LINK( &g_BotController );


bool BotController::SDK_OnLoad( char *error, size_t maxlength, bool late )
{
	g_pShareSys->RegisterLibrary( myself, "botcontroller" );

	extern sp_nativeinfo_t BotController_Natives[];
	g_pShareSys->AddNatives( myself, BotController_Natives );

	return true;
}

bool BotController::SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
	GET_V_IFACE_CURRENT( GetServerFactory, botmanager, IBotManager, INTERFACEVERSION_PLAYERBOTMANAGER );

	GBotManager().Init();

	return true;
}

bool BotController::SDK_OnMetamodUnload(char *error, size_t maxlength)
{
	GBotManager().Shutdown();

	return true;
}

static cell_t Native_CreateBot( IPluginContext *pContext, const cell_t *params )
{
	char *botName = NULL;
	pContext->LocalToString( params[ 1 ], &botName );

	CBot *pBot = GBotManager().CreateBot( botName );

	if ( !pBot )
	{
		return pContext->ThrowNativeError( "Unable to create bot" );
	}

	return pBot->GetIndex();
}

sp_nativeinfo_t BotController_Natives[] =
{
	{ "BotController_CreateBot", Native_CreateBot },
	{ NULL, NULL },
};
