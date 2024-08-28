#include <string>

#include "format.h"

using std::string;

// done - TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long HH = seconds/3600;
    long MM = (seconds%3600)/60;
    long SS = (seconds%3600)%60;
    return  std::to_string(HH)+":"+std::to_string(MM)+":"+std::to_string(SS);
 }