/* SenzuVM.c */
#include "SenzuVM.h"

int8 map(Opcode o) {
	
	int8 n, ret;
	IM *p;

	ret = 0;
	for(n=IMs, p=instrmap; n; n--, p++) {
		if (p->o == o) {
			ret = p->s;
			break;
		}	
	}
	return ret;
}

VM *virtualmachine() {
	VM *p;
//	Program *pp;
	int16 size;

	size = $2 sizeof(struct s_vm);
	p = (VM *)malloc($i size);
	if (!p) {
		errno = ErrMem;
		return (VM *)0;
	}
	zero($1 p, size);

//	pp = (Program)malloc($i progsz);
//	if (!pp) {
//		free(p);
//		errno = ErrMem;
//
//		return (VM *)0;
//	}
//
//	copy(pp, pr, progsz);
//
	return p;
}



Program *exampleprogram(VM *vm) {
	Program *p;
	Instruction *i1, *i2;
	Args *a1;
	int16 s1, s2, sa1;
	s1 = map(mov);
	s2 = map(nop);
	
	i1 = (Instruction *)malloc($i s1);
	i2 = (Instruction *)malloc($i s2);
	assert(i1 && i2);
	zero($1 i1, s1);
	zero($1 i2, s2);

	i1->o = mov;
	sa1 = (s1-1);
	if(s1) 
		a1 = (Args *)malloc($i sa1);
	if(a1) {
		assert(a1);
		zero(a1, sa1);
		*a1 = 0x00;
		*(a1+1) = 0x05;
		// 0000 0001 mov eax
		// 0000 0000
		// 0000 0005 mov eax, 0x05
	}

	p = vm->m;
	copy($1 p, $1 i1, 1);
	p++;

	if(a1) {
		
		copy($1 p, $1 a1, sa1);
		p+= sa1;
		free(a1);
	}

	i2->o = nop;
	copy($1 p, $1 i2, 1);
	free(i1);
	free(i2);

	return vm->m;
}


int main(int argc, char *argv[]) {
	int8 size;
	Program *prog;
	VM *vm;

	vm = virtualmachine();
	printf("vm  = %p\n", vm);

	prog = exampleprogram(vm);
	printf("prog = %p\n", prog);

	printhex($1 prog, (map(mov)+map(nop)), ' ');

    return 0;
}
