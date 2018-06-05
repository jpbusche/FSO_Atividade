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
#define RAND_TIME (rand() % 9) + 1;

struct Student{
  int id;
  int help_numbers;
};

pthread_mutex_t mutex;
sem_t help;
sem_t ae_ready;
sem_t student_ready;
sem_t sit_down;
sem_t student_come;
sem_t student_leave;

void *student_action(void* param) {
  struct Student *student = (struct Student *)param;
  int thread_id = student->id;
  printf("Estudante %d indo tirar duvida com o AE.\n", thread_id);
  sem_post(&student_come);
  printf("Estudante %d esperando pelo AE.\n", thread_id);
  sem_post(&student_ready);
  sem_wait(&ae_ready);

  printf("Estudante %d saiu.\n", thread_id);
  sem_post(&student_leave);
}

void *ae_action(void* param){
  printf("AE esta dormindo esperando um estudante.\n");
  sem_wait(&student_come);
  printf("O AE acordou e esta indo conferir a fila.\n");
  // ajudando estudante
  // printf("AE esta ajudando o estudante %d.\n", student.id);
  // terminando de ajudar conferir se tem outro estudante
  // int numbers_of_student =
  // if(numbers_of_student > 0){
  //   return ae_action();// se tiver outro estudante, ajudar
  // } else {
  //   // se não tiver estudante, dormir
  // }
}

int main() {
  srand(time(NULL));
  int students = rand() % (MAX_STUDENTS - MIN_STUDENTS) + MIN_STUDENTS, chairs = students / 2;
  pthread_t tae, tstudent[students];
	pthread_attr_t attr_a, attr_s[students];
  sem_init(&help, 0, 0);
  sem_init(&ae_ready, 0, 0);
  sem_init(&student_ready, 0, 0);
  sem_init(&sit_down, 0, 1);
  sem_init(&student_come, 0, 0);
  sem_init(&student_leave, 0, 0);

  pthread_create(&tae, &attr_a, ae_action, NULL);

  struct Student student[students];
  for (int i = 0; i < students; ++i) {
    student[i].id = i;
    student[i].help_numbers = MAX_HELPS;
    pthread_attr_init(&attr_s[i]);
    pthread_create(&tstudent[i], &attr_s[i], student_action, &student[i]);
  }

  for(int i = 0; i < students; i++) {
    pthread_join(tstudent[i], NULL);
  }

  sem_destroy(&help);
  sem_destroy(&ae_ready);
  sem_destroy(&student_ready);
  sem_destroy(&sit_down);
  sem_destroy(&student_come);
  sem_destroy(&student_leave);
  pthread_exit(NULL);

  return 0;
}
