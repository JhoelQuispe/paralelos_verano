#include <omp.h>
#include <cstdio>
#include <semaphore.h>
#include <fstream>
#include <string>
#include <iostream>
#include <queue>
#include <string.h>

#define THREADS 4

using namespace std;


sem_t sem;
sem_t sem2;
queue<string> shared_queue;
char *saveptr;

int count;


void consumer(){
	while(1){
		sem_wait(&sem);
		cout << "size" << shared_queue.size() << endl;
		string line = shared_queue.front();
		char *cstr = new char[line.length() ];
		strcpy(cstr, line.c_str());

		shared_queue.pop();

		char * word;
		word = strtok_r (cstr, " ", &saveptr);
		while (word != NULL){
			printf("%s\n", word);
			word = strtok_r(NULL, " ", &saveptr);
		}

		cout << line << endl;
	}
}

void producer(){
	cout << "AA" << endl;
	sem_wait(&sem2);
	std::string text = "t" + std::to_string(count) + ".txt";
	count++;
	sem_post(&sem2);
	std::cout << text << std::endl;
	ifstream myfile (text);
	string line;

	if (myfile.is_open()) {
		while (getline (myfile, line)){
			shared_queue.push(line);
		}
		sem_post(&sem);

	}

}

int main(int argc, char const *argv[])
{

	count = 1;

	sem_init(&sem2, 0, 1);
	
	#pragma omp parallel num_threads(THREADS)
	{ 
		if(omp_get_thread_num() %2 == 0) {
			consumer();
		}
		else {
			producer();
		}
	}
	
	return 0;
}