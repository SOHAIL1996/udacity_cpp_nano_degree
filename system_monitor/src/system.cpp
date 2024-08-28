#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// done - TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    vector<int> all_pids = LinuxParser::Pids();  // Get all PIDs
    processes_.clear();  

    for (int pid : all_pids) {
        // Check if the process directoryy exists
        if (access((LinuxParser::kProcDirectory + std::to_string(pid)).c_str(), F_OK) != -1) {
            Process current_pid(pid); 
            processes_.push_back(current_pid);  
        }
    }

    // Sort processes based on the overloaded < operator 
    std::sort(processes_.begin(), processes_.end());
    return processes_;
}

// done - TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    return LinuxParser::Kernel();
}

// done - TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
}

// done - TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();
}

// done - TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses();
 }

// done - TODO: Return the total number of processes on the system
int System::TotalProcesses() {     
    return LinuxParser::TotalProcesses();
 }

// done -TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime();
}