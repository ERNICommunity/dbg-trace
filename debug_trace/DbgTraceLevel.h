/*
 * DbgTraceLevels.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_
#define PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_

class DbgTraceLevel
{
public:

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

  virtual ~DbgTraceLevel() { }

private:
  DbgTraceLevel() { }

  DbgTraceLevel& operator = (const DbgTraceLevel& src); // assignment operator
  DbgTraceLevel(const DbgTraceLevel& src);              // copy constructor
};


#endif /* PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_ */
