from dotMatr import *

def TryDot(dot, *args, **kwargs):
    matr = [[]]
    try:
        matr, t = dot(*args, **kwargs)
        print("result matrix: ")
        printMatrix(matr)
    except ValueError as e:
        print("the matrices cannot be multiplied")
    return matr

def testDot(dot, rangeN, samples = 1):
    data = []
    for n in rangeN:
        matr = [[i * j for j in range(n)] for i in range(n)]
        avg_time = 0
        for _ in range(samples):
            _, t = dot(matr, matr)
            avg_time += t
        avg_time /= samples
        data.append(avg_time)
    print(data)
    return data
            

def inputMatrix(message):
    print(f"Input {message} matrix: ")
    n = int(input("input N: "))
    m = int(input("input M: "))
    matr = [[] for i in range(n)]
    for i in range(n):
        matr[i] = list(map(float, input().split()))

    print()
    return matr

def printMatrix(matr):
    for row in matr:
        for elem in row:
            print(elem, end=" ")
        print()
    print()

def equalMatr(matr_a, matr_b):
    if len(matr_a) != len(matr_b) or len(matr_a[0]) != len(matr_b[0]):
        return False
    
    for i in range(len(matr_a)):
        for j in range(len(matr_a[0])):
            if matr_a[i][j] != matr_b[i][j]:
                return False
    return True

def InputMode():
    matr_1 = inputMatrix("first")
    matr_2 = inputMatrix("second")
    m1 = TryDot(dotMatrix, matr_1, matr_2)
    m2 = TryDot(dotMatrixVinograd, matr_1, matr_2)
    m3 = TryDot(dotMatrixVinogradOptimizate, matr_1, matr_2)

    if not equalMatr(m1, m2) or not equalMatr(m1, m3) or not equalMatr(m2, m3):
        print("Error!")

test1 = range(100, 501, 100)
test2 = range(101, 502, 100)

test = test2
print([i for i in test])
std = testDot(dotMatrix, test)
vin = testDot(dotMatrixVinograd, test)
vinOpt = testDot(dotMatrixVinogradOptimizate, test)

for i, n in enumerate(test):
    print(n, std[i], vin[i], vinOpt[i])

"""
3
2
1 1
1 1
1 1
2
3
1 1 1
1 1 1
"""