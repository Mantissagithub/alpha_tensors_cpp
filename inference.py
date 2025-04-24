import subprocess
import re
import matplotlib.pyplot as plt

matrix_sizes = [2**i for i in range(2, 11)]  # 4 to 1024
valid_sizes = []
normal_times = []
strassen_times = []
speedups = []

for size in matrix_sizes:
    cmd = f'g++ strassens-algo-even-optimzed.cpp -o strassens-algo-even-optimzed && echo {size} | ./strassens-algo-even-optimzed'
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, text=True)
    out, err = process.communicate()

    normal_match = re.search(r"Time taken by normal multiplication:\s+(\d+)", out)
    strassen_match = re.search(r"Time taken by Strassen's algorithm:\s+(\d+)", out)
    speedup_match = re.search(r"Speedup:\s+([\d.]+)", out)

    if normal_match and strassen_match and speedup_match:
        valid_sizes.append(size)
        normal_times.append(int(normal_match.group(1)))
        strassen_times.append(int(strassen_match.group(1)))
        speedups.append(float(speedup_match.group(1)))
    else:
        print(f"Skipped: size {size}\nOutput:\n{out}\nError:\n{err}")

plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(valid_sizes, normal_times, label='Normal', marker='o')
plt.plot(valid_sizes, strassen_times, label="Strassen's", marker='x')
plt.xlabel('Matrix Size (2^n)')
plt.ylabel('Time (μs)')
plt.title('Execution Time')
plt.legend()
plt.grid(True)

plt.subplot(1, 2, 2)
plt.plot(valid_sizes, speedups, label='Speedup', marker='s', color='purple')
plt.xlabel('Matrix Size (2^n)')
plt.ylabel('Speedup Factor')
plt.title('Strassen Speedup')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
