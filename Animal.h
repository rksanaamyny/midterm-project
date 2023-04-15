#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
#include "Cell.h"

class Animal : public Cell
{
public:
    int num_chromosomes;
    const std::vector<std::string> &chromosomes;
    Cell cell;

    Animal(int num_chromosomes, const std::vector<std::string> &chromosomes);

    double calculate_genetic_similarity(const Animal &other) const;
    bool operator==(const Animal &other) const;
    Animal asexual_reproduction() const;
    Animal operator+(const Animal &other) const;
    void cell_death_with_chromosome_removal();
};

#endif // ANIMAL_H
