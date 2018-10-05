// DS2 ex1
#include <cstdlib>
#include <cstring>
#include <stdio.h>     // C  printf scanf
#include <stdlib.h>    // atoi  (char array to integer)
#include <iostream>    // C++ cout cin
#include <new>         // 動態配置
#include<fstream>      // C++ 讀檔
#include <string.h>
#include <vector>
#include <math.h>
using namespace std;

string   fileName ;    // 讀檔名(數字)
string   number ;      // 紀錄檔名(數字)
int mission = 0;       // 讀入任務
int check = 0 ;        // 0 初始化 ， 1 有資料 ， 2 無資料請重新輸入。
int gPrint = 0;
string  gSchool;
string  gDepartment;
string  gDay_or_night;
string  gRank;

typedef struct Heap
{   int i ;            // 流水編號
    int quantity_student;
}  ha;

typedef struct cT
{   string  number_school;
    string  school;
    string  department;
    string  day_or_night;
    string  rank;
    int     quantity_student;
}   collegeType;



bool load( vector<collegeType> & ) ;               // 讀檔
void filter(vector<collegeType> & ) ;              // 篩選(任務一)
void need () ;                                     // 篩選條件
void print() ;                                     // 印出
void heapInsert () ;                               // 做min heap
vector<collegeType> gAnswer;                       // 篩選後結果
vector<ha> heap;                                   // min heap
vector<ha> kheap ;
void swapheap( int , int ) ;
bool IsOddFloor( int ) ;                           //判斷層數
void case2(int ) ;                                 // 恩 很明顯的case2
void rebulid(int) ;                                //重新建樹
void printKans() ;

int main(void){
  cout << "歡迎使用此程式!\n" ;
  vector< collegeType >     cSet;                  // set of output records
  cout << "輸入'1'，依照指定欄位篩選資料檔\n"
		  "輸入'2'，即結束此程式。\n";
  cin >> mission ;
  int Nnum = 0 ;
  while ( mission < 2 && mission > 0 ) {
    load(cSet);                                    // 讀檔
    if ( check == 1 ) {                            // 確認是有效的檔名
         need();
         filter(cSet);
         print();
         if ( check == 1 && gAnswer.size() != 0 )  {       // 如果沒有資料 就不進去任務2
           heapInsert() ;
           cout << "輸入n筆最大資料       "  ;
		   cin >> Nnum ;
		   case2( Nnum);
		   printKans() ;
         }
         else if( check == 2 ) ;
         else
		   cout << "0筆資料不成立heap" ;
    } // if

    cout << "\n若想繼續使用，請再次輸入指令。\n"
            "輸入'1'，依照指定欄位篩選資料檔\n"
            "若無，請按'2'結束程式\n"  ;
    cSet.clear();
    gAnswer.clear() ;
    heap.clear() ;
    kheap.clear() ;
    check = 0;
    cin >> mission ;

  } // while

  //system("pause");
  return 0;
}	// end main

void rebulid(int place ){
   while ( place < heap.size() && place != 0  ){
     int leftson = place * 2 + 1, rightson = leftson + 1,llgson = leftson *2 +1 ;    //左兒 右兒 左左孫
     int lrgson = llgson +1 , rlgson = lrgson +1, rrgson = rlgson +1 ;               // 左右孫 右左孫 右右孫
     int findGson = 0 ;
                                                                                     // 先檢查兒子有沒有比他大的
     if ( leftson < heap.size() ) if( heap[leftson].quantity_student > heap[place].quantity_student ) swapheap( leftson,place ) ;
     if ( rightson < heap.size() ) if( heap[rightson].quantity_student > heap[place].quantity_student ) swapheap( rightson,place ) ;
                                                                                     // 檢查孫子有沒有比他大的
     if ( llgson < heap.size() )  findGson = llgson ;                                //找出 孫子中最大的
     if( lrgson < heap.size() && heap[findGson].quantity_student < heap[lrgson].quantity_student ) findGson = lrgson ;
     if( rlgson < heap.size() && heap[findGson].quantity_student < heap[rlgson].quantity_student ) findGson = rlgson ;
     if( rrgson < heap.size() && heap[findGson].quantity_student < heap[rrgson].quantity_student ) findGson = rrgson ;
     if ( findGson != 0 && heap[findGson].quantity_student > heap[place].quantity_student ) swapheap( place,findGson ) ;
     place = findGson ;
    }//while()
}

void case2( int num ){
    for( int k = 0 ; k < num ; k ++ ) {
      int test = 0 ;                                                 //紀錄我拿左邊還是右邊的
      if ( heap[1].quantity_student > heap[2].quantity_student ) {   //判斷哪邊大 拿大的之後移到最右下角
      	kheap.push_back( heap[1] ) ;
      	swapheap( 1, heap.size()-1 ) ;
      	test = 1 ;
      }
      else {
	    kheap.push_back( heap[2] ) ;
	    swapheap( 2, heap.size()-1 ) ;
	    test = 2 ;
	  }
	  heap.pop_back() ;  //刪除最後一個
	  rebulid( test ) ;
	  test = 0 ;
    }

}
bool load( vector<collegeType> &cSet ) {                    // 負責讀入檔案的function
    fstream infile ;
    string name ;
    char *buffer = new char[255] ;                          // 動態配置一個char array用來暫存讀入的東西
    while ( 1) {
      cout << "\n請輸入檔案名稱 : \n" ;
      cin >> name ;                                         // 讀入檔案的名字
      name = "input" + name + ".txt" ;
      infile.open( name.c_str(), fstream::in ) ;            // 開啟檔案
      if ( !infile ) {                                      // 如果無法開啟直接結束load
          cout << name << "檔案不存在" << endl ;
          check == 2;
      }
      else break ;
    }

    for ( int i = 0 ; i < 3 ; i++ )                         // 前三行並非要的資料直接讀掉不予理會
        infile.getline( buffer, 255 ) ;
    delete [] buffer ;                                      // 清空buffer中的東西
    buffer = new char[255] ;

    int pre = 0, pos = 0 ;

    while(  !infile.eof() ) {                               // 若非資料結尾則繼續迴圈
        infile.getline( buffer, 255 ) ;                     // 讀入整行資料
        collegeType one ;                                   // 暫存切割完的資料
         int pre = 0, pos = 0 ;                             // pre存選取字串的起始位置   pos存最後位置
        string temp ;                                       // 存轉成String的buffer
        temp.assign( buffer ) ;                             // buffer轉string
        int switch_count = 0 ;                              // 給下面迴圈的switch計數用
        bool check2 = true ;                                // 確認下面的迴圈是否繼續

        while ( check2 ) {                                  // 此迴圈用來切割讀入的整行資料
            pos = temp.find_first_of( '\t', pre ) ;         // 找到下一個\t的位置存在pos

            switch( switch_count++ ) {
                case 1 :                                    // 學校編號存入one
                    one.number_school = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 2 :                                    // 學校名稱存入one
                    one.school = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 3 :                                    // 科系代碼不需要不予理會
                    pre = pos + 1 ;
                    break ;
                case 4 :                                    // 科系名稱存入one
                    one.department = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 5 :                                    // 日夜別存入one
                    one.day_or_night = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 6 :                                    // 等級別存入one
                    one.rank = temp.substr( pre, pos - pre ) ;
                    pre = pos + 1 ;
                    break ;
                case 7 :                                    // 學生數存入one
                    one.quantity_student = atoi(temp.substr( pre, pos - pre ).c_str()) ;
                    pre = pos + 1 ;
                    check2 = false ;
                    break ;
                default :
                    break ;
            }
        } // in_while
        if(one.day_or_night.empty() || one.department.empty() || one.number_school.empty()
		   || one.rank.empty() || one.school.empty() || one.quantity_student == 0 )
		   int h = 0;
        else
           cSet.push_back( one ) ;                          // 將one放入cSet這個vector的尾端

    } // out_while

    infile.close() ;
    check = 1 ;
    if (!cSet.size()) {
        cout << endl << "### Get nothing from the file " << fileName << " ! ### " << endl;
        check = 2 ;
    } // if
}

void need() {
    cout << "\nEnter a keyword of 學校名稱: [*]for all\n";
    cin >> gSchool;
    cout << "Enter a keyword of 科系名稱: [*]for all\n";
    cin >> gDepartment;
    cout << "Enter a keyword of 日夜別: [*]for all\n";
    cin >> gDay_or_night;
    cout << "Enter a keyword of 等級別: [*]for all\n";
    cin >> gRank;
}

void print() {
     cout << "\n共有" << gAnswer.size() << "筆資料" << endl ;
	 int i = 0;
	 while( i < gAnswer.size()) {
	     cout << "[" << i+1 << "]" << gAnswer[i].school << gAnswer[i].department << ", " ;
         cout << gAnswer[i].day_or_night << ", " << gAnswer[i].rank << ", " << gAnswer[i].quantity_student << endl ;
         i = i + 1;
     }
}

void printKans() {
  for ( int i = 0 ; i < kheap.size() ; i++ ) {
     cout << "Top  " << i+1 << ":[" <<  kheap[i].i+1 << "]  " << gAnswer[kheap[i].i].school << gAnswer[kheap[i].i].department << ", ";
     cout << gAnswer[kheap[i].i].day_or_night << ", " << gAnswer[kheap[i].i].rank << ", " << gAnswer[kheap[i].i].quantity_student << endl;
  }
}


void filter(vector<collegeType> &aSet){
    vector<collegeType> tempS(aSet);                      // a copy of the entire vector (array)
    collegeType answer ;
    int i = 0;
    for( ; i < tempS.size() ; i ++  )                     // 一筆筆資料往下找 全部篩選條件符合就印出
        if ( gSchool == "*" || strstr( tempS[i].school.c_str(),gSchool.c_str()) != NULL )
           if ( gDepartment == "*" || strstr( tempS[i].department.c_str(), gDepartment.c_str() ) != NULL)
              if ( gDay_or_night  == "*" || strstr( tempS[i].day_or_night.c_str(), gDay_or_night.c_str() ) != NULL )
                 if ( gRank == "*" || strstr( tempS[i].rank.c_str(), gRank.c_str() ) != NULL )
                 	gAnswer.push_back( tempS[i] ) ;       // 把符合資料的放入答案占存
} // 篩選  { if (size >= MAX_HEAP)

void swapheap( int sparent, int splace ){
  Heap temp;
  temp.i = heap[sparent].i;
  temp.quantity_student = heap[sparent].quantity_student;
  heap[sparent].i = heap[splace].i;
  heap[sparent].quantity_student = heap[splace].quantity_student;
  heap[splace].i = temp.i;                        // swap items[place] and items[parent]
  heap[splace].quantity_student = temp.quantity_student;
}

bool IsOddFloor( int number ) {
  int total = 0, floor = 0  ;                               // floor+1是目前層數
  for (;  total < number; floor ++ )  total = total + pow( 2, floor ) ;	    	            // pow為 計算次方的公式
  if( floor % 2 != 0 ) return true ;                        // 迴圈結束已經自動+1 不須再特別注意
  else return false ;
}
void heapInsert () {
	int i = 0;
	while(i < gAnswer.size() ) {
		Heap put;
	    put.i = i;
	    put.quantity_student = gAnswer[i].quantity_student ;
	    heap.push_back( put ) ;

        int place = heap.size()-1;               // 子節
        int parent = ( place - 1) / 2; //父節
   	    int grandparent = ( parent -1 ) / 2 ;    //祖父
        while ( place - 1 > 0 ){
		  bool IsOdd = IsOddFloor( place +1)  ;                // 判斷層數是以1開始 所以要+1
		  if ( !IsOdd ) {                                      // 偶數層
		  	if ( heap[place].quantity_student < heap[parent].quantity_student )
                swapheap( parent,place ) ;
		  	if ( place != 0 && parent != 0 )                   //是否有祖父
			  if ( heap[place].quantity_student > heap[grandparent].quantity_student )
                swapheap( grandparent,place ) ;
		  }
		  else{  //奇數層
		  	if ( heap[place].quantity_student > heap[parent].quantity_student ) swapheap( parent,place ) ;
		  	if ( place != 0 && parent != 0 )
			  if ( heap[place].quantity_student < heap[grandparent].quantity_student )	swapheap( grandparent,place ) ;
		  }
          place = parent;
          parent = (place - 1)/2;
          grandparent = ( parent -1 ) / 2 ;
        } // end while
        i = i + 1;
      }
	  int total = 0, floor = 0  ;                               // floor+1是目前層數
      for (;  total < i-1  ; floor ++ )  total = total + pow( 2, floor ) ;	    	            // pow為 計算次方的公式
      total = 0 ;    //計算層數
 	  for ( int k = 0 ; k < floor -1  ; k ++ ) total = total + pow( 2, k ) ;                               //用層數去算最左邊的號碼
      cout << "底部(右下): [" << heap[i-1].i+1 << "]  " << heap[i-1].quantity_student << endl;
	  cout << "底部(左下): [" << heap[total].i+1 << "]  " << heap[total].quantity_student << endl;
      //for ( int qq= 0 ; qq < heap.size() ; qq ++ ) {
      //	cout << qq << "  " << heap[qq].quantity_student << endl ;
      //}
} // end heapInsert








