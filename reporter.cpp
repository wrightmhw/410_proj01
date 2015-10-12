#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>

#include "reporter.h"

using namespace std;


int main(int argc, char** argv) {
  interval = 1; // in seconds
  // Give PID and basic information
  cout << "The reporter program's PID is " << getpid() << endl;
  cout << "The default report interval is " << interval << endl;


  struct sigaction s1;
  s1.sa_handler = sigusr1_handler;

  struct sigaction s2;
  s2.sa_handler = sigusr2_handler;

  struct sigaction sa;
  sa.sa_handler = alarm_handler;

  if (sigaction(SIGALRM, &sa, NULL) == -1)
  {
    cout << "failed to register alarm handler" << endl;
    exit(EXIT_FAILURE);
  }

  if (sigaction(SIGUSR1, &s1, NULL) == -1)
  {
    cout << "failed to register user1 handler" << endl;
    exit(EXIT_FAILURE);
  }

  if (sigaction(SIGUSR2, &s2, NULL) == -1)
  {
    cout << "failed to register user2 handler" << endl;
    exit(EXIT_FAILURE);
  }

//  alarm(2);
  while (1){
    if (interval >=  1){

      alarm(interval);
    }
   else{
      ualarm(interval * 1000000, 0);
    }
    print_mem_report();
    sleep (1);
  
  }

}

