// C++ program to create target string, starting from 
// random string using Genetic Algorithm 
  
#include <bits/stdc++.h> 
using namespace std; 
  
// Number of individuals in each generation 
#define POPULATION_SIZE 100
  
// Valid Genes 
const string GENES = "ABCDEFGHIJKLMNOPQRSTUVWX"; 
  
// Target string to be generated 
const string TARGET_CHOLERIS = "ABCDEF";
const string TARGET_MELANCHOLIS = "GHIJKL";
const string TARGET_PHLEGMATIC = "MNOPQR";
const string TARGET_SANGUINIS = "STUVWX";

// Function to generate random numbers in given range  
int random_num(int start, int end) 
{ 
    int range = (end-start)+1; 
    int random_int = start+(rand()%range); 
    return random_int; 
} 
  
// Create random genes for mutation 
char mutated_genes() 
{ 
    int len = GENES.size(); 
    int r = random_num(0, len-1); 
    return GENES[r]; 
} 
  
// create chromosome or string of genes 
string create_gnome(int TARGET) 
{ 
	if(TARGET == 0) {
		int len = TARGET_CHOLERIS.size(); 
	    string gnome = ""; 
	    for(int i = 0;i<len;i++) 
	        gnome += mutated_genes(); 
	    return gnome; 	
	} else if (TARGET == 1) {
		int len = TARGET_MELANCHOLIS.size(); 
	    string gnome = ""; 
	    for(int i = 0;i<len;i++) 
	        gnome += mutated_genes(); 
	    return gnome;
	} else if (TARGET == 2) {
		int len = TARGET_PHLEGMATIC.size(); 
	    string gnome = ""; 
	    for(int i = 0;i<len;i++) 
	        gnome += mutated_genes(); 
	    return gnome; 
	} else {
		int len = TARGET_SANGUINIS.size(); 
	    string gnome = ""; 
	    for(int i = 0;i<len;i++) 
	        gnome += mutated_genes(); 
	    return gnome; 
	}
} 
  
// Class representing individual in population 
class Individual 
{ 
public: 
    string chromosome;
    int TARGET;
    int fitness; 
    Individual(string chromosome, int TARGET); 
    Individual mate(Individual parent2, int TARGET); 
    int cal_fitness(int TARGET); 
}; 
  
Individual::Individual(string chromosome, int TARGET) 
{ 
    this->chromosome = chromosome; 
    fitness = cal_fitness(TARGET);  
}; 
  
// Perform mating and produce new offspring 
Individual Individual::mate(Individual par2, int TARGET) 
{ 
    // chromosome for offspring 
    string child_chromosome = ""; 
  
    int len = chromosome.size(); 
    for(int i = 0;i<len;i++) 
    { 
        // random probability  
        float p = random_num(0, 100)/100; 
  
        // if prob is less than 0.45, insert gene 
        // from parent 1  
        if(p < 0.45) 
            child_chromosome += chromosome[i]; 
  
        // if prob is between 0.45 and 0.90, insert 
        // gene from parent 2 
        else if(p < 0.90) 
            child_chromosome += par2.chromosome[i]; 
  
        // otherwise insert random gene(mutate),  
        // for maintaining diversity 
        else
            child_chromosome += mutated_genes(); 
    } 
  
    // create new Individual(offspring) using  
    // generated chromosome for offspring 
    return Individual(child_chromosome, TARGET); 
}; 
  
  
// Calculate fittness score, it is the number of 
// characters in string which differ from target 
// string. 
int Individual::cal_fitness(int TARGET) 
{ 
	if(TARGET == 0) {
		int len = TARGET_CHOLERIS.size(); 
	    int fitness = 0; 
	    for(int i = 0;i<len;i++) 
	    { 
	        if(chromosome[i] != TARGET_CHOLERIS[i]) 
	            fitness++; 
	    } 
	    return fitness; 
	} else if (TARGET == 1) {
		int len = TARGET_MELANCHOLIS.size(); 
	    int fitness = 0; 
	    for(int i = 0;i<len;i++) 
	    { 
	        if(chromosome[i] != TARGET_MELANCHOLIS[i]) 
	            fitness++; 
	    } 
	    return fitness;
	} else if (TARGET == 2) {
		int len = TARGET_PHLEGMATIC.size(); 
	    int fitness = 0; 
	    for(int i = 0;i<len;i++) 
	    { 
	        if(chromosome[i] != TARGET_PHLEGMATIC[i]) 
	            fitness++; 
	    } 
	    return fitness;
	} else {
		int len = TARGET_SANGUINIS.size(); 
	    int fitness = 0; 
	    for(int i = 0;i<len;i++) 
	    { 
	        if(chromosome[i] != TARGET_SANGUINIS[i]) 
	            fitness++; 
	    } 
	    return fitness; 
	}    
}; 
  
// Overloading < operator 
bool operator<(const Individual &ind1, const Individual &ind2) 
{ 
    return ind1.fitness < ind2.fitness; 
} 
  
// Driver code 
int main() 
{ 
	int GEN = 0;
	int TARGET;
	for(int x=0; x<4; x++) {
		srand((unsigned)(time(0))); 
  
	    // current generation 
	    int generation = 0; 
	  
	    vector<Individual> population; 
	    bool found = false; 
	  
	    // create initial population 
	    for(int i = 0;i<POPULATION_SIZE;i++) 
	    { 
	        string gnome = create_gnome(x); 
	        population.push_back(Individual(gnome, x)); 
	    } 
  
	    while(! found) 
	    { 
	        // sort the population in increasing order of fitness score 
	        sort(population.begin(), population.end()); 
	  
	        // if the individual having lowest fitness score ie.  
	        // 0 then we know that we have reached to the target 
	        // and break the loop 
	        if(population[0].fitness <= 0) 
	        { 
	            found = true; 
	            break; 
	        } 
	  
	        // Otherwise generate new offsprings for new generation 
	        vector<Individual> new_generation; 
	  
	        // Perform Elitism, that mean 10% of fittest population 
	        // goes to the next generation 
	        int s = (10*POPULATION_SIZE)/100; 
	        for(int i = 0;i<s;i++) 
	            new_generation.push_back(population[i]); 
	  
	        // From 50% of fittest population, Individuals 
	        // will mate to produce offspring 
	        s = (90*POPULATION_SIZE)/100; 
	        for(int i = 0;i<s;i++) 
	        { 
	            int len = population.size(); 
	            int r = random_num(0, 50); 
	            Individual parent1 = population[r]; 
	            r = random_num(0, 50); 
	            Individual parent2 = population[r]; 
	            Individual offspring = parent1.mate(parent2, x); 
	            new_generation.push_back(offspring);  
	        } 
	        population = new_generation; 
	        cout<< "Generation: " << generation << "\t"; 
	        cout<< "String: "<< population[0].chromosome <<"\t"; 
	        cout<< "Fitness: "<< population[0].fitness << "\n"; 
	  
	        generation++; 
	    } 
	    cout<< "Generation: " << generation << "\t"; 
	    cout<< "String: "<< population[0].chromosome <<"\t"; 
    	cout<< "Fitness: "<< population[0].fitness << "\n"; 	
    	if (GEN > generation || GEN == 0){
    		GEN = generation;
			TARGET = x;	
		}
	}
	
	cout << "\n\n";
    
	if (TARGET == 0) {
		cout << "CHOLERIS";
	} else if (TARGET == 1) {
		cout << "MELANCHOLIS";
	} else if (TARGET == 2) {
		cout << "PHLEGMATIC";
	} else {
		cout << "SANGUINIS";
	}
	
} 