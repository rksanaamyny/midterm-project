#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <ctime>
#include "Animal.h"

Animal::Animal(int num_chromosomes, const std::vector<std::string> &chromosomes)
    : Cell(num_chromosomes, chromosomes), num_chromosomes(num_chromosomes), chromosomes(chromosomes) {
}

double Animal::calculate_genetic_similarity(const Animal &other) const
{
    if (num_chromosomes != other.num_chromosomes)
    {
        return 0.0;
    }

    int total_characters = 0;
    int matches = 0;

    for (int i = 0; i < num_chromosomes; ++i)
    {
        const Genome& genome1 = Genome(chromosomes[i]);
        const Genome& genome2 = Genome(other.chromosomes[i]);

        const std::string &dna1_first = genome1.DNA.first;
        const std::string &dna1_second = genome1.DNA.second;
        const std::string &dna2_first = genome2.DNA.first;
        const std::string &dna2_second = genome2.DNA.second;

        for (size_t j = 0; j < dna1_first.length(); ++j)
        {
            if (dna1_first[j] == dna2_first[j])
            {
                ++matches;
            }
            ++total_characters;
        }

        for (size_t j = 0; j < dna1_second.length(); ++j)
        {
            if (dna1_second[j] == dna2_second[j])
            {
                ++matches;
            }
            ++total_characters;
        }
    }

    return 100.0 * static_cast<double>(matches) / static_cast<double>(total_characters);
}

bool Animal::operator==(const Animal &other) const
{
    double similarity = calculate_genetic_similarity(other);
    return similarity > 70.0 && num_chromosomes == other.num_chromosomes;
}

Animal Animal::asexual_reproduction() const
{
    if (num_chromosomes % 2 == 1)
    {
        throw std::runtime_error("Asexual reproduction does not occur if n is odd.");
    }

    std::vector<std::string> child_chromosomes(num_chromosomes);
    std::vector<int> indices(num_chromosomes);
    for (int i = 0; i < num_chromosomes; ++i)
    {
        indices[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    int similarity_threshold = static_cast<int>(num_chromosomes * 0.7);

    for (int i = 0; i < similarity_threshold; ++i)
    {
        child_chromosomes[i] = chromosomes[indices[i]];
    }

    for (int i = similarity_threshold; i < num_chromosomes; ++i)
    {
        int index = indices[i];
        child_chromosomes[i] = chromosomes[index];
        child_chromosomes[index] = chromosomes[index];
    }

    return Animal(num_chromosomes, child_chromosomes);
}

Animal Animal::operator+(const Animal &other) const
{
    if (num_chromosomes != other.num_chromosomes)
    {
        throw std::runtime_error("Both animals must have the same number of chromosomes.");
    }

    Animal child1 = asexual_reproduction();
    Animal child2 = other.asexual_reproduction();

    std::vector<std::string> combined_chromosomes(num_chromosomes);

    int similarity_threshold = static_cast<int>(num_chromosomes * 0.7);

    for (int i = 0; i < similarity_threshold; ++i)
    {
        combined_chromosomes[i] = child1.chromosomes[i];
    }

    for (int i = similarity_threshold; i < num_chromosomes; ++i)
    {
        combined_chromosomes[i] = child2.chromosomes[i];
    }

    return Animal(num_chromosomes, combined_chromosomes);
}

void Animal::cell_death_with_chromosome_removal()
{
    cell_death();

    int max_unlinked_points = -1;
    int chromosome_index_to_remove = -1;

    for (int i = 0; i < num_chromosomes; ++i)
    {
        int unlinked_points = Genome(chromosomes[i]).count_unlinked_dna_points();
        if (unlinked_points > max_unlinked_points)
        {
            max_unlinked_points = unlinked_points;
            chromosome_index_to_remove = i;
        }
    }

    if (chromosome_index_to_remove >= 0)
    {
        //chromosomes.erase(chromosomes.begin() + chromosome_index_to_remove);
        num_chromosomes--;
    }
}
