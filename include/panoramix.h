/*
** EPITECH PROJECT, 2024
** panoramix
** File description:
** panoramix
*/

#pragma once

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct arguments {
    int nb_villagers;
    int pot_size;
    int current_pot_size;
    int nb_fights;
    int nb_refills;
    pthread_mutex_t refill_mutex;
    sem_t empty_pot_sem;
    sem_t refill_pot_sem;
} arguments_t;

typedef struct villager {
    int id;
    int nb_fights;
    arguments_t *args;
} villager_t;

int parse_arguments(char **argv, arguments_t *args);
void *druid_thread_function(void *arg);
void *villager_thread_function(void *arg);
void cleanup_and_exit(arguments_t *args, pthread_t **villager_threads,
    pthread_t *druid_thread, villager_t **villagers);
void create_villagers_and_threads(arguments_t *args,
    villager_t **villagers, pthread_t **villager_threads);
void join_villager_threads(const arguments_t *args,
    pthread_t **villager_threads);
void fight(villager_t *villager);
