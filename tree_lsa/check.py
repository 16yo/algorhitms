f_ans = open("./ans.txt", 'r')
f_out = open("./out.txt", 'r')

s_ans = f_ans.readlines()
s_out = f_out.readlines()

f_ans.close()
f_out.close()

good = True

if len(s_out) != len(s_ans):
    print("Difference:")
    good = False

l = min(len(s_ans), len(s_out))

for i in range(0, l):
    if s_out[i] != s_ans[i]:
        print("Line " + str(i + 1) + ": out: " + s_out[i][:-1] + " - ans: " + s_ans[i][:-1])
        good = False

if good:
    print("Good")



# file1 = open("ans.txt",'r')
# file2 = open("out.txt",'r')

# file1_lines = file1.readlines()
# file2_lines = file2.readlines()

# for i in range(len(file1_lines)):
#     if file1_lines[i] != file2_lines[i]:
#         print("Line " + str(i+1) + " doesn't match.")
#         print("------------------------")
#         print("ANS: " + file1_lines[i])
#         print("OUT: " + file2_lines[i])

# file1.close()
# file2.close()
