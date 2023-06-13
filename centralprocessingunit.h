/*******************************************************************
*
*  DESCRIPTION: Atomic CentralProcessingUnit MainMemory
*
*  AUTHOR: Yu Wang
*
*  EMAIL: mailto://ambitionwang@gmail.com
*
*  DATE: 15/10/2012
*
*******************************************************************/

#ifndef __CENTRAL_PROCESSING_UNIT_H
#define __CENTRAL_PROCESSING_UNIT_H

#include "atomic.h"     // class Atomic


/** forward declarations **/
class Distribution ;

class CentralProcessingUnit : public Atomic
{
public:
	CentralProcessingUnit( const string &name = "CentralProcessingUnit" );					//Default constructor
	~CentralProcessingUnit();
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port & ControlIn;
	Port &DataIn;
	Port &AddressOut;
	Port &ErrorOut;
	Port &DataReceived;

	int DataAccessNum ;
	int TotalDataAccessNum;
	int AddressSending;
	int DataReceivedFlag;
	int Data;
	int Address;
	int ErrorFlag;
	int transfertimes;
	Time SendingPreparationTime;
	Time DataTimingOutTime;
	Distribution * dist;
	Distribution &distribution()
		{return *dist;}

};	// class CentralProcessingUnit

// ** inline ** //
inline
string CentralProcessingUnit::className() const
{
	return "CentralProcessingUnit" ;
}

#endif   //__CENTRAL_PROCESSING_UNIT_H
