#include "Cell.h"
#include "Genome.h"
#include <iostream>

Cell::Cell() : num_chromosomes(0), dead(false) {
}
Cell::Cell(int num_chromosomes, const std::vector<std::string>& chromosomes_content) : num_chromosomes(0), dead(false){
    for (const std::string chromosome_content : chromosomes_content) {
        chromosomes.push_back(Genome(chromosome_content));
    }
}

void Cell::cell_death() {    
    bool should_die = false;

    for (Genome& chromosome : chromosomes) {
        int unlinked_dna_points = chromosome.count_unlinked_dna_points();
        
        int at_pairs, cg_pairs;
        chromosome.get_base_pairs_count(at_pairs, cg_pairs);

        if (unlinked_dna_points > 5 || (at_pairs > 3 * cg_pairs)) {
            should_die = true;
            break;
        }
    }

    if (should_die) {
         dead = true;
    }
}



void Cell::largeMutations(const std::string& S1, int n, const std::string& S2, int m) {
    if (n >= num_chromosomes || m >= num_chromosomes) {
        return; // Return if n or m are outside the valid chromosome indices
    }

    Genome& chromosome_n = chromosomes[n];
    Genome& chromosome_m = chromosomes[m];

    // Find the first occurrence of S1 in chromosome n
    size_t found_n_first = chromosome_n.DNA.first.find(S1);
    size_t found_n_second = chromosome_n.DNA.second.find(S1);

    // Find the first occurrence of S2 in chromosome m
    size_t found_m_first = chromosome_m.DNA.first.find(S2);
    size_t found_m_second = chromosome_m.DNA.second.find(S2);

    // If the substrings are found in both chromosomes, replace S1 in chromosome n with S2 from chromosome m
    if (found_n_first != std::string::npos && found_m_first != std::string::npos) {
        chromosome_n.largeMutations(S1, S2);
    }

    if (found_n_second != std::string::npos && found_m_second != std::string::npos) {
        chromosome_n.largeMutations(S1, S2);
    }
}


void Cell::smallMutations(int A, int C, int n, int m) {
    if (n >= num_chromosomes) {
        return; // Return if n is outside the valid chromosome indices
    }

    Genome& chromosome_n = chromosomes[n];
    chromosome_n.smallMutations(A, C, m);
}



void Cell::reverseMutation(const std::string& S1, int n) {
    if (n >= num_chromosomes) {
        return; // Return if n is outside the valid chromosome indices
    }

    Genome& chromosome_n = chromosomes[n];
    chromosome_n.reverseMutation(S1);
}


void Cell::print_complementary_palindromes(int n, int min_length) {
    if (n >= num_chromosomes) {
        return; // Return if n is outside the valid chromosome indices
    }

    Genome& chromosome_n = chromosomes[n];
    std::vector<std::string> palindromes = chromosome_n.find_complementary_palindromes(min_length);

    std::cout << "Complementary palindromes longer than " << min_length << " in chromosome " << n << ":" << std::endl;
    for (const std::string& palindrome : palindromes) {
        std::cout << palindrome << std::endl;
    }
}

