#include "../include/StrParsing.h"

int main(int argc, char *argv[]){
	// 读入一行命令所需的变量
	char *cmd_inct = (char*)malloc(CMD_STR_NUM * sizeof(char));
	char **cmd_parsed = (char**)malloc(SUBCMD_NUM * sizeof(char*));
	for(int i = 0 ; i < 3 ; i++)
		cmd_parsed[i] = (char*)malloc(PARSED_CMD_NUM * sizeof(char));
	
	/* 读取输入指令 */
	if(cmd_read(&cmd_inct) != NULL){
		/* printf("your entered is : %s\n",cmd_inct);	 */
	}

	/* 解析相关命令 */
	cmd_parsed = par_cmd(&cmd_parsed, &cmd_inct);

	if(cmd_match(&cmd_parsed) == SUCCESS){
		printf("match success!\r\n");		
	}else{
		printf("match failed!\r\n");
	}

	/* 释放相关指针变量 */
	/* free(cmd_delim); */
	for(int i = 0 ; i < 3 ;i++){
		if(cmd_parsed[i] != NULL){
			free(cmd_parsed[i]);
		}
	}
	free(cmd_parsed);

	return 0;
}
