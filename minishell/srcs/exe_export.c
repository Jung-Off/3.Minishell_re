
#include "../includes/minishell.h"

static void	create_list(t_env **lst)
{
	*lst = malloc(sizeof(t_env));
	(*lst)->key = NULL;
	(*lst)->value = NULL;
    (*lst)->idx = 0;
	(*lst)->next = NULL;
	(*lst)->env_flag = 0;
}

static void add_node(t_env *add_lst, t_env **env_lst)
{
	t_env *move;

	move = *env_lst;

	if (*env_lst == NULL)
		*env_lst = add_lst;
	else
	{
		while (move->next)
			move = move->next;
		move->next = add_lst;
	}
}

void export_split(t_env *lst, char **argv)
{
	char **export_oneline;

	export_oneline = ft_split(argv[1], '=');

	int i = 0;
	while(export_oneline[i])
	{
		printf("____%s____%d\n", export_oneline[i], i);
		++i;
	}
	lst->key = export_oneline[0];
	
	
	if(ft_strchr(argv[1], '='))
	{
		lst->value = export_oneline[1];
		lst->env_flag = 1;
	}

}

int duplicate_search(t_env *env_lst, t_env *lst)
{
	//a만 들어가면 일단 들어는 가져 a
	//a=, a=dadsa 이런식으로 들어가면 다 엎어


	while(env_lst)
	{	
		if (ft_strlen(env_lst->key) <= ft_strlen(lst->key))
		{
			if(ft_strncmp(env_lst->key, lst->key, ft_strlen(lst->key)) == 0)
			{
				printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
				if (lst->env_flag == 0)
					return (1);
				else
				{
				// printf("before\t");
				// printf("env\tkey ; %s  value : %s  env_flag :%d\n", env_lst->key, env_lst->value, env_lst->env_flag);
				// printf("lst\tkey ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
					env_lst->value = lst->value;
					env_lst->env_flag = 1;
				// printf("after\t");
				// printf("env\tkey ; %s  value : %s  env_flag :%d\n", env_lst->key, env_lst->value, env_lst->env_flag);
				// printf("lst\tkey ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
					return (1);
				}
			}
		}
		else
		{
			if(ft_strncmp(lst->key, env_lst->key, ft_strlen(env_lst->key)) == 0)
			{
				if (lst->env_flag == 0)
					return (1);
				else
				{
					env_lst->value = lst->value;
					env_lst->env_flag = 1;
					return (1);
				}
			}
		}
		env_lst = env_lst->next;
	}
	return (0);
}


int add_export(t_env **env_lst, t_cmd *cmd)
{
	t_env *lst;

	create_list(&lst);
	export_split(lst, cmd->argv);
	if (duplicate_search(*env_lst, lst))
	{
			return (1);
		// printf("out");
		// printf("key ; %s  value : %s  env_flag :%d\n", (*env_lst)->key, (*env_lst)->value, (*env_lst)->env_flag);
		// printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
		// free(lst);
	}

//printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
	add_node(lst, env_lst);

	return (0);
}

int ft_num(t_env *env_lst, t_env *move_lst)
{
    int i = 0;

    if (env_lst == move_lst)
        return (0);
    
    // ft_putstr_fd(env_lst->key, 1);
    // ft_putstr_fd(" ", 1);
    // ft_putstr_fd(move_lst->key, 1);
    // ft_putstr_fd("\n", 1);

    while (env_lst->key[i] != 0 && move_lst->key[i] != 0)
    {
        if (env_lst->key[i] > move_lst->key[i])
        {
            return (1);
        }
        else if (env_lst->key[i] < move_lst->key[i])
        {
            return (0);
        }
        ++i;
    }
    //ft_putstr_fd("\n", 1);
    if (ft_strlen(env_lst->key) > ft_strlen(move_lst->key))
        return (1);
    return (0);
}

void sort_export(t_env *env_lst)
{
    t_env *move_lst;
    t_env *print_lst;

    t_env *first_lst = env_lst;

    print_lst = env_lst;
    move_lst = env_lst;
    while (env_lst)
    {
        move_lst = first_lst;
        while (move_lst)
        {
            env_lst->idx += ft_num(env_lst, move_lst);
            move_lst = move_lst->next;
        }
         env_lst = env_lst->next;
    }
    // while (print_lst)
    // {
    //     ft_putnbr_fd(print_lst->idx, 1);
    //     ft_putstr_fd(" ", 1);
    //     ft_putstr_fd(print_lst->key, 1);
    //     ft_putstr_fd("\n", 1);
    //     print_lst = print_lst->next;
    // }

}


void print_export(t_env *env_lst)
{
	t_env *print_lst;
    t_env *first_lst;

    first_lst = env_lst;
    print_lst = env_lst;
	sort_export(env_lst); //위에거 지우기

    // while (print_lst)
    // {
    //     ft_putnbr_fd(print_lst->idx, 1);
    //     ft_putstr_fd(" ", 1);
    //     ft_putstr_fd(print_lst->key, 1);
    //     ft_putstr_fd("\n", 1);
    //     print_lst = print_lst->next;
    // }
    int i = 0;
    while(env_lst)
    {
        print_lst = first_lst;
        
    while (print_lst)
	{
        if (print_lst->idx == i)
        {
            ft_putnbr_fd(print_lst->idx, 1);
		    ft_putstr_fd("declare -x ", 1);
		    ft_putstr_fd(print_lst->key, 1);
            if(print_lst->env_flag == 1)
		    {
			    ft_putstr_fd("=", 1);
			    if(print_lst->value == NULL)
				    ft_putstr_fd("\"\"", 1);
			    ft_putstr_fd(print_lst->value, 1);	
		    }
		    ft_putstr_fd("\n", 1);
	//두가지를 구분하기 위함 플래그
        }
		
        print_lst = print_lst->next;
	}
	// print_lst->idx = 0;
    ++i;
    env_lst = env_lst->next;
    }

	while(first_lst)
	{
		first_lst->idx = 0;
		first_lst = first_lst->next;
	}


}



void exe_export(t_env **env_lst, t_cmd *cmd)
{

	if (cmd->argv[1])
	{
		if (add_export(env_lst, cmd))
			return ; // 탐색의 과정도 필요할 듯
		//정렬하여서 출력하기
	}
	else
	{
		print_export(*env_lst); // 정렬을 하고 출력을 하기
	}
	// 	//print로 빼버리기
	// 	while (print_lst)
	// 	{
	// 		ft_putstr_fd("declare -x ", 1);
	// 		ft_putstr_fd(print_lst->key, 1);

	// 		if(print_lst->env_flag == 1)
	// 		{
	// 			ft_putstr_fd("=", 1);
	// 			if(print_lst->value == NULL)
	// 				ft_putstr_fd("\"\"", 1);
	// 			ft_putstr_fd(print_lst->value, 1);	
	// 		}
	// 		ft_putstr_fd("\n", 1);
	// 	//두가지를 구분하기 위함 플래그
	// 		print_lst = print_lst->next;
	// 	}
	// }
	//정렬하는 과정 여기서 쯤 필요할 듯
}