#include<iostream>
#include<string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <cstdlib>
using namespace std;

vector<char*> parse(char *args[], int n){
    vector<char*> ans;
    for(int i=1;i < n;i++){
        cout << args[i] << " ";
        ans.push_back(args[i]);
    }
    cout << endl;
    return ans;
}

int main(int argc, char *argv[]){
    if(argc < 1) cout << "enter command properly" << endl;
    else if(argc == 1) cout << "enter followup command" << endl;
    else if(argc >= 2){
        vector<char*> command = parse(argv, argc);
        command.push_back(nullptr);

        // execvp(command[0], command.data()); // cannot get pid like this -> need to fork and get the child pid
        // perror("execvp failed");
        pid_t pid = fork();

        if(pid == 0){
            execvp(command[0], command.data());
            perror("execvp failed");
            _exit(1);
        } else if(pid > 0){
            cout << "Started child process with PID: " << pid << endl;
            // int status;
            // waitpid(pid, &status, 0);
            while(true){
                // string path = "/proc" + to_string(pid) + "/status";
                // ifstream file;
                // string line;

                // file.open(path);
                // if(!file.is_open()){
                //     cerr << "cannot open file" << endl;
                //     return 0;
                // }

                // while(getline(file, line)){
                //     if(line.find("VmRSS:") == 0){
                //         cout << "PID: " << pid << " Memory usage: "
                //     }
                // }

                string cmd = "./log.sh " + to_string(pid) + " >> cpu_pulse_log.txt";
                int ret = system(cmd.c_str());
                if (ret != 0) {
                    cerr << "Script failed or process ended" << endl;
                }

                int status;
                pid_t result = waitpid(pid, &status, WNOHANG);
                if (result == 0)sleep(1);
                else break;
            }
            cout << "Child exited" << endl;
        } else {
            perror("fork failed");
            return 0;
        }
        
    }
    return 0;
}