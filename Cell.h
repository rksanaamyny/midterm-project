#ifndef CELL_H
#define CELL_H

#include <vector>
#include <string>
#include "Genome.h" // Include the Genome class

class Cell
{
public:
    Cell();
    Cell(int num_chromosomes, const std::vector<std::string> &chromosomes_contnet);

    void cell_death();
    void largeMutations(const std::string &S1, int n, const std::string &S2, int m);
    void smallMutations(int A, int C, int n, int m);
    void reverseMutation(const std::string &S1, int n);
    void print_complementary_palindromes(int n, int min_length);

private:
    int num_chromosomes;
    std::vector<Genome> chromosomes;
    bool dead;
};

#endif // CELL_H
