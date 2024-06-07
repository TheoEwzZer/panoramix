/*
** EPITECH PROJECT, 2024
** bspanoramix
** File description:
** main
*/

#include "panoramix.h"

int parse_arguments(char **argv, arguments_t *args)
{
    char *endptr = NULL;

    args->nb_villagers = (int)strtol(argv[1], &endptr, 10);
    if ((*endptr != '\0') || (args->nb_villagers <= 0)) {
        return -1;
    }
    args->pot_size = (int)strtol(argv[2], &endptr, 10);
    args->current_pot_size = args->pot_size;
    if ((*endptr != '\0') || (args->pot_size <= 0)) {
        return -1;
    }
    args->nb_fights = (int)strtol(argv[3], &endptr, 10);
    if ((*endptr != '\0') || (args->nb_fights <= 0)) {
        return -1;
    }
    args->nb_refills = (int)strtol(argv[4], &endptr, 10);
    if ((*endptr != '\0') || (args->nb_refills <= 0)) {
        return -1;
    }
    return 0;
}

void create_villagers_and_threads(arguments_t *args,
    villager_t **villagers, pthread_t **villager_threads)
{
    sem_init(&args->empty_pot_sem, 0, 0);
    sem_init(&args->refill_pot_sem, 0, 0);
    for (int i = 0; i < args->nb_villagers; i++) {
        villagers[i] = calloc(1, sizeof(villager_t));
        villagers[i]->id = i;
        villagers[i]->nb_fights = args->nb_fights;
        villagers[i]->args = args;
        villager_threads[i] = calloc(1, sizeof(pthread_t));
        pthread_create(villager_threads[i], NULL,
            villager_thread_function, villagers[i]);
    }
}

void join_villager_threads(const arguments_t *args,
    pthread_t **villager_threads)
{
    for (int i = 0; i < args->nb_villagers; i++) {
        pthread_join(*villager_threads[i], NULL);
    }
}

void cleanup_and_exit(arguments_t *args, pthread_t **villager_threads,
    pthread_t *druid_thread, villager_t **villagers)
{
    pthread_join(*druid_thread, NULL);
    join_villager_threads(args, villager_threads);
    pthread_mutex_destroy(&args->refill_mutex);
    sem_destroy(&args->empty_pot_sem);
    sem_destroy(&args->refill_pot_sem);
    free(villagers);
    free(villager_threads);
    free(druid_thread);
    free(args);
}

int main(int argc, char **argv)
{
    arguments_t *args = calloc(1, sizeof(arguments_t));
    pthread_t **villager_threads = NULL;
    pthread_t *druid_thread = NULL;
    villager_t **villagers = NULL;

    if ((argc != 5) || (parse_arguments(argv, args) == -1)) {
        fprintf(stderr, "USAGE: %s <nb_villagers> ", argv[0]);
        fprintf(stderr, "<pot_size> <nb_fights> <nb_refills>\n");
        free(args);
        return 84;
    }
    druid_thread = calloc(1, sizeof(pthread_t));
    villager_threads = calloc((size_t)args->nb_villagers, sizeof(pthread_t *));
    villagers = calloc((size_t)args->nb_villagers, sizeof(villager_t *));
    pthread_mutex_init(&args->refill_mutex, NULL);
    pthread_create(druid_thread, NULL, druid_thread_function, args);
    create_villagers_and_threads(args, villagers, villager_threads);
    cleanup_and_exit(args, villager_threads, druid_thread, villagers);
    return 0;
}
