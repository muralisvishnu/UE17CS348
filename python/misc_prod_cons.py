import threading
import queue
import random
def producer(q,lock):
    lock.acquire()
    item = random.randint(1,100)
    q.put(random.randint(1,100))
    print(threading.currentThread().getName(),"Produced",item)
    lock.release()

def consumer(q,lock):
    read = 0
    while (not read):
        lock.acquire()
        if (not q.empty()):
            read = 1
            print(threading.currentThread().getName(),"Consumed",q.get())
        lock.release()

threads = []
q = queue.Queue()
lock = threading.Lock()

for i in range(1,12):
    if (i %2):
        threads.append(threading.Thread(None, producer,i,(q,lock)))
    else:
        threads.append(threading.Thread(None,consumer,i,(q,lock)))

for item in threads:
    item.start()

for item in threads:
    item.join()