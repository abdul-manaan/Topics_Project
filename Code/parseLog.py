filename = 'ashed.txt'
apps = ['com.yandex.browser', 'com.sec.android.app.sbrowser', 'com.android.chrome', 'com.microsoft.emmx', 'org.mozilla.firefox']
with open(filename) as w:
    str = w.readline()
    while str :
        if  ('ActivityManager: Displayed' in str):
            for i in apps: 
                if i in str:
                    print str
        
        str = w.readline()
