# Given two strings, it will parse them as time in format => HH:MM:SS.mmm
def get_time_difference(t1,t2):
    try:
            t1s = t1.split(':')
            t2s = t2.split(":")

            hrs = float (t2s[0]) -  float(t1s[0]) 
            mins = float (t2s[1]) -  float(t1s[1])
            secs = float (t2s[2]) -  float(t1s[2])

            ans = hrs*3600+mins*60+secs
            return ans
    except Exception as e:
        print('Error in conversion of string to time')
        print(e)
'''  Abrar COde 
def find_app_record(apps):
	for app in apps:
		main_dict[app] = {}

	with open(filename) as fin:
		all_data = fin.read().split('\n')
		length = len(all_data)

		for app in apps:
			print "====> ", app
			i = 0
			while i<length:
				# print i
				process_killed = 0
				if "Activity_launch_request" in all_data[i] and app in all_data[i]:
					launch_request_time = all_data[i].split()[1]

					while (not (app in all_data[i] and "ActivityManager: Displayed" in all_data[i])) and i<length:
						if "ActivityManager: Killing" in all_data[i]:
							process_killed += 1
						i += 1

					if app in all_data[i] and "ActivityManager: Displayed" in all_data[i]:
						launch_display_time = all_data[i].split()[1]
						launch_time = get_time_difference(launch_request_time,launch_display_time)

						if "launch_time" not in main_dict[app]:
							main_dict[app]["launch_time"] = launch_time
						if "process_killed" not in main_dict[app]:
							main_dict[app]["process_killed"] = process_killed

						if "launch_time" in main_dict[app]:
							main_dict[app]["launch_time_L"] = launch_time
						if "process_killed" in main_dict[app]:
							main_dict[app]["process_killed_L"] = process_killed


				i += 1


        with open("result.csv", "w+") as f:
		df = pd.DataFrame(main_dict,columns = list(main_dict.keys()).sort())
		df.to_csv(f, header=True)
		f.write('\n')
'''



# This function will save a dict as CSV in given filename.
# Requirements: Pandas Library 
def save_as_csv(dict, filename):
    try:
        import pandas as pd
	with open(filename, "w+") as f:
		df = pd.DataFrame(dict,columns = list(dict.keys()).sort())
		df.to_csv(f, header=True)
		f.write('\n')
    except Exception as e:
        print('Error: Can not save dict as csv.')
        print(e)

# Given an app name and logfile Name, it will return time of Launch of that app and num of apps killed during that time
# Requirements: None
def parser(filename,app,try_num):
    try:
        dict = {}
        with open(filename) as f:
            
            start = False
            end = False
            num_of_kills = 0
            time = '-1'
            launchReq = ''
            visibleRes = ''
            should_start = try_num
            for i, line in enumerate(f):
                if app in line:
                    if try_num:
                        if 'Displayed' in line:
                            try_num -= 1
                        continue
                    if 'Displayed' in line and start and time == '-1':
                        time = line.split(' ')[-1]
                        if time[-3] == ')':
                            time = time[:-3]
                    elif 'Activity_launch_request' in line and not start:
                        launchReq = line.split(' ')[1]
                        start = True
                    elif 'Activity_windows_visible' in line and start and not end:
                        visibleRes = line.split(' ')[1]
                        end = True
                elif ('Killing' in line or 'died' in line ) and start and not end:
                    num_of_kills += 1
            if time:
                time = get_time_difference( launchReq,visibleRes)
            dict['Launch_Time'] = str(time)
            dict['Num of Processes Killed'] = num_of_kills
        return dict
                    
    except Exception as e:
        print("Error in parser")
        print(e)



# Given a list of apps, it will traverse over all apps and will find launch time of all apps
# Requirements: None
def find_apps(filename, apps,num_of_tries):
    try:
        dict = {}
        for i in range(num_of_tries):
            for j,app in enumerate(apps):
                ans = parser(filename,app,i)
                if app not in dict:
                    dict[app] = ans
                    continue
                dict[app]['Launch_Time_'+str(i)] = ans['Launch_Time']
                dict[app]['Num of Processes Killed_'+str(i)] = ans['Num of Processes Killed']
        return dict
    except Exception as e:
        print(e)


# This is main function that serves as starting point of code
# Requirements: Sys Library
def main():
    try:
        import sys
        if len(sys.argv) < 3:
            print("Format: python parseLog.py FileName.csv LogFile num_of_tries")
        
        tries =   sys.argv[3]
        logfile = sys.argv[2]
        csvfile = sys.argv[1]

        apps = ['com.yandex.browser', 'com.android.chrome', 'com.microsoft.emmx', 'org.mozilla.firefox']
        num_of_tries = int(tries)
        save_as_csv( find_apps(logfile,apps,num_of_tries) , csvfile)
    
    except Exception as e:
        print("Error in main")
        print(e)


main()