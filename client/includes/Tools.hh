#ifndef TOOLS_HH_
# define TOOLS_HH_

# include <iostream>
# include <boost/cstdint.hpp>

class SelfUtils {
public:
	static uint32_t secondsSinceEpoch();
	static std::string* getActiveWindowTitle();
	static uint16_t getActiveWindowPID();
};

#endif /* !TOOLS_HH_ */
