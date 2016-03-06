
for (int i = 0; i < l; i++) {
  /* code */
}

// condicion negada
i > =l
i - l >= 0

//conceptos:
//banderas
  Z: zero
  C: carry // cuando es sin signo
  N: negative
  V: overflow

  // adressing mode

  EXT: extendido
  DIR: directo
  IMM: inmediato

//Equivaletne en ascembler
CLR i;  // inicializo i = 0
label_for:   
        LDDA i; // muevo la variable i a registro A
        CMPA l // comparo el registro A con la memoria l
        BHS <labbel> // salta a la etiquta // ale del for.. SIN SIGNO. con signo se utiliza (BGE)
        /* code */
        INC i   // incremento la variable i del registro A
        BRA <labere_for>  //

labbel:
/* code */

// [para pasar a complemento a 2 lo paso a complemento a 1 y le sumo 1]

SUMAR CON DOS BYTES.
TRY CATCH a mano para ver si hubo overflow.


//1do parcial
  traduccion a ascembler sin validacion.

//2do parcial
  con validaciones.
  penalidad por tiempo.
  20 por dia re retraso.

// practico
  ultimo dia de clases.
  el que ovidio pida
  assembler de PIC

//
