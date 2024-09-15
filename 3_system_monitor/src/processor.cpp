#include "processor.h"
#include "linux_parser.h"

// done - TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  long active_jiffies = LinuxParser::ActiveJiffies(); // Total active jiffies
  long total_jiffies = LinuxParser::Jiffies();        // Total jiffies
  
  if (total_jiffies == 0) {
    return 0.0;
  }

  return static_cast<float>(active_jiffies) / total_jiffies;
}

// Add for separate processes
float Processor::ProcessUtilization(int pid) {
  long active_jiffies = LinuxParser::ActiveJiffiesP(pid);
  long system_uptime = LinuxParser::UpTime();
  long starttime = LinuxParser::StartTime(pid);
  long hertz = LinuxParser::Hertz();

  long total_time = active_jiffies / hertz;
  long elapsed_time = system_uptime - (starttime / hertz);

  if (elapsed_time == 0) {
    return 0.0;
  }

  return static_cast<float>(total_time) / elapsed_time;
}