#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#define MAX_STUDENTS 40
#define MIN_STUDENTS 3
#define MAX_HELPS 3
#define RAND_TIME rand() % 10 + 1

typedef struct student {
  int id;
  int num_help; 
} Student;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t tae;
pthread_attr_t attr_ae;
sem_t semaphore;

void *student_actions(void *param);
void *ae_action(void *param);

int main() {
  srand(time(NULL));
  int students = rand() % (MAX_STUDENTS - MIN_STUDENTS + 1) + MIN_STUDENTS;
  // int students = MIN_STUDENTS;
  int chairs;
  pthread_t tstudents[students];
  pthread_attr_t attr_s[students];
  if(students % 2 == 0) chairs = students / 2;
  else chairs = students / 2 + 1;
  printf("Numero de estudantes: %d\nNumero de cadeiras: %d\n", students, chairs);
  sem_init(&semaphore, 0, chairs);
  Student stus[students];
  for(int i = 0; i < students; ++i) {
    stus[i].id = i;
    stus[i].num_help = MAX_HELPS;
    pthread_attr_init(&attr_s[i]);
    pthread_create(&tstudents[i], &attr_s[i], student_actions, &stus[i]);
  }
  for(int i = 0; i < students; ++i) {
    pthread_join(tstudents[i], NULL);
  }
  printf("AE voltou a dormir\n");
  sem_destroy(&semaphore);
  pthread_mutex_destroy(&lock);
  return 0;
}

void *student_actions(void *param) {
  Student * stu = (Student*)param;
  int n = stu->num_help;
  while(n != 0) {
    printf("Estudante %d esta programando.\n", stu->id);
    sleep(RAND_TIME);
    printf("Estudante %d foi procurar ajuda\n", stu->id);
    if(sem_trywait(&semaphore) == 0) {
      printf("Estudante %d esta sentado esperando o AE\n", stu->id);
      pthread_mutex_lock(&lock);
      pthread_attr_init(&attr_ae);
      pthread_create(&tae, &attr_ae, ae_action, stu);
      pthread_join(tae, NULL);
      n--;
      pthread_mutex_unlock(&lock);
      sem_post(&semaphore);
    } else printf("Sem cadeiras disponiveis, estudante %d voltou a programar\n", stu->id);
  }
  printf("Estudante %d terminou suas atividades\n", stu->id);
}

void *ae_action(void* param){
  Student * stu = (Student*)param;
  printf("AE esta ajudando o estudante %d\n", stu->id);
  sleep(RAND_TIME);
  printf("AE terminou de ajudar o estudante %d\n", stu->id);
}
