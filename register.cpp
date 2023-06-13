/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Rujun Hu
*
*  STUDENT#: 258902
*
*  EMAIL: rujun_hu@yahoo.ca
*
*  DATE: 16/10/2001
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "mainmemory.h"    // class MainMemory
#include "centralprocessingunit.h"   //class CenralProcessingUnit
#include "cachel1.h"        // class CacheL1
#include "cachel2.h"        // class CacheL1
//#include "subnet.h"        // class Subnet
//#include "subnet2.h"        // class Subnet2

void MainSimulator::registerNewAtomics()
{
 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MainMemory>(), "MainMemory" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CentralProcessingUnit>(), "CentralProcessingUnit" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CacheL1>(), "CacheL1" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CacheL2>(), "CacheL2" ) ;

}

