#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <fcntl.h>
#include <cstring>
#include <cmath>
#include <cmath>
#include <sstream>
#include <unistd.h>
#include <string>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::strlen;
using std::strcat;





std::string get_current_directory(){
    char buf[PATH_MAX+1];
    getcwd(buf, sizeof(buf));
    return std::string(buf);
}


void helpMcd(){
    std::cout <<">Afther you writhe Mcd.\n>Please write yor Path with /mnt/c/...(linux notation).\n>If name of Path will be incorrect then No such file in directory.\n>And exit process.\n>Or you can -h/--help for help"<< std::endl;
}

void helpMpwd(){
    std::cout <<">Afther you writhe Mpwd.\n>You will see your curent directory."<< std::endl;

}

void helpMexit(){
    std::cout <<">Afther you writhe Mpwd.\n"
            ">Please write : \n"
            ">>>mexit number\n"
            ">>>mexit -h for more information.\n"
            ">>>mexit --help"<< std::endl;

}

void change_directory(const char *dirPATH){
    int erno1 = chdir(dirPATH);
    if (erno1 == -1){
        //std::cout <<"No such file in directory."<< std::endl;
		perror("Error");
        //exit(erno1);
    }

}


void ToDoFunctionInTheseDirectory(vector<std::string> dataFromConsol){

                int args_n = dataFromConsol.size();

                char **args = static_cast<char**>(
                        malloc( (args_n + 1) * sizeof(char*)));

                //args[0] = arg1;
                for(int i = 0; i<dataFromConsol.size();i++){
                    args[i] = (char *) dataFromConsol[i].c_str();
                }

                string victim_name(args[0]);



                pid_t parent = getpid();
                pid_t pid = fork();


                if (pid == -1)
                {
                    std::cerr << "Failed to fork()" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else if (pid > 0)
                {
                    // We are parent process
                    int status;
                    waitpid(pid, &status, 0);
                    //cout << "Parent: child stopped, exit code: " << status << endl;
                }
                else
                {
                    //const char *cstr = mainDirectory.c_str();
                    //change_directory((char *) cstr);
                    //std::cout <<get_current_directory()<< std::endl;
                    //std::cout<<victim_name<<std::endl;
                    execvpe(victim_name.c_str(), args, environ);

                    //const char *cstr2 = thisDirectory.c_str();
                    //change_directory((char *) cstr2);

                    cerr << "Parent: Failed to execute " << victim_name << " \n\tCode: " << errno << endl;
                    exit(EXIT_FAILURE);   // exec never returns

                }
}









bool ExitProcess(std::string Exit){

    if (Exit == "mexit"){
        return false;
    }
    else{
        return true;
    }
}

std::vector<std::string> split_cmd_line(std::istream& is) {
    std::string commandline;
    std::vector<std::string> parsed_command;
    std::getline(is, commandline);
    std::stringstream ss(commandline);
    std::string word;
    while (ss >> word) {
        parsed_command.push_back(word);
    }
    return parsed_command;
}

int main(int argc, char *argv[]) {
    int error = 0;
    //auto path_ptr = getenv("PATH");// Your Path is
    std::string mainDirectory = get_current_directory();
    std::string word;
    int MyeroNumber = 0;
    std::string argument;
    bool ExitKey = true;
    std::string thisDirectory;

    while (ExitKey) {
        std::cout << "\n>>> ";
        auto dataFromConsol = split_cmd_line(std::cin);



            if (1 < dataFromConsol.size() && dataFromConsol[0] == "mexit" &&
                (dataFromConsol[1] == "-h" || dataFromConsol[1] == "--help")) {
                helpMexit();
            } else if (1 < dataFromConsol.size() && dataFromConsol[0] == "mexit") {
                MyeroNumber = std::stoi(dataFromConsol[1]);
                ExitKey = ExitProcess(dataFromConsol[0]);
                if(dataFromConsol.size() != 2){
                    error = 1;
                }
            } else if (1 == dataFromConsol.size() && dataFromConsol[0] == "mexit") {
                MyeroNumber = 0;
                ExitKey = ExitProcess(dataFromConsol[0]);
            } else if (1 < dataFromConsol.size() && dataFromConsol[0] == "mcd" &&
                       (dataFromConsol[1] == "-h" || dataFromConsol[1] == "--help")) {
                helpMcd();
            } else if (1 < dataFromConsol.size() && dataFromConsol[0] == "mcd") {
                const char *cstr = dataFromConsol[1].c_str();
                change_directory((char *) cstr);
                thisDirectory = get_current_directory();

                if(dataFromConsol.size() != 2){
                    error = 1;
                }
            } else if (1 < dataFromConsol.size() && dataFromConsol[0] == "mpwd" &&
                       (dataFromConsol[1] == "-h" || dataFromConsol[1] == "--help")) {
                helpMpwd();
            } else if (dataFromConsol[0] == "mpwd") {
                std::cout << get_current_directory() << std::endl;

            } else if(dataFromConsol[0] == "merrno") {
                std::cout << error << std::endl;

            } else if (dataFromConsol[0] == "./mycat") {
                if(dataFromConsol.size() != 2){
                    error = 1;
                }
                int args_n = 0;
                //char arg1[] = "mycat.exe";
                if(1 < dataFromConsol.size()) {
                    args_n = 2;
                } else if(2 < dataFromConsol.size()){
                    args_n = 3;
                }

                
                char **args = static_cast<char**>(
                        malloc( (args_n + 1) * sizeof(char*)));

                //args[0] = arg1;
                for(int i = 0; i<dataFromConsol.size();i++){
                    args[i] = (char *) dataFromConsol[i].c_str();
                }
                
                string victim_name("./mycat.exe");





                pid_t parent = getpid();
                pid_t pid = fork();


                if (pid == -1)
                {
                    std::cerr << "Failed to fork()" << std::endl;
                    exit(EXIT_FAILURE);
                }
                else if (pid > 0)
                {
                    // We are parent process
                    int status;
                    waitpid(pid, &status, 0);
                    //cout << "Parent: child stopped, exit code: " << status << endl;
                }
                else
                {
                    const char *cstr = mainDirectory.c_str();
                    change_directory((char *) cstr);
                    //std::cout <<get_current_directory()<< std::endl;
                    execvpe(victim_name.c_str(), args, environ);

                    const char *cstr2 = thisDirectory.c_str();
                    change_directory((char *) cstr2);

                    cerr << "Parent: Failed to execute " << victim_name << " \n\tCode: " << errno << endl;
                    exit(EXIT_FAILURE);   // exec never returns
                }
            }
            //else if(dataFromConsol[0].substr(0, 2) == "./" && dataFromConsol[0] != "./mycat" ){
            else {
                //std::cout<<dataFromConsol[0]<<std::endl;
                //dataFromConsol[0] = dataFromConsol[0] + ".exe";
                //cout << "Executing " << dataFromConsol[0] << endl;
                ToDoFunctionInTheseDirectory(dataFromConsol);
            }
        }

    exit(MyeroNumber);
}







