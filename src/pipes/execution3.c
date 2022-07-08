// #include "../../include/minishell.h"
// #include "../../include/minishell_d.h"
// #include "../../include/minishell_f.h"
// #include "../../include/minishell_s.h"


// // VERSION HUGO
// extern t_sh g_sh;

// int nb_pipes(t_pipe *pass)
// {
//     int i;

//     i = 0;
//     while (pass->next)
//     {
//         i++;
//         pass = pass->next;
//     }
//     printf("nb pipe = %d\n", i);
//     return (i);
// }

// void    ft_close(int **fd, int i)
// {
//     int j;

//     j = 0;
//     while (j < i)
//     {
//         close(fd[j][0]);
//         close(fd[j][1]);
//         j++;
//     }
// }

// void    ft_free_fd(int **fd, int i)
// {
//     int j;

//     j = 0;
//     while (j < i)
//     {
//         free(fd[j]);
//         j++;
//     }
//     free(fd);
// }

// void    ft_dup_fds(t_pipe *pipe_lst)
// {
//     pipe_lst->cpy_input = dup(0);
//     pipe_lst->cpy_output = dup(1);
//     dup2(pipe_lst->input, 0);
//     dup2(pipe_lst->output, 1);
// }

// void    ft_close_fds(t_pipe *pipe_lst)
// {
//     dup2(pipe_lst->cpy_input, 0);
//     dup2(pipe_lst->cpy_output, 1);
//     close(pipe_lst->cpy_input);
//     close(pipe_lst->cpy_output);
//     if (pipe_lst->input != 0 && pipe_lst->input != -1)
//         close(pipe_lst->input);
//     if (pipe_lst->output != 1 && pipe_lst->output != -1)
//         close(pipe_lst->output);
// }


// void    ft_pipe_3(int **fd, int i)
// {
//     ft_close(fd, i);
//     ft_free_fd(fd, i);
//     wait(0);
// }

// int **init_pipe(int i)
// {
//     int     **fd;
//     int     j;

//     fd = ft_calloc(i, sizeof(int *));
//     j = 0;
//     while (j < i)
//     {
//         fd[j] = ft_calloc(2, sizeof(int));
//         j++;
//     }
//     j = 0;
//     while (j < i)
//     {
//         if (pipe(fd[j]) == -1)
//             return (0);
//         j++;
//     }
//     return (fd);
// }

// void    ft_pipe_2(t_pipe *pass, t_sh *sh, int **fd, int i, char **env_init)
// {
//     pid_t   pid;

//     if (pass->is_builtin == 1)
//         index_builtins(sh);
//     else if (sh->pipe_lst->cmd_verified != NULL)
//     {
//         pid = fork();
//         if (pid == -1)
//             return ;
//         if (!pid)
//         {
//             ft_close(fd, i);
//             execve(pass->cmd_verified, pass->args, env_init);
//         }
//     }
//     ft_close_fds(pass);
// }



// void    ft_pipe(t_sh *sh, int i, t_pipe *pass, int k, char **env_init)
// {
//     int     j;
//     int     **fd;

//     j = 0;
//     fd = init_pipe(i);
//     while (pass)
//     {
//         ft_dup_fds(pass);
//         if (!k)
//             dup2(fd[j][1], pass->output);
//         else if (k && !pass->next)
//             dup2(fd[j][0], pass->input);
//         else if (k && pass->next)
//         {
//             dup2(fd[j][0], pass->input);
//             dup2(fd[j + 1][1], pass->output);
//         }
//         ft_pipe_2(pass, sh, fd, i, env_init);
//         if (k % 2 != 0)
//             j++;
//         k++;
//         pass = pass->next;
//     }
//     ft_pipe_3(fd, i);
// }

// void    execution(t_sh *sh, char **env_init)
// {
//     t_pipe  *pass;
//     pid_t   pid;
//     int     i;
//     int     k;

//     k = 0;
//     pass = sh->pipe_lst;
//     i = nb_pipes(pass);
//     if (!pass->next)
//     {
//         ft_dup_fds(pass);
//         if (pass->is_builtin == 1)
//             index_builtins(sh);
//         else if (pass->cmd_verified != NULL)
//         {
//             pid = fork();
//             if (pid == -1)
//                 return ;
//             else if (!pid)
//                 execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init);
//         }
//         ft_close_fds(pass);
//     }
//     else
//         ft_pipe(sh, i, pass, k, env_init);
// }