import subprocess

#  Defining Dictionary Mappings
result_map = {
    True:"match success!\n",
    False:"match failed!\n"
}

test_cases = [
    (["info w"], result_map[True]),
    (["info r"], result_map[True]),
    (["info   r"], result_map[True]),
    (["info   w"], result_map[True]),

    (["info a"], result_map[False]),
    (["info  364d"], result_map[False]),
    (["info     \r"], result_map[False]),
    (["info w 123"], result_map[False]),
    (["info r -a*!!"], result_map[False]),
    (["info w /sza"], result_map[False]),

    (["si 10"], result_map[True]),
    (["si 10086"], result_map[True]),
    (["si 0"], result_map[True]),
    (["si "], result_map[True]),
    (["si   10"], result_map[True]),

    (["si -10"], result_map[False]),
    (["si -0"], result_map[True]),
    (["si abc"], result_map[False]),
    (["si ,abc"], result_map[False]),
    (["si 1.23"], result_map[False]),
    (["si 100086"], result_map[False]),
    (["si 10 15*!"], result_map[False]),
    (["si 1.23 abc"], result_map[False]),
    (["si -0.23"], result_map[False]),

]

def run_test(command, expected_output):
    """运行一个单独的测试"""
    try:
        # 将命令列表转换为一个空格分隔的字符串，作为子进程输入
        command_str = ' '.join(command)

        # 启动子进程，并控制输入输出
        process = subprocess.Popen(
            ['./build/elf'],           # 执行的程序
            stdin=subprocess.PIPE,     # 允许我们向子进程传递输入
            stdout=subprocess.PIPE,    # 捕获标准输出
            stderr=subprocess.PIPE,    # 捕获标准错误
            text=True                   # 使用文本模式
        )

        # 向子进程逐行输入数据
        stdout, stderr = process.communicate(input=command_str + '\n')  # 传递输入，并加上换行符

        # 获取程序输出
        if stdout == expected_output:
            print(f"Test passed for command: {command_str}")
        else:
            print(f"Test failed for command: {command_str}")
            print(f"Expected: {expected_output}")
            print(f"Got: {stdout}")

    except subprocess.CalledProcessError as e:
        print(f"Error running test for command: {command_str}: {e}")
    except Exception as e:
        print(f"Error running test for command: {command_str}: {e}")

def run_all_tests():
    """批量运行所有测试用例"""
    for command, expected_output in test_cases:
        run_test(command, expected_output)

if __name__ == "__main__":
    run_all_tests()

