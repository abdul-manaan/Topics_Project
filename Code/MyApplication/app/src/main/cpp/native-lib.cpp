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
using namespace std;
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject instance,
        jint oom,
        jint mem,
        string fname,
        jint session) {
    std::string hello = "Hello C++";
    setuid(0);
    nice(oom);
    char *process_name="org.chromium.chrome";
    int id;
    pid_t pid = -1;
    DIR* dir;
    FILE *fp;
    char filename[32];
    char cmdline[256];

    struct dirent * entry;


    if (process_name == NULL)
        pid= -1;

    dir = opendir("/proc");
    if (dir == NULL)
        pid= -1;

    while((entry = readdir(dir)) != NULL) {
        id = atoi(entry->d_name);
        if (id != 0) {
            sprintf(filename, "/proc/%d/cmdline", id);
            fp = fopen(filename, "r");
            if (fp) {
                fgets(cmdline, sizeof(cmdline), fp);
                fclose(fp);

                if (strcmp(process_name, cmdline) == 0) {
                    /* process found */
                    pid = id;
                    break;
                }
            }
        }
    }

    closedir(dir);



    vector<string> s;

    FILE* file;
    file = fopen((std::string("/sdcard/")+fname).c_str(), "wb");

    int timer = 0;
    if (file != NULL)
    {
        int i =0;
        while(timer < session) {
            i++;
            if(i < mem){
                string sstr(1024*1024, ' ');
                s.push_back(sstr);
            } else {
                timer++;
            }
            int tSize = 0, resident = 0, share = 0;
            int tSize1 = 0, resident1 = 0, share1 = 0;
            ifstream buffer("/proc/self/statm");
            buffer >> tSize >> resident >> share;
            buffer.close();
            const char * pid_char=to_string(id).c_str();
            char proc_chrome_dir[1024]="/proc/";
            strcat(proc_chrome_dir,pid_char);
            strcat(proc_chrome_dir,"/statm");
            ifstream buffer1(proc_chrome_dir);
            buffer1 >> tSize1 >> resident1 >> share1;
            buffer1.close();

            long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
//            __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "Page Size %d",sysconf(_SC_PAGE_SIZE) );
            double self_rss = resident * page_size_kb;

            double self_shared_mem = share * page_size_kb;

            double chrome_rss = resident1 * page_size_kb;

            double chrome_shared_mem = share1 * page_size_kb;

            __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "index: %d \t Self_PSS: %f \t Chrome_PSS: %f",i,(self_rss - self_shared_mem), (chrome_rss - chrome_shared_mem));
            fprintf(file, "%d,%f,%f\n",i,(self_rss - self_shared_mem), (chrome_rss - chrome_shared_mem));
            if (timer > 0){
                sleep(1);
            }
        }
        fflush(file);
        fclose(file);

    } else {
        __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "File error! Can't Open File");

    }

    return env->NewStringUTF(hello.c_str());
}
