// debug.h
// created 23.09.2013
// updated 30.09.2013
// updated 01.2017

#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <sstream>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
using sstr = std::stringstream;


#define DEBUG_ON
#ifdef DEBUG_ON

//If DEBUG_ON, preprocessor will replace all following debugging macros in
//source code regardless debug level so you can change level during runtime.
//If you want to do so, debug_level must be changed within DBG() or D() macro!
//For example in your main function paste: DBG( debug_level=50 )
//You can check it for example with this macro: DP(50, "checking debugging")

	template <typename T>
	sstr& glue(sstr& ss, T t) { ss << t; return ss; }
	template<typename T, typename... Args>
	sstr& glue(sstr& ss, T t, Args... args) {
		ss << t;
		return glue(ss, args...);
	}

	#define DEFAULT_DEBUG_LEVEL 100

	// default debug output is set to standard output
	// output may be changed during runtime, e.g.: DBG( debug_output = &file_stream);
	static std::ostream *debug_output = &cout;

	// higher level = more debugging info
	static int debug_level = DEFAULT_DEBUG_LEVEL;

	// execute expr if debug_level is high enough
	// in other words smaller value of dbg_level - more important info
	#define D(dbg_level,expr) \
		do { if( (dbg_level) <= debug_level) {(expr)} } while(0)
	#define DBG(expr) do { (expr) } while(0)

	// debug print functions
	template <typename... Args>
	void PR( int dbg_level, Args...args ) {
		if( dbg_level <= debug_level ) {
			sstr ss;
			glue(ss, args...);
			*debug_output << "[DEBUG]" << ss.str() << endl;
		}
	}
	template <typename... Args>
	void DPR(Args...args) { PR(debug_level, args...); }

	// debug - trace variable macros
	#define TRC(dbg_level,var) \
		do { if( (dbg_level) <= debug_level ) { \
			(*debug_output) << "[DBG_TRC" << (dbg_level) << "]" << #var <<"="<< (var) \
			<< endl; } } while(0)
	#define DTRC(var) do { if( 0 <= debug_level ) { \
		(*debug_output) << "[DBG_TRC0]" << #var <<"="<< (var) << endl; } while (0)

	inline void FAIL(const char* x, const char* file, int line) {
		*debug_output << "FAIL '" << x << "' in '" << file << ":" << line << "'"
			<< endl;
		abort();
	}
	// assertions
	#define ASSERT(x) ( (void) ( (x) || ( FAIL(#x,__FILE__,__LINE__), 1 ) ) )

#else // no debug
	#define D(a,b)
	#define DBG(b)
	inline void PR(int a, const string &b) {}
	inline void DPR(const string &b) {}
	#define TRC(a,b)
	#define DTRC(b)
	inline void FAIL(const char* x, const char* f, const char* l){}
	#define ASSERT(x) (void)sizeof(x);
#endif //DEBUG_ON

#endif //DEBUG_H

