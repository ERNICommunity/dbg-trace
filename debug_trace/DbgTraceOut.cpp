/*
 * DbgTraceOut.cpp
 *
 *  Created on: 20.04.2015
 *      Author: aschoepfer
 */

#include "DbgTraceOut.h"

DbgTrace_Out::DbgTrace_Out(char* name, IDbgPrint* dbgPrint)
: m_name(name)
, m_nextOut(0)
, m_dbgPrint(dbgPrint)
{

}


