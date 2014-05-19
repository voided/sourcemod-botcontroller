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

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>


IBotManager *botmanager = NULL;

CBotManager g_BotManager;


void BotManager_GameFrame( bool simulating )
{
	GBotManager().Think();
}

void CBotManager::Init()
{
	g_pSM->AddGameFrameHook( BotManager_GameFrame );

	playerhelpers->AddClientListener( this );
}

void CBotManager::Shutdown()
{
	playerhelpers->RemoveClientListener( this );

	g_pSM->RemoveGameFrameHook( BotManager_GameFrame );
}

CBot *CBotManager::CreateBot( const char *botName )
{
	Assert( botmanager );

	edict_t *pEdict = botmanager->CreateBot( botName );

	if ( !pEdict )
	{
		// server is likely full
		return NULL;
	}

	CBot *pBot = new CBot( pEdict );
	m_Bots.AddToTail( pBot );

	return pBot;
}

void CBotManager::Think()
{
	FOR_EACH_VEC( m_Bots, i )
	{
		m_Bots[ i ]->Think();
	}
}

void CBotManager::OnClientDisconnecting( int client )
{
	IGamePlayer *pPlayer = playerhelpers->GetGamePlayer( client );
	Assert( pPlayer );

	if ( pPlayer->IsFakeClient() )
	{
		edict_t *pEdict = pPlayer->GetEdict();

		if ( !pEdict )
			return; // well...

		CBot *pBot = BotOfEdict( pEdict );

		if ( pBot )
		{
			m_Bots.FindAndRemove( pBot );
			delete pBot;
		}
	}
}

CBot *CBotManager::BotOfEdict( const edict_t *pEdict )
{
	FOR_EACH_VEC( m_Bots, i )
	{
		if ( m_Bots[ i ]->GetEdict() == pEdict )
			return m_Bots[ i ];
	}

	return NULL;
}
