//Visualizar la tarifa de la luz según el gasto de corriente
eléctrica. Para un gasto menor de 1 000 kwh la tarifa es 1.2,
entre 1 000 y 1 850 kwh es 1.0 y mayor de 1 850 kwh, 0.9.
Sentencias If y Switch

#include <iostream>
#include <studio.h>
using namespace std;

int main(){
   float tarifa, gasto;
   cout <<"Ingrese el gasto de corriente electrica en kwh:";
    cin >> gasto;
    
    if (gasto < 1000){
        tarifa = 1.2;
    }
    else if (gasto >= 1000 && gasto <= 1850){
        tarifa = 1.0;
    }
    else {
        tarifa = 0.9;
    }
}


//Una empresa quiere hacer una compra de varias piezas de la
misma clase a una fabrica de refracciones. La empresa,
dependiendo del monto total de la compra, decidirá que
hacer para pagar al fabricante.
Sí el monto total de la compra excede de $9.000.000 la
empresa tendrá la capacidad de invertir de su propio dinero
un 55% del monto de la compra, pedir prestado al banco un
30% y el resto lo pagará solicitando un crédito al fabricante.
Sí el monto total dela compra no excede los $9.000.000 la
empresa tendrá capacidad de invertir de su propio dinero un
70% y el restante 30% lo pagará solicitando crédito al
fabricante. El fabricante cobra por concepto de intereses un
20% sobre la cantidad que se le pague a crédito.v

#include <iostream>
#include <stdio.h>
using namespace std;

int main()
float compra, inversion, banco, credito, total;
cout << "Ingrese el monto total de la compra: ";
cin >> compra;

if(compra > 9000000){
    inversion = compra * 0.55;
    banco = compra * 0.30;
    credito = compra * 0.15;
    total = credito + (credito * 0.20);
    cout <<"El total de la inversion es :"<<inversion<< endl;
    cout <<"El total a pedir al banco es: "<<banco<< endl;
    cout <<"El total a pagar al fabricante es: "<<total<< endl; 

    else( compra <= 9000000){
        inversion = compra * 0.70;
        credito = compra * 0.30;
        total = credito + (credito * 0.20);
        cout <<"El total de la inversion es: "<<inversion<< endl;
        cout <<"El total a pagar al fabricante es: "<<total<< endl;
    }
    cout<<" Gracias por su compra"<< endl;
    return 0;
    
}