import multiprocessing as mp
from queue import Queue    #使用多核心的模組 Queue
from multiprocessing import Process,Queue
import time

def job1( workList,q,num ):   

    for i in range( 0,int(num) ): 
        bubleSort(workList[i],q)
        
    putIn = []
    listNum = [] 
    for i in range( 0,int(num) ):
        putIn.append(q.get())

    workList.clear()

    for i in range( 0,int(num) ):
        for j in range( 0, len(putIn[i]) ):
            workList.append(putIn[i][j])
        listNum[i] = len(putIn[i])
    
    for i in range( 0,int(num)-1 ):
        a = int(listNum[i]) + a   
        merge(workList,0, a-1 ,(a+int(listNum[i+1])-1),q)

    q.put(putIn)
    
    
def bubleSort(lst,q):

    print(lst , "fff")
    for k in range(0,len(lst)):
        temp = lst[k] #臨時值,用於交換

        for j in range(k+1,len(lst)):
            #'''  若值比基準值小則將基準值與當前值交換位置 10 '''
            if lst[j]<lst[k]:
                temp=lst[k]
                lst[k]=lst[j]
                lst[j]=temp
    print( "hahahahaha  ", lst )
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
    #for k in range(len(arr)): 
     #   q.put(arr[k])
   
    
def processWork( lst,timetime,outputName ):
    num = input(">>> K : ")
    proc = []
    listKnif = int(int(len(lst)) / int(num))     # 1 = 5 / 3
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
    print(len(listNum))

    tStart = time.clock()  # 計時開始

    for i in range( 0,int(num) ):     
        tt.append(lst[a:(a+int(listNum[i]))])
        a = int(listNum[i]) + a

    p = mp.Process(target=job1, args=(tt,q,num) )
    p.start()
    proc.append(p)
    #p.join()
    #time.sleep(0)

    
    print("aa")

    lst.clear()
        
    lst.append(q.get())
    lst = lst[0]
    tEnd = time.clock()    # 計時結束 
    #print(lst)  
    timetime[0] = str(tEnd-tStart) 

    outputfile = open( outputName, 'w' )

    for i in range( 0,len(lst)):
        outputfile.write(str(lst[i]))
        outputfile.write(' ')
    
    outputfile.write('\n' )
    outputfile.write( 'CPU run time : ' + timetime[0])
    outputfile.close()
