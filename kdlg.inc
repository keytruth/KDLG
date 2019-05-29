// Author: keytruth
// Version: 1.0 (29.05.2019)

#if defined _kdlg_included
	#endinput
#endif
#define _kdlg_included

#if !defined _samp_included
    #error Not connected include <a_samp>!
#endif

#define DIALOG:%0(%1,%2,%3,%4) forward dlgnm%0(%1,%2,%3,%4); public dlgnm%0(%1,%2,%3,%4)
#define DLG:%0(%1,%2,%3,%4) 													DIALOG:%0(%1,%2,%3,%4)
#define dialog(%0,%1,%2,%3,%4) 													DIALOG:%0(%1,%2,%3,%4)
#define dlg(%0,%1,%2,%3,%4) 													DIALOG:%0(%1,%2,%3,%4)

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

forward OnDialogReceived(playerid, dialogid);
forward OnDialogPerformed(playerid, dialogid, listitem, inputtext);

new buffer[15];

public OnGameModeInit()
{
    print("\n\n=====================================");
    print("KDLG (1.0) successfully loaded!");
    print("Author: keytruth");
    print("=====================================\n\n");
    new kdlg = 1;
    #if defined kdlg_OnGameModeInit
	kdlg = kdlg_OnGameModeInit();
    #endif
    #pragma unused kdlg
    return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit kdlg_OnGameModeInit
#if defined kdlg_OnGameModeInit
	forward kdlg_OnGameModeInit();
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    #if defined OnDialogPerformed
    CallRemoteFunction("OnDialogPerformed", "id", playerid,  dialogid, listitem, inputtext);
    #endif
    format(buffer, sizeof buffer, "dlgnm%d", dialogid); 
    if(isnull(inputtext)) CallLocalFunction(buffer, "ddd", playerid, response, listitem);
    else CallLocalFunction(buffer, "ddds", playerid, response, listitem, inputtext);
    #if defined kdlg_OnDialogResponse
	return kdlg_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse kdlg_OnDialogResponse
#if defined kdlg_OnDialogResponse
	forward kdlg_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

stock kdlg_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
    #if defined OnDialogReceived
    if(!CallRemoteFunction("OnDialogReceived", "id", playerid, dialogid)) return 0;
    #endif
    ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
    /*#if defined OnDialogPerformed
    CallRemoteFunction("OnDialogPerformed", "id", playerid,  dialogid, listitem, inputtext);
    #endif*/
    return 1;
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog kdlg_ShowPlayerDialog