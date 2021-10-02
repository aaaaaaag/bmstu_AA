def bubble_sort(mass, cmp = lambda a, b: a - b):
    len_mass= len(mass)
    for i in range(len_mass, 0, -1):
        need = False
        for j in range(1, i):
            if cmp(mass[j-1], mass[j]) > 0:
                mass[j-1], mass[j] = mass[j], mass[j-1]
                need = True
        if not need: break
    return mass

def insertion_sort(mass, cmp = lambda a, b: a - b):
    len_mass = len(mass)
    for i in range(1, len_mass):
        v = mass[i]
        j = i
        while cmp(mass[j-1], v) > 0 and j > 0:
            mass[j] = mass[j-1]
            j -= 1
        mass[j] = v
    return mass

def selection_sort(mass, cmp = lambda a, b: a - b):
    len_mass = len(mass)
    for i in range(len_mass):
        min_i = i
        for j in range(i+1, len_mass):
            if cmp(mass[j], mass[min_i]) < 0:
                min_i = j
        mass[min_i], mass[i] = mass[i], mass[min_i]
    return mass

if __name__ == "__main__":
    a = [3, 2, 1]
    print(bubble_sort(a))
    print(insertion_sort(a))
    print(selection_sort(a))