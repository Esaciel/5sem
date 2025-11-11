#!/usr/bin/env python3
import sys
import subprocess
import glob
import os

# 1. расставить в проге timestamp("msg");
# 2. собрать
# 3. запустить в директори с app-cli-release

# 0.5 максимум потоков - 25 + 1 рут = 26 латинских букв

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} N")
    sys.exit(1)

N = int(sys.argv[1]) # число потоков
if N < 0:
    print("N must be a positive integer or 0")
    sys.exit(1)

subprocess.run(["./app-cli-release", "../stuff/500.gv", "5", str(N), "1"], check=True)

files = glob.glob("out_*")
expected_count = N + 1
if len(files) != expected_count:
    print(f"Warning: expected {expected_count} out_* files, found {len(files)}")

lines = []
for f in files:
    with open(f, encoding="utf-8") as fin:
        for line in fin:
            parts = line.strip().split('\t\t\t\t', 1)
            if len(parts) < 2:
                continue
            timestamp, message = parts[0], parts[1]
            lines.append((timestamp, message, f))

lines.sort(key=lambda x: x[0])

unique_names = []
seen = set()
for _, __, name in lines:
    if name not in seen:
        seen.add(name)
        unique_names.append(name)

replacement_names = {}
for i, name in enumerate(unique_names):
    if i >= 26:
        raise ValueError("Too many unique names > 26")
    letter = chr(65 + i)
    nname = " " * i + letter + " " * (N - 1 - i)
    replacement_names[name] = nname

output_file = f"sorted_{N}.txt"
with open(output_file, "w", encoding="utf-8") as fout:
    for ts, msg, oldname in lines:
        name = replacement_names[oldname]
        fout.write(f"{ts}\t{name}\t\t\t{msg}\n")

for f in files:
    try:
        os.remove(f)
    except Exception as e:
        print(f"Failed to remove {f}: {e}")
