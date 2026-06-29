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
	t_list *tabl;
	t_list *tabl2;

	t_list *Node;
	t_list *node_addr[6];
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
		if (1 < array_input[j]) {
			do {
				tabl2 = tabl2->next;
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
		tabl2->next = tabl;
		j = j + 1;
		tabl2 = tabl;
	} while (j < 6);

	tabl2->next = NULL;

	j = 0;
	do {
		if (node_addr[0]->value < node_addr[0]->next->value) 
			printf("boom 3 \n");
		
		printf("%d\n", node_addr[0]->value);
		node_addr[0] = node_addr[0]->next;
		j = j + 1;
	} while (j < 5);
	printf("%d\n", node_addr[0]->value);
	printf("youpi\n");
	return;
}

int	main(int ac, char **av){
	phase_6(av[1]);

	return 0;
}