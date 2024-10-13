// Lyf_FFT_iFFT.h
#ifndef LYF_FFT_IFFT_H
#define LYF_FFT_IFFT_H

#include <iostream>
#include <complex>
#include <cmath> // 包含cmath头文件以使用acos函数
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

class Sample_Data {
	private:
		static const unsigned int FillSampleDataLength = 10;		// 填充采样数据长度数组
		std::array<unsigned int, FillSampleDataLength> Fixed_Sample_data_length; // 固定采样数据长度数组
	
	protected:
		using cpd = std::complex<double>; 	// complex number type
		static const double pi; 			// 圆周率
		const cpd _1i = cpd(0, 1); 			// 虚数单位
		std::vector<cpd> x; 				// 原始采样数据
		unsigned long Sample_Rate ; 		// 采样率, 单位为Hz/s
		enum class Win_Func {
			Hann_Window,
			Hamming_Window,
			Blackman_Window,
			Rectangular_Window	
		};									// 窗函数类型

	public:
		Sample_Data(); 													// 构造函数
		
		static unsigned int GetFillSampleDataLength(); 					// 获取固定采样数据长度

		unsigned int _32bit_reverse(unsigned int x);
		unsigned int _8bit_reverse(unsigned int x);

		std::vector<cpd> Data_UpPadding(std::vector<cpd>& x);			// 向上填充(扩展)原始采样数据使其长度为2的幂
		unsigned long Get_UpPadding_length(std::vector<cpd>& x);		// 获取向上填充后采样数据长度
		unsigned long Extened_sample_time_length(
			unsigned long UpPadding_length,
			unsigned long Sample_rate); 								// 扩展采样时间长度
		std::vector<cpd> Window_Function_Filter_Sample_Data(
			Win_Func win_fun,
			std::vector<cpd>& x,
			unsigned long Sample_time_length); 							// 窗函数滤波对数据进行处理
		std::vector<cpd> Radix_sort(std::vector<cpd>& x);				// 雷德算法对原始采样数据进行排序
		std::vector<cpd> X_butterfly(std::vector<cpd>& x);				// 蝴蝶算法实现FFT变换
		std::vector<double> Get_Frequency_Axis(
			std::vector<cpd>& x
			, unsigned long Fs
			, unsigned long Nfft);										// 获取频率轴
		std::vector<double> Get_Amplitude(
			std::vector<cpd>& x
			, bool is_normalized);										// 获取幅度
		std::vector<double> Get_Phase(std::vector<cpd>& x);				// 获取相位
		// 对结果进行归一化处理
		// 对结果进行可视化处理

		std::vector<cpd> Recursive_fft1(std::vector<cpd>& x);			// 经典的基2迭代FFT算法	
		void printHelloworld();  										// 用于测试
	
};


#endif // LYF_FFT_IFFT_H