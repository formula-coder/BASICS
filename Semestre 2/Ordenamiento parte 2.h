void ordenar (int **arrPunteros){

    for (int i = 0; i < 9; i++) {
        int imin = i;
        for (int j = i + 1; j < 10; j++) {
            if (**(arrPunteros + j) < **(arrPunteros + imin)) {
                imin = j;
            }
        }
        if (imin != i) {
            int *aux = *(arrPunteros + imin);
            *(arrPunteros + imin) = *(arrPunteros + i);
            *(arrPunteros + i) = aux;
        }
    }

}