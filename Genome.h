#ifndef GENOME_H
#define GENOME_H

#include <string>
#include <vector>
#include <utility>

class Genome
{
public:
    Genome(const std::string &chromosome_contnet);
    std::string RNA;
    std::pair<std::string, std::string> DNA;

    void getGeneticContent() const;
    void makeDNAfromRNA();
    void smallMutations(char from, char to, int n);
    void largeMutations(const std::string &from, const std::string &to);
    void reverseMutation(const std::string &target);
    void setRNA(const std::string &rna);
    void setDNA(const std::string &first, const std::string &second);
    void get_base_pairs_count(int &at_pairs, int &cg_pairs) const;
    void swap_substring(int start_index, Genome &other, int other_start_index, int length);
    std::vector<std::string> find_complementary_palindromes(int min_length);
    bool is_complementary_palindrome(const std::string& s);
    int count_unlinked_dna_points() const;
};

#endif