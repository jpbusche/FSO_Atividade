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

typedef struct student{
  int help_numbers;
} Student;

void *student_action(void* param) {

}

void *ae_action(void* param){

}

int main() {
  srand(time(NULL));
  int students = rand() % (MAX_STUDENTS - MIN_STUDENTS) + MIN_STUDENTS, chairs = students / 2;
  pthread_t tae, tstudent[students];
	pthread_attr_t attr_a, attr_s[students];
  printf("%d\n", students);
  return 0;
}
