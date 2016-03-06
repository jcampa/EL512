
for (i = l; i + l < j; i = j + l) {
  if (i + l > 3) {
    i = l + 3;
  }
  else
  {
    l = l - i + 5;
  }
}

// condiciones negadas
// i + l - j >= 0
// i + l - 3 <= 0

//Equivalente en assembler
/*i = l + 1*/
        LDAA    l
        STAA    i
L2:
// i + l - j >= 0
        LDAA    i
        ADDA    l
        CMPA    j //A –M
        BGE     <L1> // branch if >= zero
/* if  i + l - 3 <= 0*/
        LDAA    l
        ADDA    i
        CMPA    #3
        BLE     <L3>
/* i = l + 3;*/
        LDAA    l
        ADDA    #3
        STAA    i
        BRA/JMP L4
L3:
        LDAA    l
        ADDA    #3
        SUBA    i
        STAA    l
L4:
/* i*=2 */
        LDAA    i
        ADDA    j
        STAA    i
        BRA     <L2> // cuando la distancia a la que va a saltar es menor a 127
L1:
