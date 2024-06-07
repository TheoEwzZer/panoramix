/*
** EPITECH PROJECT, 2024
** panoramix
** File description:
** thread_functions
*/

#include "panoramix.h"

void *druid_thread_function(void *arg)
{
    arguments_t *args = (arguments_t *)arg;

    printf("Druid: I'm ready... but sleepy...\n");
    while (args->nb_refills > 0) {
        sem_wait(&args->refill_pot_sem);
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! ");
        printf("Beware I can only make %d ", args->nb_refills - 1);
        printf("more refills after this one.\n");
        args->current_pot_size = args->pot_size;
        args->nb_refills--;
        sem_post(&args->empty_pot_sem);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}

void fight(villager_t *villager)
{
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        villager->id, villager->args->current_pot_size);
    if (villager->args->current_pot_size == 0) {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n",
            villager->id);
        sem_post(&villager->args->refill_pot_sem);
        sem_wait(&villager->args->empty_pot_sem);
    }
    villager->args->current_pot_size--;
    villager->nb_fights--;
    printf("Villager %d: Take that roman scum! Only %d left.\n",
        villager->id, villager->nb_fights);
}

void *villager_thread_function(void *arg)
{
    villager_t *villager = (villager_t *)arg;
    pthread_mutex_t *pot_mutex = &villager->args->refill_mutex;

    printf("Villager %d: Going into battle!\n", villager->id);
    sleep(1);
    while (villager->nb_fights > 0) {
        pthread_mutex_lock(pot_mutex);
        fight(villager);
        pthread_mutex_unlock(pot_mutex);
        sleep(1);
    }
    sleep(1);
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
    return NULL;
}
