#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LATTICE_SIZE 20 // Set the size of the lattice/grid as needed

// Function to calculate energy contribution from neighboring spins
double calculateEnergyContribution(int lattice[LATTICE_SIZE][LATTICE_SIZE], int x, int y) {
    double J = 1.0; // Interaction energy. Set as needed.
    int sumOfNeighboringSpins = 0;

    // Calculate the sum of the neighboring spins
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Skip the center point
            if (dx == 0 && dy == 0) continue;

            // Add the spin of the neighboring site, with periodic boundary conditions
            sumOfNeighboringSpins += lattice[(x + dx + LATTICE_SIZE) % LATTICE_SIZE][(y + dy + LATTICE_SIZE) % LATTICE_SIZE];
        }
    }

    // Calculate the energy contribution from this spin site
    double energyContribution = -J * lattice[x][y] * sumOfNeighboringSpins;

    return energyContribution;
}

// Function to perform Monte Carlo simulation for spin flips
void monteCarloFerromagnet(int lattice[LATTICE_SIZE][LATTICE_SIZE], int mcIterations) {
    // int i, j;

    for (int iteration = 0; iteration < mcIterations; iteration++) {
        // Select a random occupied site (t)
        int x = rand() % LATTICE_SIZE;
        int y = rand() % LATTICE_SIZE;

        // Calculate the change in energy (∆H)
        double deltaH = 0.0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                deltaH += calculateEnergyContribution(lattice, (x + dx + LATTICE_SIZE) % LATTICE_SIZE, (y + dy + LATTICE_SIZE) % LATTICE_SIZE);
            }
        }

        // Implement Metropolis algorithm to decide whether to flip the spin or not
        if (deltaH <= 0.0 || (rand() / (double)RAND_MAX) < exp(-deltaH)) {
            // Flip the spin
            lattice[x][y] *= -1;
        }
    }
}

int main() {
    // Example usage
    int lattice[LATTICE_SIZE][LATTICE_SIZE];

    // Initialize your lattice with initial spin values (1 or -1)
    for (int i = 0; i < LATTICE_SIZE; i++) {
        for (int j = 0; j < LATTICE_SIZE; j++) {
            lattice[i][j] = (rand() % 2) ? 1 : -1; // Randomly assign 1 or -1
        }
    }

    // Print the initial lattice
    printf("Initial lattice:\n");
    for (int i = 0; i < LATTICE_SIZE; i++) {
        for (int j = 0; j < LATTICE_SIZE; j++) {
            printf(" %2d", lattice[i][j]); // Use formatted printing
        }
        printf("\n");
    }

    int mcIterations = 10000; // Specify the number of Monte Carlo iterations

    monteCarloFerromagnet(lattice, mcIterations);

    // After the simulation, the lattice will have undergone spin flips according to the Monte Carlo algorithm

    // Print the final lattice
    printf("\nFinal lattice after Monte Carlo simulation:\n");
    for (int i = 0; i < LATTICE_SIZE; i++) {
        for (int j = 0; j < LATTICE_SIZE; j++) {
            printf(" %2d", lattice[i][j]); // Use formatted printing
        }
        printf("\n");
    }

    return 0;
}
