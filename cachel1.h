/*******************************************************************
*
*  DESCRIPTION: Atomic CacheL1
*
*  AUTHOR: Yu Wang
*
*  EMAIL: mailto://ambitionwang@gmail.com
*
*  DATE: 15/10/2012
*
*******************************************************************/

#ifndef __CACHEL1_H
#define __CACHEL1_H

#include "atomic.h"     // class Atomic


/** forward declarations **/
class Distribution ;

class CacheL1 : public Atomic
{
public:
	CacheL1( const string &name = "CacheL1" );					//Default constructor
	~CacheL1();
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
	int CacheAddress[4];
	int CacheData[4];
	int CacheCounter[4];
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
string CacheL1::className() const
{
	return "CacheL1" ;
}

#endif   //__CACHEL1_H
