import subprocess

# Defining Dictionary Mappings
result_map = {
    True: "match success!",
    False: "match failed!"
}

# 测试用例：每个元素是一个包含命令和预期输出的元组
test_cases = [
    (["info w"], result_map[True]),
    (["info r"], result_map[True]),
    (["info   r"], result_map[True]),
    (["info   w"], result_map[True]),

    (["info a"], result_map[False]),
    (["info  364d"], result_map[False]),
    (["info     "], result_map[False]),
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

    (["x 10 0x1100"],result_map[True]),
    (["x 1 0x1100af87"],result_map[True]),
    (["x 10 0xffffffff"],result_map[True]),
    (["x 10 0xFFFFFFFF"],result_map[True]),
    (["x 120 0x12380aeb"],result_map[True])

]

def run_test(command, expected_output):
    """运行一个单独的测试"""
    try:
        # 将命令列表转换为一个空格分隔的字符串，作为子进程输入
        command_str = ' '.join(command)

        # 使用 subprocess.run 启动子进程，并捕获输出
        result = subprocess.run(
            ['./build/elf'],           # 执行的程序
            input=command_str+'\n',   # 向程序传递命令，模拟输入
            text=True,                  # 使用文本模式（解码 stdout）
            stdout=subprocess.PIPE,     # 捕获标准输出
            stderr=subprocess.PIPE      # 捕获标准错误输出
        )
        # 去除输出中的多余空白字符（例如换行符）
        stdout = result.stdout.strip()
        # 例如，假设回显的输入是命令本身，可以移除它
        stdout = stdout.replace(command_str,'').strip()

        # 检查错误输出
        if result.stderr:
            print(f"Error in stderr for command {command_str}: {result.stderr.strip()}")

        # 比较程序输出和期望输出
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



