#include "../include/StrParsing.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


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

/* 初始化函数指针数组 */
operation_SGDB_func SGDB_OPs[SUB_CMD0_NUM] = {
	SGDB_OP_StepExec,
	SGDB_OP_PrintStatus,
	SGDB_OP_ScanMem,
	SGDB_OP_ExprEval,
	SGDB_OP_SetMoniPoi,
	SGDB_OP_DelMoniPoi
};

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
 * desc: sgdb_op_index是命令行函数指针的索引，用于标识执行哪一个命令行函数
 * para: 
 *     cmd_parsed: 二维指针地址，将其第一和第二个输入命令与命令匹配表进行匹配
 * ret: 
 *     int: 返回值，指示成功或失败
 *  */
int cmd_match(char*** cmd_parsed){
	int sgdb_op_index = -1;
	/* 首先判断第一个命令是否符合格式标准。符合则进一步判断与执行，否则返回错误 */
	if( cmd0_match(cmd_parsed, &sgdb_op_index) == SUCCESS &&
		SGDB_OPs[sgdb_op_index](cmd_parsed) == SUCCESS){
		return SUCCESS;			
	}
	return ERROR;
}

/* func name: cmd0_match
 * desc: 对解析后的第一个命令进行匹配
 * para:
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功或失败
 *  */
int cmd0_match(char*** cmd_parsed,int* args){
	for(int i = 0 ; i < SUB_CMD0_NUM ; i++){
		if(strcmp((*cmd_parsed)[0] , CmdMatchTable.sub_cmd0[i]) == 0){
			*args = i;
			return SUCCESS;
		}
	}
	return ERROR;
}

/* func name: SGDB_OP_StepExec
 * desc: 单步执行，执行次数为N.strtol将字符串转换为长整型long int,判断字符是否为数字;将字符转换为数字;判断字符是否为整数且在合理范围内;
 * para: 
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功or失败
 *  */
int SGDB_OP_StepExec(char*** cmd_parsed){
	if((*cmd_parsed)[1] == NULL){
		// 执行一次
		return SUCCESS;
	}

	char* endptr;
	long ret = strtol((*cmd_parsed)[1] , &endptr , 10);
	if( endptr == (*cmd_parsed)[1] ){
		return ERROR;	// no digits were found	
	}
	if( *endptr == '\0' && // 判断是否指向字符串末尾
		ret <= 65535 &&	// 判断是否在合理范围内
		ret >=0){
		// 执行N次

	}
	return SUCCESS;
}

/* func name: SGDB_OP_PrintStatus 
 * desc: 打印程序状态
 * para: 
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功or失败
 *  */
int SGDB_OP_PrintStatus(char ***cmd_parsed){
	// 具体内容
	return SUCCESS;
}

/* func name: SGDB_OP_ScanMem 
 * desc: 扫描内存 
 * para: 
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功or失败
 *  */
int SGDB_OP_ScanMem(char ***cmd_parsed){
	// 具体内容
	return SUCCESS;
}

/* func name: SGDB_OP_ExprEval 
 * desc: 表达式求值
 * para: 
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功or失败
 *  */
int SGDB_OP_ExprEval(char ***cmd_parsed){
	// 具体内容
	return ERROR;
}

/* func name: SGDB_OP_SetMoniPoi 
 * desc: 设置监视点
 * para: 
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功or失败
 *  */
int SGDB_OP_SetMoniPoi(char ***cmd_parsed){
	// 具体内容
	return SUCCESS;
}

/* func name: SGDB_OP_DelMoniPoi  
 * desc: 删除监视点
 * para: 
 *     cmd_parsed: 二维指针地址
 * ret:
 *     int: 返回值，指示成功or失败
 *  */
int SGDB_OP_DelMoniPoi(char ***cmd_parsed){
	// 具体内容
	return SUCCESS;
}

