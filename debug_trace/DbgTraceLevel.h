/*
 * DbgTraceLevels.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_
#define PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_

#include <string.h>

class DbgTrace_Level
{
public:
  virtual ~DbgTrace_Level() { }

  typedef enum
  {
    none      = -1,
    emergency =  0,
    alert     =  1,
    critical  =  2,
    error     =  3,
    warning   =  4,
    notice    =  5,
    info      =  6,
    debug     =  7
  } Level;

  static const char* levelToString(Level level)
  {
      switch (level)
      {
          case none:      return "none";
          case emergency: return "emergency";
          case alert:     return "alert";
          case critical:  return "critical";
          case error:     return "error";
          case warning:   return "warning";
          case notice:    return "notice";
          case info:      return "info";
          case debug:     return "debug";
          default:        return "[unknown debug level]";
      }
  }

  static Level stringToLevel(const char* levelStr)
  {
    if(0 == strncmp("emergency", levelStr, s_cMaxLevelLength))
    {
      return emergency;
    }
    else if(0 == strncmp("alert", levelStr, s_cMaxLevelLength))
    {
      return alert;
    }
    else if(0 == strncmp("critical", levelStr, s_cMaxLevelLength))
    {
      return critical;
    }
    else if(0 == strncmp("error", levelStr, s_cMaxLevelLength))
    {
      return error;
    }
    else if(0 == strncmp("warning", levelStr, s_cMaxLevelLength))
    {
      return warning;
    }
    else if(0 == strncmp("notice", levelStr, s_cMaxLevelLength))
    {
      return notice;
    }
    else if(0 == strncmp("info", levelStr, s_cMaxLevelLength))
    {
      return info;
    }
    else if(0 == strncmp("debug", levelStr, s_cMaxLevelLength))
    {
      return debug;
    }
    else
    {
      return none;
    }
  }

  static const unsigned int s_cMaxLevelLength = 12;

private:
  DbgTrace_Level& operator = (const DbgTrace_Level& src); // assignment operator
  DbgTrace_Level(const DbgTrace_Level& src);              // copy constructor
  DbgTrace_Level();
};


#endif /* PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_ */
