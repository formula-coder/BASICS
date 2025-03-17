

print("===========") 
print("Calculadora")
print("===========")

num_int = int(input("Ingrese un valor entre 1,2,3 y 4:"))
if num_int == 1:
    print("se ecogio calculadora")
    operacion = str(input("Escoja las distintas operaciones suma, resta, multiplicacion y division:"))
    if operacion == 'suma':
        print("se va a realizar una suma:")
        num_uno = int (input("ingrese el primer valor para la suma:"))
        num_dos = int(input("ingrese el segundo valor para la suma:"))
        resultado = num_uno + num_dos
        print("=============================")
        print("El resultado de la suma es:",resultado)
        print("=============================")
    elif operacion == 'resta':
        print("se va a realizar una resta:")
        num_uno = int(input("Ingrese el primer numero para la resta:"))
        num_dos = int(input("Ingrese el segundo numero para la resta:"))
        resultado = num_uno - num_dos
        print("=============================")
        print("El resultado de la resta es:",resultado)
        print("=============================")
    elif operacion == 'Division':
        print("se va a rrealizar una division:")
        num_uno = int(input("ingrese el primer numero para la division:"))
        num_dos = int(input("ingrese el segundo numero para la division:"))
        resultado = num_uno / num_dos
        print("===============================")
        print("El resultado de la divison es:", resultado)
        print("===============================")
    elif operacion == 'multiplicacion':
        print("se va a realizar una multiplicacion:")
        num_uno = int(input("Ingrese el primer valor para la multiplicacion:"))
        num_dos = int(input("Ingrese el segundo valor para la multiplicacion:"))
        resultado = num_uno * num_dos
        print("======================================")
        print("El resultado de la multiplicacion es:",resultado)
        print("======================================")
elif num_int == 2:
    print("Se escogio ecuacion general")
    num_uno = int(input("Ingrese el valor a:"))
    num_dos = int(input("ingrese el valor b:"))
    num_tres = int(input("ingrese el valor c:"))
    print("======================================")
    resultado = -num_dos + (num_dos**2 - 4*num_uno*num_tres)**0.5 / 2*num_uno
    print("======================================")
    print("El resultado de la ecuacion general es:",resultado)

elif num_int == 3:
    num_uno = int(input("ingrese un numero para determinar si el numero es par o impar"))
    if num_uno % 2 == 0 :
        print("El numero es par")
    else:
        print("El numero es impar")
elif num_int == 4:
    print("Vamos a promediar sus notas del colegio")
    num_uno = float(input("ingrese su nota de matematicas:"))
    num_dos = float(input("Ingrese su nota de ingles:"))
    num_tres = float(input("Ingrese su nota de ciencias sociales:"))
    num_cuatro = float(input("Ingrese su nota de español:"))
    num_cinco = float(input("ingrese su nota de educacion fisica:"))
    resultado = num_uno + num_dos + num_tres + num_cuatro + num_cinco 
    resultado = resultado / 5
    print("su promedio es:",resultado)
    if resultado >= 4.0:
        print("va pasando")
    else:
        print("tienes que mejorar")

else:
    print("no se escogio ninguna opcion")
    print("escoja un valor")

