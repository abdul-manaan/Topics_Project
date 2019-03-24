#include <jni.h>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <android/log.h>
#include <iostream>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <map>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>
using namespace std;


vector<string> splitStr(string line);
map<string,long long> readInput(string fileName);
int getNum(string s);
map<string,long long>  doSegment(string sentence);
string execShell(const char* cmd);
int getPidof(string appName);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject instance,
        jint oom,
        jint mem,
        jstring fname_ ,
        jint session,
        jstring appName_) {


    const char *fname = (*env).GetStringUTFChars(fname_,0);
    (*env).ReleaseStringUTFChars( fname_, fname);

    const char *appName = (*env).GetStringUTFChars(appName_,0);
    (*env).ReleaseStringUTFChars( appName_, appName);



    std::string hello = "Hello C++";
    setuid(0);
    nice(oom);
    auto process_name=appName;
    int id;
    pid_t pid = -1;
    DIR* dir;
    FILE *fp;
    char filename[32];
    char cmdline[256];

    struct dirent * entry;

    pid = getPidof(appName);
    __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "File error! Can't Open File %s %d", appName, pid);




    vector<string> s;

    FILE* file;
    string xx = "/sdcard/";
    string yy = fname;
    string fileName = xx+yy;
    file = fopen(fileName.c_str(), "wb");

    int timer = 0;
    if (file != NULL)
    {
        auto meminfoTable = readInput("/proc/meminfo");
        string command_dumpsys = "/proc/" + to_string(getpid()) + "/smaps";
        string app_dumpsys = "/proc/" + to_string(pid)+"/smaps";
        auto dumpsysTable    = doSegment(command_dumpsys.c_str());
        auto appDumpsysTable = doSegment(app_dumpsys.c_str());


        int i =0;
        fprintf(file,"index,TotalSize,Resident,Shared,App_TotalSize,App_Resident,App_Shared");
//
        for (auto const& x : dumpsysTable){
            fprintf( file, ",%s", x.first.c_str() );
        }

        for (auto const& x : appDumpsysTable){
            fprintf( file, ",%s", ("App_" + x.first).c_str() );
        }

        for (auto const& x : meminfoTable){
            fprintf( file, ",%s", x.first.c_str() );
        }
        fprintf(file,"\n");
        auto command = "su -c \"echo " + to_string(oom) + " > /proc/"+(to_string(getpid()))+"/oom_adj\" ";
        auto command2 = "su -c \"chmod " + to_string(444) + " /proc/"+(to_string(getpid()))+"/oom_adj\" ";
        system(command.c_str());
        system(command2.c_str());

        while(timer < session) {
            if(timer%50 == 0)
                pid = max(pid,getPidof(appName));
//            nice(oom);
//            auto command = "su -c \"echo " + to_string(oom) + " > /proc/"+(to_string(getpid()))+"/oom_adj\" ";
//            system(command.c_str());
            ofstream myfile;
            myfile.open ("/proc/"+(to_string(getpid())) + "/oom_adj");
            myfile << oom;
            myfile.close();
            i++;
            int x = 0;
            while((dumpsysTable["Pss"]/1024) + x < mem){
                string sstr(1024*1024*50, ' ');
                s.push_back(sstr);
                x += 50;
            }
            timer++;

            long long cur_process[5];
            long long given_app[5];
            ifstream buffer("/proc/self/statm");
            buffer >> cur_process[0] >> cur_process[1] >> cur_process[2];
            buffer.close();

            const char * pid_char=to_string(pid).c_str();
            char proc_chrome_dir[1024]="/proc/";
            strcat(proc_chrome_dir,pid_char);
            strcat(proc_chrome_dir,"/statm");
            ifstream buffer1(proc_chrome_dir);
            buffer1 >> given_app[0] >> given_app[1] >> given_app[2];
            buffer1.close();

            long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
//            __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "Page Size %d",sysconf(_SC_PAGE_SIZE) );

            meminfoTable = readInput("/proc/meminfo");
            app_dumpsys = "/proc/" + to_string(pid)+"/smaps";
            dumpsysTable    = doSegment(command_dumpsys.c_str());
            appDumpsysTable = doSegment(app_dumpsys.c_str());

//            __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "index: %d \t Self_PSS: %f \t Chrome_PSS: %f",i,(self_rss - self_shared_mem), (chrome_rss - chrome_shared_mem));

            fprintf(file, "%d,%d,%d,%d,%d,%d,%d",i,cur_process[0],cur_process[1],cur_process[2],given_app[0],given_app[1],given_app[2]);

            for (auto const& x : dumpsysTable){
                fprintf( file, ",%s" , to_string(x.second).c_str() );
            }
            for (auto const& x : appDumpsysTable){
                fprintf( file, ",%s" , to_string(x.second).c_str() );
            }

            for (auto const& x : meminfoTable){
                fprintf( file, ",%s" , to_string(x.second).c_str() );
            }
            fprintf(file,"\n");


            if (timer > 0){
                sleep(1);
            }
        }
        fflush(file);
        fclose(file);

    } else {
        __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "File error! Can't Open File");

    }
    ifstream buf(fileName.c_str());
    string ss;
    while(buf >> ss){
        __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s %s",ss.c_str(),("/proc/"+(to_string(getpid())) + "/oom_adj").c_str());

    }
    return env->NewStringUTF(hello.c_str());
}

int getNum(string s){
    for (unsigned int i = 0; i < s.length(); ++i)
    {
        if (isdigit(s[i]))
        {
            return stoi(s.substr(i));
        }
    }
    cout << "Error in Node Num" << endl;
    return -1;
}


map<string,long long> readInput(string fileName){

    ifstream file;
    file.open(fileName.c_str());
    map<string,long long> allData;
    if (!file) {
        __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "File error! Can't Open File smaps");
        return allData;
//        exit(1);   // call system to stop
    }

    string s;
    while(getline(file,s)) {
        auto str = splitStr(s);
        allData[str[0]] = getNum(str[1]);
    }
    return allData;
}

vector<string> splitStr(string line){
    int n = line.length();
    int start = 0;
    vector<string> result;
    for (int i = 0; i < n; ++i) {
        if( !isalnum(line[i]) && line[i] != '_' ) {
            if(i > start) {
                result.push_back(line.substr(start, i-start));
            }
            start = i+1;

        }
    }
    if(start < n) {
        result.push_back(line.substr(start,n-start));
    }
    return result;
}

int getPidof(string appName) {
    //ps -aux "com.android.chrome" | grep com
    string filen = "su -c \"ps -aux " + appName + " | grep " + appName + " > /sdcard/temo.txt\" ";
    system(filen.c_str());
    ifstream file;
    file.open("/sdcard/temo.txt");
    if (!file) {
        __android_log_print(ANDROID_LOG_ERROR , "TRACKERS" , "File error! Can't Open File ");
        return -1;
    }
    string s;
    int ans;
    file >> s >> ans;
    __android_log_print(ANDROID_LOG_ERROR , "TRACKERS" , "File error! Can't Open File %s" ,s.c_str());
    file.close();
    return ans;
}

map<string,long long>  doSegment(string fileName)
{
    string filen = "su -c \"cat " +  fileName + " > /sdcard/tempo.txt\" ";
    system(filen.c_str());
    ifstream file;
    map<string,long long> allData;
    file.open("/sdcard/tempo.txt");
    if (!file) {
        __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "e %s",fileName.c_str());
        return allData;
    }

    string ss;

    allData["Rss"] = 0;
    allData["Pss"] = 0;
    allData["Shared_Clean"] = 0;
    allData["Shared_Dirty"] = 0;
    allData["Private_Clean"] = 0;
    allData["Private_Dirty"] = 0;
    allData["Referenced"] = 0;
    allData["Anonymous"] = 0;
    allData["AnonHugePages"] = 0;
    allData["Swap"] = 0;
    allData["SwapPss"] = 0;
    allData["KernelPageSize"] = 0;
    allData["MMUPageSize"] = 0;
    allData["Locked"] = 0;

    while(getline(file,ss)){
        auto xs = splitStr(ss);
        if (xs[0] == "Pss" ||
            xs[0] == "Rss" ||
            xs[0] == "Shared_Clean" ||
            xs[0] == "Shared_Dirty" ||
            xs[0] == "Private_Clean" ||
            xs[0] == "Private_Dirty" ||
            xs[0] == "Referenced" ||
            xs[0] == "Anonymous" ||
            xs[0] == "AnonHugePages" ||
            xs[0] == "Swap" ||
            xs[0] == "SwapPss" ||
            xs[0] == "KernelPageSize" ||
            xs[0] == "MMUPageSize" ||
            xs[0] == "Locked"){
            allData[xs[0]] += stoll(xs[1]);
        }
    }
    return allData;
}