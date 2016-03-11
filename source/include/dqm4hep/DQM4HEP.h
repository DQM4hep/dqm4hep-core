  /// \file DQM4HEP.h
/*
 *
 * DQM4HEP.h header template automatically generated by a class generator
 * Creation date : dim. oct. 5 2014
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQM4HEP_H
#define DQM4HEP_H

// -- std headers
#include <set>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <ctime>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <exception>
#include <limits>
#include <pthread.h>


// apple stuff for stdint.h
#ifdef __APPLE__
#include <_types.h>
#include <_types/_uint8_t.h>
#include <_types/_uint16_t.h>
#include <_types/_uint32_t.h>
#include <_types/_uint64_t.h>
#include <sys/_types/_int16_t.h>
#include <sys/_types/_int64_t.h>
#include <sys/_pthread/_pthread_types.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#else
#include <bits/pthreadtypes.h>
#include <stdint.h>
#endif

// -- dqm4hep headers
#include "DQMCoreConfig.h"

//-------------------------------------------------------------------------------------------------

// bit operations
#define DQM_BIT(n)       (1ULL << (n))
#define DQM_SETBIT(n,i)  ((n) |= DQM_BIT(i))
#define DQM_CLRBIT(n,i)  ((n) &= ~DQM_BIT(i))
#define DQM_TESTBIT(n,i) ((bool)(((n) & DQM_BIT(i)) != 0))

#if defined(__GNUC__) && defined(BACKTRACE)
    #include <cstdlib>
    #include <execinfo.h>
#endif

// limits definitions platform independent
#ifdef _MSC_VER
    #include <float.h>
    #define IS_NAN _isnan
    #define IS_INF !_finite
#else
    #define IS_NAN std::isnan
    #define IS_INF std::isinf
#endif

namespace dqm4hep
{

class DQMMonitorElement;
template <typename T>
class DQMStreamer;
class DQMEvent;
class DQMEventStreamer;
class DQMQualityTest;
class DQMQualityTestResult;
class DQMStatisticsService;
class DQMPath;
struct DQMStats;

//-------------------------------------------------------------------------------------------------

// typedefs for streaming
typedef char                  dqm_char;
typedef uint8_t               dqm_uchar;
typedef int16_t               dqm_short;
typedef uint16_t              dqm_ushort;
typedef int16_t               dqm_short_int;
typedef uint16_t              dqm_ushort_int;
typedef int64_t               dqm_lint;
typedef uint64_t              dqm_ulint;
typedef float                 dqm_real;
typedef float                 dqm_float;
typedef double                dqm_double;
typedef bool                  dqm_bool;
typedef int64_t               dqm_int;
typedef uint64_t              dqm_uint;

// basic typedefs
typedef std::vector<int>            IntVector;
typedef std::vector<unsigned int>   UIntVector;
typedef std::vector<float>          FloatVector;
typedef std::vector<double>         DoubleVector;
typedef std::vector<std::string>    StringVector;
typedef std::set<std::string>       StringSet;

// specifics typedefs
//typedef std::map<std::string, std::vector<std::string> > SubscriptionMap;

typedef std::vector<DQMMonitorElement*> DQMMonitorElementList;
typedef std::map<const std::string, DQMMonitorElement*> DQMMonitorElementMap;

typedef std::queue<DQMEvent*> DQMEventQueue;

typedef std::map<std::string, DQMQualityTestResult> DQMQualityTestResultMap;
typedef std::map<std::string, DQMQualityTest*>      DQMQualityTestMap;

typedef std::vector<DQMStats> DQMStatsList;

// typedef for messaging
typedef std::map<std::string, DQMMonitorElementList> DQMPublication;
typedef std::map<std::string, std::string> DQMMonitorElementInfo;
typedef std::vector<DQMMonitorElementInfo> DQMMonitorElementInfoList;
typedef std::map<std::string, std::string> DQMHostInfo;
typedef std::map<std::string, std::string> DQMMonitorElementListNameRequest;
typedef std::multimap<std::string, std::string> DQMMonitorElementRequest;

}

//-------------------------------------------------------------------------------------------------

#define RETURN_RESULT_IF(StatusCode1, Operator, Command)		\
  {									\
    const dqm4hep::StatusCode statusCode(Command);			\
    if (statusCode Operator StatusCode1)				\
      {									\
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , #Command << " return " << dqm4hep::statusCodeToString(statusCode) ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in function: " << __FUNCTION__ ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in file:     " << __FILE__ << " line#: " << __LINE__ ); \
		  return statusCode;						\
      }									\
  }

//-------------------------------------------------------------------------------------------------

#define RETURN_RESULT_IF_AND_IF(StatusCode1, StatusCode2, Operator, Command) \
  {									\
    const dqm4hep::StatusCode statusCode(Command);			\
    if ((statusCode Operator StatusCode1) && (statusCode Operator StatusCode2))	\
      {									\
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , #Command << " return " << dqm4hep::statusCodeToString(statusCode) ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in function: " << __FUNCTION__ ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in file:     " << __FILE__ << " line#: " << __LINE__ ); \
		  return statusCode;						\
      }									\
  }

//-------------------------------------------------------------------------------------------------

#define THROW_RESULT_IF(StatusCode1, Operator, Command)			\
  {									\
    const dqm4hep::StatusCode statusCode(Command);			\
    if (statusCode Operator StatusCode1)				\
      {									\
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , #Command << " throw " << dqm4hep::statusCodeToString(statusCode) ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in function: " << __FUNCTION__ ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in file:     " << __FILE__ << " line#: " << __LINE__ ); \
	    throw dqm4hep::StatusCodeException(statusCode);			\
      }									\
  }

//-------------------------------------------------------------------------------------------------

#define THROW_RESULT_IF_AND_IF(StatusCode1, StatusCode2, Operator, Command)                     \
  {									\
    const dqm4hep::StatusCode statusCode(Command);			\
    if ((statusCode Operator StatusCode1) && (statusCode Operator StatusCode2))	\
      {									\
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , #Command << " throw " << dqm4hep::statusCodeToString(statusCode) ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in function: " << __FUNCTION__ ); \
		  LOG4CXX_ERROR( dqm4hep::dqmMainLogger , "    in file:     " << __FILE__ << " line#: " << __LINE__ ); \
		  throw dqm4hep::StatusCodeException(statusCode);			\
      }									\
  }

//-------------------------------------------------------------------------------------------------

#define PROCESS_CODE_IF_AND_RETURN(StatusCode1, Operator, Command, Code) \
  {									\
    const dqm4hep::StatusCode statusCode(Command);			\
    if (statusCode Operator StatusCode1)				\
      {									\
    		Code								\
			return statusCode;						\
      }									\
  }

//-------------------------------------------------------------------------------------------------

#define PROCESS_CODE_IF_AND_IF_AND_RETURN(StatusCode1, StatusCode2, Operator, Command, Code) \
  {									\
    const dqm4hep::StatusCode statusCode(Command);			\
    if ((statusCode Operator StatusCode1) && (statusCode Operator StatusCode2))	\
      {									\
    	Code								\
	  return statusCode;						\
      }									\
  }

//-------------------------------------------------------------------------------------------------

#define NOTIFY_METHOD_CALLED \
		LOG4CXX_DEBUG( dqm4hep::dqmMainLogger ,  "Method called : " << __FUNCTION__ );

//-------------------------------------------------------------------------------------------------

#define DQM_PLUGIN_DECL( ClassName , ClassStr ) \
		class DQMPlugin_##ClassName : public dqm4hep::DQMPlugin, public ClassName \
		{ \
		public: \
			DQMPlugin_##ClassName (bool shouldRegister = true) : dqm4hep::DQMPlugin(ClassStr, shouldRegister), ClassName() {} \
			DQMPlugin *create() const { return new DQMPlugin_##ClassName (false) ; } \
		}; \
		DQMPlugin_##ClassName instance_DQMPlugin_##ClassName;

//-------------------------------------------------------------------------------------------------

// macros for enumerators
#define GET_ENUM_ENTRY(a, b)  a,
#define GET_NAME_SWITCH(a, b) case a : return b;
#define GET_STR_COMPARE(a, b) if(str == b) return a;

#define GET_ENUM_ENTRY_2(a, b, c) a,
#define GET_NAME_SWITCH_2(a, b, c) case a : return b;
#define GET_PREFIX_SWITCH_2(a, b, c) case a : return c;
#define GET_STR_COMPARE_1(a, b, c) if(str == b) return a;
#define GET_STR_COMPARE_2(a, b, c) if(str == c) return a;


// definitions of the status code table
#define STATUS_CODE_TABLE(d)                                                                            \
    d(STATUS_CODE_SUCCESS,                  "STATUS_CODE_SUCCESS"                   )                   \
    d(STATUS_CODE_FAILURE,                  "STATUS_CODE_FAILURE"                   )                   \
    d(STATUS_CODE_NOT_FOUND,                "STATUS_CODE_NOT_FOUND"                 )                   \
    d(STATUS_CODE_NOT_INITIALIZED,          "STATUS_CODE_NOT_INITIALIZED"           )                   \
    d(STATUS_CODE_ALREADY_INITIALIZED,      "STATUS_CODE_ALREADY_INITIALIZED"       )                   \
    d(STATUS_CODE_ALREADY_PRESENT,          "STATUS_CODE_ALREADY_PRESENT"           )                   \
    d(STATUS_CODE_OUT_OF_RANGE,             "STATUS_CODE_OUT_OF_RANGE"              )                   \
    d(STATUS_CODE_NOT_ALLOWED,              "STATUS_CODE_NOT_ALLOWED"               )                   \
    d(STATUS_CODE_INVALID_PARAMETER,        "STATUS_CODE_INVALID_PARAMETER"         )                   \
    d(STATUS_CODE_UNCHANGED,                "STATUS_CODE_UNCHANGED"                 )                   \
    d(STATUS_CODE_INVALID_PTR,              "STATUS_CODE_INVALID_PTR"               )

//-------------------------------------------------------------------------------------------------

namespace dqm4hep
{

/** StatusCode enumerator
 */
enum StatusCode
{
	STATUS_CODE_TABLE(GET_ENUM_ENTRY)
	NUMBER_OF_STATUS_CODES
};

std::string statusCodeToString(const StatusCode statusCode);

//-------------------------------------------------------------------------------------------------

/** StatusCodeException class
 */
class StatusCodeException : public std::exception
{
public:

	/** Constructor
		*/
	StatusCodeException(const StatusCode statusCode);

	/** Constructor
		*/
	~StatusCodeException() throw();

	/** Get status code
		*/
	StatusCode getStatusCode() const;

	/** Get status code as a string
		*/
	std::string toString() const;

	/** Get back trace at point of exception construction (gcc only)
		*/
	const std::string &getBackTrace() const;

private:

	const StatusCode    m_statusCode;   ///< The status code
	std::string          m_backTrace;    ///< The back trace
};

//-------------------------------------------------------------------------------------------------

// definitions of the quality table
#define DQM_QUALITY_TABLE(d)                   \
    d(NO_QUALITY,          "NO_QUALITY")        \
    d(VERY_BAD_QUALITY,    "VERY_BAD_QUALITY")  \
    d(BAD_QUALITY,         "BAD_QUALITY")       \
    d(NORMAL_QUALITY,      "NORMAL_QUALITY")    \
    d(GOOD_QUALITY,        "GOOD_QUALITY")      \
    d(VERY_GOOD_QUALITY,   "VERY_GOOD_QUALITY")

/** DQMQuality enum
 */
enum DQMQuality
{
	DQM_QUALITY_TABLE(GET_ENUM_ENTRY)
	NUMBER_OF_DQM_QUALITIES
};

inline std::string qualityToString(const DQMQuality quality)
{
	switch (quality)
	{
		DQM_QUALITY_TABLE(GET_NAME_SWITCH)
		default : throw dqm4hep::StatusCodeException(STATUS_CODE_INVALID_PARAMETER);
	}
}

//-------------------------------------------------------------------------------------------------

/** DQMKey class
 */
class DQMKey
{
public:
	static const std::string    MODULE_NAME;
	static const std::string    DETECTOR_NAME;
	static const std::string    ME_NAME;
	static const std::string    ME_PATH;
	static const std::string    ME_TYPE;
	static const std::string    ME_DESCRIPTION;

	static const std::string    SYSTEM_NAME;
	static const std::string    NODE_NAME;
	static const std::string    RELEASE;
	static const std::string    VERSION;
	static const std::string    MACHINE;
	static const std::string    HOST_NAME;
};

//-------------------------------------------------------------------------------------------------

/** DQM4HEP class.
 *
 *  Definitions and utilities
 */
class DQM4HEP
{
public:
	/** Convert std::string to a type
	 */
	template <class T>
	static bool stringToType(const std::string &s, T &t);

	/** Convert type to std::string
	 */
	template <class T>
	static std::string typeToString(const T &t);

	/** Screen splash of DQM4HEP
	 */
	static void screenSplash();

	/** Tokenize string with delimiter.
	 */
	static void tokenize(const std::string &inputString, StringVector &tokens, const std::string &delimiter = " ");

	/** Return the quality that corresponds to
	 *  a value between 0 and 1
	 */
	static DQMQuality scaleToQuality(float scale);
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template <class T>
inline bool DQM4HEP::stringToType(const std::string &s, T &t)
{
	std::istringstream iss(s);
	return !(iss >> t).fail();
}

//-------------------------------------------------------------------------------------------------

template <class T>
inline std::string DQM4HEP::typeToString(const T &t)
{
	std::ostringstream oss;

	if ((oss << t).fail())
		throw;

	return oss.str();
}

//-------------------------------------------------------------------------------------------------

/** Specialization for booleans
 */
template <>
inline bool DQM4HEP::stringToType(const std::string &s, bool &t)
{
	if(s == "on" || s == "1" || s == "true")
		t = true;
	else if(s == "off" || s == "0" || s == "false")
		t = false;
	else
		return false;

	return true;
}

//-------------------------------------------------------------------------------------------------

inline std::string statusCodeToString(const StatusCode statusCode)
{
	switch (statusCode)
	{
		STATUS_CODE_TABLE(GET_NAME_SWITCH)
		default : throw dqm4hep::StatusCodeException(STATUS_CODE_INVALID_PARAMETER);
	}
}

//-------------------------------------------------------------------------------------------------

// definitions of the state table
#define DQM_STATE_TABLE(d)               \
    d(STOPPED_STATE,    "STOPPED_STATE")  \
    d(RUNNING_STATE,    "RUNNING_STATE")  \
    d(PAUSED_STATE,     "PAUSED_STATE")

/** DQMState enum
 */
enum DQMState
{
	DQM_STATE_TABLE(GET_ENUM_ENTRY)
	NUMBER_OF_DQM_STATES
};

inline std::string stateToString(const DQMState state)
{
 switch (state)
 {
  DQM_STATE_TABLE(GET_NAME_SWITCH)
		default : throw dqm4hep::StatusCodeException(STATUS_CODE_INVALID_PARAMETER);
 }
}

//-------------------------------------------------------------------------------------------------

// definitions of the monitor element type table
#define DQM_MONITOR_ELEMENT_TYPE_TABLE(d)                                \
    d(NO_ELEMENT_TYPE,                 "NO_ELEMENT_TYPE",                 "")                 \
    d(INT_ELEMENT_TYPE,                "INT_ELEMENT_TYPE",                "int")                \
    d(REAL_ELEMENT_TYPE,               "REAL_ELEMENT_TYPE",               "float")\
    d(SHORT_ELEMENT_TYPE,              "SHORT_ELEMENT_TYPE",              "short")\
    d(STRING_ELEMENT_TYPE,             "STRING_ELEMENT_TYPE",             "string")\
    d(INT_HISTOGRAM_1D_ELEMENT_TYPE,   "INT_HISTOGRAM_1D_ELEMENT_TYPE",   "TH1I")\
    d(REAL_HISTOGRAM_1D_ELEMENT_TYPE,  "REAL_HISTOGRAM_1D_ELEMENT_TYPE",  "TH1F")\
    d(SHORT_HISTOGRAM_1D_ELEMENT_TYPE, "SHORT_HISTOGRAM_1D_ELEMENT_TYPE", "TH1S")\
    d(CHAR_HISTOGRAM_1D_ELEMENT_TYPE,  "CHAR_HISTOGRAM_1D_ELEMENT_TYPE",  "TH1C")\
    d(INT_HISTOGRAM_2D_ELEMENT_TYPE,   "INT_HISTOGRAM_2D_ELEMENT_TYPE",   "TH2I")\
    d(REAL_HISTOGRAM_2D_ELEMENT_TYPE,  "REAL_HISTOGRAM_2D_ELEMENT_TYPE",  "TH2F")\
    d(CHAR_HISTOGRAM_2D_ELEMENT_TYPE,  "CHAR_HISTOGRAM_2D_ELEMENT_TYPE",  "TH2C")\
    d(SHORT_HISTOGRAM_2D_ELEMENT_TYPE, "SHORT_HISTOGRAM_2D_ELEMENT_TYPE", "TH2S")\
    d(INT_HISTOGRAM_3D_ELEMENT_TYPE,   "INT_HISTOGRAM_3D_ELEMENT_TYPE",   "TH3I")\
    d(REAL_HISTOGRAM_3D_ELEMENT_TYPE,  "REAL_HISTOGRAM_3D_ELEMENT_TYPE",  "TH3F")\
    d(PROFILE_1D_ELEMENT_TYPE,         "PROFILE_1D_ELEMENT_TYPE",         "TProfile")\
    d(PROFILE_2D_ELEMENT_TYPE,         "PROFILE_2D_ELEMENT_TYPE",         "TProfile2D")\
    d(USER_DEFINED_ELEMENT_TYPE,       "USER_DEFINED_ELEMENT_TYPE",       "user")

/** DQMMonitorElementType enum
 */
enum DQMMonitorElementType
{
	DQM_MONITOR_ELEMENT_TYPE_TABLE(GET_ENUM_ENTRY_2)
	NUMBER_OF_DQM_MONITOR_ELEMENT_TYPES
};

inline std::string monitorElementTypeToString(const DQMMonitorElementType type)
{
	switch (type)
	{
		DQM_MONITOR_ELEMENT_TYPE_TABLE(GET_NAME_SWITCH_2)
		default : throw dqm4hep::StatusCodeException(STATUS_CODE_INVALID_PARAMETER);
	}
}

inline DQMMonitorElementType stringToMonitorElementType(const std::string &str)
{
	DQM_MONITOR_ELEMENT_TYPE_TABLE(GET_STR_COMPARE_1)
	else return NO_ELEMENT_TYPE;
}

inline DQMMonitorElementType stringToMonitorElementRootType(const std::string &str)
{
	DQM_MONITOR_ELEMENT_TYPE_TABLE(GET_STR_COMPARE_2)
	else return NO_ELEMENT_TYPE;
}

//-------------------------------------------------------------------------------------------------

// definitions of the reset policy table
#define DQM_RESET_POLICY_TABLE(d)                              \
    d(NO_RESET_POLICY,           "NoReset")             \
    d(END_OF_CYCLE_RESET_POLICY, "EndOfCycle")   \
    d(END_OF_RUN_RESET_POLICY,   "EndOfRun")

/** DQMResetPolicy enum
 *
 *  Corresponds to the period at
 *  which the element have to be reset. If eNoReset is chosen
 *  then the user can call reset at any time in the processing.
 *  The default one is eResetAtEndOfCycle.
 */
enum DQMResetPolicy
{
	DQM_RESET_POLICY_TABLE(GET_ENUM_ENTRY)
	NUMBER_OF_DQM_RESET_POLICIES
};

inline std::string resetPolicyToString(const DQMResetPolicy policy)
{
 switch (policy)
 {
  DQM_RESET_POLICY_TABLE(GET_NAME_SWITCH)
		default : throw dqm4hep::StatusCodeException(STATUS_CODE_INVALID_PARAMETER);
 }
}

inline DQMResetPolicy stringToResetPolicy(const std::string &str)
{
	DQM_RESET_POLICY_TABLE(GET_STR_COMPARE)
	else return NO_RESET_POLICY;
}

//-------------------------------------------------------------------------------------------------

/** LogLevel enumerator
 */
enum LogLevel
{
	DEBUG = 0,
	MESSAGE,
	WARNING,
	ERROR
};

//-------------------------------------------------------------------------------------------------

/** UpdateMode enumerator
 */
enum UpdateMode
{
	NO_UPDATE = 0,
	REPLACE = 1,
	APPEND = 2
};

//-------------------------------------------------------------------------------------------------

/** Stats struct
 */
struct DQMStats
{
	time_t          m_timeStamp;
	unsigned int    m_statistics;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template <typename T>
class PositiveValidator
{
public:
	static bool validate(const T &t) { return t >= static_cast<T>(0); }
};

//-------------------------------------------------------------------------------------------------

template <typename T>
class NegativeValidator
{
public:
	static bool validate(const T &t) { return t<0; }
};

//-------------------------------------------------------------------------------------------------

template <typename T>
class NonNullValidator
{
public:
	static bool validate(const T &t) { return fabs(static_cast<float>(t) - 0.f) < std::numeric_limits<T>::epsilon(); }
};

//-------------------------------------------------------------------------------------------------

template <typename T>
class IntervalValidator
{
public:
	IntervalValidator(const T &min, const T &max) : m_min(min), m_max(max) {}

	bool validate(const T &t) { return t>m_min && t<m_max; }
private:
	T     m_min;
	T     m_max;
};

//-------------------------------------------------------------------------------------------------

template <typename T>
class BiggerThanValidator
{
public:
	BiggerThanValidator(const T &compare) : m_compare(compare) {}

	bool operator ()(const T &t) const { return t>m_compare; }
private:
	T     m_compare;
};

//-------------------------------------------------------------------------------------------------

template <typename T>
class LessThanValidator
{
public:
	LessThanValidator(const T &compare) : m_compare(compare) {}

	bool operator ()(const T &t) const { return t<m_compare; }
private:
	T     m_compare;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

/** scoped_mutex class
 */
class scoped_lock
{
public:
	/** Constructor that locks the mutex
	 */
	scoped_lock(pthread_mutex_t *pMutex);

	/** Destructor that unlocks the mutex
	 */
	~scoped_lock();
private:
	pthread_mutex_t      *m_pMutex;
};

//-------------------------------------------------------------------------------------------------

/** Print the raw buffer
 */
void printRawBuffer(char *pBuffer, int bufferSize);

}

#endif  //  DQM4HEP_H
