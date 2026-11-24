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

#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>


IBotManager *botmanager = nullptr;

CBotManager g_BotManager;


void BotManager_GameFrame(bool)
{
	GBotManager().Think();
}

void CBotManager::Init()
{
	g_pSM->AddGameFrameHook(BotManager_GameFrame);
	playerhelpers->AddClientListener(this);
}

void CBotManager::Shutdown()
{
	playerhelpers->RemoveClientListener(this);
	g_pSM->RemoveGameFrameHook(BotManager_GameFrame);
	bots_.clear();
}

CBot *CBotManager::CreateBot( const char *botName )
{
	if (!botmanager)
		return nullptr;

	edict_t *pEdict = botmanager->CreateBot(botName);

	if (!pEdict)
	{
		return nullptr;
	}

	auto bot = std::make_unique<CBot>(pEdict);
	CBot *result = bot.get();
	bots_.push_back(std::move(bot));
	return result;
}

void CBotManager::Think()
{
	// RunPlayerMove can invoke plugin callbacks that modify the bot collection.
	// Keep the index-based iteration used by the original manager.
	for (std::size_t i = 0; i < bots_.size(); ++i)
		bots_[i]->Think();
}

void CBotManager::OnClientDisconnecting( int client )
{
	IGamePlayer *pPlayer = playerhelpers->GetGamePlayer(client);

	if (!pPlayer || !pPlayer->IsFakeClient())
		return;

	edict_t *pEdict = pPlayer->GetEdict();
	if (!pEdict)
		return;

	auto bot = std::find_if(bots_.begin(), bots_.end(), [pEdict](const auto &candidate) {
		return candidate->GetEdict() == pEdict;
	});
	if (bot != bots_.end())
	{
		bots_.erase(bot);
	}
}
