import threading
import time
def myfunc(name,delay):
    count = 0
    while count < 5:
        time.sleep(delay)
        count += 1
        print(name,delay)

a = threading.Thread(None,myfunc,"A",("A",1))
b = threading.Thread(None,myfunc,"B",("B",2))
a.start()
b.start()