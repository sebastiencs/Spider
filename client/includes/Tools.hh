#ifndef TOOLS_HH_
# define TOOLS_HH_

# include <iostream>
# include <boost/cstdint.hpp>

class SelfUtils {
public:
	static uint32_t secondsSinceEpoch();
	static std::string* getActiveWindowTitle();
	static uint16_t getActiveWindowPID();
	static std::string* getNameFromPID(uint16_t pid);
	static std::string* getCleanName(const std::string& fullName);
};

#endif /* !TOOLS_HH_ */
