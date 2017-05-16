/*
 * DbgTracePort.cpp
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#include <DbgTraceContext.h>
#include <DbgTraceOut.h>
#include <DbgTracePort.h>
#include <DbgCliCommand.h>

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <time.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

//-----------------------------------------------------------------------------
// concrete command class DbgCli_Command_ChangeOut
//-----------------------------------------------------------------------------

/**
 * @brief Concrete cli command implementation to access the output of a trace port.
 */
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
    if (argc > idxToFirstArgToHandle)
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
          Serial.println(buf);
  #else
          printf("%s\n", buf);
  #endif
        }
      }
      else if(0 == strncmp(cmd, "set", 4))
      {
        if((0 !=  m_tracePort) && (0 != m_tracePort->getOut()) && (0 != context))
        {
          if (argc <= idxToFirstArgToHandle+1)
          {
#ifdef ARDUINO
#ifndef __ets__
            Serial.println(F("Output Name missing"));
#else
            Serial.println("Output Name missing");
#endif
            Serial.println(this->getHelpText());
#else
            printf("Output Name missing\n");
            printf("%s\n", this->getHelpText());
#endif
          }
          else
          {
            DbgTrace_Out* newOut = context->getTraceOut(args[idxToFirstArgToHandle+1]);
            char buf[20 + DbgTrace_Out::s_cMaxOutNameLength];

            if(0 != newOut)
            {
              m_tracePort->setOut(newOut);
              snprintf(buf, sizeof(buf), "OK! Out: \"%s\"" , m_tracePort->getOut()->getName());
            }
            else
            {
              snprintf(buf, sizeof(buf), "Fail! Out: \"%s\"" , m_tracePort->getOut()->getName());
            }
     #ifdef ARDUINO
            Serial.println(buf);
     #else
            printf("%s\n", buf);
     #endif
          }
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
              // mark currently used output
              snprintf(buf, sizeof(buf),">%s" , tmpOut->getName());
            }
            else
            {
              snprintf(buf, sizeof(buf), " %s" , tmpOut->getName());
            }
  #ifdef ARDUINO
            Serial.println(buf);
   #else
            printf("%s\n", buf);
   #endif
            tmpOut = tmpOut->getNextOut();
          }
        }
      }
      else
      {
  #ifdef ARDUINO
  #ifndef __ets__
    Serial.print(F("Unknown command: "));
  #else
    Serial.print("Unknown command: ");
  #endif
    Serial.println(cmd);
    Serial.println(this->getHelpText());
  #else
    printf("Unknown command: %s\n", cmd);
    printf("%s\n", this->getHelpText());
  #endif
      }
    }
    else
    {
#ifdef ARDUINO
#ifndef __ets__
      Serial.println(F("Cmd missing"));
#else
      Serial.println("Cmd missing");
#endif
      Serial.println(this->getHelpText());
#else
      printf("Cmd missing\n");
      printf("%s\n", this->getHelpText());
#endif
    }
  }
private:
  DbgCli_Command_ChangeOut();
};

//-----------------------------------------------------------------------------
// concrete command class DbgCli_Command_ChangeLevel
//-----------------------------------------------------------------------------

/**
 * @brief Concrete cli command implementation to access the level of a trace port.
 */
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
    if (argc > idxToFirstArgToHandle)
    {
      const char* cmd = args[idxToFirstArgToHandle];

      if (0 == strncmp(cmd, "get", 4))
      {
        if (0 !=  m_tracePort)
        {
          char buf[20 + DbgTrace_Level::s_cMaxLevelLength];
          snprintf(buf, sizeof(buf), "Level: \"%s\"" , DbgTrace_Level::levelToString(m_tracePort->getLevel()));
          // Print current level
#ifdef ARDUINO
          Serial.println(buf);
#else
          printf("%s\n", buf);
#endif
        }
      }
      else if (0 == strncmp(cmd, "set", 4))
      {
        if (0 !=  m_tracePort)
        {
          if (argc <= idxToFirstArgToHandle+1)
          {
#ifdef ARDUINO
#ifndef __ets__
            Serial.println(F("Level missing"));
#else
            Serial.println("Level missing");
#endif
            Serial.println(this->getHelpText());
#else
            printf("Level missing\n");
            printf("%s\n", this->getHelpText());
#endif
          }
          else
          {
            char buf[20 + DbgTrace_Level::s_cMaxLevelLength];

            // Get new level, as additional parameter
            DbgTrace_Level::Level newLevel = DbgTrace_Level::stringToLevel(args[idxToFirstArgToHandle+1]);
            if (DbgTrace_Level::none != newLevel)
            {
              m_tracePort->setLevel(newLevel);
              snprintf(buf, sizeof(buf), "OK! Level: \"%s\"" , DbgTrace_Level::levelToString(m_tracePort->getLevel()));
            }
            else
            {
              snprintf(buf, sizeof(buf), "Fail! Level: \"%s\"" , DbgTrace_Level::levelToString(m_tracePort->getLevel()));
            }
            // Print new level
  #ifdef ARDUINO
            Serial.println(buf);
  #else
            printf("%s\n", buf);
  #endif
          }
        }
      }
      else if (0 == strncmp(cmd, "list", 5))
      {
        if (0 !=  m_tracePort)
        {
          int level = 0;
          char buf[4 + DbgTrace_Level::s_cMaxLevelLength];
          while (DbgTrace_Level::LEVEL_ENUM_LIMIT != level)
          {
            // List all valid levels, line by line.
            if (level == m_tracePort->getLevel())
            {
              // mark currently used level
              snprintf(buf, sizeof(buf),">%s" , DbgTrace_Level::levelToString(static_cast<DbgTrace_Level::Level>(level)));
            }
            else
            {
              snprintf(buf, sizeof(buf)," %s" , DbgTrace_Level::levelToString(static_cast<DbgTrace_Level::Level>(level)));
            }
#ifdef ARDUINO
            Serial.println(buf);
#else
            printf("%s\n", buf);
#endif
            level++;
          }
        }
      }
      else
      {
#ifdef ARDUINO
#ifndef __ets__
        Serial.print(F("Unknown command: "));
#else
        Serial.print("Unknown command: ");
#endif
        Serial.println(cmd);
        Serial.println(this->getHelpText());
#else
        printf("Unknown command: %s\n", cmd);
        printf("%s\n", this->getHelpText());
#endif
      }
    }
    else
    {
#ifdef ARDUINO
#ifndef __ets__
      Serial.println(F("Cmd missing"));
#else
      Serial.println("Cmd missing");
#endif
      Serial.println(this->getHelpText());
#else
      printf("Cmd missing\n");
      printf("%s\n", this->getHelpText());
#endif
    }
  }
private:
  DbgCli_Command_ChangeLevel();
};

//-----------------------------------------------------------------------------
// Class DbgTrace_Port
//-----------------------------------------------------------------------------

DbgTrace_Port::DbgTrace_Port(const char* tag, DbgTrace_Level::Level level, const char* outName)
: m_out(DbgTrace_Context::getContext()->getTraceOut(outName))
, m_level(level)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->addTracePort(this);
  }
}

DbgTrace_Port::DbgTrace_Port(const char* tag, DbgTrace_Level::Level level)
: m_out(DbgTrace_Context::getContext()->getTraceOut(reinterpret_cast<const char*>("trConOut")))
, m_level(level)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->addTracePort(this);
  }
}

#ifdef ARDUINO
#ifndef __ets__
DbgTrace_Port::DbgTrace_Port(const __FlashStringHelper* tag, DbgTrace_Level::Level level, const __FlashStringHelper* outName)
: m_out(DbgTrace_Context::getContext()->getTraceOut(reinterpret_cast<const char*>(outName)))
, m_level(level)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->addTracePort(this);
  }
}

DbgTrace_Port::DbgTrace_Port(const __FlashStringHelper* tag, DbgTrace_Level::Level level)
: m_out(DbgTrace_Context::getContext()->getTraceOut(reinterpret_cast<const char*>(F("trConOut"))))
, m_level(level)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->addTracePort(this);
  }
}
#endif
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

void DbgTrace_Port::printStrFormat(const char* format, ...)
{
  char stream[s_cTraceBufSize];
  va_list args;
  va_start(args, format);
  vsnprintf(stream, s_cTraceBufSize, format, args);
  va_end(args);
  printStr(stream);
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
#ifdef AVR
    snprintf(stream, sizeof(stream), "%s - %s: ", timeStr, getTag());
    dtostrf(val, 6, 3, &stream[12]);
#else
    snprintf(stream, sizeof(stream), "%s - %s: %f", timeStr, getTag(), val);
#endif

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
    new DbgCli_Command_ChangeOut(this, portTopic, "out", "Cmds: get, set <outName>, list");
    new DbgCli_Command_ChangeLevel(this, portTopic, "lvl", "Cmds: get, set <levelName>, list");
  }
}

