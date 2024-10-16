
#include "../main.h"
#include "util.h"
#include "keystuff.h"
#include "task.h"

extern CGame *pGame;

extern BYTE	*pbyteCurrentPlayer;

//-----------------------------------------------------------
// Used for instancing the local player.

CPlayerPed::CPlayerPed()
{
	m_dwGTAId = 1; // 0x001
	m_pPed = GamePool_FindPlayerPed();
	m_pEntity = (ENTITY_TYPE *)GamePool_FindPlayerPed();

	m_bytePlayerNumber = 0;
	SetPlayerPedPtrRecord(m_bytePlayerNumber,(DWORD)m_pPed);
	ScriptCommand(&set_actor_weapon_droppable,m_dwGTAId,1);
	ScriptCommand(&set_actor_can_be_decapitated,m_dwGTAId,0);

	field_2A8 = 1;
	field_2AC = 1;
	m_dwArrow = 0;
	field_2B9 = 0;
	field_2F2 = 0;
	field_2D2 = 0;
	field_2DE = 0;
	field_2E2 = 0;
	field_48 = 0;
	m_bGoggleState = FALSE;
	field_2C1 = 0;
	field_2C5 = 0;
	field_2C9 = 0;
	field_2F6 = 0;
	field_2F7 = 0;
	field_2F8 = 0;

	int x=0;
	while(x!=10) {
		field_4C[x] = 0;
		field_27C[x] = 0;
		memset(&field_74[x], 0, sizeof(struc_97));
		x++;
	}

	field_2F9 = 0;
}

//-----------------------------------------------------------



//-----------------------------------------------------------
// If the game has internally destroyed the ped
// during this frame, the ped pointer should become 0

void CPlayerPed::ResetPointers()
{
	m_pPed = GamePool_Ped_GetAt(m_dwGTAId);
	m_pEntity = (ENTITY_TYPE *)m_pPed;
}

//-----------------------------------------------------------

void CPlayerPed::SetInitialState()
{
	DWORD dwPedPtr = (DWORD)m_pPed;

	_asm push 0
	_asm mov ecx, dwPedPtr
	_asm mov edx, 0x60CD20 ; internal_CPlayerPed_SetInitialState
	_asm call edx
}

//-----------------------------------------------------------

BYTE CPlayerPed::GetSpecialKey()
{
	GTA_CONTROLSET *pInternalKeys = GameGetInternalKeys();

	if(pInternalKeys->wKeys1[11]) // yes
		return 1;
	else if(pInternalKeys->wKeys1[10]) // no
		return 2;
	else if(pInternalKeys->wKeys1[9]) // honk
		return 3;

	return 0;
}


//-----------------------------------------------------------

CAMERA_AIM * CPlayerPed::GetCurrentAim()
{
	return GameGetInternalAim();
}

//-----------------------------------------------------------

void CPlayerPed::SetCurrentAim(CAMERA_AIM *pAim)
{
	GameStoreRemotePlayerAim(m_bytePlayerNumber, pAim);
}

//-----------------------------------------------------------

BYTE CPlayerPed::GetCurrentWeapon()
{
	if(!m_pPed) return 0;
	if(GamePool_Ped_GetAt(m_dwGTAId) == 0) return 0;

	DWORD dwRetVal;
	ScriptCommand(&get_actor_armed_weapon,m_dwGTAId,&dwRetVal);
	return (BYTE)dwRetVal;
}

//-----------------------------------------------------------

int CPlayerPed::GetCurrentVehicleID()
{
	if(!m_pPed) return 0;

	VEHICLE_TYPE *pVehicle = (VEHICLE_TYPE *)m_pPed->pVehicle;
	return GamePool_Vehicle_GetIndex(pVehicle);
}

//-----------------------------------------------------------

void CPlayerPed::HideMarker()
{
	if (m_dwArrow) ScriptCommand(&disable_marker, m_dwArrow);
	m_dwArrow = NULL; // Just make sure
}

//-----------------------------------------------------------

BOOL CPlayerPed::IsOnScreen()
{
	if(m_pPed) return GameIsEntityOnScreen((DWORD *)m_pPed);
	return FALSE;
}

//-----------------------------------------------------------

void CPlayerPed::SetImmunities(BOOL bBullet, BOOL bFire, BOOL bExplosion, BOOL bDamage, BOOL bUnknown)
{
	if(!m_pPed) return;
	if(GamePool_Ped_GetAt(m_dwGTAId) == 0) return;

	ScriptCommand(&set_actor_immunities, m_dwGTAId, bBullet, bFire, bExplosion, bDamage, bUnknown);
}

//-----------------------------------------------------------

float CPlayerPed::GetHealth()
{
	if(!m_pPed) return 0.0f;
	return m_pPed->fHealth;
}

//-----------------------------------------------------------

void CPlayerPed::SetHealth(float fHealth)
{
	if(!m_pPed) return;
	m_pPed->fHealth = fHealth;
}

//-----------------------------------------------------------

float CPlayerPed::GetArmour()
{
	if(!m_pPed) return 0.0f;
	return m_pPed->fArmour;
}

//-----------------------------------------------------------

void CPlayerPed::SetArmour(float fArmour)
{
	if(!m_pPed) return;
	m_pPed->fArmour = fArmour;
}

//-----------------------------------------------------------

DWORD CPlayerPed::GetStateFlags()
{
	if(!m_pPed) return 0;
	return m_pPed->dwStateFlags;
}

//-----------------------------------------------------------

void CPlayerPed::SetStateFlags(DWORD dwState)
{
	if(!m_pPed) return;
	m_pPed->dwStateFlags = dwState;
}

//-----------------------------------------------------------

BOOL CPlayerPed::IsDead()
{
	if(!m_pPed) return TRUE;
	if(m_pPed->fHealth > 0.0f) return FALSE;
	return TRUE;
}

//-----------------------------------------------------------

BYTE CPlayerPed::GetActionTrigger()
{
	return (BYTE)m_pPed->dwAction;
}

//-----------------------------------------------------------

void CPlayerPed::SetActionTrigger(BYTE byteTrigger)
{
	if(!m_pPed) return;

	m_pPed->dwAction = byteTrigger;
}

//-----------------------------------------------------------

BOOL CPlayerPed::IsInVehicle()
{
	if(!m_pPed) return FALSE;

	if(IN_VEHICLE(m_pPed)) {
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------

float CPlayerPed::GetTargetRotation()
{
	if(!m_pPed) return 0.0f;
	if(GamePool_Ped_GetAt(m_dwGTAId) == 0) return 0.0f;

	MATRIX4X4 mat;
	GetMatrix(&mat);

	float fZAngle = atan2(-mat.up.X, mat.up.Y) * 180.0f / PI;
	// Bound it to [0, 360)
	if ( fZAngle < 0.0f )
		fZAngle += 360.0f;
	else if ( fZAngle >= 360.0f )
		fZAngle -= 360.0f;
	return fZAngle;
}

//-----------------------------------------------------------

void CPlayerPed::SetTargetRotation(float fRotation)
{
	if(!m_pPed) return;
	if(!GamePool_Ped_GetAt(m_dwGTAId)) return;

	m_pPed->fRotation2 = DegToRad(fRotation);
	m_pPed->fRotation1 = DegToRad(fRotation);
}

//-----------------------------------------------------------

void CPlayerPed::ForceTargetRotation(float fRotation)
{
	if(!m_pPed) return;
	if(!GamePool_Ped_GetAt(m_dwGTAId)) return;

	m_pPed->fRotation1 = DegToRad(fRotation);
	m_pPed->fRotation2 = DegToRad(fRotation);

	ScriptCommand(&set_actor_z_angle,m_dwGTAId,fRotation);   
}

//-----------------------------------------------------------

BOOL CPlayerPed::IsAPassenger()
{
	if( m_pPed->pVehicle && IN_VEHICLE(m_pPed) )
	{
		VEHICLE_TYPE * pVehicle = (VEHICLE_TYPE *)m_pPed->pVehicle;

		if( pVehicle->pDriver != m_pPed || 
			pVehicle->entity.nModelIndex == TRAIN_PASSENGER ||
			pVehicle->entity.nModelIndex == TRAIN_FREIGHT ) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	return FALSE;
}

//-----------------------------------------------------------

VEHICLE_TYPE * CPlayerPed::GetGtaVehicle()
{
	return (VEHICLE_TYPE *)m_pPed->pVehicle;
}

//-----------------------------------------------------------	

void CPlayerPed::GiveWeapon(int iWeaponID, int iAmmo)
{
	if(!m_pPed) return;
	if(!GamePool_Ped_GetAt(m_dwGTAId)) return;

	int iModelID = 0;
	iModelID = GameGetWeaponModelIDFromWeaponID(iWeaponID);

	if(iModelID == -1) return;

	if(!pGame->IsModelLoaded(iModelID)) {
		pGame->RequestModel(iModelID);
		pGame->LoadRequestedModels();
		while(!pGame->IsModelLoaded(iModelID)) Sleep(1);
	}

	*pbyteCurrentPlayer = m_bytePlayerNumber;

	GameStoreLocalPlayerWeaponSkills();
	GameSetRemotePlayerWeaponSkills(m_bytePlayerNumber);

	DWORD dwPedPtr = (DWORD)m_pPed;

	_asm mov ecx, dwPedPtr
	_asm push 1
	_asm push iAmmo
	_asm push iWeaponID
	_asm mov edx, 0x5E6080
	_asm call edx

	GameSetLocalPlayerWeaponSkills();

	SetArmedWeapon(iWeaponID, false);

	*pbyteCurrentPlayer = 0;
}

//-----------------------------------------------------------

void CPlayerPed::ClearAllWeapons()
{
	DWORD dwPedPtr = (DWORD)m_pPed;

	*pbyteCurrentPlayer = m_bytePlayerNumber;

	if(dwPedPtr) {
		_asm mov ecx, dwPedPtr
		_asm mov eax, 0x5E6320
		_asm call eax
	}

	*pbyteCurrentPlayer = 0;
}

//-----------------------------------------------------------

void CPlayerPed::SetArmedWeapon(int iWeaponType, bool bUnk)
{
	if(!m_pPed) return;
	if(!GamePool_Ped_GetAt(m_dwGTAId)) return;

	*pbyteCurrentPlayer = m_bytePlayerNumber;

	GameStoreLocalPlayerWeaponSkills();
	GameSetRemotePlayerWeaponSkills(m_bytePlayerNumber);

	if((!m_pPed || !IN_VEHICLE(m_pPed)) && !bUnk)
		ScriptCommand(&set_actor_armed_weapon,m_dwGTAId,iWeaponType);
	else
	{
		DWORD dwPedPtr = (DWORD)m_pPed;
		if(dwPedPtr) {
			_asm mov ecx, dwPedPtr
			_asm push iWeaponType
			_asm mov edx, 0x5E6280
			_asm call edx
		}
	}

	GameSetLocalPlayerWeaponSkills();

	*pbyteCurrentPlayer = 0;
}

//-----------------------------------------------------------

void CPlayerPed::RemoveWeaponWhenEnteringVehicle()
{
	DWORD dwPedPtr = (DWORD)m_pPed;

	if(dwPedPtr) {
		_asm mov ecx, dwPedPtr
		_asm push 0
		_asm mov edx, 0x5E6370
		_asm call edx
	}
}

//-----------------------------------------------------------

WEAPON_SLOT_TYPE * CPlayerPed::GetCurrentWeaponSlot()
{
	if(m_pPed) {
		return &m_pPed->WeaponSlots[m_pPed->byteCurWeaponSlot];
	}
	return NULL;
}

//-----------------------------------------------------------

BOOL CPlayerPed::HasAmmoForCurrentWeapon()
{
	if(m_pPed) {
		WEAPON_SLOT_TYPE * WeaponSlot = GetCurrentWeaponSlot();

		if(!WeaponSlot) return TRUE;

		// Melee types always have ammo.
		if( WeaponSlot->dwType <= WEAPON_CANE ||
			WeaponSlot->dwType == WEAPON_PARACHUTE ) return TRUE;

		if(!WeaponSlot->dwAmmo) return FALSE;
	}
	return TRUE;
}
//-----------------------------------------------------------

float CPlayerPed::GetDistanceFromVehicle(CVehicle *pVehicle)
{
	MATRIX4X4	matFromPlayer;
	MATRIX4X4	matThis;
	float		fSX,fSY,fSZ;

	GetMatrix(&matThis);
	pVehicle->GetMatrix(&matFromPlayer);

	fSX = (matThis.pos.X - matFromPlayer.pos.X) * (matThis.pos.X - matFromPlayer.pos.X);
	fSY = (matThis.pos.Y - matFromPlayer.pos.Y) * (matThis.pos.Y - matFromPlayer.pos.Y);
	fSZ = (matThis.pos.Z - matFromPlayer.pos.Z) * (matThis.pos.Z - matFromPlayer.pos.Z);

	return (float)sqrt(fSX + fSY + fSZ);
}

//-----------------------------------------------------------

WORD CPlayerPed::GetAmmo()
{
	if(m_pPed) {
		WEAPON_SLOT_TYPE * WeaponSlot = GetCurrentWeaponSlot();

		if(!WeaponSlot) return -1;
		
		// Melee types always have ammo.
		if( WeaponSlot->dwType <= WEAPON_CANE ||
			WeaponSlot->dwType == WEAPON_PARACHUTE ) return -1;

		return (WORD)WeaponSlot->dwAmmo;
	}
	return 0;
}

//-----------------------------------------------------------

WEAPON_SLOT_TYPE * CPlayerPed::FindWeaponSlot(DWORD dwWeapon)
{
	if (m_pPed)
	{
		BYTE i;
		for (i = 0; i < 13; i++)
		{
			if (m_pPed->WeaponSlots[i].dwType == dwWeapon) return &m_pPed->WeaponSlots[i];
		}
	}
	return NULL;
}

//-----------------------------------------------------------

void CPlayerPed::SetAnimationSet(PCHAR szAnim)
{
	if(m_pPed) {
		ScriptCommand(&set_actor_animation_set,m_dwGTAId,szAnim);
	}
}

//-----------------------------------------------------------

void CPlayerPed::SetMoney(int iAmount)
{
	ScriptCommand(&set_actor_money,m_dwGTAId,0);
	ScriptCommand(&set_actor_money,m_dwGTAId,iAmount);
}

//-----------------------------------------------------------

void CPlayerPed::StartJetpack()
{
	if(!m_pPed) return;

	*pbyteCurrentPlayer = m_bytePlayerNumber;

	// reset CTasks so the CJetPack task priority can be enforced
	TeleportTo(m_pPed->entity.mat->pos.X, m_pPed->entity.mat->pos.Y, m_pPed->entity.mat->pos.Z);

	_asm mov eax, 0x439600
	_asm call eax

	*pbyteCurrentPlayer = 0;
}

//-----------------------------------------------------------

void CPlayerPed::StopJetpack()
{
	if(!m_pPed || IN_VEHICLE(m_pPed)) return;

	if(m_pPed->Tasks->pdwJumpJetPack == NULL) return;

	DWORD dwJmpVtbl = m_pPed->Tasks->pdwJumpJetPack[0];

	if(dwJmpVtbl == 0x8705C4) {
		DWORD dwJetPackTask = (DWORD)m_pPed->Tasks->pdwJumpJetPack;
		_asm mov ecx, dwJetPackTask
		_asm mov edx, 0x6801D0
		_asm push 1
		_asm call edx
		m_pPed->Tasks->pdwJumpJetPack = 0;
	}
}

//-----------------------------------------------------------

BOOL CPlayerPed::IsInJetpackMode()
{
	if(!m_pPed || IN_VEHICLE(m_pPed)) return FALSE;
	if(m_pPed->Tasks->pdwJumpJetPack == NULL) return FALSE;

	DWORD dwJmpVtbl = m_pPed->Tasks->pdwJumpJetPack[0];

	if(dwJmpVtbl == 0x8705C4) return TRUE;

	return FALSE;
}

//-----------------------------------------------------------

void CPlayerPed::StartGoggles()
{
	if (HasGoggles()) return;
	if (FindWeaponSlot( 44 ) == NULL && FindWeaponSlot( 45 ) == NULL)
		GiveWeapon( 44, 1 ); // Prevents crashing due to lack of animations.

	CTaskGoggles* pGoggles = new CTaskGoggles();
	pGoggles->ApplyToPed( this );
	m_bGoggleState = TRUE;
}

//-----------------------------------------------------------

void CPlayerPed::StopGoggles()
{
	if (!m_pPed || !HasGoggles()) return;

	m_bGoggleState = FALSE;
	DWORD dwPedPointer = (DWORD)m_pPed;
	_asm mov ecx, dwPedPointer
	_asm mov eax, 0x5E6010
	_asm call eax
}

//-----------------------------------------------------------

BOOL CPlayerPed::HasGoggles()
{
	if (!m_pPed) return FALSE;
	return (BOOL)(m_pPed->dwActiveVision != 0 || m_bGoggleState);
}

//-----------------------------------------------------------
