// Author: keytruth
// Version: 2.1 (13.11.2019)

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

#define HidePlayerDialog(%0) ShowPlayerDialog(%0,-1,DIALOG_STYLE_MSGBOX,!" ",!" ",!" ",!" ")

forward OnDialogReceived(playerid, dialogid);

static buf[32],
	   dlgnm[MAX_PLAYERS][32];

public OnGameModeInit()
{
    print("\n\n=====================================");
    print("KDLG (2.1) successfully loaded!");
    print("Author: keytruth");
    print("=====================================\n\n");
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
    CallLocalFunction(dlgnm[playerid], "ddds", playerid, response, listitem, (inputtext[0] == EOS) ? ("\1") : (inputtext));
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

stock kdlg_ShowPlayerDialog(playerid, dialog[], style, caption[], info[], button1[], button2[])
{
    #if defined OnDialogReceived
    if(!CallLocalFunction("OnDialogReceived", "id", playerid, funcidx(dialog))) return 0;
    #endif
    format(buf, sizeof buf, "dlgnm%s", dialog), format(dlgnm[playerid], 32, buf);
    return ShowPlayerDialog(playerid, funcidx(buf), style, caption, info, button1, button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog(%0,%1,%2) kdlg_ShowPlayerDialog(%0,#%1,%2)
