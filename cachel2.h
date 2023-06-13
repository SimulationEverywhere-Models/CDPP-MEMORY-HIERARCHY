/*******************************************************************
*
*  DESCRIPTION: Atomic CacheL2
*
*  AUTHOR: Yu Wang
*
*  EMAIL: mailto://ambitionwang@gmail.com
*
*  DATE: 15/10/2012
*
*******************************************************************/

#ifndef __CACHEL2_H
#define __CACHEL2_H

#include "atomic.h"     // class Atomic


/** forward declarations **/
class Distribution ;

class CacheL2 : public Atomic
{
public:
	CacheL2( const string &name = "CacheL2" );					//Default constructor
	~CacheL2();
	virtual string className() const ;
	int indexEqualAddressIn(int AddressIn);
	int replaceIndex();

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &AddressIn;
	const Port &DataIn;
	const Port &AddressOut;
	const Port &DataOut;
	const Port &ErrorOut;
	int CacheAddress[8];
	int CacheData[8];
	int CacheCounter[8];
	Time CacheAccessTime;
	Time CacheTimingOutTime;
	int data;
	int address;
	int hit;
	int miss;
	int index;
	int ErrorFlag;
	int AddressSent;
};	// class CacheL1

// ** inline ** //
inline
string CacheL2::className() const
{
	return "CacheL2" ;
}

#endif   //__CACHEL2_H
