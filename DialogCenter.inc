/*
	---------------------------------------

		Dialog Center Text
		@author: Ino
		@version: 1.0.0
		@release: 27/12/2016
		@build: 1	
		@download: github.com/Ino42O/Dialog-Center-Text

	---------------------------------------

	 	Changelog:

	 		27-12-2016:
	 			* Initial release



	 	Thanks to:
	 		[uL]Kanada42O - Consultations

	---------------------------------------
*/

#include <a_samp>


#define _INC_CENTER_DIALOG // For other includes


static const stock letters[ ] [ ] = 
{
	// Uppercase
	{ 'A' , 12},
	{ 'B' , 11}, 
	{ 'C' , 11},  
	{ 'D' , 11},  
	{ 'E' , 10},  
	{ 'F' ,  9},  
	{ 'G' , 12},  
	{ 'H' , 11},  
	{ 'I' ,  4},  
	{ 'J' ,  9},  
	{ 'K' , 12}, 
	{ 'L' ,  9}, 
	{ 'M' , 13},  
	{ 'N' , 11},  
	{ 'O' , 12},  
	{ 'P' , 10},  
	{ 'Q' , 12},  
	{ 'R' , 12},  
	{ 'S' , 10},  
	{ 'T' , 10},  
	{ 'U' , 11},  
	{ 'V' , 11},  
	{ 'W' , 15},  
 	{ 'X' , 12},  
	{ 'Y' , 12},  
	{ 'Z' , 10}, 

	// Lowercase
	{ 'a' ,  9}, 
	{ 'b' ,  9}, 
	{ 'c' ,  8}, 
	{ 'd' ,  9}, 
	{ 'e' ,  9}, 
	{ 'f' ,  8}, 
	{ 'g' ,  9}, 
	{ 'h' ,  9}, 
	{ 'i' ,  4}, 
	{ 'j' ,  5}, 
	{ 'k' ,  9}, 
	{ 'l' ,  4}, 
	{ 'm' , 12}, 
	{ 'n' ,  9}, 
	{ 'o' ,  9}, 
	{ 'p' ,  9}, 
	{ 'q' ,  9}, 
	{ 'r' ,  7}, 
	{ 's' ,  8}, 
	{ 't' ,  7}, 
	{ 'u' ,  9}, 
	{ 'v' , 11}, 
	{ 'w' , 13}, 
	{ 'x' , 11}, 
	{ 'y' ,  9}, 
	{ 'z' ,  8},

	// Numbers
	{ '1' ,  7},
	{ '2' ,  9},
	{ '3' ,  9},
	{ '4' ,  9},
	{ '5' ,  9},
	{ '6' ,  9},
	{ '7' ,  9},
	{ '8' ,  9},
	{ '9' ,  9},
	{ '0' ,  9},

	// Special characters
	{ '!' ,  4},
	{ '"' ,  8}, 
	{ '$' ,  9}, 
	{ '%' , 14}, 
	{ '&' , 12}, 
	{ '/' ,  6}, 
	{ '(' ,  6}, 
	{ ')' ,  6}, 
	{ '=' , 10}, 
	{ '?' , 10}, 
	{ '+' , 10}, 
	{ '\'',  4}, 
	{ '[' ,  6}, 
	{ ']' ,  6}, 
	{ '-' ,  6}, 
	{ '.' ,  4}, 
	{ ',' ,  4},
	{ '|' ,  4},
	{ '_' ,  6},
	{ ' ' ,  4}
};


#define MAX_LINES 	(100)
#define MAX_CENTER 	(6)

static centerBuffer[4096];
static bool:use = false;

stock dcenter_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	new defaultSize;

	switch (style)
	{
		case DIALOG_STYLE_MSGBOX: 			{ defaultSize = 200; }
		case DIALOG_STYLE_INPUT: 			{ defaultSize = 200; }
		case DIALOG_STYLE_LIST: 			{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); } // Still in progress
		case DIALOG_STYLE_PASSWORD: 		{ defaultSize = 200; }
		case DIALOG_STYLE_TABLIST: 			{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); } // Still in progress
		case DIALOG_STYLE_TABLIST_HEADERS: 	{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); } // Still in progress
		default: 							{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); }
	}


	if (use) return dcenter_ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);

	use = true;

	centerBuffer[0] = '\0';

	new 
			 lineInfo 	 [MAX_LINES],
			 lineSize 	 [MAX_LINES],
			 lineSpace	 [MAX_LINES],
		bool:lineCenter  [MAX_LINES],
			 biggest,
			 biggestID,
			 line = 0,

			 // Find centers
			 cpos = -2,

			 // Count lines
			 pos = -2,
			 lines = 0
	;	


	while (-1 != ( pos = strfind(info, "\n", false, pos + 2) ) ) lines++;

	if (lines != 0) 
		lines++;

	if (lines > 0)
	{
		// Find positions for new line
		for (new i = 0, c = 0; i < strlen(info); i++)
		{
			if (info[i] == '\n')
				lineInfo[c++] = i;

			if (i == strlen(info) - 1) lineInfo[c] = strlen(info);
		}

		for (new i = 0; i < lines; i++)
		{
			if (i == 0)	lineSize[i] = lineInfo[i];
			else if (0 < i < lines) lineSize[i] = (lineInfo[i] - lineInfo[i - 1] - 1);
		}
	}


	new tmp[3];
	if (lines > 0)
	{
		for (new i = 0; i < lines; i++)
		{
			
			if (i == 0)
			{
				strmid(tmp, info, 0, 3);

				if (strfind(tmp, "\\c", false) != -1)
					lineCenter[i] = true;
			}
			else 
			{
				strmid(tmp, info, (lineInfo[i - 1] + 1), (lineInfo[i - 1] + 4));

				if (strfind(tmp, "\\c", false) != -1)
					lineCenter[i] = true;
			}
		}
	}
	else
	{
		strmid(tmp, info, 0, 3);

		if (strfind(tmp, "\\c", false) != -1)
			lineCenter[0] = true;
	}


	format (centerBuffer, sizeof(centerBuffer), "%s", info);


	// Find biggest line
	if (lines > 0)
	{
		for (new i = 0; i < lines; i++)
		{
			new t1 = ( (lines > 0) ? ( (i == 0) ? (0) : (lineInfo[i - 1] + 1) ) : (0) );
			new t2 = ( (lines > 0) ? (lineInfo[i]) : (strlen(info)) );
			for (new u = t1; u < t2; u++)
			{
				if (centerBuffer[u] == '{')
				{
					u += 7;
					continue;
				}

				for (new j = 0; j < sizeof(letters); j++)
				{
					if (centerBuffer[u] == letters[j][0])
					{
						lineSpace[i] += letters[j][1];
						break;
					}
				}
			}
		}

		biggest = 0;
		for (new i = 0; i < lines; i++)
		{
			if (lineSpace[i] > biggest)
			{
				biggest = lineSpace[i];
				biggestID = i;
			}
		}
	}


	generate_line:

	if (!lineCenter[line])
		goto generate_fail;

	new space = 0;


	for (new i = ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) ); i < ( (lines > 0) ? (lineInfo[line]) : (strlen(info)) ); i++)
	{
		if (centerBuffer[i] == '{')
		{
			i += 7;
			continue;
		}

		for (new j = 0; j < sizeof(letters); j++)
		{
			if (centerBuffer[i] == letters[j][0])
			{
				space += letters[j][1];
				break;
			}
		}
	}

	if (lines == 0)
	{ 
		if (space < defaultSize)
		{
			new loop = ( ( (defaultSize - space) / 4) / 2) + 1;
			new start = ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) );

			for (new i = start; i < loop + start; i++)
			{
				strins(centerBuffer, " ", i);
				space += 4;

				for (new j = 0; j < lines; j++)
					lineInfo[j]++;
			}
		}
		else
		{
			strins(centerBuffer, "  ", ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) ));

			for (new j = 0; j < lines; j++)
				lineInfo[j] += 2;
		}
	}
	else if (lines > 0)
	{
		new loop = ( ( ( ( (biggest < defaultSize) ? (defaultSize) : (biggest) ) - space) / 4) / 2) - ( ( (biggest < defaultSize) ? (-1) : ( (space < defaultSize) ? ( (lineCenter[biggestID]) ? (4) : (2) ) : (1) ) ) );
		new start = ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) );

		for (new i = start; i < loop + start; i++)
		{
			strins(centerBuffer, " ", i);
			space += 4;

			for (new j = 0; j < lines; j++)
				lineInfo[j]++;
		}
	}


	generate_fail:
	if (lines > 0)
	{
		if (line++ < lines - 1)	
			goto generate_line;
	}


	while (-1 != ( cpos = strfind(centerBuffer, "\\c", false, cpos + 2) ) )
		strdel(centerBuffer, cpos, cpos + 2);

	use = false;
	return ShowPlayerDialog(playerid, dialogid, style, caption, centerBuffer, button1, button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog dcenter_ShowPlayerDialog