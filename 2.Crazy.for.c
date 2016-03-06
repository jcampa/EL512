
for (i = l + 1; i < l + 1; i*=2) {
  if (l > i) {
    l = i - l;
  }
}

// condicion negada
//  i >= l + 1
//  i - l - 1 >= 0

//Equivalente en ascembler
/*i = l + 1*/
        LDAA    l
        INCA
        STAA    i

// i - l - 1 >= 0
L2:
        LDAA    i
        DECA
        CMPA    l //A –M
        BGE     L1 // branch if >= zero

/* if  l - i >= 0*/
        LDAA    l
        CMPA    i
        BLE     <L3>
        
/* l = i - l*/
        LDAA    i
        SUBA    l
        STAA    l

L3:
/* i*=2 */
        LDAA    i
        ADDA    i
        STAA    i
        JMP     <L2>
L1:
//
