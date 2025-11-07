# FAST standard input
import sys
input = sys.stdin.readline 

n = int(input())
arr = list(map(int, input().split()))
sys.stdout.write(str(sum(arr)) + "\n")

# FOR FILES
with open("input.txt", "r") as fin, open("output.txt", "w") as fout:
    n = int(fin.readline())
    arr = list(map(int, fin.readline().split()))
    fout.write(str(sum(arr)) + "\n")
