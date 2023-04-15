#include "Animal.h"
#include <iostream>

int main()
{
    // Test Genome class
    std::string chromosome_content = "ATCG";
    Genome genome(chromosome_content);
    genome.getGeneticContent();
    genome.setRNA("ATCG");
    genome.makeDNAfromRNA();
    genome.smallMutations('A', 'T', 1);
    genome.getGeneticContent();
    genome.largeMutations("CG", "TA");
    genome.getGeneticContent();
    genome.reverseMutation("GC");
    genome.getGeneticContent();
    int unlinked_points = genome.count_unlinked_dna_points();
    std::cout << "Unlinked DNA points: " << unlinked_points << std::endl;
    int at_pairs, cg_pairs;
    genome.get_base_pairs_count(at_pairs, cg_pairs);
    std::cout << "AT pairs: " << at_pairs << ", CG pairs: " << cg_pairs << std::endl;
    genome.swap_substring(0, genome, 2, 2);
    genome.getGeneticContent();
    std::vector<std::string> palindromes = genome.find_complementary_palindromes(2);
    std::cout << "Complementary palindromes: ";
    for (const std::string& palindrome : palindromes) {
        std::cout << palindrome << ", ";
    }
    std::cout << std::endl;

    // Test Cell class
    std::vector<std::string> chromosomes_content = {"ATCG", "TAGC"};
    Cell cell(2, chromosomes_content);
    cell.cell_death();
    cell.smallMutations('A', 'C', 0, 1);
    cell.largeMutations("AT", 0, "GC", 1);
    cell.reverseMutation("CG", 0);
    cell.print_complementary_palindromes(1, 2);

    // Test Animal class
    Animal animal1(2, chromosomes_content);
    Animal animal2(2, chromosomes_content);
    double similarity = animal1.calculate_genetic_similarity(animal2);
    std::cout << "Genetic similarity: " << similarity << std::endl;
    if (animal1 == animal2) {
        std::cout << "The animals are genetically identical" << std::endl;
    } else {
        std::cout << "The animals are not genetically identical" << std::endl;
    }

    return 0;
}
