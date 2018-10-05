import multiprocessing as mp
from queue import Queue                      # 使用多核心的模組 Queue
from multiprocessing import Process,Queue
import time

def job1( workList ):
    test1.bubleSort(workList)
    
def bubleSort(lst,q):
    #for k in range(first,last+1):
    for k in range(0,len(lst)):
        print('現在到' , k )
        temp = lst[k]                        # 臨時值,用於交換
        #for j in range(k+1,last+1):
        for j in range(k+1,len(lst)):

            if lst[j]<lst[k]:
                temp=lst[k]
                lst[k]=lst[j]
                lst[j]=temp
    
    q.put(lst)

    
def merge(arr, low, mid, high,q):
    leftIndex = low
    rightIndex = mid + 1
    tempArr = []
    while leftIndex <= mid and rightIndex <= high:
        if arr[leftIndex] <= arr[rightIndex]:
            tempArr.append(arr[leftIndex])
            leftIndex += 1
        else:
            tempArr.append(arr[rightIndex])
            rightIndex += 1
    if leftIndex > mid:
        while rightIndex <= high:
            tempArr.append(arr[rightIndex])
            rightIndex += 1
    else:
        while leftIndex <= mid:
            tempArr.append(arr[leftIndex])
            leftIndex += 1
    leftIndex = low
    for temp in tempArr:
        arr[leftIndex] = temp
        leftIndex += 1
        
    q.put(arr)
    

def processWork( lst,timetime,outputName ):
    num = input(">>> K : ")
    proc = []
    listKnif = int(int(len(lst)) / int(num))                    # 1 = 5 / 3
    q = mp.Queue()
    listNum = []
    i = -1

    for long in range(int(num) , len(lst)+1, listKnif):         # 1 1 1  餘2
        i = i + 1
        listNum.append(listKnif)

    i = -1

    for j in range( 0,int(int(len(lst)) % int(num)) ):          # 2 2 1
        i = i + 1
        listNum[i] = int(listNum[i]) + 1
        
    a = 0
    tt = []

    for i in range( 0,int(num) ):    
        tt.append(lst[a:(a+int(listNum[i]))])
        a = int(listNum[i]) + a

    tStart = time.clock()  # 計時開始

    for i in range( 0,int(num) ):
        p = mp.Process(target=bubleSort, args=(tt[i],q) )
        p.start()
        proc.append(p)
    
    # for pro in proc:
    #    pro.join()
    #
    #print('---------bubble done!------')

    putIn = []

    for i in range( 0,int(num) ):
        putIn.append(q.get())

    lst.clear()
    #print('get done! ')
    
    for i in range( 0,int(num) ):
        for j in range( 0, len(putIn[i]) ):
            lst.append(putIn[i][j])
            listNum[i] = len(putIn[i])
            
    putIn.clear()
    putIn = lst

    a = 0

    procc = []
    #print('start merge !')
    for i in range( 0,int(num)-1 ):
        a = int(listNum[i]) + a
        pp = mp.Process(target=merge,args=(putIn,0, a-1 ,(a+int(listNum[i+1])-1),q))
        pp.start()
        procc.append(pp)
        putIn.clear()
        putIn.append(q.get())
        putIn = putIn[0]


    #print('merge end')
        
    #for ro in procc:
     #   ro.join()
      
    tEnd = time.clock()    # 計時結束
    lst = putIn

    timetime[0] = str(tEnd-tStart) 

    outputfile = open( outputName, 'w' )

    for i in range( 0,len(lst)):
        outputfile.write(str(lst[i]))
        outputfile.write(' ')
    
    outputfile.write('\n' )
    outputfile.write( 'CPU run time : ' + timetime[0])
    outputfile.close()
