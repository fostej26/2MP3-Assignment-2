//Include everything necessary here 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // <YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code>
    if (argc!= 6) { //checks for valid # of inputs
        printf("Invalid number of inputs");
        return 1;
    }
    // <YOUR CODE: Assign all inputs given by the user argv[i]> like
    // POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria
    //make take inputs from user later
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);
    double best_fitness = 1.0; //placeholderS

    if (POPULATION_SIZE <= 0 || MAX_GENERATIONS <= 0 || crossover_rate < 0 || mutate_rate < 0 || stop_criteria < 0){ // checks if input is valid
        printf("Invalid input(s), please try again\n");
        return 1;
    }

    // ###################################################################################
    // you dont need to change anything here
    // the number of variables
    int NUM_VARIABLES = 2;
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
    // ###################################################################################


    // <YOUR CODE: Here make all the initial print outs>
    printf("Genetic Algorithem is initialized\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("The number of variables is %d\n", NUM_VARIABLES);
    printf("Lower bounds: ");
    for (int i = 0; i < NUM_VARIABLES; i++) {
        printf("%f ", Lbound[i]);
    }
    printf("\n");
    printf("Upper bounds: ");
    for (int i = 0; i < NUM_VARIABLES; i++) {
        printf("%f ", Ubound[i]);
    }
    printf("\n\n");
    printf("Population Size: %d\n", POPULATION_SIZE);
    printf("Max Generations: %d\n", MAX_GENERATIONS);
    printf("Stopping Criteria: %.16f\n\n", stop_criteria);
    printf("Results\n");
    printf("-------------------------------------------------------------------------------\n");

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // <YOUR CODE: Declare all the arrays you need here>
    double fitness[POPULATION_SIZE]; 
    double best_solution[NUM_VARIABLES];
    double best_solution1[NUM_VARIABLES];
    double population[POPULATION_SIZE][NUM_VARIABLES];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];
    
    
    
    // <YOUR CODE: Call generate_population function to initialize the "population"> like:
    // generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);

    // <YOUR CODE: Implement the logic of stopping criteria here>
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) { //finish loop if max generation or if condition is met
        // <YOUR CODE: Compute the fitness values using objective function for
        // each row in "population" (each set of variables)> like:
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);
        // <YOUR CODE: Here implement the logic of finding the best solution with minimum fitness value
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (fitness[i] < best_fitness) {
                best_fitness = fitness[i]; //replace best fitness placeholder with current best fitness
                for (int j = 0; j < NUM_VARIABLES; j++) {
                    best_solution[j] = population[i][j]; //find best combonation of fitness in population
                }
            } 
        }

        if (best_fitness < stop_criteria) { //break loop if below criteria
            break;
        }
        
        // <YOUR CODE: Implement the logic of crossover here>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);
        // <YOUR CODE: Implement the logic of mutation here>
        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
        //printf("%d\n", generation);
        // Now you have the new population, and it goes to the beginning of loop to re-compute all again
    }

    // <YOUR CODE: Jump to this part of code if the stopping criteria is met before MAX_GENERATIONS is met>

    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // <Here print out the best solution and objective function value for the best solution like the format>
    printf("Best solution guess: \n");
    for (int i = 0; i < NUM_VARIABLES; i++) {
        printf("%f ", best_solution[i]);
    }

    printf("\n");
    printf("Best fitness guess: %f\n", best_fitness);

    return 0;
}