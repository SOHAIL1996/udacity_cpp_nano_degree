#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// done - TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float mem_total, mem_free, buffer, cache;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          mem_total = std::stof(value);
        }
        if (key == "MemFree:") {
          mem_free = std::stof(value);
        }
        if (key == "Buffers:") {
          buffer = std::stof(value);
        }
        if (key == "Cached:") {
          cache = std::stof(value);
        }
      }
    }
  }
  return (mem_total - mem_free - buffer - cache) / mem_total;
}

// done - TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string total_time, cpu_idle_time;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> total_time >> cpu_idle_time;
  }
  return std::stol(total_time);
}

// done - TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long jiffies, val;
  string line, cpu_label;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu_label;
    while (linestream >> val) {
      jiffies += val;
    };
  }
  return jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffiesP(int pid) {
  string line, value;
  long utime, stime, cutime, cstime;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    vector<string> values;
    while (linestream >> value) {
      values.push_back(value);
    }
    if (values.size() > 21) {
      utime = stol(values[13]);  // 14th value: utime
      stime = stol(values[14]);  // 15th value: stime
      cutime = stol(values[15]); // 16th value: cutime
      cstime = stol(values[16]); // 17th value: cstime
      return utime + stime + cutime + cstime;
    }
  }
  return 0;
}

// done -  TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long active_jiffies, user, nice, system, idle, iowait, irq, softirq, steal;
   
  string line, cpu_label;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu_label;

    linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    active_jiffies = user + nice + system + irq + softirq + steal;
  }
  return active_jiffies;
}

// done - TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long idle_jiffies = 0, idle, iowait;
  string line, cpu_label;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu_label;
    linestream >> idle >> iowait;
    idle_jiffies = idle + iowait;
  }
  return idle_jiffies;
}

// done - TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line, value;
  vector<string> cpu_values;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      if (value != "cpu") {
        cpu_values.push_back(value);
      }
    }
  }
  return cpu_values;
}

// done - TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

// done - TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

// done - TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line, full_cmd_line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      full_cmd_line += line;
    };
  }
  return full_cmd_line;
}

// done - TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  int ram = 0;
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmRSS:") {  // VmRss gives actual real ram usage
          ram = std::stoi(value) / 1000;
        }
      }
    }
    return std::to_string(ram);
  }
  return string();
}

// done - TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  int uid;
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {  // VmRss gives actual real ram usage
          uid = std::stoi(value);
        }
      }
    }
    return std::to_string(uid);
  }
  return string();
}

// done - TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = LinuxParser::Uid(pid);
  string line, key, value, user, x, uid_str;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      std::getline(linestream, user, ':');
      std::getline(linestream, x, ':');
      std::getline(linestream, uid_str, ':');
      if (uid == uid_str) {
        return user;
      }
    }
  }
  return string();
}

// done - TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) {
  string line;
  long starttime = 0;
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    vector<string> values;
    string value;
    
    while (linestream >> value) {
      values.push_back(value);
    }

    if (values.size() > 21) {
      starttime = stol(values[21]);  
    }
  }

  long system_uptime = LinuxParser::UpTime();
  long hertz = sysconf(_SC_CLK_TCK); 
  
  return system_uptime - (starttime / hertz);
}

long LinuxParser::StartTime(int pid) {
  string line, value;
  long starttime = 0;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    vector<string> values;
    while (linestream >> value) {
      values.push_back(value);
    }
    if (values.size() > 21) {
      starttime = stol(values[21]);  // 22nd value: starttime
    }
  }
  return starttime;
}

long LinuxParser::Hertz() {
  return sysconf(_SC_CLK_TCK);
}
