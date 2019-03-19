import datetime
import pandas as pd
import numpy as np

filename = 'ashed.txt'
apps = ['com.yandex.browser', 'com.android.chrome', 'com.microsoft.emmx', 'org.mozilla.firefox']
main_dict = {}

# with open(filename) as w:
#     str = w.readline()
#     while str :
#         if  ('ActivityManager: Displayed' in str or "ActivityManager: Killing" in str):
#             for i in apps: 
#                 if i in str:
#                     print str
        
#         str = w.readline()


def get_time_difference(t1,t2):
	t1s = t1.split(':')
	t2s = t2.split(":")

	hrs = float (t2s[0]) -  float(t1s[0]) 
	mins = float (t2s[1]) -  float(t1s[1])
	secs = float (t2s[2]) -  float(t1s[2])

	ans = hrs*3600+mins*60+secs
	print ans
	return ans

def find_app_record(apps):
	for app in apps:
		main_dict[app] = {}

	with open(filename) as fin:
		all_data = fin.read().split('\n')
		length = len(all_data)

		for app in apps:
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

					if not app in all_data[i] and "ActivityManager: Displayed" in all_data[i]:
						break

					launch_display_time = all_data[i].split()[1]
					launch_time = get_time_difference(launch_request_time,launch_display_time)

					if "launch_time" not in main_dict[app]:
						main_dict[app]["launch_time"] = []
					if "process_killed" not in main_dict[app]:
						main_dict[app]["process_killed"] = []

					main_dict[app]["launch_time"].append(launch_time)
					main_dict[app]["process_killed"].append(process_killed)

				i += 1

	with open("result.csv", "w+") as f:
		df = pd.DataFrame(main_dict,columns = list(main_dict.keys()).sort())
		df.to_csv(f, header=True)
		f.write('\n')

		


def main():
	find_app_record(apps)


main()

# filename = 'ashed.txt'
# with open(filename) as fin:
# 	line = fin.readline()
# 	while line:
# 		if "yandex" in line:
# 			print line
# 		line = fin.readline()
