// TODO: Implement RakPeerInterface.h

#ifndef __RAK_PEER_INTERFACE_H
#define __RAK_PEER_INTERFACE_H

#include "Export.h"

class RAK_DLL_EXPORT RakPeerInterface
{
public:

	virtual void vftable_0()=0;
	virtual void vftable_4()=0;
	virtual void vftable_8()=0;
	virtual void vftable_C()=0;
	virtual void vftable_18()=0;
	virtual void vftable_1C()=0;
	virtual void vftable_20()=0;
	virtual void vftable_24()=0;
	virtual void vftable_28()=0;

	/// Sets how many incoming connections are allowed. If this is less than the number of players currently connected,
	/// no more players will be allowed to connect.  If this is greater than the maximum number of peers allowed,
	/// it will be reduced to the maximum number of peers allowed.  Defaults to 0.
	/// \param[in] numberAllowed Maximum number of incoming connections allowed.
	virtual void SetMaximumIncomingConnections( unsigned short numberAllowed )=0;

	/// Returns the value passed to SetMaximumIncomingConnections()
	/// \return the maximum number of incoming connections, which is always <= maxConnections
	virtual unsigned short GetMaximumIncomingConnections( void ) const=0;

	virtual void vftable_2C()=0;
	virtual void vftable_30()=0;
	virtual void vftable_34()=0;
	virtual void vftable_38()=0;
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

};

#endif