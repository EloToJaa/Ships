import os
import filecmp
import shutil

dir = "D:\\"
dir = os.path.join(dir, "VS Projects", "Ships", "Debug")
exe_name = "Ships"
n = 33

errors = []

if os.path.isfile(f"{exe_name}.exe"):
    os.remove(f"{exe_name}.exe")
shutil.copy(f"{dir}\\{exe_name}.exe", "./")
if os.path.isdir("mout/"):
    shutil.rmtree("mout/")
os.mkdir("mout/")

test_nr = [i for i in range(1, n + 1)]

for i in test_nr:
    print(f"Sprawdzam test nr {i}")
    os.system(f"{exe_name}.exe < ./in/ship{i}.in > ./mout/ship{i}.out")
    with open(f"./mout/ship{i}.out") as f:
        content = f.read()
    if len(content) > 0 and content[-1] == '\n':
        content = content[:-1]
        with open(f"./mout/ship{i}.out", "w") as f:
            f.write(content)

    if filecmp.cmp(f"out/ship{i}.out", f"mout/ship{i}.out") == 0:
        errors.append(i)

if len(errors) == 0:
    print("Brak bledow")
else:
    print("Bledy w testach:", end=" ")
    for error in errors:
        print(error, end=" ")

