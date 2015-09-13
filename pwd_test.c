#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<stdbool.h>

#define Second 1000000
#define Min 60
#define Hour 60
#define Day 24
#define Year 365

void my_pow(unsigned int base,unsigned int exp){
       int i;
       unsigned long long sum = 1;
        
       int count = 0;
       double sec = 0;
       double min = 0;
       double hour = 0;
       double day = 0;
       double year = 0;

       int num_to_dec = 0;

      for(i = 0; i < exp; i++){
           sum = sum *((unsigned long long)(base)); 
           sec =(double)(base)* sec;
           min = (double)(base)* min;
           hour = (double)(base)*hour;
           day = (double)(base)*day;
           year = (double)(base)*year;           
       
           if(sum > Second){
              num_to_dec = sum/Second; 
              sec = sec + num_to_dec;
              sum = sum - num_to_dec * Second;
              }

          if(sec > Min){
             num_to_dec = sec/Min;
             min = min + num_to_dec;
             sec = sec - num_to_dec * Min;
            }  

          if(min > Hour){
             num_to_dec = min/Hour; 
             hour = hour + num_to_dec;
             min = min - num_to_dec * Hour;
           }  

          if(hour > Day){
             num_to_dec = hour/Day;
             day = day + num_to_dec;
             hour = hour - num_to_dec * Day;
          }

         if(day > Year){
           num_to_dec = day/Year;
           year = year + num_to_dec;
           day = day - num_to_dec * Year;
          }     
          
        }
       


      if(day!=0)fprintf(stdout,"Use desktopPC CPU:1GHz to crack have to spend %f years,%f days,%f hrs,%f mins ,%f secs",year,day,hour,min,sec);
      else if(hour!=0)fprintf(stdout,"Use desktopPC CPU:1GHz to crack have to spend %f days,%f hrs,%f mins ,%f secs",day,hour,min,sec);
      else if(min!=0)fprintf(stdout,"Use desktopPC CPU:1GHz to crack have to spend %f hrs,%f mins ,%f secs",hour,min,sec);
      else if(sec!=0)fprintf(stdout,"Use desktopPC CPU:1GHz to crack have to spend %f mins,%f secs",min,sec);
    
   
}

bool issymbol(char c){

   unsigned int ascii_num = (unsigned int)c;

   if(ascii_num>=32 && ascii_num <= 47)return true;
   else if(ascii_num>=58 && ascii_num <= 64)return true;
   else if(ascii_num>=91 && ascii_num <= 96)return true;
   else if(ascii_num>=123 && ascii_num <= 126)return true;
   else return false;
}

bool Number_middle_Alpha(unsigned int prev,unsigned int current){

    if( (prev != current) && prev != 0)return true;
    else return false;
}


bool UpperAlpha(unsigned int prev,unsigned int current){
 
  if(prev == current && current ==1)return true;
  else return false;
}

bool LowerAlpha(unsigned int prev, unsigned int current){
    
   if(prev == current && current == 2)return true;
   else return false;
}

bool NumberRpt(unsigned int prev, unsigned int current){

   if(prev == current && current == 3)return true;
   else return false;
}

bool SymbolRpt(unsigned int prev,unsigned int current){

   if(prev == current && current == 4)return true;
   else return false;
}


unsigned int AsciiRpt(char *buf){   

    int array[127];
    int c;
    unsigned int repeat = 0;
    for(c = 0; c < 127; c++)array[c] = 0;

    while(*buf!='\0'){
     array[(unsigned int)(*buf)]++;
     buf++;
    }
    for(c = 32; c < 126; c++){
       if(array[c]>1)repeat+=array[c];     
    }     

  return repeat;
}


bool Continue_Three_Time(unsigned int prev,unsigned int current,unsigned int next){
   
     if(prev+1 == current && current+1 == next )return true;
     else return false;
}


unsigned int Password_Test(char * str)
{
     unsigned int score = 0;
     unsigned int Upper_Count = 0;  // NmA 1
     unsigned int Lower_Count = 0;  // NmA 2
     unsigned int Number_Count = 0; // NmA 3
     unsigned int Symbol_Count = 0; // NmA 4

     unsigned int Num_middle_Alpha = 0;    
     unsigned int Num_middle_Alpha_prev = 0;
      
     unsigned int passwd_mid = 0;
     
     unsigned int Upper_repeat = 0;
     unsigned int Lower_repeat = 0;
     unsigned int Number_repeat = 0;
     unsigned int Symbol_repeat = 0;
     unsigned int Ascii_repeat = 0;    
     unsigned int CTT_repeat = 0;

     unsigned int AsciiCode_prev,AsciiCode_current;

     unsigned int len;
         
     
     AsciiCode_prev = -1;
     AsciiCode_current = -1;  
  
     len = strlen(str);  

     char * buffer = (char*)malloc(sizeof(char)*(len+1));
     strcpy(buffer,str);
            
     
    while((*str)!='\0'){
      if( isupper(*str)){
          
           Upper_Count++; 

           Num_middle_Alpha_prev = Num_middle_Alpha;
           Num_middle_Alpha = 1;

           AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);
         }
     else if( islower(*str)){
           
              Lower_Count++;
             
              Num_middle_Alpha_prev = Num_middle_Alpha;    
              Num_middle_Alpha = 2;

             AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);
         
         }
     else if( isdigit(*str)){
              Number_Count++;
             
              Num_middle_Alpha_prev = Num_middle_Alpha;
              Num_middle_Alpha = 3;

              AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);
        }
     else if( issymbol(*str)){
         Symbol_Count++;
         Num_middle_Alpha_prev = Num_middle_Alpha;
         Num_middle_Alpha = 4;

         AsciiCode_prev = AsciiCode_current;
           AsciiCode_current = (unsigned int)(*str);

        }
     

      /*--------------------------------------------------------------------*/
     if(Number_middle_Alpha(Num_middle_Alpha,Num_middle_Alpha_prev)){passwd_mid++;}

     /*--------------------Decersing Score------------------------------*/


     if(UpperAlpha(Num_middle_Alpha_prev,Num_middle_Alpha)){
         //  printf("Upper\n");
           Upper_repeat++;
     }
     if(LowerAlpha(Num_middle_Alpha_prev,Num_middle_Alpha)){
         //  printf("Lower\n");
          Lower_repeat++; 
      }    
     if(NumberRpt(Num_middle_Alpha_prev,Num_middle_Alpha)){
         Number_repeat++;
      }
     if(SymbolRpt(Num_middle_Alpha_prev,Num_middle_Alpha)){
         Symbol_repeat++;
      }

     Ascii_repeat = AsciiRpt(buffer);
      
      
      
     unsigned int end_or_not = *(str+1) == '\0' ? -1  : (unsigned int)(*(str+1));
     if( Continue_Three_Time(AsciiCode_prev,AsciiCode_current,end_or_not) ){
           CTT_repeat++;
      }
      str++;
    }



  /* printf("%u:%u:%u:%u:%u\n  %u:%u:%u:%u:%u:%u\n",Upper_Count,Lower_Count,Number_Count,Symbol_Count,passwd_mid,
                                                     Upper_repeat,Lower_repeat,Number_repeat,Symbol_repeat,Ascii_repeat,CTT_repeat);       */
     
   //------------------------------------day to Crack------------------------------------------------------//
   if(Upper_Count !=0 && Lower_Count!=0 && Number_Count!=0 && Symbol_Count!=0){my_pow(95,len);}

   else if(Upper_Count != 0 && Lower_Count != 0 && Number_Count!=0){my_pow(63,len);}
  
   else if(Upper_Count != 0 && Lower_Count != 0 && Symbol_Count!=0){my_pow(85,len);}
   
   else if(Upper_Count != 0 && Number_Count != 0 && Symbol_Count !=0){my_pow(69,len);}
   
   else if(Lower_Count != 0 && Number_Count != 0 && Symbol_Count!=0 ){my_pow(69,len);}

   else if(Upper_Count != 0 && Lower_Count !=0){my_pow(52,len);}
 
   else if(Upper_Count != 0 && Number_Count !=0){my_pow(36,len);}
   
   else if(Upper_Count !=0 && Symbol_Count!=0){my_pow(58,len);}

   else if(Lower_Count != 0 && Number_Count!=0){my_pow(36,len);}
   
   else if(Lower_Count != 0 && Symbol_Count!=0){my_pow(58,len);}
  
   else if(Symbol_Count != 0 && Number_Count!=0){my_pow(42,len);}

   else if(Upper_Count!=0){my_pow(26,len);}
   
   else if(Lower_Count!=0){my_pow(26,len);}

   else if(Symbol_Count!=0){my_pow(32,len);}

   else if(Number_Count!=0){my_pow(10,len);}
    
}



int main(int argc,char * argv[]){
  
   if(argc!=2){fprintf(stdout,"error format\n"); return -1;}

   Password_Test(argv[1]);
    

  return 0;
}
