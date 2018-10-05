import time

def bubleSort(list,timetime):
    tStart = time.clock()  # 計時開始
    for k in range(len(list)):
        temp = list[k] #臨時值,用於交換
        for j in range(k+1,len(list)):
            #'''  若值比基準值小則將基準值與當前值交換位置 10 '''
            if list[j]<list[k]:
                temp=list[k]
                list[k]=list[j]
                list[j]=temp 
    tEnd = time.clock()    # 計時結束
    timetime[0] = str(tEnd - tStart)
