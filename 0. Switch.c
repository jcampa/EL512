switch(v)
{
	case 1:
		//-----
		break;

	case 2:
		//-----

	case 3:
		//-----
		break;

	default:
}

/// assembler equivalent

	LDAA	v
	CMPA	#1
	BEQ		E1
	CMPA	#2
	BEQ		E1
	CMPA	#3
	BEQ		E1
	JMP		Default
E1:
	//----
	JMP fin

E2:
	//----

E3:
	//----
	JMP fin

Default:
	//----

fin:
	//----
