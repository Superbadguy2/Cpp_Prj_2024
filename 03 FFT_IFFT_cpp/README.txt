2024-10-1
    ʹ��ǰ����ϸ�Ķ�.vscode��CMakeLists.txt�ļ��е�ע�͡�
    ȷ��������MinGW-w64��cmake���
    cpp�ļ�����source�ļ����У�ͷ�ļ�����include�ļ����С�

    1����ɴ����д�����Ŀ���������������ӣ�
        ���նˣ�������Ŀ��Ŀ¼���������
        mkdir build
        cd build
        cmake .. -G "MinGW Makefiles"

        �����ɹ��������Ŀ�ı��롢�������ɿ�ִ���ļ����������
        mingw32-make.exe

        �����Ѿ����������ļ�������build�ļ��У����¹�����Ҫ�������
        cmake ..
        
        ���¹���ʧ���뽫build�ļ����е���������ɾ�������¹������������
        rm -rf build # linux��ʹ��rm -rf build����ɾ��build�ļ���
        rm -r -fo build # windows��ʹ��rm -r -fo build����ɾ��build�ļ���
        mkdir build
        cd build
        cmake .. -G "MinGW Makefiles"

    2�����г���
        ����build�ļ��У��������
        ����.\���������ļ���.exe���г���
        .\main.exe

    ע�⣺
        �ļ�ʹ��cmake�������֮��ֻҪ�����ļ��ṹ�����޸ģ�ֻ��Ҫ���б������Ӽ��ɣ�����Ҫ�ٴ�����cmake���
        CMakeLists.txt�ļ��У�CMAKE_BUILD_TYPE���������ã���������ΪDebug��Release��Ĭ��ΪDebug��

