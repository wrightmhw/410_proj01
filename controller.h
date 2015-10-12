#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

using namespace std;
pid_t target_pid;


float interval = 1;                  // seconds
const float MIN_INTERVAL = 0.0625;   // 1/16 second
const float MAX_INTERVAL = 16;       // seconds


/* 
 * name:    print_menu
 * purpose: prints the menu of this program
 * receive: none
 * return:  none
 */
void print_menu() {
    cout << string(10, '\n');
    cout << "The following options are available:" << endl;
    cout << "(d) Double the speed of reporting." << endl;
    cout << "(h) Halve the speed of reporting." << endl;
    cout << "(q) Quit by killing the reporter program and exiting the controller." 
         << endl;
    cout << "Please enter your choice:" << endl;
}

/*
 * name:    get_input
 * purpose: gets input from the user
 * receive: none
 * return:  the choice selected by the user
 */
string get_input() {
    string choice;
    while(true) {
        cin >> choice;
        if(choice == "D" || choice == "d" ||
           choice == "H" || choice == "h" ||
           choice == "Q" || choice == "q") {
            return choice;
        }
        else {
            cout << "Invalid option. Please enter d, h or q" << endl;
            print_menu();
        }
    }
}


/*
 * name:    parse_argv
 * purpose: parse the parameters
 * receive: the arguments argv and argc
 * return:  true if the arguments are valid, false otherwise.
 *          there is only one argument, the target reporter process's PID
 */
bool parse_argv(int argc, char* argv[])
{
    char *endptr; // for strtol

    if(argc != 2) {
        return false;
    }

    target_pid = strtol(argv[1], &endptr, 0);
    if(*endptr || target_pid <= 0) { // Invalid interval value
                                   // it must be a positive int
        cerr << "Invalid PID. "; 
        if(target_pid <= 0) {
            cout << "The interval must be a positive value.";
        }
        cout << endl;
        return false;
    }

    return true;
}

/*
 * name:    help_message
 * purpose: prints the useage of this program
 * receive: none
 * return:  none
 */
void help_message(char** argv) {
    cout << endl;
    cout << "The program " << argv[0] << " controls another reporter program."
         << endl;
    cout << endl;
    cout << "Usage: " << argv[0] << " target_PID" << endl;
}


/*
 * name:    print_ret_error
 * purpose: prints the ret error message
 * receive: the ret value of kill()
 * return:  none
 */
void print_ret_error(int ret) {
    cout << "kill() failed with reason: " << strerror(errno) << endl;
}
