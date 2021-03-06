SendMessageToChannel(playerID, channel[], message[], targetPlayerID = INVALID_PLAYER_ID)
{
	new string[256];
	new targetUserID;
	if (targetPlayerID != INVALID_PLAYER_ID)
	{
		targetUserID = PVar:targetPlayerID[USERID];
	}
	MySQLQuery("INSERT INTO `chatlog` (`userId`, `targetUserId`, `channel`, `time`, `text`) VALUES('%d', '%d', '%s', NOW(), '%s')", PVar:playerID[USERID], targetUserID, channel, MySQLEscapeString(message));
	if (IsStr(channel, "ADMINS"))
	{
		Format:string("[%s@Admins] %s", GetPlayerNameEx(playerID), message);
		PlayerLoop(loopPlayerID)
		{
			if (permissions[loopPlayerID][PERMISSION_ADMIN] || loopPlayerID == playerID)
			{
				SendClientMessage(loopPlayerID, COLOR_CHAT_ADMINS, string);
			}
		}
		return true;
	}
	if (IsStr(channel, "ALL"))
	{
		PlayerLoop(loopPlayerID)
		{
			Format:string("[%s@%s] %s", GetPlayerNameEx(playerID), LanguageString(loopPlayerID, StringID:310("All")), message);
			SendClientMessage(loopPlayerID, COLOR_CHAT_ALL, string);
		}
		Format:string("[%s] %s", GetPlayerNameEx(playerID), message);
		return true;
	}
	if (IsStr(channel, "INRANGE"))
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		GetPlayerPos(playerID, posX, posY, posZ);
		Format:string("[%s] %s", GetPlayerNameEx(playerID), message);
		PlayerLoop(loopPlayerID)
		{
			new Float:distance = GetPlayerDistanceFromPoint(loopPlayerID, posX, posY, posZ);
			if (distance <= CHAT_MAXDISTANCE)
			{
				SendClientMessage(loopPlayerID, COLOR_CHAT_INRANGE, string);
			}
		}
		return true;
	}
	if (IsStr(channel, "JOB"))
	{
		Format:string("[%s@Job] %s", GetPlayerNameEx(playerID), message);
		PlayerLoop(loopPlayerID)
		{
			if (PVar:playerID[JOBID] == PVar:loopPlayerID[JOBID])
			{
				SendClientMessage(loopPlayerID, COLOR_CHAT_JOB, string);
			}
		}
		return true;
	}
	if (IsStr(channel, "PLAYER"))
	{
		if (targetPlayerID == INVALID_PLAYER_ID)
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:147("Player not found!"));
			return false;
		}
		Format:string("[%s -> %s] %s", GetPlayerNameEx(playerID), GetPlayerNameEx(targetPlayerID), message);
		SendClientMessage(targetPlayerID, COLOR_CHAT_PLAYER, string);
		SendClientMessage(playerID, COLOR_CHAT_PLAYER, string);
		return true;
	}
	return false;
}