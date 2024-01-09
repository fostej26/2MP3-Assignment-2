// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <math.h>

double generate_random(double min, double max)
{
    // implement a function to return a value between min and max
    return ((double)rand()/(double)RAND_MAX)*(max-min)+min; 
}

unsigned int generate_int()
{
    // implement the function to return a random integer value
    return rand(); //generates random int from 0 to 32784
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES]){
    for(int i =0; i < POPULATION_SIZE;i++){
        for (int j=0; j < NUM_VARIABLES; j++){
            population[i][j] = generate_random(Lbound[j],Ubound[j]); //float (min-max) for each index in population
        }
    }
    // randomly initialize for all values in "population[i][j]""

}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    for(int i = 0; i < POPULATION_SIZE; i++) {
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);
        /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
        by calling "Objective_function" */
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/

    double fitness_probs[POPULATION_SIZE];
    double fitness_sum = 0.0;
    double cumulative_prob[POPULATION_SIZE];
    int index[POPULATION_SIZE];

    for (int i = 0; i < POPULATION_SIZE; i++) { // find individual fitness and avoid divide by 0 error
        fitness_probs[i] = 1/(fitness[i] + 1e-6);
        fitness_sum += fitness_probs[i];
    }
    for (int i = 0; i < POPULATION_SIZE; i++) { //normalize the probabilities
        fitness_probs[i] /= fitness_sum;
    }
    cumulative_prob[0]=fitness_probs[0];
    for (int i = 1; i < POPULATION_SIZE; i++) { 
        cumulative_prob[i] = fitness_probs[i]+cumulative_prob[i - 1]; //calculate prob of i and all before i
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        double random_num = generate_random(0, 1); //AI assisted (tabnine and chatgpt)
        if (cumulative_prob[i]<random_num && random_num<cumulative_prob[i+1]) {//select chromasomes that survive
            index[i] = 0;
        }else {
            index[i] = 1;
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < NUM_VARIABLES; j++) {
            new_population[i][j] = population[index[i]][j]; //population of surviving chromosomes to new pop
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i+=2) { //skip for each set of parents
        if (generate_random(0, 1) < crossover_rate) {
            
            double parent1[NUM_VARIABLES]; //initialize family :)
            double parent2[NUM_VARIABLES];
            double child1[NUM_VARIABLES]; 
            double child2[NUM_VARIABLES];

            double crosspoint = generate_random(1, NUM_VARIABLES); // generate crosspoint
            for (int j = 0; j < NUM_VARIABLES; j++) { // Select parents
                parent1[j] = population[i][j];
                parent2[j] = population[i + 1][j];
            }

            for(int j=0; j<NUM_VARIABLES;j++){
                if(j<crosspoint){
                    child1[j] = parent1[j]; //selects which genes are/are not crossed
                    child2[j] = parent2[j];
                }else{
                    child1[j] = parent2[j];
                    child2[j] = parent1[j];
                }
            }

            for (int j = 0; j < NUM_VARIABLES; j++) {
                new_population[i][j] = child1[j];
                new_population[i + 1][j] = child2[j];
            }
        }
    }

    for (int i = 0; i < POPULATION_SIZE; i++){ //new population replaces old population
        for (int j = 0; j < NUM_VARIABLES; j++) {
            population[i][j] = new_population[i][j];
        }
    }
}


void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double new_population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/
    int total_gen = POPULATION_SIZE * NUM_VARIABLES;
    int total_gen_mutate = round(total_gen * mutate_rate); //find total number of genes to be mutated
    int genes_to_mutate_indices[total_gen_mutate]; //array of mutated genes

    for (int i = 0; i < total_gen_mutate; i++) {
        do { genes_to_mutate_indices[i] = round(generate_random(0, total_gen)); 
        } while (genes_to_mutate_indices[i] == genes_to_mutate_indices[i-1] && i>0); //AI generated (tabnine & chatgpt)
    } //mutates all genes that are meant to be mutated
     
    for (int i = 0; i < total_gen_mutate; i++) {  //mutate selected genes from array
        int row = genes_to_mutate_indices[i]/NUM_VARIABLES; 
        int column = genes_to_mutate_indices[i]%NUM_VARIABLES;
        new_population[row][column] = generate_random(Lbound[column], Ubound[column]);
    }
    for (int i = 0; i < POPULATION_SIZE; i++) { //new population replaces old population
        for (int j = 0; j < NUM_VARIABLES; j++) {
            population[i][j] = new_population[i][j];
        }
    }
}