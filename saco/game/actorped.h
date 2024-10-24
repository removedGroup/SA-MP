
#pragma once

//-----------------------------------------------------------

class CActorPed : public CEntity
{
public:

	// Constructor/Destructor.
	CActorPed(int iSkin, float fPosX, float fPosY, float fPosZ, float fRotation = 0.0f);
	virtual ~CActorPed();

	void  Destroy();

	float GetHealth();
	float GetArmour();
	void  SetArmour(float fArmour);

	PED_TYPE    *m_pPed;
	DWORD		m_dwMarkerID;
	DWORD 		m_dwArrow;
	BYTE		m_byteCreateMarker;
	BYTE		m_byteImmune;
};

//-----------------------------------------------------------
