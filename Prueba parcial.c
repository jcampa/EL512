int foo (intl, int *v, int n)
{
        int i, j, k;

        for (i = 3; i < v[l]; i-=2)
        {
                v[i] = foo(l, v, i);
                v[i + 2] = v[j] - v[l];
        }
        if (v[i] > v[i-2] + 2)
        {
                do{
                        v[i] *= 3;
                }while(v[i + j] > 0)
        }
        else{
                return v[l] - v[i + 1];
        }
        while(i < j)
        {
                v[j] = v[i + k];
        }
        return 1;
}

//// SOL
main:
        DES             // Return value
        LDAA    l
        PSHA            // stack l
        LDX     #v      
        PSHX            // stack *v
        LDAA    n
        PSHA            // stack n
        JSR     foo
        INS             // dealocate n
        INS             // dealocate v
        INS             // dealocate v
        INS             // dealocate l
        PULA            // A = foo(l, v, i);

foo:
        DES             // i
        DES             // i
        DES             // k
        PSHA            // transparencia
        PSHB            // transparencia
        PSHX            // transparencia
        TSX             // set X to point to the top byte of the stack
        //-----
foo_fin:
        PULX            //
        PULB            //
        PULA            //
        INS             // dealocate k
        INS             // dealocate j
        INS             // dealocate i
        RST             // return

// for (i = 3; i < v[l]; i-=2)
        LDAA    #3      // A = 3
        STAA    6, X    // i = 3
foo_for:
        LDAA    6, X    // A = i
        LDAB   12, X    // B = l
   ---> PSHX            // save X on the stack
  |     LDX    10, X    // X = v
  |     ABX             // X = v + l
  |     CMPA    0, X    // i - v[l]
   ---> PULX
        BGE     foo_end_for     // >= 0 ? 
        //-----
        LDAA    6, X    // A = i
        SUBA    #2      // A = i - 2
        STAA    6, X    // i = i -2
        JMP     foo_for
foo_end_for:

// v[i] = foo(l, v, i);
        DES             // Return value
        LDAA    l
        PSHA            // stack l
        LDX     #v      
        PSHX            // stack *v
        LDAA    n
        PSHA            // stack n
        JSR     foo
        INS             // dealocate n
        INS             // dealocate v
        INS             // dealocate v
        INS             // dealocate l
        PULA            // A = foo(l, v, i);
        LDAB    6, X    // B = i
   ---> PSHX            // save X on the stack
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i
  |     STAA    0, X    // v[i] = foo(l, v, i);
   ---> PULX            // Retrieve X

// v[i + 2] = v[j] - v[l];
   ---> PSHX            // save X on the stack
  |     LDAB    5, X    // B = j
  |     LDX    10, X    // X = v
  |     ABX             // X = v + j
  |     LDAB    0, X    // A = v[j]
  |     PULX
  |     PSHX
  |     LDAB   12, X    // B = l
  |     LDX    10, X    // X = v
  |     ABX             // X = v + l
  |     SUBA    0, X    // A = v[j] - v[l]
  |     PULX
  |     PSHX
  |     LDAB    6, X    // B = i
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i
  |     STAA    2, X    // v[i + 2] = v[j] - v[l]
   ---> PULX            // Retrieve X

// if (v[i] > v[i-2] + 2) -->> v[i] - 2 - v[i-2]  <= 0
   ---> PSHX            // save X on the stack
  |     LDAB    6, X    // B = i
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i
  |     LDAA    0, X    // A = v[i]
  |     SUBA    #2      // A = v[i] - 2
  |     PULX
  |     PSHX
  |     LDAB    6, X    // B = i
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i
  |     CMPA   -2, X    //  A - v[i - 2]
  |     BLE     foo_else
   ---> PULX            // Retrieve X
foo_else:
        //-----

// do {} while(v[i + j] > 0)
foo_while:
        //-----
   ---> PSHX            // save X on the stack
  |     LDAB    6, X    // B = i
  |     ADDB    5, X    // B = i + j
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i + j
  |     LDAA    0, X    // A = v[i + j]
  |     CMPA    #0      // V[i + j] - 0
   ---> PULX            // Retrieve X
        BGT     foo_while 

// v[i] *= 3;
   ---> PSHX            // save X on the stack
  |     LDAB    6, X    // B = i
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i
  |     LDAA    0, X    // A = v[i]
  |     ADDA    0, X    // A = v[i] + v[i]
  |     ADDA    0, X    // A = v[i] + v[i] + v[i] = 3 * v[i]
  |     STAA    0, X    // v[i] = 3 * v[i]
   ---> PULX            // Retrieve X

// return v[l] - v[i+1];
   ---> PSHX            // save X on the stack
  |     LDAB   12, X    // B = l
  |     LDX    10, X    // X = v
  |     ABX             // X = v + l
  |     LDAA    0, X    // A = v[l]
  |     PULX
  |     PSHX
  |     LDAB    6, X    // B = i
  |     LDX    10, X    // X = v
  |     ABX             // X = v + i
  |     LDAA    0, X    // A = v[i]
  |     SUBA    1, X    // A = v[l] - v[i + 1]
  |     PULX
  |     PSHX
  |     STAA   13, X    // return = v[l] - v[i + 1]
   ---> PULX            // Retrieve X
        JMP     foo_fin

// while(i < j)
        LDAA     6, X   // A = i
        CMPA    12, X   // i - l 
        BGE     foo_fin_while   // >= 0 ?
        // ------
foo_fin_while:

// v[j] = v[i + k];
   ---> PSHX            // save X on the stack
  |     LDAB    6, X    // B = i
  |     ADDB    4, X    // B = i + k
  |     LDX    10, X    // X = v
  |     ABX             // x = v + i + k
  |     LDAA    0, X    // A = v[i + k]
  |     PULX
  |     PSHX
  |     LDAB    5, X    // B = j
  |     LDX    10, X    // X = v
  |     ABX             // x = v + j
  |     STAA    0, X    // v[j] = v[i + k]
   ---> PULX            // Retrieve X

// return 1;
        LDAA    #1      // A = 1
        STAA   13, X    // return = 1
        JMP foo_fin


    //*< PILA >*///
iX->    |_RX_| 0
        |_RX_| 1
        |_RB_| 2
        |_RA_| 3
        |__k_| 4
        |__j_| 5
        |__i_| 6
        |_RET| 7
        |_RET| 8
        |__n_| 9
        |_*v_| 10
        |_*v_| 11
        |__l_| 12
        |____| 13






