// opcion 1: vector de vectores
// opcion 2: mapeo del punto (x,y)
//
// (i, j) -> i*m + j * sizeof(dato)
//
//
//   5
// * 4
// ---
// 2 0
// A B     // B es el bit menos significativo

int v[10][5];
v[i][j] = m

//(i,l) i*10 + l

      LDAA    i       // cargamos la variable i al registro A
      LDAB    #5      // cargamos 5 al registro B
      MUL             // A * B = D
      ADDD    l       // D + l -> D
//
// Repasar funciones, paso de parametros, retorno
// Tipos de variables, volatiles, estaticas, globales, scope
