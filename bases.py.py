#imprimir en pantalla (print)
print("hola mundo")

#variables son las que almacenan texto no pueden contener espacios
    #numeros enteros (llamados int)
    #Los numeros decimales o reales(float)
    #los que almacenan texto se les llama (strings)
print("Esto es una suma")
numero_uno = 2
numero_dos = 4
resultado = numero_uno + numero_dos
print(resultado)

"""Cadena de caracteres(strings) son una serie de caracteres compuestas por letras,numeros, signos y simbolos su funcion es la interaccion con el usuario
#La asignacion, la concatenacion, la busqueda, la busqueda, la extraccion y la comparacion"""

#La asignacion, consiste en asignar una cadena de carecteres a otra(+-)
mensaje = "hola"
mensaje += " "
mensaje += "como estas"
mensaje += " "
mensaje+="Ernesto"
print(mensaje)

print("esto es una resta")
x= 25
x-= 35
print(x)

#La concatenacion, es una operacion que consiste en unir dos cadenas o mas, para formar una cadena de mayor tamaño es necesario utilizar +
mensaje = "hi"
espacio =" "
nombre ="ernesto"
print(mensaje+espacio+nombre)

#La busqueda, consiste en localizar dentro de una cadena, una subcadena mas pequeña a un caracter(find)
mensaje="hi ernesto"
buscar_subcadena = mensaje.find("ernesto")
print(buscar_subcadena)

#La extraccion, se trata de sacarfuera de una cadena, una porcion de la misma segun su posicion dentro de ella.(mensaje[1:8])

mensaje ="Hola ernesto"
extraer_subcadena = mensaje[0:8]
print(extraer_subcadena)

#La comparacion, se utiliza para comparar dos cadenas de caracteres(==)

mensaje_uno = "Hola"
mensaje_dos = "Hola" 
print(mensaje_uno == mensaje_dos)

"""Palabras reservadas, son para uso exclusivo, no pueden ser utilizadas para identificar y nombrar variables.
tienen un significado asignado (28)
and, del, for, is , raise, assert, if, else, elif, from, lambda, return, break, global, not, try class, except, or, while, continue, exec, import, yield, def, finally, in, print."""

prinT = 5
Print = 6
resultado = prinT + Print
print(resultado)

#Opetadores aritmeticos, son los simbolos que se utilizan para realizar operaciones matematicas
#suma(+), resta(-), multiplicacion(*), division(/), modulo(%), potencia(**), division entera(//)

print("suma")
x = 5
y = 6
resultado = x + y
print("El resultado de la suma es:"+ str(resultado))

print("resta")
x = 5
y = 15
resultado = x - y
print("El resultado de la resta es:"+ str(resultado))

print("multiplicacion")
x = 5
y = 6
resultado = x * y
print("El resultado de la multiplicacion es:"+ str(resultado))

print("division")
x = 30
y = 6
resultado = x / y
print("El resultado de la division es:"+ str(resultado))

print("modulo")
x = 30
y = 8
resultado = x % y
print("El resultado del modulo es:"+ str(resultado))

print("potencia")
x = 5
y = 6
resultado = x ** y
print("El resultado de la potencia es:"+ str(resultado))

print("division entera")
x = 36
y = 6
resultado = x // y
print("El resultado de la division entera es:"+ str(resultado))

"""Tipos de datos:
    int: son los numeros enteros, son aquellos que no tienen parte decimal tanto positivos como negativos
    Long: son los numeros enteros muy grandes
    float: son los numeros decimales, son aquellos que tienen parte decimal
    complex: son los numeros complejos son los que tienen parte real e imaginaria
    string: son las cadenas de caracteres
    Boleano: son los valores de verdadero o falso(true o false)
    List: son listas de datos"""

#tipo de dato entero o largo
numero_uno = 15
print(numero_uno, type(numero_uno))

#tipo de dato flotante
numero_flotante = 15.5
print(numero_flotante, type(numero_flotante))

#tipo de dato complejo
numero_complejo = 5 + 6j
print(numero_complejo, type(numero_complejo))

#tipo de dato string
cadena = "hola mundo"
print(cadena, type(cadena))

#tipo de dato boleano
verdadero_falso = 3 == 3
print(verdadero_falso, type(verdadero_falso))

"""Entrada de datos, es la forma en la que el usuario puede interactuar con el programa, para ingresar datos se utiliza la funcion input()"""

palabra = input("ingrese su nombre:")
num_int = int(input( "introduzca numero entero:"))
num_float = float(input("introduzca numero flotante:"))
num_complex = complex(input("introduzca numero complejo:"))
print("string:",palabra,)
print("entero:",num_int)
print("flotante:",num_float)
print("complejo:",num_complex)

nombre = input("ingrese su nombre:")
print("hola "+ nombre +",vamos a realizar una suma")
num_uno = int(input("introduce el primer valor:"))
num_dos = int(input("introduce el segundo valor:"))
resultado = num_uno + num_dos
print("el resultado de la suma es:", resultado)

"""Condicionales, son estructuras de control que permiten evaluar si una o mas condiciones se cumplen, para ejecutar un bloque de codigo determinado"""

#1. Sentencia condicional simple if
 #if condicion logica:
    #instrucciones no tienen limite

nombre =input("ingrese el nombre:")
print("hola "+ nombre+",deseo saber su edad")
edad = int(input("ingrese su edad:"))
if edad == 18:
     print(nombre,"es mayor de edad")
print("gracias por su respuesta")

#2. Sentencia condicional if else
num_uno =5
if num_uno == 5:
    print("el numero es igual a 5")
else:
    print("el numero no es igual a 5")

num_uno =10
if num_uno == 5:
    print("el numero es igual a 5")
else:
    print("el numero no es igual a 5")

"""3. Sentencia condicional if elif else multiuples"""
# podemos encontrar multiples condiciones en una misma estructura
#nos permite elegir una ruta entre varias posibles, con base al valor que actua como selector.

"""if condicion logica:
    Instruccion
elif condicion logica:
    Instruccion
else:
    Instruccion"""

num_uno = 5
if num_uno == 5:
    print("el numero es igual a 5")
elif num_uno == 2:
    print("el numero es igual a 2")
else:
    print("el numero no es igual a 5 ni a 2")
print("fin del programa")

"""Sentencia condicional anidada, es cuando presentan por el camino de verdadero o falso de una sentencia condicional hay otra sentencia condicional"""
"""operadores relacionales,, dentro de una sentencia condicional, si el resultado de la comparacion es correcto, la expresion o condicion es considereada verdadera y en caso contrario es falsa""" 
""" < menor que, > mayor que, <= menor o igual que, >= mayor o igual que, == igual que, != diferente que"""

"""operadores logicos, son los que permiten combinar dos o mas condiciones, para formar una sola condicion compuesta"""
#conjuncion (and), disyuncion (or), negacion (not)

if num_uno == 5 and num_uno < 10:
    print("el numero es igual a 5 y menor que 10")
else:
    print("el numero no es igual a 5 y menor que 10")

if num_uno == 5 or num_uno < 10:
    print("el numero es igual a 5 o menor que 10")

if not num_dos > 5:
    print("el numero no es mayor que 5")
else:
    print("el numero es mayor que 5")

#Conjuncion
print("conjuncion(and)")
num_uno = int(input("ingrese un numero mayot a 2 y menor a 5:"))

if num_uno > 2 and num_uno < 5:
    print("el numero",num_uno,"cumple con la condicion")
else:
    print("el numero",num_uno,"no cumple con la condicion")

#Disyuncion
print("disyuncion(or)")
palabra = input("Para cumplir con la condcion escribe si o yes:")
if palabra == "si" or palabra == "yes":
    print("has cumplido con la condicion")
else:
    print("no has cumplido con la condicion")

#Negacion
print("negacion(not)")
num_uno = int(input("ingrese un numero igual a 5:"))
if not num_uno == 5:
    print("el numero no es igual a 5 y si cumple la comdicion")
else:
    print("el numero es igual a 5 y no cumple la condicion")

"""Operador de asignacion, es el simbolo que se utiliza para asignar un valor a una variable"""
# =, +=, -=, *=, /=, %=, **=, //=
""" X = 5, X += 5, X -= 5, X *= 5, X /= 5, X %= 5, X **= 5, X //= 5"""