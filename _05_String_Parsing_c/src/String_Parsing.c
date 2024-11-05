#include "../include/StrParsing.h"
#include <stdio.h>
#include <string.h>

static const char* cmd_delim = " ";

/* 声明Cmd_Match_Table实例并初始化 */
static const Cmd_Match_Table CmdMatchTable = {
	.sub_cmd0 = {
		"si",
		"info",
		"x",
		"p",
		"w",
		"d"
	},
	.sub_cmd1 = {
		"r",
		"w"
	}
};
int cmd0_match_table_result[6] = {0};
int cmd1_match_table_result[2] = {0};

/* func name: cmd_read
 * desc: 输入字符串指针地址，读取一行字符串并函数字符串指针
 * para: 
 *     str_ptr: 字符串指针地址
 * ret:
 *     char*:char类型指针
 *  */
char* cmd_read(char **str_ptr){
	/* 从标准准输入读取一行字符串 */
	char temp_buffer[CMD_STR_NUM];	// 用于临时存储字符串
	if(fgets(temp_buffer,sizeof(temp_buffer),stdin) != NULL){
		/* 去掉换行符 */
		/* temp_buffer[strcspn(temp_buffer,"\n")] = "\0"; */
		/* 动态分配内存并复制输入字符串 */
		/* *str_ptr = (char*)malloc((strlen(temp_buffer) + 1) * sizeof(char)); */
		if(*str_ptr != NULL){
			/* 复制字符串 */
			strcpy(*str_ptr,temp_buffer);
		}
		return *str_ptr;
	}
	return NULL;
}

/* func name: par_cmd
 * desc: 对输入命令解析解析，输入命令又三种可能，最多分成三个
 * para:
 *     cmd_parsed: 二维指针地址，存放解析后的命令
 *     cmd_str: 字符串地址，未解析的命令
 * ret:
 *     char**: 动态二维数组指针
 *  */
char** par_cmd(char ***cmd_parsed , char **cmd_str){
	if((*cmd_parsed) != NULL && (*cmd_str) != NULL){
		/* 第一次对命令解析 */
		char *temp_buffer_str = (char*)malloc(CMD_STR_NUM * sizeof(char));
		/* 解析第一个命令 */
		strcpy(temp_buffer_str,*cmd_str);
		(*cmd_parsed)[0] = strtok(temp_buffer_str,cmd_delim);
		/* printf("Current Token is:%s\r\n",(*cmd_parsed)[0]); */

		/* 解析第二个命令 */
		(*cmd_parsed)[1] = strtok(NULL,cmd_delim);
		if((*cmd_parsed)[1] != NULL){
			(*cmd_parsed)[1] = strdup((*cmd_parsed)[1]);
			/* printf("Current Token is:%s\r\n",(*cmd_parsed)[1]); */
		}

		/* 解析第三个命令 */
		(*cmd_parsed)[2] = strtok(NULL,"");
		if((*cmd_parsed)[2] != NULL){
			(*cmd_parsed)[2] = strdup((*cmd_parsed)[2]);
			/* printf("Current Token is:%s\r\n",(*cmd_parsed)[2]); */
		}

		return *cmd_parsed;
	}else{
		return NULL;
	}
}

/* func name: cmd_match
 * desc: 对解析后的命令进行匹配，使用一个确定的命令表进行匹配，匹配成功则返回SUCCESS，匹配失败则返回ERROR
 * para: 
 *     cmd_parsed: 二维指针地址，将其第一和第二个输入命令与命令匹配表进行匹配
 * ret: 
 *     int: 返回值，指示成功或失败
 *  */
int cmd_match(char*** cmd_parsed){
	int ret = ERROR;
	ret = cmd0_match(cmd_parsed);
	if(ret == SUCCESS){
		if(cmd0_match_table_result[1] == 1){
			ret = cmd1_match(cmd_parsed);
			if(ret == SUCCESS){
				return SUCCESS;
			}else{
				return ERROR;
			}
		}else{
			return SUCCESS;
		}
	}
	return ERROR;
}

int cmd0_match(char*** cmd_parsed){
	for(int i = 0 ; i < SUB_CMD0_NUM ; i++){
		if(strcmp((*cmd_parsed)[0] , CmdMatchTable.sub_cmd0[i]) == 0){
			cmd0_match_table_result[i] = 1;
			return SUCCESS;
		}
	}
	return ERROR;
}

int cmd1_match(char*** cmd_parsed){
	for(int i = 0 ; i < SUB_CMD1_NUM ; i++){
		if(strcmp((*cmd_parsed)[1] , CmdMatchTable.sub_cmd1[i]) == 0){
			cmd1_match_table_result[i] = 1;
			return SUCCESS;
		}
	}
	return ERROR;
}
