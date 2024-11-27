#include <stdio.h>
#include <regex.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1

/* ^：匹配字符串的开始。
 * [1-9]：匹配一个非零的数字（1到9）。
 * [0-9]*：匹配零个或多个数字（0到9）。
 * $：匹配字符串的结束。 */
static const char* patter = "^[1-9][0-9]*$";

int match_posive_integer(const char* str){
	regex_t regex;
	int ret;

	ret = regcomp(&regex , patter , REG_EXTENDED);
	if(ret){
		printf("Couldn't compile regex\n");
		return ERROR;
	}	

	ret = regexec(&regex , str , 0 , NULL , 0);
	regfree(&regex);

	if(ret == 0){
		printf("match success!\n");
		return SUCCESS;
	}else if(ret == REG_NOMATCH){
		printf("don't march\n");
		return ERROR;
	}else{
		printf("no match\n");
		return ERROR;
	}

}

int main(int argc , char* argv[]){
	if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }		
	return match_posive_integer(argv[1]);
}

