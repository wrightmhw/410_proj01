#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <errno.h>

using namespace std;

float interval = 1;

/*
 * name:    confirm_exit
 * purpose: gets inputs from the user until the user input Y/y/N/n
 * receive: none
 * return:  true - if Y/y is entered
 *          false - if N/n is entered
 */
bool confirm_exit() {
    string choice;
    cout << "Do you realy want to exit the program? (Y/N)";
    // Ask for inputs until the user enters either Y or N.
    cin >> choice;
    while(true) {
        if(choice == "Y" || choice == "y") {
            return true;
        }
        else if(choice == "N" || choice == "n") {
            return false;
        }
        else {
            cout << "Please enter (Y/N): ";
            cin >> choice;
        }
    }
}

/*
 * name:    split
 * purpose: split a string into a vector of substrings based on delim
 * receive: s - string to be split
 *          delim - the delimiter
 * return:  the result vector of the substrings
 */
vector<string> split(const string &s, char delim) {
    vector<string> elems; // the result vector
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        if(item.length() > 0) {
            elems.push_back(item);
        }
    }
    return elems;
}

/*
 * name:    print_mem_report
 * purpose: print a memory status report to the terminal
 * receive: none
 * return:  none 
 */
void print_mem_report() {
    string line;

    ifstream read_fd;
    string proc_path = "/proc/meminfo";

    string mem_free, active, inactive, dirty, kernel_stack, page_tables;
    string key_mem_free = "MemFree:",
           key_active = "Active:",
           key_inactive = "Inactive:",
           key_dirty = "Dirty:", 
           key_kernel_stack = "KernelStack:",
           key_page_tables = "PageTables:";

    read_fd.open(proc_path.c_str(),  ifstream::in);
    if(read_fd.is_open() == true) {
        cout << "MEMORY STATUS: " << endl;
        while(getline(read_fd, line)) {
            vector<string> line_split= split(line, ' ');
            if(line_split[0] == key_mem_free) {
                line = line.replace(0, key_mem_free.length() + 1, "Mem Free:");
                // Change "MemFree: " to "Mem Free:"
                cout << line << endl;
            }
            else if(line_split[0] == key_active) {
                cout << line << endl;
            }
            else if(line_split[0] == key_inactive) {
                cout << line << endl;
            }
            else if(line_split[0] == key_dirty) {
                cout << line << endl;
            }
            else if(line_split[0] == key_kernel_stack) {
                line = line.replace(0, key_kernel_stack.length() + 1, 
                                    "Kernel Stack:");
                // Change "KernelStack: " to "Kernel Stack:"
                cout << line << endl;
            }
            else if(line_split[0] == key_page_tables) {
                line = line.replace(0, key_page_tables.length() + 1, 
                                    "Page Tables:"); 
                // Change "PageTables: " to "Page Tables:"
                cout << line << endl;
            }
        }
        read_fd.close();
    }   
    else {
        cout << "Opening " << proc_path << " failed with reason" 
             << strerror(errno) << endl;
        cout << "Unable to read memory info in alarm_handler. Program exiting."
             << endl;
        exit(EXIT_FAILURE);
    }
}

/*
 * name:    print_report
 * purpose: print all reports to the terminal
 * receive: none
 * return:  none
 */
void print_report() {
    cout << "The reporter's PID is " << getpid() << endl;
    print_mem_report();
    cout << "The current report interval is " << interval << " second" << endl;
}


/*
 * name:    clear_screen
 * purpose: print a hundred newlines to clear the screen
 * receive: none
 * return:  none
 */
void clear_screen() {
    cout << string(100, '\n');
}

/*
 * name:    sigusr1_handler
 * purpose: handle the SIGUSR1 signal
 * receive: none
 * return:  none
 */
void sigusr1_handler(int signo)
{
  if (signo == SIGUSR1)
  {
    cout << "sigusr1 has been called" <<endl;
    interval = interval / 2;
  }
}

/*
 * name:    sigusr2_handler
 * purpose: handle the SIGUSR2 signal
 * receive: none
 * return:  none
 */
void sigusr2_handler(int signo)
{
  if (signo == SIGUSR2)
  {
    cout << "sigusr2 has been called" << endl;
    interval = interval * 2;
  }
}

/*
 * name:    sigint_handler
 * purpose: handle the SIGINT signal
 * receive: none
 * return:  none
 */
void sigint_handler(int signo)
{
  if (signo == SIGINT)
  {
    cout << "sigint signal" << endl;
    //ask user for confirmation
    if (confirm_exit())
    {
      cout << "Program terminates" << endl;
      exit(1);
    }
    else
    {
      cout << "Program continues" << endl;
    }
  }
}

void alarm_handler(int signo){
  if (signo == SIGALRM){
    cout << "alarm goes off" << endl;
    //alarm(interval);
    }
}
