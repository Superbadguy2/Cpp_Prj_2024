#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Frame{
	uint16_t **framebuf;
} Frame;

uint16_t** create2DArray(uint16_t ROWS, uint16_t COLS) {
    uint16_t** array = malloc(ROWS * sizeof(uint16_t*));
    for (int i = 0; i < ROWS; i++) {
        array[i] = malloc(COLS * sizeof(uint16_t));
    }
	printf("array address is :%p\r\n",array);
    return array;
}

Frame *frame_ptr = NULL;

int main(){
	uint16_t row = 3;
	uint16_t col = 4;		
	frame_ptr =(Frame *)malloc(sizeof(Frame));

	frame_ptr->framebuf = create2DArray(row, col);

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
