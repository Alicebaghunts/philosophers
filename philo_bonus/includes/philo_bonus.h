/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:56:59 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/02 18:34:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# define INVALID_ARGUMENT 1
# define INVALID_SYMBOLS 2
# define INVALID_PHILO_COUNT 3
# define INVALID_NUMBER 4
# define CALLOC_ERROR 5
# define SEMAPHORE_INIT_ERROR 6

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			index;
	int			eat_count;
	long long	last_meal;
	sem_t		*last_meal_sem;
	pthread_t	philo_death_thread;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_eats_count;
	int			full_eats_count;
	int			program_stop;
	int			all_dead;
	long long	start_time;
	sem_t		*deadlock_protect;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*fullness;
	sem_t		*stop_sem;
	sem_t		*all_dead_sem;
	sem_t		*death;
	pthread_t	fullness_thread;
	pthread_t	death_thread;
	pthread_t	monitoring_thread;
	t_philo		*philo;
	pid_t		*pid;
}	t_table;
//validation
int		validation(int argc, char **argv);
int		validate_arguments(int argc, char **argv);
int		ft_isdigit(int ch);
int		is_valid_number(char *str);
int		has_only_valid_chars(int argc, char **argv);
//libft function
char	*ft_itoa(int n);
long	ft_atol(const char *str);
int		ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		get_malloc_size(char const *s, unsigned int start, size_t len);
void	error_handling(int num);
//initalization
t_table	*init_table(int argc, char **argv);
int		init_philo(t_table *table);
int		init_semaphore(t_table *table);
//free
void	free_table(t_table *table);
void	free_semaphores(t_table *table);
//timing
long	get_time_in_ms(void);
void	delay_ms(long long ms);
// print action
void	print_action(t_philo *philo, const char *str);
//actions

void	actions(t_philo *philo);
void	pick_fork(t_philo *philo);
void	put_fork(t_philo *philo);
void	one_philo_pick_fork(t_philo *philo);
void	philo_thinking(t_philo *philo);
void	philo_usleep(int sleep_time);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	create_philo(t_table *table);
//threads

void	*death_monitor(void *data);
void	*check_death_philo(void *data);
void	*fullness_philos(void *data);

void	create_threads(t_table *table);
void	handle_sigterm(int sig);

#endif