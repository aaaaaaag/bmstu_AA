from sorts import *
from time import process_time 
from random import randint

def mode_input():
    arr = list(map(int, input("Введите массив: ").split()))

    print("Сортировка пузырьком с флагом:")
    print(bubble_sort(arr))

    print("Сортировка вставками")
    print(insertion_sort(arr))

    print("Сортировка выбором")
    print(selection_sort(arr))


def getTime(arr, func, samples = 2):
    t = 0
    for i in range(samples):
        copy_arr = arr.copy()
        t_start = process_time()
        func(copy_arr)
        t_end = process_time()
        t += t_end - t_start
    return t / samples

def testSort(arr, samples = 2):
    # getTime(arr, selection_sort, samples)
    print(f"{len(arr):8} {getTime(arr, bubble_sort, samples):10.5f} {getTime(arr, insertion_sort, samples):10.5f} {getTime(arr, selection_sort, samples):10.5f}")

def mode_test():
    range_n = (10, 50, 100, 250, 500, 1000, 2500)
    for n in range_n:
        arr = [randint(-1000, 1000) for _ in range(n)]
        arr.sort()
        testSort(arr, 300)

mode_test()