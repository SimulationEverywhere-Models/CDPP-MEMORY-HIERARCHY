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

/** include files **/
#include "cachel2.h"      // class MainMemory
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
CacheL2::CacheL2( const string &name )
: Atomic( name )
, AddressIn( addInputPort( "AddressIn" ) )
, DataIn( addInputPort( "DataIn" ) )
, AddressOut( addOutputPort( "AddressOut" ) )
, DataOut( addOutputPort( "DataOut" ) )
, ErrorOut( addOutputPort( "ErrorOut" ) )
, CacheAccessTime(0,0,20,0)
, CacheTimingOutTime(0,0,50,0)
, hit(0)
, miss(0)
, ErrorFlag(0)
, AddressSent(0)
{
	string time1( MainSimulator::Instance().getParameter( description(), "CacheAccessTime" ) ) ;

		if( time1 != "" )
			CacheAccessTime = time1 ;

	string time2( MainSimulator::Instance().getParameter( description(), "CacheTimingOutTime" ) ) ;

	    if( time2 != "" )
	    	CacheTimingOutTime = time2 ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &CacheL2::initFunction()
{
	this-> passivate();
	//packet = 0;
	int i=0;
	for(i=0;i<8;i++)
		CacheCounter[i]= -1;  // this means the array has no data,  -1 means no data in the array element
	return *this ;
}

int CacheL2::replaceIndex()
{
	int i=0;
	int index=0;
	int minvalue=CacheCounter[0];
	for(i=1;i<8;i++)
	{
	  if ( CacheCounter[i] < minvalue )
	  {
          index=i;
          minvalue=CacheCounter[i];
	  }
	}
	return index ;
}

 int CacheL2::indexEqualAddressIn(int AddressIn)
{
	 int i;
	 for(i=0;i<8;i++)
		if( CacheAddress[i]==AddressIn && CacheCounter[i]!=-1 )
		{
	//	   cout<<"indexEqualfunction "<<endl;
		   return i;
		}
//	cout<<"indexEqualfunction "<<endl;
	return -1 ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &CacheL2::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == AddressIn && this->state() == passive && !ErrorFlag)
	{
		//index ++;
		address = static_cast < int > (msg.value());
	//	cout<<"address "<<address<<endl;
        index = indexEqualAddressIn(address);

		if(index==-1)
		{
		  miss = 1;
	//	  cout<<"miss "<<miss<<endl;
		  AddressSent = 1;
	//	  cout<<"index -1"<<endl;
		}
		else
		{
		  hit = 1;

          CacheCounter[index]+=1;
          data=CacheData[index];
		}

	//	cout<<"hit "<< hit <<endl;
	//	cout<<"miss "<< miss <<endl;

		holdIn( active, CacheAccessTime );

	}
	else if( msg.port() == DataIn && this->state() == active && miss )
	{
		//index ++;

		data = static_cast < int > (msg.value());
		int index = replaceIndex();
        CacheAddress[index]=address;
        CacheData[index]=data;
        CacheCounter[index]=0;
        miss=0;
        hit =1;
		holdIn( active, Time::Zero );
	}


	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &CacheL2::internalFunction( const InternalMessage & )
{
	if(ErrorFlag)
	{
		this->passivate();
	}
	else if(hit)
	{
		hit=0;
		this->passivate();
	}
	else if(miss && AddressSent==1)
	{
		AddressSent++;
		holdIn( active, CacheTimingOutTime );
	}
	else if(miss && AddressSent !=1 )
	{
		ErrorFlag=1;
		// cout << "error" <<endl;
		holdIn( active, Time::Zero );
	}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model & CacheL2::outputFunction( const InternalMessage &msg )
{
	//if ((double)rand() / (double) RAND_MAX  < 0.95)
	if( miss && AddressSent==1 )
	{
      sendOutput( msg.time(), AddressOut, address ) ;
	}
	if(hit)
	{
	  sendOutput( msg.time(), DataOut, data ) ;
	}
	if(ErrorFlag)
	{
	  sendOutput( msg.time(), ErrorOut, 1) ;
	}

	return *this ;
}

CacheL2::~CacheL2()
{
	// delete dist;
}
