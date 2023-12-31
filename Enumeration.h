#ifndef Enumeration_H
#define Enumeration_H

// Source

namespace AssaultCube
{
	enum
	{
		SA_KICK = 0,
		SA_BAN,
		SA_REMBANS,
		SA_MASTERMODE,
		SA_AUTOTEAM,
		SA_FORCETEAM,
		SA_GIVEADMIN,
		SA_MAP,
		SA_RECORDDEMO,
		SA_STOPDEMO,
		SA_CLEARDEMOS,
		SA_SERVERDESC,
		SA_SHUFFLETEAMS,
		SA_NUM
	};
	enum
	{
		VOTE_NEUTRAL = 0,
		VOTE_YES,
		VOTE_NO,
		VOTE_NUM
	};
	enum
	{
		FA_PICKUP = 0,
		FA_STEAL,
		FA_DROP,
		FA_LOST,
		FA_RETURN,
		FA_SCORE,
		FA_NUM,
		FA_RESET
	};
	enum
	{
		FM_PICKUP = 0,
		FM_DROP,
		FM_LOST,
		FM_RETURN,
		FM_SCORE,
		FM_KTFSCORE,
		FM_SCOREFAIL,
		FM_RESET,
		FM_NUM
	};
	enum
	{
		GUN_KNIFE = 0,
		GUN_PISTOL,
		GUN_CARBINE,
		GUN_SHOTGUN,
		GUN_SUBGUN,
		GUN_SNIPER,
		GUN_ASSAULT,
		GUN_CPISTOL,
		GUN_GRENADE,
		GUN_AKIMBO,
		NUMGUNS
	};
	enum
	{
		CS_ALIVE = 0,
		CS_DEAD,
		CS_SPAWNING,
		CS_LAGGED,
		CS_EDITING,
		CS_SPECTATE
	};
	enum
	{
		CR_DEFAULT = 0,
		CR_ADMIN
	};
	enum
	{
		TEAM_CLA = 0,
		TEAM_RVSF,
		TEAM_CLA_SPECT,
		TEAM_RVSF_SPECT,
		TEAM_SPECT,
		TEAM_NUM,
		TEAM_ANYACTIVE
	};
	enum
	{
		SM_NONE = 0,
		SM_DEATHCAM,
		SM_FOLLOW1ST,
		SM_FOLLOW3RD,
		SM_FOLLOW3RD_TRANSPARENT,
		SM_FLY,
		SM_OVERVIEW,
		SM_NUM
	};
	enum
	{
		FPCN_VOID = -4,
		FPCN_DEATHCAM = -2,
		FPCN_FLY = -2,
		FPCN_OVERVIEW = -1
	};
	enum
	{
		BT_NONE,
		BT_NADE,
		BT_GIB
	};

	enum
	{
		GMODE_DEMO = -1,
		GMODE_TEAMDEATHMATCH = 0,
		GMODE_BOTTEAMSURVIVOR,
		GMODE_TEAMSURVIVOR,
		GMODE_CTF,
		GMODE_BOTTEAMDEATHMATCH,
		GMODE_HUNTTHEFLAG,
		GMODE_TEAMKEEPTHEFLAG,
		GMODE_TEAMPF,
		GMODE_TEAMLSS,

		GMODE_COOPEDIT,
		GMODE_DEATHMATCH,
		GMODE_SURVIVOR,

		GMODE_PISTOLFRENZY,

		GMODE_BOTDEATHMATCH,
		GMODE_LASTSWISSSTANDING,
		GMODE_ONESHOTONEKILL,
		GMODE_TEAMONESHOTONEKILL,
		GMODE_BOTONESHOTONEKILL,

		GMODE_KEEPTHEFLAG,

		GMODE_BOTPISTOLFRENZY,
		GMODE_BOTLSS,

		GMODE_BOTTEAMONESHOTONKILL,
		GMODE_NUM

	};

	enum // static entity types
	{

		LIGHT, // lightsource, attr1 = radius, attr2 = intensity

		I_AMMO,
		I_GRENADE,
		I_HEALTH,
		I_HELMET,
		I_ARMOUR,
		I_AKIMBO,

		LADDER,
		CTF_FLAG, // attr1 = angle, attr2 = red/blue
		SOUND,
		CLIP,
		PLCLIP,

	};
}

#endif