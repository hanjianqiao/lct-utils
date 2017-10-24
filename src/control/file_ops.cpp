#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>

using namespace std;

#define PATH "/sys/fs/cgroup/cpu/20per/"

int main(){
    int ret;
    ofstream myfile;

    cout << "mkdir ";
    ret = mkdir(PATH, 0x00755);
    if(ret){
        cout << "failed: " << ret << endl;
    }else{
        cout << "success" << endl;
    }
    cout << "ret = " << ret << endl;

    cout << "chomod ";
    ret = chmod(PATH,0755);
    if(ret){
        cout << "failed: " << ret << endl;
    }else{
        cout << "success" << endl;
    }
    cout << "ret = " << ret << endl;

    myfile.open("/sys/fs/cgroup/cpu/20per/cpu.cfs_quota_us", ios::app | ios::out);
    if (myfile.is_open())
    {
        myfile << 20000;
        myfile.close();
    }

    myfile.open("/sys/fs/cgroup/cpu/20per/tasks");
    if (myfile.is_open())
    {
        myfile << 6661;
        myfile.close();
    }

    ifstream myinfile (PATH"cpu.cfs_period_us");
    if (myinfile.is_open())
    {
        myinfile >> ret;
        cout << ret << endl;
        myinfile.close();
    }
    else cout << "Unable to open file";

    return 0;
}

