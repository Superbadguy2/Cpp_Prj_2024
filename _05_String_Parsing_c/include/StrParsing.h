#ifndef STRPARSING_H 
#define STRPARSING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

/* 别名定义 */
typedef int (*operation_SGDB_func)(char***);

/* 函数声明 */
char* cmd_read(char **str_ptr);
char** par_cmd(char ***cmd_parsed, char **cmd_str);
int cmd_match(char*** cmd_parsed);
int cmd0_match(char*** cmd_parsed,int* args);

int SGDB_OP_StepExec(char*** cmd_parsed);
int SGDB_OP_PrintStatus(char*** cmd_parsed);
int SGDB_OP_ScanMem(char*** cmd_parsed);
int SGDB_OP_ExprEval(char*** cmd_parsed);
int SGDB_OP_SetMoniPoi(char*** cmd_parsed);
int SGDB_OP_DelMoniPoi(char*** cmd_parsed);

/* 宏定义 */
#define CMD_STR_NUM 32 * 3
#define SUBCMD_NUM 3
#define PARSED_CMD_NUM 32
#define SUB_CMD0_NUM 6
#define SUB_CMD1_NUM 2
#define MONI_POI_NUM 20		// 监视点数量，最多20个
#define MemSize 0x40000000

#define SUCCESS 1
#define ERROR 0

/* 结构体与类型定义 */
typedef struct {
	char* sub_cmd0[SUB_CMD0_NUM];
	char* sub_cmd1[SUB_CMD1_NUM];
}Cmd_Match_Table;

typedef struct {
	u_int8_t MoniPoiCount;
	u_int32_t* MoniPois[MONI_POI_NUM];
}Monitor_Point;

/* 外部变量声明 */
extern operation_SGDB_func SGDB_OPs[SUB_CMD0_NUM];

#endif
