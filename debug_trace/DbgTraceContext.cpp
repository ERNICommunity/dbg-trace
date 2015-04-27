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
  s_context = this;
}

DbgTrace_Port* DbgTrace_Context::getTracePort(const char* tag)
{
  if(0 == m_firstPort)
  {
    // no ports, return
    return 0;
  }
  else
  {
    // search port
    DbgTrace_Port* tmpPort = m_firstPort;

    while((0 != tmpPort))
    {
      if(0 == strncmp(tmpPort->getTag(), tag, DbgTrace_Port::s_cMaxPortTagLength))
      {
        // Port with this tag could be found
        return tmpPort;
      }
      tmpPort = tmpPort->getNextPort();
    }
    return tmpPort;
  }
}

void DbgTrace_Context::addTracePort(DbgTrace_Port* port)
{
  // check if port with this tag already exists in the list.
  DbgTrace_Port* tmpPort = m_firstPort;
  DbgTrace_Port* previousPort = m_firstPort;
  const char* portTag;
  if(0 != port)
  {
    portTag = port->getTag();

    while((0 != tmpPort))
    {
      if(0 == strncmp(tmpPort->getTag(), portTag, DbgTrace_Port::s_cMaxPortTagLength))
      {
       // fail, port with this tag already exists.
       return;
      }
      previousPort = tmpPort;
      tmpPort = tmpPort->getNextPort();
    }
    // no port with this tag, add port to list.
    if(0 != previousPort)
    {
      previousPort->setNextPort(port);
    }
    else
    { // special adding of the very first out.
      m_firstPort = port;
    }

    // Create DbgCliTopic and DbgCliCommands for this port
    if(0 != m_contextDbgTopic)
    {
      port->createCliNodes(m_contextDbgTopic);
    }
  }
}

void DbgTrace_Context::deleteTracePort(const char* tag)
{
  // check if port with this tag already exists in the list.
  DbgTrace_Port* tmpPort = m_firstPort;
  DbgTrace_Port* previousPort = m_firstPort;

  while((0 != tmpPort))
  {
    if(0 == strncmp(tmpPort->getTag(), tag, DbgTrace_Port::s_cMaxPortTagLength))
    {
      // found the searched TracePort, change nextPort-ptrs
      DbgTrace_Port* nextPort = tmpPort->getNextPort();
      if(0 != nextPort)
      {
        previousPort->setNextPort(nextPort);
      }
      else
      {
        // found TracePort was the last one.
        previousPort->setNextPort(0);
      }
      return;
    }
    previousPort = tmpPort;
    tmpPort = tmpPort->getNextPort();
  }
}

DbgTrace_Out* DbgTrace_Context::getTraceOut(const char* name)
{
  if(0 == m_firstOut)
  {
    // no out's, return
    return 0;
  }
  else
  {
    // search out
    DbgTrace_Out* tmpOut = m_firstOut;

    while((0 != tmpOut))
    {
      if(0 == strncmp(tmpOut->getName(), name, DbgTrace_Out::s_cMaxOutNameLength))
      {
        // Out with this name could be found
        return tmpOut;
      }
      tmpOut = tmpOut->getNextOut();
    }
    return tmpOut;
  }
}

void DbgTrace_Context::addTraceOut(DbgTrace_Out* out)
{
  // check if out with this name already exists in the list.
  DbgTrace_Out* tmpOut = m_firstOut;
  DbgTrace_Out* previousOut = m_firstOut;
  const char* outName;

  if(0 != out)
  {
    outName = out->getName();

    while((0 != tmpOut))
    {
      if(0 == strncmp(tmpOut->getName(), outName, DbgTrace_Out::s_cMaxOutNameLength))
      {
       // fail, out with this name already exists.
       return;
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
  }
}

void DbgTrace_Context::deleteTraceOut(const char* name)
{
  // check if out with this name already exists in the list.
  DbgTrace_Out* tmpOut = m_firstOut;
  DbgTrace_Out* previousOut = m_firstOut;

  while((0 != tmpOut))
  {
    if(0 == strncmp(tmpOut->getName(), name, DbgTrace_Out::s_cMaxOutNameLength))
    {
      // found the searched TraceOut, change nextOut-ptrs
      DbgTrace_Out* nextOut = tmpOut->getNextOut();
      if(0 != nextOut)
      {
        previousOut->setNextOut(nextOut);
      }
      else
      {
        // found TraceOut was the last one.
        previousOut->setNextOut(0);
      }
      return;
    }
    previousOut = tmpOut;
    tmpOut = tmpOut->getNextOut();
  }
}
