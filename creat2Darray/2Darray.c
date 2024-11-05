#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* 用于测试的结构体内部的二维指针 */
typedef struct Frame{
	uint16_t **framebuf;
} Frame;

/*
 * @brief 创建uint16_t类型的二维数组指针，并返回
 * @brief ROWS:创建行数
 * @brief COLS:创建列数
 * @brief malloc返回的是void 类型的指针，故需要对其进行类型转换
 * @brief 首先分配行内存，在分配列内存
 * @brief 注意使用malloc在堆上分配内存空间时，注意所在环境
 * （软/硬件）允许分配的最大空间大小
 */
uint16_t** create2DArray(uint16_t ROWS, uint16_t COLS) {
    uint16_t** array = (uint16_t **)malloc(ROWS * sizeof(uint16_t*));
	if(array == NULL){
		printf("array memory allocate failed!\r\n");
	}else{
		printf("array address is :0x%p\r\n",array);
	}
    for (int i = 0; i < ROWS; i++) {
        array[i] = (uint16_t *)malloc(COLS * sizeof(uint16_t));
		if(array[i] == NULL){
			printf("array[%d] memory allocate failed!\r\n",i);
		}else{
			printf("array[%d] memory allocate success! addr is 0x%p\r\n",i,array[i]);
		}
    }
    return array;
}

Frame *frame_ptr = NULL;

int main(){
	uint16_t row = 3;
	uint16_t col = 4;		
	frame_ptr =(Frame *)malloc(sizeof(Frame));

	frame_ptr->framebuf = create2DArray(row, col);
	printf("uint16_t occupy %d Byte Size\r\n",(int)sizeof(uint16_t));
	if ((frame_ptr->framebuf) == NULL){
		printf("failed to allocatte\r\n");
		return 1;
	}

	for(int i = 0 ; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
				frame_ptr->framebuf[i][j] = 2; 
		}
	}
	for(int i = 0 ; i < row ; i++){
		for(int j = 0 ; j < col ; j++){
			printf("%d ",frame_ptr->framebuf[i][j]);
		}
		printf("\n");
	}
}
