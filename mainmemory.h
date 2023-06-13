/*******************************************************************
*
*  DESCRIPTION: Atomic Model MainMemory
*
*  AUTHOR: Yu Wang
*
*  EMAIL: mailto://ambitionwang@gmail.com
*
*  DATE: 15/10/2012
*
*******************************************************************/

#ifndef __MAINMEMORY_H
#define __MAINMEMORY_H

#include "atomic.h"     // class Atomic


/** forward declarations **/
class Distribution ;

class MainMemory : public Atomic
{
public:
	MainMemory( const string &name = "MainMemory" );					//Default constructor
	~MainMemory();
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	Port &errorout;
	int address ;
	Time MemoryAccessTime;
	int memoryerrorflag;
	int memory_array[32];

};	// class MainMemory

// ** inline ** //
inline
string MainMemory::className() const
{
	return "MainMemory" ;
}

#endif   //__MAINMEMORY_H
