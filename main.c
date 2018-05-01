#include <stdio.h>
#include <stdlib.h>

#pragma pack(push,1)
struct s1 {
	struct {
		int (*aa)[1]; 
		int (*ab)[2];
	} * a; 
	char ch;
};
#pragma pack(pop)

static void * _alloc(void) {
	void* p 			= malloc(sizeof(void*)  + sizeof(char));
	*(void **)p 		= malloc(sizeof(void*)*2);
	**(void ***)p 		= malloc(sizeof(int));
	*(void**)((*(void ***)p) + 1) = malloc(sizeof(int)*2);
	printf("Entry = %p\n", p);
	return p;
}

static void _fill(void *p) {
	*(char*)((void**)p + 1) 			= 'A';
	***(int***)p 						= 9;
	**(int**)(*(void***)p + 1) 			= 8;
	*(*(int**)(*(void***)p + 1) + 1)   	= 7;
	return ;
}

static void _read(struct s1 *p) {
	printf("p->ch : %c\n", p->ch);
	printf("p->a->aa[0] : %d\n", (*p->a->aa)[0]);
	printf("p->a->ab[0] : %d\n", (*p->a->ab)[0]);
	printf("p->a->ab[1] : %d\n", (*p->a->ab)[1]);

	return ;
}
int main(void) {
	struct s1* p;

	p = _alloc();
	_fill(p);
	_read(p);

	return 0;
}
