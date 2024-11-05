import subprocess

test_cases = [
    (["info w"], "match success!\n"),
    (["info r"], "match success!\n"),
    (["info a"], "match failed!\n"),
    (["info  364d"], "match failed!\n"),
    (["info     "], "match failed!\n")
]

def run_test(command, expected_output):
    """运行一个单独的测试"""
    try:
        # 将命令列表转换为一个空格分隔的字符串，作为子进程输入
        command_str = ' '.join(command)

        # 调用外部程序，并提供标准输入（通过 input 参数）
        result = subprocess.run(
            ['./build/elf'],  # 执行命令
            input=command_str,  # 向子进程提供标准输入
            capture_output=True,  # 捕获标准输出和错误
            text=True,            # 结果以文本格式返回
            check=True            # 如果子进程返回非零退出状态，抛出异常
        )

        # 获取程序输出
        output = result.stdout
        if output == expected_output:
            print(f"Test passed for command: {command_str}")
        else:
            print(f"Test failed for command: {command_str}")
            print(f"Expected: {expected_output}",end='')     # 不加额外换行
            print(f"Got: {output}")     # 默认换行

    except subprocess.CalledProcessError as e:
        print(f"Error running test for command: {command_str}: {e}")

def run_all_tests():
    """批量运行所有测试用例"""
    for command, expected_output in test_cases:
        run_test(command, expected_output)

if __name__ == "__main__":
    run_all_tests()

