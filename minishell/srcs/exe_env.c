
#include "../includes/minishell.h"

static void	create_list(t_env **lst)
{
	*lst = malloc(sizeof(t_env));
	(*lst)->key = NULL;
	(*lst)->value = NULL;
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

void env_split(t_env *lst, char *env)
{
	char **env_oneline;

	env_oneline = ft_split(&env[0], '=');
	lst->key = env_oneline[0];
	lst->value = env_oneline[1];
	lst->env_flag = 1; //env로 쓰겟다.
}

void exe_env(char **envp, t_env **env_lst)
{
	t_env *lst;

	while (*envp)
	{
		create_list(&lst);
		// lst = (t_env *)malloc(sizeof(t_env));
	//	printf("%s\n", envp[0]);

		env_split(lst, envp[0]);
		// exe_split(lst, envp[0]);
		
		// printf("head : %s", lst->key);		
		//new_lst->value
		add_node(lst, env_lst);
		++envp;

	}
}

void print_env(t_env *env_lst)
{
	while (env_lst)
	{
	// 	printf("yyyyyyyy : %s, vvvvvvv : %s\n", env_lst->key, env_lst->value);
	// //지양
		if(env_lst->env_flag)
		{
			ft_putstr_fd(env_lst->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env_lst->value, 1);
			ft_putstr_fd("\n", 1);
		}	
		//두가지를 구분하기 위함 플래그
		env_lst = env_lst->next;
	}
}