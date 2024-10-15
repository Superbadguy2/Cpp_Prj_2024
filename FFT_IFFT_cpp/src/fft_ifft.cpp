#include "../include/fft_ifft.h"

//构造函数
Sample_Data::Sample_Data()
{
    Fixed_Sample_data_length = {
        1 << 12, // 2^12 = 4096个采样点        4K
        1 << 14, // 2^14 = 16384个采样点       16K
        1 << 16, // 2^16 = 65536个采样点       64K
        1 << 18, // 2^18 = 262144个采样点      256K
        1 << 20, // 2^20 = 1048576个采样点     1M
        1 << 22, // 2^22 = 4194304个采样点     4M
        1 << 24, // 2^24 = 16777216个采样点    16M
        1 << 26, // 2^26 = 67108864个采样点    64M
        1 << 28, // 2^28 = 268435456个采样点   256M
        1 << 30  // 2^30 = 1073741824个采样点  1G
    };
};

const double Sample_Data::pi = acos(-1);

/*  fuction：使用递归对采样数据实现fft算法
    input：采样数据x
    output: fft结果
    algorithmic complexity：O(nlogn)
*/
std::vector<Sample_Data::cpd> Sample_Data::Recursive_fft1(std::vector<cpd>& x){
    // 递归终止条件
    if(x.size() == 1) return x; // 只有一个采样点，fft结果就是该点
    // n大于1时，递归，将x分成两个子序列X_e和X_o，分别对子序列进行fft
    std::vector<cpd> X_e(x.size()/2) , X_o(x.size()/2);
    for(int i = 0; i < static_cast<int>(x.size()/2); i++) 
	{// 将x分成两个子序列X_e和X_o
        X_e[i] = x[2*i];
        X_o[i] = x[2*i+1];
    }
    // 对子序列X_e和X_o分别进行fft
    std::vector<cpd> X_e_fft = Recursive_fft1(X_e);
    std::vector<cpd> X_o_fft = Recursive_fft1(X_o);
    // 计算fft结果
    std::vector<cpd> X_fft(x.size());
    cpd delta_w(cos(-2*pi/x.size()), sin(-2*pi/x.size())); // 计算旋转因子

    for(int i = 0; i < static_cast<int>(x.size()/2); i++)
	{       
        X_fft[i] = X_e_fft[i] + pow(delta_w,i) * X_o_fft[i];
        X_fft[i+x.size()/2] = X_e_fft[i] - pow(delta_w,i) * X_o_fft[i];
    }
    return X_fft;
};

/*  fuction：对使用雷德算法对原始采样数据进行排序后的数据进行蝴蝶变换
    input：重新排序后的数据x
    output: 蝴蝶变换结果
    algorithmic complexity：
*/
std::vector<Sample_Data::cpd> Sample_Data::X_butterfly(std::vector<cpd>& x)
{
    unsigned long n = x.size(); // 获取数据长度
    // 验证数据长度是否为2的幂
    if(n & (n-1)){
        std::cout << "Error: Data size is not a power of 2!" << std::endl;
        return x;       
    }

    std::vector<cpd> X_temp(n);
    X_temp = x;
    std::vector<cpd> X_butterfly(n); // 定义蝴蝶变换结果
    unsigned long butf_windowns = 2;// 蝴蝶变换窗口
    while(butf_windowns <= n){
        cpd delta_w(cos(-2*pi/butf_windowns), sin(-2*pi/butf_windowns)); // 计算旋转因子
        for(unsigned long i = 0; i < n; i = i + butf_windowns){
            for(unsigned long j = 0; j < butf_windowns/2; j++){
                X_butterfly[i+j] = X_temp[i+j] + pow(delta_w,j) * X_temp[i+j+butf_windowns/2];
                X_butterfly[i+j+butf_windowns/2] = X_temp[i+j] - pow(delta_w,j) * X_temp[i+j+butf_windowns/2];
            }
        }
        X_temp = X_butterfly; // 更新X_temp
        butf_windowns = butf_windowns * 2; // 蝴蝶变换窗口扩大
    }
    return X_butterfly;
}

/*  fuction：32bit位反转
    input：32位整数x为正常顺序的序号
    output: 32位整数x为反转顺序的序号
    algorithmic complexity：
*/
unsigned int Sample_Data::_32bit_reverse(unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    
    return((x >> 16) | (x << 16));
}

/*  function:8bit位反转
    input：8位整数x为正常顺序的序号
    output: 8位整数x为反转顺序的序号
    algorithmic complexity：
*/
unsigned int Sample_Data::_8bit_reverse(unsigned int x)
{
    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    return ((x >> 4) | (x << 4));
};

/*  function:   radix_sort雷德算法对原始采样数据进行排序，获取数据的下标
                首先将数组的下标转换为二进制数，除了首位下标不变外数组往后的每一位数据的下标都由上一位的下标决定
                对下标的二进制数进行高位加法：最高位若为0，则最高位变为1，其余位不变；
                若最高位为1，则将最高位变为0，次高位加1，若次高位也为1，则也将次高位变为0，第三高位加1，以此类推
    input：原始采样数据x
    output: 排序后的数据x
    algorithmic complexity：O(nlogn)???
*/
std::vector<Sample_Data::cpd> Sample_Data::Radix_sort(std::vector<cpd> &x)
{
    unsigned long n = x.size(); // 获取数据长度
    std::vector<cpd> sorted_x(n); // 定义排序后的数据
    unsigned int nbit = static_cast<unsigned int>(log2(n)); // 获取数据长度的二进制位数
    sorted_x[0] = x[0];
    // cout << "nbit = " << nbit << endl;
    unsigned int bit_in_num = 0;// Bit inverted ordinal number
    for (unsigned int i = 1; i < n; i = i + 1) {
        // 如果最高位是0，则将最高位置一即可
        if ((bit_in_num >> (nbit - 1)) == 0){
            bit_in_num = bit_in_num + (1 << (nbit - 1));
            sorted_x[i] = x[bit_in_num];
        }
        // 如果最高位是1
        else if ((bit_in_num >> (nbit - 1)) == 1){
            int j = nbit - 1;
            while (j > 0) {
                if ((bit_in_num >> j) == 1){
                    bit_in_num = bit_in_num - (1 << j); // 最高位为1时，将最高位置为0
                    if (bit_in_num >> (j - 1) == 0) { // 判断次高位是为0
                        bit_in_num = bit_in_num + (1 << (j - 1)); // 将次高位置为1，结束循环
                        j = 0;
                    }
                    else if (bit_in_num >> (j - 1) == 1) { // 次高位为1
                        j--; // 将次高位变为最高位
                    }
                }
            }
            sorted_x[i] = x[bit_in_num];
        }
        // cout << "bit_in_num = " << bit_in_num << endl;
    };
    return sorted_x;
};

/*  function: 采用循环填充的方式，向上填充(扩展长度)原始采样数据使其长度为2的幂
    input：原始采样数据x
    output: 对数据进行填充
    algorithmic complexity：O(n)
*/
std::vector<Sample_Data::cpd> Sample_Data::Data_UpPadding(std::vector<cpd> &x)
{
    unsigned long Signal_length = x.size();
    for(int i = 0; 
			i < static_cast<int>(Sample_Data::GetFillSampleDataLength());
			i++){
        if(Signal_length < Fixed_Sample_data_length[i]){
            unsigned long padding_length 
                = Fixed_Sample_data_length[i] - Signal_length;
            for(unsigned long j = 0; j < padding_length; j++){
                x.push_back(x[j]);
            }
        }
    }
    return x;
}

/*  function: 等效采样时间返回，由于之前以及对采样序列进行了填充，这里也需要将相应的时间进行延长
    以获取填充采样序列对应的等效采样时间
    input：Sample_length为填充采样序列长度，
           Sample_rate为采样率，单位为Hz/s
    output: 扩展后的等效采样时间,单位为ns
    algorithmic complexity：
*/
unsigned long Sample_Data::Extened_sample_time_length(unsigned long UpPadding_length, unsigned long Sample_rate)
{
    unsigned long Extened_sample_time = (UpPadding_length / Sample_rate) * 1e9;
    return Extened_sample_time;
}

/*  function: 接口函数，返回填充采样数据长度数组
    input：
    output: 填充采样数据长度数组
    algorithmic complexity：
*/
unsigned int Sample_Data::GetFillSampleDataLength()
{
    return FillSampleDataLength;
}

/*  function: 获取填充采样数据长度
    input：填充信号序列
    output: 填充采样数据长度
    algorithmic complexity：
*/
unsigned long Sample_Data::Get_UpPadding_length(std::vector<cpd> &x)
{
    return x.size();
}

/*  function: 获取频率轴
    input：填充信号序列
    output: 频率轴
    algorithmic complexity：
*/
std::vector<double> Sample_Data::Get_Frequency_Axis(
	std::vector<cpd> &x, 
	unsigned long Fs, 
	unsigned long Nfft)
{
    std::vector<double> Frequency_Axis(Nfft);   // 定义频率轴
    std::iota(Frequency_Axis.begin()            // 填充频率轴
       , Frequency_Axis.end()
       , 0);    

    // 计算“视觉分辨率” or “FFT分辨率” , DeltaRfft = Fs / Nfft
    // Fs为采样率 Hz/s，Nfft为FFT长度
    float DeltaRfft = Fs / (Nfft - 1);          // unit: Hz
    std::transform(Frequency_Axis.begin()
       , Frequency_Axis.end()
       , Frequency_Axis.begin()
       , [DeltaRfft](double value) {
        return value * DeltaRfft;
    });
    
    // 取一半区间
    Frequency_Axis.resize(Nfft / 2 + 1);
    return Frequency_Axis;
}

/*  function: 获取幅值
    input：填充信号序列
    output: 幅值
    algorithmic complexity：
*/
std::vector<double> Sample_Data::Get_Amplitude(
    std::vector<cpd> &x
    , bool is_normalized)
{
    std::vector<double> Amplitude(x.size());
    // 获取x的模到Amplitude中
    std::transform(x.begin()
       , x.end()
       , Amplitude.begin()
       , [](cpd value) {
        return abs(value);
    });

    // 归一化
    if (is_normalized){
        float ratio = 2 / x.size();
        std::transform(Amplitude.begin()
            , Amplitude.end()
            , Amplitude.begin()
            , [ratio](double value) {
                return value * ratio;
        });
    }

    // 取一半区间
    Amplitude.resize(x.size() / 2 + 1);
    return Amplitude;
}

/*  function: 获取相位
    input：填充信号序列
    output: 相位
    algorithmic complexity：
*/
std::vector<double> Sample_Data::Get_Phase(std::vector<cpd> &x)
{
    std::vector<double> Phase(x.size());
    // 获取x的相位到Phase中
    std::transform(x.begin()
       , x.end()
       , Phase.begin()
       , [](cpd value) {
        return atan2(value.imag(), value.real());
    });
    // 转换为角度制
    std::transform(Phase.begin()
       , Phase.end()
       , Phase.begin()
       , [](double value) {
        return value * 180 / Sample_Data::pi;
    });

    // 取一半区间
    Phase.resize(x.size() / 2 + 1);
    return Phase;
}

/*	for test
 *
 */
void Sample_Data::printHelloworld()
{
    std::cout << "Hello, world!" << std::endl;
}
