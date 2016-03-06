int *v;
int i, l, s;
s = 0;

for (i = 0; i < l; i++) {
  s += v[i];
}

// Registro X direcciones
// Registro A para datos

//Traduccion en assembler

        CRL     s         // s = 0
        CRL     i         // i = 0
L2:
        LDAA    i         // cargar la variable i al registro A
        CMPA    l         // i - l
        BHS     L1        // i - l >= 0 ?

        LDX     v         // X = v        cargar el vector v
        LDAB    i         // B = i        cargarmos la variable i al registro B
        ABX               // X = v + i    apuntamos a la direccion v + i
        LDDA    s         // A = s        cargamos s
        ADDA    O, x      // A += v[i]    0 saltos despues x
        STAA    s         // s = A        guardamos el registro A en la variale s

        inc     i         // i++
        BRA     L2        // volvemos al for
L1:
/* <code here> */
//  K&R
//  kernigan and richi
