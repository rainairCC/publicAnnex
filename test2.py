import threading    #導入 threading 模組
import time

def bubleSort(list, first,last):
    #print(list[0])
    for k in range(first,last+1):
        temp = list[k] #臨時值,用於交換
        for j in range(k+1,last+1):
            #'''  若值比基準值小則將基準值與當前值交換位置 10 '''
            if list[j]<list[k]:
                temp=list[k]
                list[k]=list[j]
                list[j]=temp
                
def merge(arr, low, mid, high):
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

def threadWork( list,timetime ):
    num = input(">>> K : ")
    threads = []
    listKnif = int(int(len(list)) / int(num))     # 1 = 5 / 3

    listNum = []
    i = -1
    
    for long in range(int(num) , len(list)+1, listKnif):         # 1 1 1  餘2
        i = i + 1
        listNum.append(listKnif)

    i = -1

    for j in range( int(int(len(list)) % int(num)) ):          # 2 2 1
        i = i + 1
        listNum[i] = int(listNum[i]) + 1
    tStart = time.clock()  # 計時開始
    a = 0
    for i in range( 0,int(num) ):
        # print( a,(a+int(listNum[i])-1) ) 
        t = threading.Thread(target=bubleSort, args=(list,a,(a+int(listNum[i])-1)) )
        t.start()
        threads.append(t)
        t.join()
        a = int(listNum[i]) + a

    #for thread in threads:
     #   thread.join()

    a = 0

    for i in range( 0,int(num)-1 ):
        a = int(listNum[i]) + a 
        t = threading.Thread(target=merge,args=(list,0, a ,a+int(listNum[i+1])-1))
        t.start()
        threads.append(t)

    for thread in threads:
        thread.join()
        
    tEnd = time.clock()    # 計時結束
    timetime[0] = str(tEnd-tStart) 
