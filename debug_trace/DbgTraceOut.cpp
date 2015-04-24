/*
 * DbgTraceOut.cpp
 *
 *  Created on: 20.04.2015
 *      Author: aschoepfer
 */

#include "DbgTraceContext.h"
#include "DbgTraceOut.h"
#include "IDbgPrint.h"

DbgTrace_Out::DbgTrace_Out(DbgTrace_Context* context, const char* name, IDbgPrint* dbgPrint)
: m_name(name)
, m_nextOut(0)
, m_dbgPrint(dbgPrint)
{
  if(0 != context)
  {
    context->addTraceOut(this);
  }
}

DbgTrace_Out::~DbgTrace_Out()
{
  //Delete traceOut in single linked list
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->deleteTraceOut(m_name);
  }
  m_dbgPrint = 0;
}

void DbgTrace_Out::print(const char* str)
{
  if(0 != m_dbgPrint)
  {
    m_dbgPrint->print(str);
  }
}
