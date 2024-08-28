#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::string;
using std::to_string;
using std::vector;

// Create constructor for storing pid values
Process::Process(int p):_pid(p){
    Processor pid_process;
    Process::cpu_utilization = pid_process.ProcessUtilization(_pid);
}

// done - TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    Processor pid_process;
    Process::cpu_utilization = pid_process.ProcessUtilization(_pid);
    return Process::cpu_utilization; 
}

// done - TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(_pid);
}

// done - TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(_pid);
}
// done -TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(_pid);
}

// done - TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(_pid);
}

// done -  TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function

// CPU
bool Process::operator<(Process const& process_x) const {
  return Process::cpu_utilization > process_x.cpu_utilization;
}


// RAM
// bool Process::operator<(Process const& process_x) const { 
//   return stol(LinuxParser::Ram(_pid)) > stol(LinuxParser::Ram(process_x._pid));
// }
