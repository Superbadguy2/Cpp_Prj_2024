#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// cx和cy是序列的初始实数和虚数部分
#define cx -0.7;
#define cy 0.27015;

// GenerateJulia_fpu() is a function that generates a Julia set using the Mandelbrot set algorithm
// It uses a floating-point version of the algorithm that uses FPU instructions to improve performance
// The function takes the following parameters:
// width and height are the dimensions of the image in pixels
// cx and cy are the coordinates of the center of the Julia set
// zoom is the zoom factor
// max_iter is the maximum number of iterations before the algorithm stops
// image is a pointer to the image buffer that will be filled with the Julia set
// The function returns nothing, but it fills the image buffer with the Julia set
// The image buffer is a 1D array of unsigned chars, with each pixel represented by 3 consecutive values (R, G, B)
// The image buffer should be freed after use to avoid memory leaks
void GenerateJulia_fpu(uint16_t width, uint16_t height, uint16_t x_offset, uint16_t y_offset,double radius,
  uint8_t zoom, int max_iter, unsigned char* image) {
    double z_real, z_imag;
    int x, y, i;

    // Loop through each pixel in the image and compute its color value
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            // Convert pixel coordinates to complex numbers
            z_real = (x - x_offset) / zoom;
            z_imag = (y - y_offset) / zoom;
            i = 0;
            // Compute the Mandelbrot set using the floating-point version of the algorithm
            // The algorithm stops when the point escapes the Mandelbrot set or reaches the maximum number of iterations
            // The color value is the number of iterations it took to escape the set or reach the maximum number of iterations
            // If the point does not escape the set within the maximum number of iterations, the color value is 0
            // Otherwise, the color value is the number of iterations it took to escape the set
            while (z_real * z_real + z_imag * z_imag < (radius) * (radius) && i < max_iter) {
                z_real = z_real * z_real - z_imag * z_imag + cx;
                z_imag = 2 * z_real * z_imag + cy;
                i++;
            }
            // Convert iteration count to color value
            image[y * width + x] = i;
            if (i == max_iter) {
                image[y * width + x] = 0;
            }
        }
    }
}

int main() {   
    // Set parameters for Julia set
    // You can modify these parameters to generate different Julia sets
    // note: the image size should be a multiple of 8 for SIMD optimization
    // note: the image size should be a power of 2 for faster rendering
    // width and height should be no greater than 1024
    // width is the number of pixels in the horizontal direction
    // height is the number of pixels in the vertical direction
    // width与height是图像像素点的数量，最大不能超过1024
    // 图像尺寸应为8的倍数，以便进行SIMD优化
    // 图像尺寸应为2的幂，以便快速渲染  
    uint16_t width = 255;
    uint16_t height = 255;
    // cx and cy are the coordinates of the center of the Julia set，
    // zoom is the zoom factor
    // max_iter is the maximum number of iterations before the algorithm stops
    // zoom是放大倍数, max_iter是迭代次数的上限, radius是计算的序列的半径
    // 对于计算的序列而言，序列趋向于无穷时的点才包含在Julia set中
    // 但是计算不可能无穷的进行下去，因此需要设定一个迭代次数的上限
    // 对于Julia set而言，迭代次数越多，图像越逼真，但也越容易越界，因此需要合理设置max_iter
    // 对于图像尺寸而言，越大越好，尤其是对于计算性能要求高的应用，尺寸应为2的幂，以便快速渲染
    // 对于图像尺寸的选择，需要结合具体的应用场景，例如对于图像处理而言，尺寸越大越好，尤其是对于高分辨率图像的处理
    uint16_t zoom = 100;
    uint8_t max_iter = 128;
    uint16_t x_offset = 0;
    uint16_t y_offset = 0;
    double radius = 2.0;
    // Allocate memory for the image buffer
    unsigned char* image = (unsigned char*)malloc(width * height * sizeof(unsigned char));

    GenerateJulia_fpu(width, height, x_offset, y_offset, radius, zoom, max_iter, image);
    // Save the image to a file in ppm, ppm格式保存图片
    // P6表示图像格式为PPM，后面是图像尺寸，255表示最大颜色值
    // 接下来是图像数据，每个像素点由3个字节组成，分别表示红色、绿色、蓝色的强度值
    // 图像数据是从左到右、从上到下顺序排列的，每个像素点的三个字节值是连续的
    // 因此，图像数据是width * height * 3个字节
    // 最后，写入文件
    FILE* fp = fopen("julia.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            fprintf(fp, "%c%c%c", image[i * width + j], image[i * width + j], image[i * width + j]);
        }
        fprintf(fp, "\n");
    }
    // Close the file
    fclose(fp);
    // Free the image buffer
    free(image);
    return 0;
}