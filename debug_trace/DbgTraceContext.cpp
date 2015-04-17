/*
 * DbgTraceContext.cpp
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#include "DbgTraceContext.h"
#include "DbgCliTopic.h"

DbgTrace_Context* DbgTrace_Context::s_context = 0;

DbgTrace_Context::DbgTrace_Context(DbgCli_Topic* cliParentNode)
: m_contextDbgTopic(0)
, m_firstPort(0)
//, m_firstOut(0)
{
  if(0 != cliParentNode)
  {
    m_contextDbgTopic = cliParentNode;
  }
}

DbgTrace_Port* DbgTrace_Context::getTracePort(char* tag)
{
  if(0 != m_firstPort)
  {
    // create first port
    m_firstPort = new DbgTrace_Port(tag);
    // create topic for the context, and for each port a topic with a level and a output command
    //DbgCli_Topic* portTopic = new DbgCli_Topic()
    //m_contextDbgTopic->addChildNode()
    return m_firstPort;
  }
  else
  {
    DbgTrace_Port* tmpPort = m_firstPort;
    DbgTrace_Port* previousPort = m_firstPort;

    while((0 != tmpPort))
    {
      if(0 != strncmp(tmpPort->getTag(), tag, DbgTrace_Port::s_cMaxTagLength))
      {
        return tmpPort;
      }
      previousPort = tmpPort;
      tmpPort = tmpPort->getNextPort();
    }
    // add new port
    tmpPort = new DbgTrace_Port(tag);
    previousPort->setNextPort(tmpPort);
    return tmpPort;
  }
}

//DbgTrace_Out* DbgTrace_Context::getTraceOut(char* tag)
//{
//
//}
