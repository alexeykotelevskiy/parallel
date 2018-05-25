import subprocess
import time
import random
OPEN_MP = 'openmpthreads2.exe'
POSIX = 'threads.exe'
NORMAL = 'normal.exe'


def getMillis(cmd):
        p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
        p = float(p.stdout.read())
        print(p)
        return p

k = 0
#f = open("tests\\input2.txt", 'w')
#f.write("1000000 4\n")
#for i in range(1000000):
 #       f.write(str(random.randint(-100,100)) + ' ')
#exit(0)

for i in range(10):
        k+=getMillis(OPEN_MP + " tests\\input2.txt")
print(k/10.0)