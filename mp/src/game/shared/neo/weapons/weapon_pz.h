#ifndef NEO_WEAPON_PZ_H
#define NEO_WEAPON_PZ_H
#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"
#include "npcevent.h"
#include "in_buttons.h"

#ifdef CLIENT_DLL
#include "c_neo_player.h"
#else
#include "neo_player.h"
#endif

#include "weapon_neobasecombatweapon.h"

#define	PZ_FASTEST_REFIRE_TIME 0.085f
#define PZ_FASTEST_DRY_REFIRE_TIME	0.2f

#define	PZ_ACCURACY_SHOT_PENALTY_TIME		0.2f
#define	PZ_ACCURACY_MAXIMUM_PENALTY_TIME	0.5f	// Maximum penalty to deal out

#ifdef CLIENT_DLL
#define CWeaponPZ C_WeaponPZ
#endif

class CWeaponPZ : public CNEOBaseCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponPZ, CNEOBaseCombatWeapon);

	CWeaponPZ();

	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	void	ItemPostFrame(void);
	void	ItemPreFrame(void);
	void	ItemBusyFrame(void);
	void	PrimaryAttack(void);
	void	AddViewKick(void);
	void	DryFire(void);

	virtual void Spawn(void);
	virtual bool Deploy(void);

	virtual int GetNeoWepBits(void) const { return NEO_WEP_PZ; }

	void	UpdatePenaltyTime(void);

	Activity	GetPrimaryAttackActivity(void);

	virtual bool Reload(void);

	virtual const Vector& GetBulletSpread(void)
	{
		static Vector cone;

		float ramp = RemapValClamped(m_flAccuracyPenalty,
			0.0f,
			PZ_ACCURACY_MAXIMUM_PENALTY_TIME,
			0.0f,
			1.0f);

		// We lerp from very accurate to inaccurate over time
		VectorLerp(VECTOR_CONE_1DEGREES, VECTOR_CONE_6DEGREES, ramp, cone);

		return cone;
	}

	virtual float GetFireRate(void);

#ifdef GAME_DLL
	DECLARE_ACTTABLE();
#endif

private:
	CNetworkVar(float, m_flSoonestAttack);
	CNetworkVar(float, m_flLastAttackTime);
	CNetworkVar(float, m_flAccuracyPenalty);

	CNetworkVar(int, m_nNumShotsFired);

private:
	CWeaponPZ(const CWeaponPZ &other);
};

#endif // NEO_WEAPON_PZ_H