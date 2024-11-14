//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
// Authors: 
// Adam Tomaszewski

#include "cbase.h"
#include "../bot.h"

#ifdef INSOURCE_DLL
#include "in_utils.h"
#else
#include "../in_utils.h"
#endif

#include "in_buttons.h"
#include "team.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//================================================================================
//================================================================================
SET_SCHEDULE_TASKS( CDefendCapturePointSchedule )
{
    bool carefulApproach = GetDecision()->ShouldMustBeCareful();

    ADD_TASK( BTASK_SET_FAIL_SCHEDULE, SCHEDULE_COVER );
    ADD_TASK( BTASK_DEFEND_GHOST_CAP, NULL );
}


SET_SCHEDULE_INTERRUPTS( CDefendCapturePointSchedule )
{
    ADD_INTERRUPT( BCOND_HELPLESS );
    ADD_INTERRUPT( BCOND_DEJECTED );
    ADD_INTERRUPT( BCOND_NEW_ENEMY );
    ADD_INTERRUPT( BCOND_MOBBED_BY_ENEMIES );
    ADD_INTERRUPT( BCOND_GOAL_UNREACHABLE );
}

//================================================================================
//================================================================================
float CDefendCapturePointSchedule::GetDesire() const
{
    if (!GetLocomotion())
    { // can't move
        return BOT_DESIRE_NONE;
    }

    CTeam *myTeam = GetHost()->GetTeam();
    CTeam* otherTeam = GetGlobalTeam(TheGameRules->GetOpposingTeam(myTeam->m_iTeamNum));
    if (myTeam && otherTeam && otherTeam->GetAliveMembers() <= myTeam->GetAliveMembers())
    { // take ghost / hunt vip instead
        return BOT_DESIRE_NONE;
    }

    return BOT_DESIRE_HIGH;
}