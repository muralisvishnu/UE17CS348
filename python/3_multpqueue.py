import threading
import queue
import random
class MPQ:
    def __init__(self):
        self.queue = queue.Queue()
        self.lock = threading.Lock()

    def get(self):
        if (not self.empty()):
            self.lock.acquire()
            i= self.queue.get()
            print(threading.currentThread().getName(),"GET",i)
            self.lock.release()
            return i
        return None

    def add(self,item):
        self.lock.acquire()
        i = self.queue.put(item)
        print(threading.currentThread().getName(),"ADD",item)
        self.lock.release()
        return i

    def empty(self):
        self.lock.acquire()
        i = self.queue.empty()
        self.lock.release()
        return i
    
myqueue = MPQ()
threads = []
for i in range(1,12):
    if (i %2):
        threads.append(threading.Thread(None, myqueue.add,i,(random.randint(1,100),)))
    else:
        threads.append(threading.Thread(None,myqueue.get,i))

for item in threads:
    item.start()

for item in threads:
    item.join()