import test1,test2,test34,test4

if __name__ == '__main__':

  fileName = input(">>> file name : ")

  file = open( fileName , 'r' )

  lst = []
  num = file.readline()                      # 看是第幾題


  lst = file.readline().split()              # 將答案輸入

  print ( 'how many number', len(lst), '\n') # 確定排序資料數
  file.close()

  for i in range(len(lst)):                  # 將資料轉型為int 以便比較大小
      lst[i]=int(lst[i])

  timetime = []
  timetime.append('')
  outputName = fileName + '-output.txt'      # 輸出檔案之名稱

  if int(num) == 1 :                         # 各題分開處理
      test1.bubleSort(lst,timetime)
  elif int(num) == 2 :
      test2.threadWork(lst,timetime)
  elif int(num) == 3 :
      test34.processWork(lst,timetime,outputName)
  elif int(num) == 4 :
      test4.processWork(lst,timetime,outputName)
      
  else:
      print (num)

  over = 'CPU run time : ' + timetime[0]
  print ( over )


  if int(num) == 1 or  int(num) == 2 :       # 第三跟四題在function內寫檔
      outputfile = open( outputName, 'w' )

      for i in range(len(lst)):
          outputfile.write(str(lst[i]))
          outputfile.write(' ')
    
      outputfile.write('\n' )
      outputfile.write( over )
      outputfile.close()
