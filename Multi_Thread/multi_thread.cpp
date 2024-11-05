#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#define print_num 1000

void printA() {
	for(int i = 0; i  < print_num ; i++){
		std::cout << "A" << std::endl;
	}
}

void printB() {
	for(int i = 0; i < print_num ; i++){
		std::cout << "B" << std::endl;
	}

}

int main() {

}
