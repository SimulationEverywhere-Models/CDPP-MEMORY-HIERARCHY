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

/** include files **/
#include "centralprocessingunit.h"      // class CentralProcessingUnit
#include "message.h"    // class ExternalMessage, InternalMessage
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )
#include <stdlib.h>

/** public functions **/

/*******************************************************************
* Function Name: CentralProcessingUnit
* Description:
********************************************************************/
CentralProcessingUnit::CentralProcessingUnit( const string &name )
: Atomic( name )
, ErrorOut( addOutputPort( "ErrorOut" ) )
, ControlIn( addInputPort( "ControlIn" ) )
, DataIn( addInputPort( "DataIn" ) )
, AddressOut( addOutputPort( "AddressOut" ) )
, DataReceived( addOutputPort( "DataReceived" ) )
, DataAccessNum( 0 )
, TotalDataAccessNum( 0 )
, AddressSending( 0 )
, DataReceivedFlag( 0 )
, SendingPreparationTime( 0, 0, 3, 0 )
, DataTimingOutTime( 0, 1, 20, 0 )
, ErrorFlag( 0 )
{
	int index;
	index = 1;
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
	}
/*	string time( MainSimulator::Instance().getParameter( description(), "MemoryAccessTime" ) ) ;

		if( time != "" )
			MemoryAccessTime = time ;*/
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &CentralProcessingUnit::initFunction()
{
	this->passivate();
	//packet = 0;
	DataAccessNum = 0;
	TotalDataAccessNum = 0;
	AddressSending = 0;
	DataReceivedFlag = 0;
	ErrorFlag = 0;
	transfertimes = 0;
//	cout << "hello world!" << endl;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &CentralProcessingUnit::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == ControlIn && this->state() == passive )
	{
		TotalDataAccessNum = static_cast < int > (msg.value());
		DataAccessNum = 0;
		DataReceivedFlag = 0;
		holdIn( active, Time::Zero ); // triger the internal function
	}

	if( AddressSending && msg.port() == DataIn && this->state()== active && AddressSending)
	{
		DataAccessNum++;
		AddressSending = 0;
		DataReceivedFlag = 1;
		Data = static_cast < int > (msg.value());
		holdIn( active, Time::Zero );
		transfertimes=0;
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &CentralProcessingUnit::internalFunction( const InternalMessage & )
{
	if( DataAccessNum >= TotalDataAccessNum )
		{
			this->passivate();
		}

	if( ErrorFlag )
	 {
		    this->passivate();
	 }
	else if( ( DataReceivedFlag || !DataAccessNum ) && (DataAccessNum < TotalDataAccessNum) && !AddressSending )
	{
		Address = rand() % 32;
		DataReceivedFlag = 0;
		AddressSending = 1;
		transfertimes = 1;
		holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ); // after a random time, we issue another memory access
	}
	else if( AddressSending && (transfertimes == 1))
	{
		//cout<<"DataTimingOutTime "<<DataTimingOutTime<<endl;
	//	AddressSending = 0;
		transfertimes++;
		holdIn( active, DataTimingOutTime );
	}
	else if(AddressSending && !DataReceivedFlag)
	{
	     ErrorFlag=1;
	     AddressSending=0;
	     cout << "ErrorFlag "<< ErrorFlag <<endl;
	     holdIn( active, Time::Zero );
	}




	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model & CentralProcessingUnit::outputFunction( const InternalMessage &msg )
{
	// cout<<" AddressSending "<<AddressSending<<endl;
	// cout << "ErrorFlag "<< ErrorFlag <<endl;
	 if( ErrorFlag )
	 {
	 		//cout<< "hello "<<endl;
	 	   sendOutput( msg.time(), ErrorOut, ErrorFlag ) ;
	 }
	if( AddressSending && transfertimes==1 )
	{
		sendOutput( msg.time(), AddressOut, Address ) ;
	}
	else if( DataReceivedFlag )
	{
	    sendOutput( msg.time(), DataReceived, Data ) ;
	}

	return *this ;
}

CentralProcessingUnit::~CentralProcessingUnit()
{
	 delete dist;
}
