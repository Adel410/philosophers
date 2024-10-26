/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:47:29 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/26 21:09:01 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				even;
	int				meal;
	int				nb_philo;
	int				e_time;
	int				s_time;
	int				d_time;
	long			last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*check_mutex;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				meal_max;
	int				end_flag;
	int				nb_philo;
	long			start_time;
	pthread_t		*thread;
	pthread_t		big_brother;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}					t_table;

// PARSING && INIT && CLEANUP

int					parse_arg(char **av);
void				init_table(t_table *table, char **av);
void				init_philos(t_philo *philo, t_table *table, char **av,
						int i);
void				cleanup(t_philo *ptr, t_table *table);

// TO BE OR NOT TO BE

void				create_philos(t_table *table, char **av);
void				*routine(void *arg);
void				sleeping(t_philo *ptr);
void				thinking(t_philo *ptr);
void				eating(t_philo *ptr);
long				get_time(void);
int					dont_starve(t_philo *philo);
int					check_flags(t_philo *ptr);
void				take_forks(t_philo *ptr);
void				drop_forks(t_philo *ptr);
void				big_brother(t_table *table);
void				print_routine(t_philo *ptr, int i);
void				better_sleep(long duration, t_philo *philo);
long				time_diff(t_philo *ptr);

// TOOLS

void				ft_putstr(char *str);
void				ft_putstr_fd(char *s, int fd);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
int					ft_strlen(char *str);
int					ft_atoi(const char *str);
int					ft_isspace(char c);
int					ft_isdigit(char c);

#endif