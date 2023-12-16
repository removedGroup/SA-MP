// TODO: Implement RakServerInterface.h

#ifndef __RAK_SERVER_INTERFACE_H
#define __RAK_SERVER_INTERFACE_H

#include "Export.h"

/// This is a user-interface class to act as a game server.  All it does is implement some functionality on top of RakPeer.
/// See the individual functions for what the class can do.
/// \brief Defines the functions used by a game server
class RAK_DLL_EXPORT RakServerInterface
{

public:
	virtual void vftable_0()=0;
	virtual void vftable_4()=0;
	virtual void vftable_8()=0;
	virtual void vftable_C()=0;
	virtual void vftable_10()=0;
	virtual void vftable_14()=0;
	virtual void vftable_18()=0;
	virtual void vftable_1C()=0;
	virtual void vftable_20()=0;
	virtual void vftable_24()=0;
	virtual void vftable_28()=0;
	virtual void vftable_2C()=0;
	virtual void vftable_30()=0;

	/// Set how many players are allowed on the server.
	/// If more players are currently connected then are allowed then no more players will be allowed to join until the number of players is less than the number of allowed players.
	/// \pre The server must be active for this to have meaning
	/// \param[in] AllowedPlayers The number of players to allow
	virtual void SetAllowedPlayers( unsigned short AllowedPlayers )=0;

	/// Return how many players are allowed to connect. This value was set either from Start or from SetAllowedPlayers.
	/// \pre The server must be active for this to have meaning
	/// \return The number of allowed players
	virtual unsigned short GetAllowedPlayers( void ) const=0;

	virtual void vftable_3C()=0;
	virtual void vftable_40()=0;
	virtual void vftable_44()=0;
	virtual void vftable_48()=0;
	virtual void vftable_4C()=0;
	virtual void vftable_50()=0;
	virtual void vftable_54()=0;
	virtual void vftable_58()=0;
	virtual void vftable_5C()=0;
	virtual void vftable_60()=0;
	virtual void vftable_64()=0;
	virtual void vftable_68()=0;
	virtual void vftable_6C()=0;
	virtual void vftable_70()=0;
	virtual void vftable_74()=0;
	virtual void vftable_78()=0;
	virtual void vftable_7C()=0;
	virtual void vftable_80()=0;
	virtual void vftable_84()=0;
	virtual void vftable_88()=0;
	virtual void vftable_8C()=0;
	virtual void vftable_90()=0;
	virtual void vftable_94()=0;
	virtual void vftable_98()=0;
	virtual void vftable_9C()=0;
	virtual void vftable_A0()=0;
	virtual void vftable_A4()=0;
	virtual void vftable_A8()=0;
	virtual void vftable_AC()=0;
	virtual void vftable_B0()=0;
	virtual void vftable_B4()=0;
	virtual void vftable_B8()=0;
	virtual void vftable_BC()=0;
	virtual void vftable_C0()=0;
	virtual void vftable_C4()=0;
	virtual void vftable_C8()=0;
	virtual void vftable_CC()=0;
	virtual void vftable_D0()=0;
	virtual void vftable_D4()=0;
	virtual void vftable_D8()=0;
	virtual void vftable_DC()=0;
	virtual void vftable_E0()=0;
	virtual void vftable_E4()=0;
	virtual void vftable_E8()=0;
	virtual void vftable_EC()=0;
	virtual void vftable_F0()=0;
	virtual void vftable_F4()=0;
	virtual void vftable_F8()=0;
	virtual void vftable_FC()=0;
	virtual void vftable_100()=0;
	virtual void vftable_104()=0;
	virtual void vftable_108()=0;
	virtual void vftable_10C()=0;
	virtual void vftable_110()=0;
	virtual void vftable_114()=0;
	virtual void vftable_118()=0;
	virtual void vftable_11C()=0;
	virtual void vftable_120()=0;
	virtual void vftable_124()=0;
};

#endif