ShowDialog:NaviTarget_PropertyList(playerID, searchString[])
{
	new list[2048];
	MySQLQuery("SELECT `name` FROM `properties` WHERE `name` LIKE '%%%s%%'", MySQLEscapeString(searchString));
	mysql_store_result();
	while (FetchMySQLRow())
	{
		AddLine(list, GetMySQLField("name"));
	}
	mysql_free_result();
	CreateDialog(playerID, "NaviTarget_PropertyList", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:419("Select house")), list, "OK", LanguageString(playerID, StringID:171("Back")));
}

DialogResponse:NaviTarget_PropertyList(playerID, response, listItem, inputText[])
{
	if (response)
	{
		MySQLQuery("SELECT * FROM `properties` LEFT JOIN `pickups` ON `properties`.`pickupId` = `pickups`.`id` WHERE `name` = '%s'", MySQLEscapeString(inputText));
		mysql_store_result();
		if (mysql_num_rows())
		{
			if (CalculateRoute(playerID, floatstr(GetMySQLField("posX")), floatstr(GetMySQLField("posY")), floatstr(GetMySQLField("posZ"))))
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:414("Calculating route"));
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:415("No GPS!"));
			}
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:343("No target found!"));
		}
		mysql_free_result();
	}
	else
	{
		ShowDialog:NaviTarget_PropertyName(playerID);
	}
}