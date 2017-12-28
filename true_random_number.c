// to compile: gcc -pthread true_random_number.c

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define LENGTH 32

typedef struct {
	unsigned int bit : 1;
} Bit;

struct {
	unsigned int ready:1; // to signal the start
	unsigned int index:6; // up to 32 in decimal (i.e the sizeof of binary array = LENGTH)
	Bit binary[LENGTH]; // to collect bits to form the random number in binary
} volatile rnd = {0,0};


/*Function to change all the bits to 0's*/
void *off (void *vargp){
	while(!rnd.ready); // wait for the signal
	while(rnd.index<LENGTH) rnd.binary[rnd.index++].bit = 0;
	return NULL;
};

/*Function to change all the bits to 1's*/
void *on (void *vargp){
	while(!rnd.ready); // wait for the signal
	while(rnd.index<LENGTH) rnd.binary[rnd.index++].bit = 1;
	return NULL;
};


/*Function to convert the Bit array to decimal*/
long binary_to_decimal(Bit *bin){
	long result=0, rank=1, i=0;	
	for(i=LENGTH-1; i>=0; i--){
		result += bin[i].bit * rank;
		rank *= 2;
	}
    return result;	
}


/*Function to generate the true random number*/
int true_rnd(unsigned int upper_limit){
	pthread_t t0, t1;
	pthread_create(&t1, NULL, on, NULL);
	pthread_create(&t0, NULL, off, NULL);
	sleep(0.01);
	rnd.ready = 1; // signal to both threads to start the competition
	sleep(0.01);
	// create non-volatile copy of generated binary number
	// and reset the binary array
	Bit bin[LENGTH]; 
	for(int i=0; i<32; i++) {
		bin[i] = rnd.binary[i];
		rnd.binary[i].bit = 0;
	}
	rnd.ready = rnd.index = 0; // reset rnd
	
	return (int)binary_to_decimal(bin)%upper_limit;
}


// for testing
int main(){
	printf("Insert the upper limit\n");
	int upper_limit;
	scanf("%d", &upper_limit);
	printf("Insert how many random number to generate\n");
	int n;
	scanf("%d", &n);
	printf("Result:\n");
	int i;
	for(i=0; i<n;i++){
		printf("%d\t", true_rnd(upper_limit));
	}
	printf("\n");
	fflush(stdin);
        getchar();
	
	return 0;
	
}
