# Compara dos números e imprime el resultado
n1 = int(input("Ingresa el primer número: "))
n2 = int(input("Ingresa el segundo número: "))
if n1 > n2:
    print(n1, "es mayor que", n2)
elif n1 < n2:
    print(n1, "es menor que", n2)
else:
    print(n1, "es igual a", n2)
