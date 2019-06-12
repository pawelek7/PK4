#ifndef debug_hpp
#define debug_hpp

//debug messages

#define DEBUG_BUILD

#ifndef DEBUG_BUILD
	#include <iostream>
	#define DEBUG(msg) do {std::cerr << msg; } while (0)
	#define DEBUG_IF(cond, msg) do {if (cond) std::cerr << msg;} while (0)
#else
	#define DEBUG (msg) do { } while (0)
	#define DEBUG_IF(cond, msg) do { } while(0)
#endif // !DEBUG_BUILD


#endif // !debug_hpp