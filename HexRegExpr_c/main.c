#include <stdio.h>
#include <regex.h>

#define ERROR 1
#define SUCCESS 0

// 正则表达式：匹配十六进制数字（带或不带 0x 前缀）
const char* hexadecimal = "^(0[xX])?[0-9a-fA-F]+$";

static int ExprEval(int argc, char** argv) {
    if (argc < 3) {
        printf("Insufficient arguments!\n");
        return ERROR;
    }

    regex_t regex;
    int reti;

    // 编译正则表达式
    reti = regcomp(&regex, hexadecimal, REG_EXTENDED);
    if (reti) {
        char errbuf[256];
        regerror(reti, &regex, errbuf, sizeof(errbuf));
        printf("Regex compilation failed: %s\n", errbuf);
        return ERROR;
    }

    // 打印目标字符串
    printf("Target string: %s\n", argv[2]);

    // 执行正则匹配
    reti = regexec(&regex, argv[2], 0, NULL, 0);
    if (reti == 0) {
        printf("Match success! '%s' is a valid hexadecimal number.\n", argv[2]);
        regfree(&regex);
        return SUCCESS;
    } else if (reti == REG_NOMATCH) {
        printf("No match! '%s' is not a valid hexadecimal number.\n", argv[2]);
        regfree(&regex);
        return ERROR;
    } else {
        printf("Regex execution failed!\n");
        regfree(&regex);
        return ERROR;
    }
}

int main(int argc, char** argv) {
    return ExprEval(argc, argv);
}

