/*
 * DbgTraceContext.cpp
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#include "DbgTraceContext.h"
#include "DbgTracePort.h"
#include "DbgTraceOut.h"
#include <string.h>

DbgTrace_Context* DbgTrace_Context::s_context = 0;

DbgTrace_Context::DbgTrace_Context(DbgCli_Topic* cliParentNode)
: m_contextDbgTopic(cliParentNode)
, m_firstPort(0)
, m_firstOut(0)
{

}

DbgTrace_Port* DbgTrace_Context::getTracePort(char* tag)
{
  if(0 != m_firstPort)
  {
    // create first port and return
    m_firstPort = createTracePort(tag);
    return m_firstPort;
  }
  else
  {
    // search port
    DbgTrace_Port* tmpPort = m_firstPort;
    DbgTrace_Port* previousPort = m_firstPort;

    while((0 != tmpPort))
    {
      if(0 != strncmp(tmpPort->getTag(), tag, DbgTrace_Port::s_cMaxPortTagLength))
      {
        // port with this tag could be found
        return tmpPort;
      }
      previousPort = tmpPort;
      tmpPort = tmpPort->getNextPort();
    }
    // no port with this tag, create new port
    tmpPort = createTracePort(tag);
    previousPort->setNextPort(tmpPort);
    return tmpPort;
  }
}

DbgTrace_Out* DbgTrace_Context::getTraceOut(char* name)
{
  if(0 != m_firstOut)
  {
    // no out's, return
    return 0;
  }
  else
  {
    // search port
    DbgTrace_Out* tmpOut = m_firstOut;

    while((0 != tmpOut))
    {
      if(0 != strncmp(tmpOut->getName(), name, DbgTrace_Out::s_cMaxOutNameLength))
      {
        // Out with this name could be found
        return tmpOut;
      }
      tmpOut = tmpOut->getNextOut();
    }
    return tmpOut;
  }
}

bool DbgTrace_Context::addTraceOut(DbgTrace_Out* out)
{
  // check if out with this name already exists in the list.
  DbgTrace_Out* tmpOut = m_firstOut;
  DbgTrace_Out* previousOut = m_firstOut;
  const char* outName = out->getName();

  while((0 != tmpOut))
  {
   if(0 != strncmp(tmpOut->getName(), outName, DbgTrace_Out::s_cMaxOutNameLength))
   {
     // fail, out with this name already exists.
     return false;
   }
   previousOut = tmpOut;
   tmpOut = tmpOut->getNextOut();
  }
  // no out with this name, add out to list.
  if(0 != previousOut)
  {
    previousOut->setNextOut(out);
  }
  else
  { // special adding of the very first out.
    m_firstOut = out;
  }
  return true;
}

DbgTrace_Port* DbgTrace_Context::createTracePort(char* tag)
{
  DbgTrace_Port* tracePort = new DbgTrace_Port(tag);
  return tracePort;
}
