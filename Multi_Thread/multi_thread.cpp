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

    // 使用std::thread构造函数启动线程，并将结果存储到容器中
    std::vector<std::thread> threads;
    threads.emplace_back(printA);
    threads.emplace_back(printB);

    // 等待线程执行完成
    for(auto& th : threads){
        th.join();
    }
	return 0;
}
