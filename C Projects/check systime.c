#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main(void)
{
  char *wake_open = "7:0";
  char *sleep_close = "19:30";
 
  time_t rawtime;
  struct tm* time_;
  time(&rawtime);
  time_ = localtime(&rawtime);
  
  int year=time_->tm_year + 1900;
  int month=time_->tm_mon + 1;
  int day=time_->tm_mday;
  int dst= time_->tm_isdst;
  
  printf("Date is %d/%d/%d and DST is %d\n", month,day,year,dst);
 return(0);
 }
