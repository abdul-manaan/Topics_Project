# Global Variables!
clear_logcat    = "logcat -c"
save_log_file   = "adb shell logcat *:V -v long > "
clear_app       = "pm clear "
launchApp       = "adb shell monkey -p "
launchApp_1     = " -c android.intent.category.LAUNCHER 1"
closeApp        = "adb shell am force-stop "


# This code just dumps output of a adb shell command
# Requirements: None
def dump_logcat(connection):
    try:
        data = ""
        while True:
            endata = connection.read(1024)
            if not endata:
                break
            data += endata.decode('utf-8')
        connection.close()
        print data
    except Exception as e:
       print data

# Given an app name, it clears app from cache
# Requirements: None
def clearAppFromCache(app,device):
    try:
        device.shell(clear_app + app, handler=dump_logcat, timeout=20)
    except Exception as e:
        print("Error: Can not clear cache!")

# Given a device, it will clear its logcat
# Requirements :None
def clearLog(device):
    try:
        device.shell(clear_logcat)
    except Exception as e:
        print("Error: Can not clear logcat!")

# Given a filename, it will save log of android in that file
# Requirements: subprocess
def save_log(filename):
    try:
        import subprocess
        p = subprocess.Popen(save_log_file + filename, shell=True)
        return p
    except Exception as e:
        print("Error: Can not save log in file!")

# Given an app name and timeout, it will open app and close app after given time.
# Requirements: time and os
def open_app(app,timeout):
   try: 
       import time
       import os
       os.system(launchApp + app + launchApp_1)
       time.sleep(timeout)
       os.system(closeApp + app)
   except Exception as e:
       print("Error: Can not open app!")

# This will just use all logic
# Requirements: adb.client, sys
def main():
    try:
        from adb.client import Client as AdbClient
        import sys
        if len(sys.argv) < 3:
            print("Error: Syntax: Python logger.py filename [cache clear (Y/N)]")
        apps = ["com.android.chrome", "com.yandex.browser", "com.microsoft.emmx", "org.mozilla.firefox"]
        
        client = AdbClient(host="127.0.0.1", port=5037)
        devices = client.devices()
        isCacheClear = sys.argv[2]
        for device in devices:
            if isCacheClear == 'Y': 
                for app in apps:
                    clearAppFromCache(app,device)
            clearLog(device)
            saving_log = save_log(sys.argv[1])
            time = 30
            for i in apps:
                open_app(i,time)
            saving_log.wait()
    except Exception as e:
        print("Error in  main!")

main()
