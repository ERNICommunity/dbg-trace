/*
 * DbgTracePort.cpp
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#include "DbgTraceContext.h"
#include "DbgTraceOut.h"
#include "DbgTracePort.h"
#include "DbgCliCommand.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <time.h>
#endif
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------------------
// concrete command class DbgCli_Command_ChangeOut
//-----------------------------------------------------------------------------

class DbgCli_Command_ChangeOut : public DbgCli_Command
{

private:
  DbgTrace_Port* m_tracePort;

public:
  DbgCli_Command_ChangeOut(DbgTrace_Port* port, DbgCli_Node* parentNode, const char* nodeName, const char* helpText)
  : DbgCli_Command(parentNode, nodeName, helpText)
  , m_tracePort(port)
  { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
  {
    const char* cmd = args[idxToFirstArgToHandle];
    DbgTrace_Context* context = DbgTrace_Context::getContext();

    if(0 == strncmp(cmd, "get", 4))
    {
      if((0 !=  m_tracePort) && (0 != m_tracePort->getOut()))
      {
        char buf[20 + DbgTrace_Out::s_cMaxOutNameLength];
        snprintf(buf, sizeof(buf), "Out: \"%s\"" , m_tracePort->getOut()->getName());
#ifdef ARDUINO
        Serial.print(buf);
#else
        println(buf);
#endif
      }
    }
    else if(0 == strncmp(cmd, "set", 4))
    {
      if((0 !=  m_tracePort) && (0 != m_tracePort->getOut()) && (0 != context))
      {
        DbgTrace_Out* newOut = context->getTraceOut(args[idxToFirstArgToHandle+1]);
        char buf[20 + DbgTrace_Out::s_cMaxOutNameLength];

        if(0 != newOut)
        {
          m_tracePort->setOut(newOut);
          snprintf(buf, sizeof(buf),"OK! Out: \"%s\"" , m_tracePort->getOut()->getName());
        }
        else
        {
          snprintf(buf, sizeof(buf), "Fail! Out: \"%s\"" , m_tracePort->getOut()->getName());
        }
 #ifdef ARDUINO
          Serial.print(buf);
 #else
          println(buf);
 #endif
      }
    }
    else if((0 == strncmp(cmd, "list", 5)) && (0 != context))
    {
      DbgTrace_Out* tmpOut = context->getFirstTraceOut();
      if((0 !=  m_tracePort) && (0 != m_tracePort->getOut()))
      {
        char buf[20 + DbgTrace_Out::s_cMaxOutNameLength];
        while(0 != tmpOut)
        {
          if((0 != m_tracePort->getOut()) &&
             (0 == strncmp(tmpOut->getName(), m_tracePort->getOut()->getName(), DbgTrace_Out::s_cMaxOutNameLength)))
          {
            // mark currently used out
            snprintf(buf, sizeof(buf),">%s" , tmpOut->getName());
          }
          else
          {
            snprintf(buf, sizeof(buf), " %s" , tmpOut->getName());
          }
#ifdef ARDUINO
          Serial.println(buf);
 #else
          println(buf);
 #endif
          tmpOut = tmpOut->getNextOut();
        }
      }
    }
    else
    {
#ifdef ARDUINO
  Serial.print(F("Unknown command: "));
  Serial.println(cmd);
  Serial.println(this->getHelpText());
#else
  println("Unknown command: %s", cmd);
  printf(this->getHelpText());
#endif
    }
  }
private:
  DbgCli_Command_ChangeOut();
};

//-----------------------------------------------------------------------------
// concrete command class DbgCli_Command_ChangeLevel
//-----------------------------------------------------------------------------

class DbgCli_Command_ChangeLevel : public DbgCli_Command
{

private:
  DbgTrace_Port* m_tracePort;

public:
  DbgCli_Command_ChangeLevel(DbgTrace_Port* port, DbgCli_Node* parentNode, const char* nodeName, const char* helpText)
  : DbgCli_Command(parentNode, nodeName, helpText)
  , m_tracePort(port)
  { }

  void execute(unsigned int argc, const char** args, unsigned int idxToFirstArgToHandle)
  {
    const char* cmd = args[idxToFirstArgToHandle];

    if(0 == strncmp(cmd, "get", 4))
    {
      if(0 !=  m_tracePort)
      {
        char buf[20 + DbgTrace_Level::s_cMaxLevelLength];
        snprintf(buf, sizeof(buf), "Level: \"%s\"" , DbgTrace_Level::levelToString(m_tracePort->getLevel()));
#ifdef ARDUINO
        Serial.println(buf);
#else
        printfln(buf);
#endif
      }
    }
    else if(0 == strncmp(cmd, "set", 4))
    {
      if(0 !=  m_tracePort)
      {
        char buf[20 + DbgTrace_Level::s_cMaxLevelLength];

        DbgTrace_Level::Level newLevel = DbgTrace_Level::stringToLevel(args[idxToFirstArgToHandle+1]);
        if(DbgTrace_Level::none != newLevel)
        {
          m_tracePort->setLevel(newLevel);
          snprintf(buf, sizeof(buf),"OK! Level: \"%s\"" , DbgTrace_Level::levelToString(m_tracePort->getLevel()));
        }
        else
        {
          snprintf(buf, sizeof(buf), "Fail! Level: \"%s\"" , DbgTrace_Level::levelToString(m_tracePort->getLevel()));
        }
 #ifdef ARDUINO
          Serial.print(buf);
 #else
          printfln(buf);
 #endif
      }
    }
    else if(0 == strncmp(cmd, "list", 5))
    {
      if(0 !=  m_tracePort)
      {
        unsigned int level = 0;
        char buf[4 + DbgTrace_Level::s_cMaxLevelLength];
        while(DbgTrace_Level::LEVEL_ENUM_LIMIT != level)
        {
          if(level == m_tracePort->getLevel())
          {
            // mark currently used out
            snprintf(buf, sizeof(buf),">%s" , DbgTrace_Level::levelToString(static_cast<DbgTrace_Level::Level>(level)));
          }
          else
          {
            snprintf(buf, sizeof(buf)," %s" , DbgTrace_Level::levelToString(static_cast<DbgTrace_Level::Level>(level)));
          }
#ifdef ARDUINO
          Serial.println(buf);
 #else
          println(buf);
 #endif
          level++;
        }
      }
    }
    else
    {
    #ifdef ARDUINO
      Serial.print(F("Unknown command: "));
      Serial.println(cmd);
      Serial.println(this->getHelpText());
    #else
      println("Unknown command: %s", cmd);
      printf(this->getHelpText());
    #endif
    }
  }
private:
  DbgCli_Command_ChangeLevel();
};

//-----------------------------------------------------------------------------
// Class DbgTrace_Port
//-----------------------------------------------------------------------------

DbgTrace_Port::DbgTrace_Port(DbgTrace_Context* context, const char* tag, DbgTrace_Out* out, DbgTrace_Level::Level level)
: m_out(out)
, m_level(level)
, m_nextPort(0)
, m_tag(tag)
{
  if(0 != context)
  {
    context->addTracePort(this);
  }
}

#ifdef ARDUINO
DbgTrace_Port::DbgTrace_Port(DbgTrace_Context* context, const __FlashStringHelper* tag, DbgTrace_Out* out, DbgTrace_Level::Level level)
: m_out(out)
, m_level(level)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{
  if(0 != context)
  {
    context->addTracePort(this);
  }
}
#endif

DbgTrace_Port::~DbgTrace_Port()
{
  //Delete tracePort in single linked list
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->deleteTracePort(m_tag);
  }
}

void DbgTrace_Port::printStr(const char* str)
{
  if(0 != m_out)
  {
#ifdef ARDUINO
    char timeStr[s_cArduinoTimeStamp];
#else
    char timeStr[s_cTestTimeStamp];
#endif
    char stream[s_cTraceBufSize];
    getTime(timeStr);
    snprintf(stream, sizeof(stream), "%s - %s: %s", timeStr, getTag(), str);

    m_out->print(stream);
  }
}

void DbgTrace_Port::printLong(long num)
{
  if(0 != m_out)
  {
#ifdef ARDUINO
    char timeStr[s_cArduinoTimeStamp];
#else
    char timeStr[s_cTestTimeStamp];
#endif
    char stream[s_cTraceBufSize];
    getTime(timeStr);
    snprintf(stream, sizeof(stream), "%s - %s: %ld", timeStr, getTag(), num);

    m_out->print(stream);
  }
}

void DbgTrace_Port::printDbl(double val)
{
  if(0 != m_out)
  {
#ifdef ARDUINO
    char timeStr[s_cArduinoTimeStamp];
#else
    char timeStr[s_cTestTimeStamp];
#endif
    getTime(timeStr);
    char stream[s_cTraceBufSize];
    snprintf(stream, sizeof(stream), "%s - %s: %f", timeStr, getTag(), val);

    m_out->print(stream);
  }
}

void DbgTrace_Port::getTime(char* timeStr)
{
#ifdef ARDUINO
  sprintf(timeStr,"%ld", millis());
#else
  _strtime(timeStr);
#endif
}

void DbgTrace_Port::createCliNodes(DbgCli_Topic* contextTopic)
{
  DbgCli_Topic* portTopic = new DbgCli_Topic(contextTopic, m_tag, "Offers get/set access to output and level");
  if(0 != m_out)
  {
    // Create DbgCli commands for out and level of this port
    new DbgCli_Command_ChangeOut(this, portTopic, "outCmd", "Cmd's: get, set outName, list");
    new DbgCli_Command_ChangeLevel(this, portTopic, "levelCmd", "Cmd's: get, set levelName, list");
  }
}

