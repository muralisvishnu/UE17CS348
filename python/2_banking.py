import threading

balance = 1000
lock = threading.Lock()

def update_balance(change):
    lock.acquire()
    global balance
    if (balance + change < 1000):
        print(threading.currentThread().getName(),"Balance too low")
    else:
        print(threading.currentThread().getName(),"Before",balance)
        balance = balance + change
        print(threading.currentThread().getName(),"After",balance) 
    lock.release()

threads = []
for i in range(1,11):
    if (i %2):
        threads.append(threading.Thread(None,update_balance,i,(-100,)))
    else:
        threads.append(threading.Thread(None,update_balance,i,(100,)))
    
for item in threads:
    item.start()


