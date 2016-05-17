/*
 * DbgTraceLevels.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_
#define PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_

#include <string.h>

/**
 * @brief Describes the trace levels, each message and each port has one of the defined level to be able to change the amount of information from each port at runtime.
 *
 * A trace message and a trace port have a certain level. If the level of a message is equal or greater than its port, the message will be printed.
 */
class DbgTrace_Level
{
public:
  virtual ~DbgTrace_Level() { }

  /**
   * Defined trace levels according, the cisco log levels.
   */
  typedef enum
  {
    none      = -1,   //!< none: Should not been used, only in initial states before a "real" level is set, or for switch off a specific port.
    emergency =  0,   //!< emergency: The system is unusable
    alert     =  1,   //!< alert: Immediate action is required
    critical  =  2,   //!< critical: A critical condition exists
    error     =  3,   //!< error: Error message
    warning   =  4,   //!< warning: Warning message
    notice    =  5,   //!< notice: A normal but significant condition
    info      =  6,   //!< info: Information message
    debug     =  7,   //!< debug: Debug output and very detailed logs
    LEVEL_ENUM_LIMIT  //!< LEVEL_ENUM_LIMIT: not a level, used to get the enum size
  } Level;

  /**
   * @brief Converts a level (enum value) to its string.
   * @param level Valid enum level element
   * @return The trace level as a string
   */
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
          default:        return "[unknown level]";
      }
  }

  /**
   * @brief Converts a string to a level, if the string could be matched with a level.
   * @param levelStr String of the level, beginning with a small letter
   * @return The level, if there was a suitable string passed, or none otherwise.
   */
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

  static const unsigned int s_cMaxLevelLength = 12; /*!< Max. number of characters for a level name. */

private:
  DbgTrace_Level& operator = (const DbgTrace_Level& src); // assignment operator
  DbgTrace_Level(const DbgTrace_Level& src);              // copy constructor
  DbgTrace_Level();
};


#endif /* PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_ */
