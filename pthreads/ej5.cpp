// Task queue

#include <cstdio>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include <semaphore.h>
 
void* consumer(void*);
 
using namespace std;
 
int thread_count;
sem_t* sems__;
vector<sem_t> sems;
vector<int> messages;
 
 
int main(int argc, char *argv[])
{
     
    thread_count = strtol(argv[1], NULL, 10);
    vector<pthread_t> thread_handles(thread_count);
 
    for (int thread = 0; thread < thread_count; ++thread){
        sem_t n_sem;
        sem_init(&n_sem, 0, 0);
        messages.push_back(0);
        sems.push_back(n_sem);
    }
 
    for (long thread = 0; thread < thread_count; ++thread)
    {
        pthread_create(&thread_handles[thread], NULL, consumer, (void*)thread);
    }
 
    int operation = 0;
 
    scanf("%d", &operation);
    int counter = 0;
 
    while(operation != 0){
        messages[counter] = operation;
        sem_post(&sems[counter]);
        counter = (counter+1) % thread_count;
        scanf("%d", &operation);
    }
     
    for (int i = 0; i < thread_count; ++i)
    {
        messages[i] = -1;   
        sem_post(&sems[i]);
    }
 
 
    for (int thread = 0; thread < thread_count; ++thread){
        pthread_join(thread_handles[thread], NULL);
    }
 
    return 0;
}
 
void* consumer(void* thread_id){
    while(1){
        long th_id = (long) thread_id;
        sem_wait(&sems[th_id]);
        if (messages[th_id] == -1) break;
        messages[th_id] *= 2;
        printf(" ' %d ' printed by thread %ld \n", messages[th_id], th_id);
    }
}