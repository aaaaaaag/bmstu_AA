# [process_time](https://docs-python.ru/standart-library/modul-time-python/funktsija-process-time-modulja-time/)
# Функция process_time() модуля time возвращает значение в долях секунды суммы системного и пользовательского 
# процессорного времени текущего процесса. 
# Функция time.process_time() не включает время, прошедшее во время сна.

from time import process_time 

def dotMatrix(matr_a : list, matr_b: list) -> (list, float):
    if (len(matr_b) != len(matr_a[0])):
        raise ValueError
    
    m = len(matr_a)
    n = len(matr_a[0])
    q = len(matr_b[0])
    
    matr_c = [[0] * q for i in range(m)]

    t_start = process_time()
    for i in range(m):
        for j in range(q):
            for k in range(n):
                matr_c[i][j] = matr_c[i][j] + matr_a[i][k] * matr_b[k][j]
    t_end = process_time()

    return matr_c, t_end - t_start

def dotMatrixVinograd(matr_a : list, matr_b: list) -> (list, float):
    if (len(matr_b) != len(matr_a[0])):
        raise ValueError
    
    m = len(matr_a)
    n = len(matr_a[0])
    q = len(matr_b[0])
    matr_c = [[0] * q for i in range(m)]

    row = [0] * m
    col = [0] * q
    t_start = process_time()
    for i in range(m):
        for j in range(n // 2):
            row[i] = row[i] + matr_a[i][2*j] * matr_a[i][2*j + 1]
    
    for j in range(q):
        for i in range(n // 2):
            col[j] = col[j] + matr_b[2*i][j] * matr_b[2*i+1][j]

    for i in range(m):
        for j in range(q):
            matr_c[i][j] = -row[i] - col[j]
            for k in range(n//2):
                matr_c[i][j] = matr_c[i][j] + (matr_a[i][2*k+1] + matr_b[2*k][j]) * (matr_a[i][2*k] + matr_b[2*k+1][j])

    if n % 2:
        for i in range(m):
            for j in range(q):
                matr_c[i][j] = matr_c[i][j] + matr_a[i][n-1] * matr_b[n-1][j]
    t_end = process_time()

    return matr_c, t_end - t_start

def dotMatrixVinogradOptimizate(matr_a : list, matr_b: list) -> (list, float):
    if (len(matr_b) != len(matr_a[0])):
        raise ValueError
    
    m = len(matr_a)
    n = len(matr_a[0])

    q = len(matr_b[0])
    matr_c = [[0] * q for i in range(m)]

    row = [0] * m
    col = [0] * q
    t_start = process_time()

    for i in range(m):
        for j in range(1, n, 2):
            row[i] -= matr_a[i][j] * matr_a[i][j - 1]
    
    for j in range(q):
        for i in range(1, n, 2):
            col[j] -= matr_b[i][j] * matr_b[i - 1][j]

    for i in range(m):
        for j in range(q):
            buf = row[i] + col[j]
            for k in range(1, n, 2):
                buf += (matr_a[i][k - 1] + matr_b[k][j]) * (matr_a[i][k] + matr_b[k-1][j])
            matr_c[i][j] = buf

    if n % 2:
        n1 = n - 1
        for i in range(m):
            for j in range(q):
                matr_c[i][j] += matr_a[i][n1] * matr_b[n1][j]
    t_end = process_time()

    return matr_c, t_end - t_start