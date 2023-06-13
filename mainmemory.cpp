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

/** include files **/
#include "mainmemory.h"      // class MainMemory
#include "message.h"    // class ExternalMessage, InternalMessage
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )
#include <stdlib.h>

/** public functions **/

/*******************************************************************
* Function Name: MainMemory
* Description:
********************************************************************/
MainMemory::MainMemory( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
, errorout( addOutputPort( "errorout" ) )
, MemoryAccessTime( 0, 0, 40, 0 )
{
	/*index = 1;
	try
	{
    	dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

    	MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}*/
	string time( MainSimulator::Instance().getParameter( description(), "MemoryAccessTime" ) ) ;

		if( time != "" )
			MemoryAccessTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &MainMemory::initFunction()
{
	this-> passivate();
	//packet = 0;
	memoryerrorflag=0;
	int i=0;
	for(i=0;i<32;i++)
		memory_array[i]= i*2;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &MainMemory::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in && this->state()==passive && !memoryerrorflag)
	{
		//index ++;
		address = static_cast < int > (msg.value());
		//Time t(fabs(this->distribution().get()));
		if( address<0 || address > 31)
		{
		  memoryerrorflag=1;
		}
		holdIn( active, MemoryAccessTime );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &MainMemory::internalFunction( const InternalMessage & )
{
	this->passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model & MainMemory::outputFunction( const InternalMessage &msg )
{
	//if ((double)rand() / (double) RAND_MAX  < 0.95)
	if(!memoryerrorflag)
	  sendOutput( msg.time(), out, memory_array[address] ) ;
	else
	  sendOutput( msg.time(), errorout, 1 ) ;
    
	return *this ;
}

MainMemory::~MainMemory()
{
	// delete dist;
}
