/*
 * DbgTracePort.h
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEPORT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEPORT_H_

#include "DbgTraceLevel.h"
#ifdef ARDUINO
#include <Arduino.h>
#endif

class DbgTrace_Context;
class DbgTrace_Out;
class DbgCli_Topic;

#define TR_PRINTF(PORT, LEVEL, args...) do { if ((PORT)->getLevel()>=(LEVEL)) (PORT)->printStrFormat(args); } while (0);
#define TR_PRINT_STR(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printStr((MSG)); } while (0);
#define TR_PRINT_LONG(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printLong((MSG)); } while (0);
#define TR_PRINT_DBL(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printDbl((MSG)); } while (0);
#ifdef ARDUINO
#ifndef __ets__
#define TR_PRINT_FSTR(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printFStr((MSG)); } while (0);
#endif
#endif

/**
 * @brief Instance of a trace port, to print strings or values to a specified print output.
 *
 * The trace port is assigned to a global context. It has a defined trace level and a output to print.
 * For every port will automatically generated a DbgCli topic with commands for read and modify the trace level and output.
 */
class DbgTrace_Port
{
public:
  /**
   * @brief Constructor to create a new port instance. The port will be automatically assigned to the mentioned debug trace context.
   * @param tag The tag name of the port, which should be unique and and not longer than the specified max size.
   *            The port can afterwards globally accessed by its content and tag.
   * @param level Trace level of the port. All traces with a similar or higher trace level will be printed.
   * @param out Name of an output, for printing the traces (optional, default: "trConOut").
   */
  DbgTrace_Port(const char* tag, DbgTrace_Level::Level level, const char* outName);
  DbgTrace_Port(const char* tag, DbgTrace_Level::Level level);

#ifdef ARDUINO
#ifndef __ets__
  /**
   * @brief Constructor to create a new port instance. With a tag stored in flash (ram optimized version for embedded controllers)
   * @param tag The tag name of the port, which should be unique and and not longer than the specified max size.
   *            The port can afterwards globally accessed by its content and tag.
   * @param level Trace level of the port. All traces with a similar or higher trace level will be printed.
   * @param out Name of an output, for printing the traces (optional, default: "trConOut").
   */
  DbgTrace_Port(const __FlashStringHelper* tag, DbgTrace_Level::Level level, const __FlashStringHelper* outName);
  DbgTrace_Port(const __FlashStringHelper* tag, DbgTrace_Level::Level level);
#endif
#endif

  /**
   * @brief Destructor of a trace port instance.
   */
  virtual ~DbgTrace_Port();

  /**
   * @brief Get next port. All ports of a context are stored with a single linked list.
   * @return Next port or 0 (nullptr) if there is no further port.
   */
  DbgTrace_Port* getNextPort() { return m_nextPort; }

  /**
   * @brief Set the next port. All ports of a context are stored with a single linked list.
   * The ports are added automatically by its creation from the context.
   * @param nextPort Pointer of the next trace port.
   */
  void setNextPort(DbgTrace_Port* nextPort) { if(0 != nextPort) m_nextPort = nextPort; }

  /**
   * @brief Sets a trace output to the port.
   * Output can switched in code, or at runtime by debug cli.
   * @param out Pointer to the new trace output.
   */
  void setOut(DbgTrace_Out* out) { m_out = out; }

 /**
   * @brief Get the currently used trace output
   * @return Pointer to the used debug trace output
   */
  DbgTrace_Out* getOut() { return m_out; }

  /**
   * @brief Sets the trace level of this port instance.
   * The trace level can be later switched in code, or at runtime by debug cli.
   * @param level New trace level for this port.
   */
  void setLevel(DbgTrace_Level::Level level) { m_level = level; }

  /**
   * @brief Get the current trace level for this port.
   * All trace messages with an equal or higher level than this will be printed.
   * @return Current trace level for this port.
   */
  DbgTrace_Level::Level getLevel() { return m_level; }

  /**
   * @brief Helper method to print a formatted string. Don't call this function directly, use the defined macros.
   * @param format Const char format string to be printed out.
   * @param var_arg Variable list of paramters to be printed according to placeholders in the format string.
   */
  void printStrFormat(const char* format, ...);

  /**
   * @brief Helper method to print a string. Don't call this function directly, use the defined macros.
   * @param str Const char message to be printed out.
   */
  void printStr(const char* str);
#ifdef ARDUINO
#ifndef __ets__
  /**
   * @brief Same as printStr, but with a string stored in flash (ram optimized version for embedded controllers)
   * Don't call this function directly, use the defined macros.
   * @param str  message to print out.
   */
  void printFStr(const __FlashStringHelper* str) { printStr(reinterpret_cast<const char*>(str)); }
#endif
#endif

  /**
   * @brief Helper method to print a integer or long value. Don't call this function directly, use the defined macros.
   * @param num Value to print out.
   */
  void printLong(long num);

  /**
   * @brief Helper method to print a floating point value. Don't call this function directly, use the defined macros.
   * @param val Floating point value to print out.
   */
  void printDbl(double val);

  /**
    * @brief Get the tag string of this trace port.
    * @return Tag string of this port.
    */
  const char* getTag() { return m_tag; }

  /**
    * @brief Creates the debug cli topics and commands for a trace port.
    * This method is called automatically during creation of new port.
    * @param contextTopic Pointer of the cli parent topic, where the new port topic has to be added.
    */
  void createCliNodes(DbgCli_Topic* contextTopic);

  static const unsigned int s_cMaxPortTagLength = 16; /*!< Max. number of characters for a tag name of a trace port. */
  static const unsigned int s_cTestTimeStamp = 10; /*!< Max. number of characters for the printed time-stamp using the test environment. */
  static const unsigned int s_cArduinoTimeStamp = 12; /*!< Max. number of characters for the printed time-stamp using arduino. */
  static const unsigned int s_cTraceBufSize = s_cMaxPortTagLength + s_cMaxPortTagLength + 100; /*!< Max. number of characters of the hole printed message. */

private:

  /**
   * @brief Gets the current time used for the printed trace messages. Has a platform specific implementation.
   * @param timeStr Variable the function writes the current time-stamp.
   */
  void getTime(char* timeStr);

  DbgTrace_Out* m_out; /*!< Assigned output instance of this trace port. */
  DbgTrace_Level::Level m_level; /*!< Level of this trace port, all trace messages with an equal or higher level will be printed by this port. */
  DbgTrace_Port* m_nextPort; /*!< Pointer to next trace port. The context can iterate through this single linked list. */
  const char* m_tag; /*!< Tag string of a trace port. Must be unique within the trace context. Tag length should not exceed s_cMaxPortTagLength. */

private: // forbidden default functions
  DbgTrace_Port& operator = (const DbgTrace_Port& src); // assignment operator
  DbgTrace_Port(const DbgTrace_Port& src);              // copy constructor
  DbgTrace_Port();
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEPORT_H_ */
