#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  float ProcessUtilization(int pid);

  float cpu_utilization;

  // TODO: Declare any necessary private members
 private:
};

#endif