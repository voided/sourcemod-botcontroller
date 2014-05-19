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

#include "botmanager.h"

#include "bot.h"


IBotManager *botmanager = NULL;


CBot *CBotManager::CreateBot( const char *botName )
{
	Assert( botmanager );

	edict_t *pEdict = botmanager->CreateBot( botName );

	if ( !pEdict )
	{
		Msg( "Unable to CreateBot\n" );
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
