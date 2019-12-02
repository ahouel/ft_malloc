#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>
typedef struct s {
	struct s *next;
	int	i;
} t;

size_t aligne(size_t size, size_t align)
{
	if (size < align + 1)
		return align;
	if (!(size % align))
		return size;
	return (size + (align - (size % align)));
}

void add_bot(t **lst, t *new){
	t *le_t;
	
	le_t = *lst;
	if (!le_t)
		le_t = new;
	else {
		while(le_t->next)
		{
			le_t = le_t->next;
		}
		le_t->next = new;
	}
}
int main()
{
	size_t align = 16;
	int i = -1;
	t *lst;
	t *new;
	int j;
	int k = 16;
	char *ptr = malloc(10);
	void *ptr2;

	strcat(ptr, "012345678");
	printf("%p\t%s\n", ptr, ptr);
	ptr = realloc(ptr, 0);
	strcat(ptr, "012355678");
	printf("%p\t%s\n", ptr, ptr);
	return 0;
}
