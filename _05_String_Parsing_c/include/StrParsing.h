#ifndef STRPARSING_H 
#define STRPARSING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

/* 函数声明 */
char* cmd_read(char **str_ptr);
char** par_cmd(char ***cmd_parsed, char **cmd_str);
int cmd_match(char*** cmd_parsed);
int cmd0_match(char*** cmd_parsed);
int cmd1_match(char*** cmd_parsed);

/* 宏定义 */
#define CMD_STR_NUM 32 * 3
#define SUBCMD_NUM 3
#define PARSED_CMD_NUM 32
#define SUB_CMD0_NUM 6
#define SUB_CMD1_NUM 2

#define SUCCESS 0
#define ERROR 1

/* 结构体与类型定义 */
typedef struct {
	char* sub_cmd0[SUB_CMD0_NUM];
	char* sub_cmd1[SUB_CMD1_NUM];
}Cmd_Match_Table;

#endif
