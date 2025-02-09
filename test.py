import sys
import subprocess
import random

CMD_SPIKE   = "../spike/bin/spike ../riscv-pk/build/pk a.out"
TEST_COUNT  = 100

def run_command(misalign, sel, c, n):
    cmd = []
    cmd.append(CMD_SPIKE)
    cmd.append("-m" if misalign else "")
    cmd.append(sel)
    cmd.append(c)
    cmd.append(n)
    cmd = list(map(str, cmd))
    result = subprocess.run(" ".join(cmd), shell=True)
    return result.returncode == 0

def main():
    if len(sys.argv) != 3:
        print("Usage: python3 test.py misalign memset_num")
        exit()

    misalign    = sys.argv[1] == "1"
    memset_num  = int(sys.argv[2])

    for _ in range(TEST_COUNT):
        c = random.randint(0, 255)
        n = random.randint(0, 10000)
        if not run_command(misalign, memset_num, c, n):
            print("fail: memset_" + str(memset_num), "arg:", c, n)
            exit()    
    print("Success")

if __name__ == "__main__":
    main()