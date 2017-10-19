#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

string GetStdoutFromCommand(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}

bool isRoot(){
    if (getuid() == 0){
        return 1;
    } else {
        return 0;
    }
}

int main (){
    if(!isRoot()){
        cout << "Please use root" << endl;
        return -1;
    }
    string ls = GetStdoutFromCommand("echo 20000 > /sys/fs/cgroup/cpu/10p/cpu.cfs_quota_us");
    //string ls = GetStdoutFromCommand("echo 4673 > /sys/fs/cgroup/cpu/10p/tasks");
    cout << "top -n 3 | grep systemd:\n" << ls << endl;
    return 0;
}
