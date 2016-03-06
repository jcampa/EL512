//Ejemplos de funciones

void foo(){
}

JSR foo			//Jump to Subroutine
			// guarda la direccion de retorno en la pila, y luego salta a la direccion dela subturina.

foo:
	PSHA	// 	enpila el registro A
	PSHB	// 	enpila el registro B

	PULB	// 	saca A de la pila
	PULA	//	saca B de la pila
	RTS	// 	return from subroutine

/////////////////////////////////////////////
void foo (int i){(
}

	LDAA	i
	PUSH	A
	JSR 	foo
	INS				//	increment Stack Pointer to i, and mark it as writtable.

foo:
	PSHA			// 	empilo
	PSHB			//	empilo B
	PSHX			// 	empilo x
	TSX				//	Transfer Stack Pointer to X
	LDDA	6,x		// 	caga en A lo q esta en x+6, osea i.
	PULX			//	saco X de la pila
	PULB			// 	saco B de la pila
	PULA			//	saco A de la pila
	RST				// 	return
///
///*< PILA >*///
sp ->____
iX ->____
	 _RX_ 0
	 _RX_ 1
	 _RB_ 2
	 _RA_ 3
	 _RET 4
	 _RET 5
	 __i_ 6
//////////////////
int foo (){
}

	DES		//Decrement Stack Pointer
	JSR foo
	PULA		// lee el valor que guardo la funcion foo

foo:
	PSHA
	PSHB
	PSHX
	TSX
	//--- magia
	//--- 			//calculo el retorno y lo guardo en el registro A
	STAA 6,x		//Guardo el registro a en la pila, en la posicion que reserve antes
	PULX
	PULB
	PULA
	RST
///*< PILA >*///
sp->_RX_ 0
	_RX_ 1
	_RB_ 2
	_RA_ 3
	_RET 4
	_RET 5
	____ 6
/////////////////
int foo (int i){
}

	DES
	LDAA	i
	PSHA
	JSR	foo
	INS
	PULA

foo:
	PSHA
	PSHB
	PSHX
	TSX
	LDAA 6,x
	//--- magia negra
	//--- 			//calculo el retorno y lo guardo en el registro A
	STAA 7,x		//Guardo el registro a en la pila, en la posicion que reserve antes
	PULX
	PULB
	PULA
	RST

///*< PILA >*///
	_RX_ 0
	_RX_ 1
	_RB_ 2
	_RA_ 3
	_RET 4
	_RET 5
	__i_ 6
	_____7
/////////////////
// static, volatile
int foo (int i, int j, int *v){
}

	LDDA 	i
	PSHA
	IDX	#v
	PSHX
	JSR foo
	INS
	INS
	INS

foo:
	PSHA
	PSHB
	PSHX
	TSX
	LDAA 8,x
	//
	PSHX
	LDX 6,x
	//
	PSHX
	PULX
	PULB
	PULA
	RTS

//*< PILA >*///
iX->	_RX_ 0
	_RX_ 1
	_RB_ 2
	_RA_ 3
	_RET 4
	_RET 5
	_*v_ 6
	_*v_ 7
	__i_ 8

////////////////////////////////
int foo (int i, int j, int *v){
	int k, j;  // volatile variables.
}
// la funcion principal es la misma que antes

foo:
	DES
	DES
	PUSHA
	PUSHB
	PUSHX
	TSX
	// acceso a i
	IDDA 10, x
	// acceso a j
	LDAB 4, x
	//
	PULX
	PULB
	PULA
	INS
	INS
	RTS

//*< PILA >*///
iX->	_RX_ 0
	_RX_ 1
	_RB_ 2
	_RA_ 3
	__i_ 4
	__j_ 5
	_RET 6
	_RET 7
	_*v_ 8
	_*v_ 9
	__i_ 10
////////////////////////////////
int foo (int i, int j, int *v){
	int k, j; 		// volatile variables.
	static int l;
}
// la funcion principal es la misma que antes
foo:
		PSHA
		PSHB
		PSHX
L1:		TIX		// imaginary funcition that saves the instruction pointer on x
		BRA	L2
		//
L2
		LDAA 4,x

// TRANSPARENCIA atp.
	
