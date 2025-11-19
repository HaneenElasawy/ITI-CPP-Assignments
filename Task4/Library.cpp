  #include "headers.h"

  int str_len(char arr[])
 {
    int i = 0;
    while( arr[i] != '\0')
    {
        i++;
    }
     return i;
 } 

int str_cmp(char str1[] , char str2[]){

    int i = 0;

    while (str1[i]!='\0' || str2[i] != '\0'){
        if(str1[i] > str2[i] )  
            return 1;
        else if (str1[i]< str2[i])
            return -1;

        i++;
    }
    return 0;
}
 void tolower_str(char str[]){
    int i =0;
    while(str[i] != '\0'){
        if(str[i] >= 'A' && str[i] <= 'Z') 
         str[i] = str[i] + 32 ;     
            i++ ;
    }
 }
  void toupper_str(char str[]){
    int i =0;
    while(str[i] != '\0'){
        if(str[i] >= 'a' && str[i] <= 'z') 
         str[i] = str[i] - 32 ;     
            i++ ;
    }
 }


int str_concat(char str1[], char str2[], int size_str1) {

    int len1 = str_len(str1);
    int len2 = str_len(str2);

    if (len1 + len2 + 1 > size_str1)
        return 0;  
    int i = 0;
    while (str2[i] != '\0') {
        str1[len1 + i] = str2[i];
        i++;
    }

    str1[len1 + i] = '\0';  
       return 1;
}

void str_copy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}