2024-10-1
    使用前请详细阅读.vscode和CMakeLists.txt文件中的注释。
    确保按照了MinGW-w64和cmake软件
    cpp文件放在source文件夹中，头文件放在include文件夹中。

    1、完成代码编写后的项目构建、编译与链接：
        打开终端，进入项目根目录，输入命令：
        mkdir build
        cd build
        cmake .. -G "MinGW Makefiles"

        构建成功后进行项目的编译、链接生成可执行文件，输入命令：
        mingw32-make.exe

        对于已经构建过的文件，进入build文件夹，重新构建需要输入命令：
        cmake ..
        
        重新构建失败请将build文件夹中的所有内容删除，重新构建。输入命令：
        rm -rf build # linux下使用rm -rf build命令删除build文件夹
        rm -r -fo build # windows下使用rm -r -fo build命令删除build文件夹
        mkdir build
        cd build
        cmake .. -G "MinGW Makefiles"

    2、运行程序：
        进入build文件夹，输入命令：
        输入.\链接生成文件名.exe运行程序
        .\main.exe

    注意：
        文件使用cmake构建完成之后只要不对文件结构进行修改，只需要进行编译链接即可，不需要再次运行cmake命令。
        CMakeLists.txt文件中，CMAKE_BUILD_TYPE参数的设置，可以设置为Debug或Release，默认为Debug。

