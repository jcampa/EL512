int *v;
int i, l;

while (v[i] < l) {
  v[i] = v[l];
  //v[i] = v[l+i];
  l++;
}

// traduccion

<L2>:
        LDX     v         // cargar el vector v
        LDAB    i         // cargarmos la variable i al registro B
        ABX               // apuntamos a la direccion v + i
        LDAA    0,x       // cargamos v[i] en le registro A
        CMPA    l         // v[i] - l
        BGE     <L1>      // v[i] - l >= 0 ?

        LDX     v         // cargar el vector v en la posicion 0
        LDAB    l         // cargarmos la variable l al registro B
//      ADDB    i
        ABX               // apuntamos a la direccion v + l
        LDAA    0,x       // guardamos v[l] en el registro A

        LDX     v         // cargar el vector v en la posicion 0
        LDAB    i         // cargarmos la variable i al registro B
        ABX               // apuntamos a la direccion v + i
        STAA    0,x       // guardamos el registro A en el vector v[i]

        inc     l
        BRA     <L2>
<L1>:
/* <code> */
