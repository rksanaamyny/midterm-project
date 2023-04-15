#include "Genome.h"
#include <iostream>
#include <algorithm>
// Helper function to find the complement of a given nucleotide
char getComplement(char nucleotide)
{
    switch (nucleotide)
    {
    case 'A':
        return 'T';
    case 'T':
        return 'A';
    case 'C':
        return 'G';
    case 'G':
        return 'C';
    default:
        return ' ';
    }
}


Genome::Genome(const std::string & chromosome_content){

    std::string firstStrand = "";
    std::string secondStrand = "";

    for (char nucleotide : chromosome_content)
    {
        char dnaNucleotide = getComplement(nucleotide);
        firstStrand += nucleotide;
        secondStrand += dnaNucleotide;
    }

    setDNA(firstStrand,secondStrand);
}

void Genome::getGeneticContent() const
{
    std::cout << "RNA: " << RNA << std::endl;
    std::cout << "DNA: " << std::endl;
    std::cout << DNA.first << std::endl;
    std::cout << DNA.second << std::endl;
    std::cout << std::endl;
}

void Genome::setRNA(const std::string &rna)
{
    RNA = rna;    
}

void Genome::setDNA(const std::string &first,const std::string &second){
    DNA.first = first;
    DNA.second = second;
}

void Genome::makeDNAfromRNA()
{
    std::string firstStrand = "";
    std::string secondStrand = "";

    for (char nucleotide : RNA)
    {
        char dnaNucleotide = getComplement(nucleotide);
        firstStrand += nucleotide;
        secondStrand += dnaNucleotide;
    }

    std::cout << "RNA: " << RNA << std::endl;
    std::cout << "DNA: " << std::endl;
    std::cout << firstStrand << std::endl;
    std::cout << secondStrand << std::endl;
    std::cout << std::endl;
}

void Genome::smallMutations(char from, char to, int n)
{
    int count = 0;
    for (size_t i = 0; i < RNA.size() && count < n; i++)
    {
        if (RNA[i] == from)
        {
            RNA[i] = to;
            count++;
        }
    }

    count = 0;
    for (size_t i = 0; i < DNA.first.size(); ++i)
    {
        if (DNA.first[i] == from)
        {
            DNA.first[i] = to;
            DNA.second[i] = getComplement(to);
            ++count;
        }
        else if (DNA.second[i] == from)
        {
            DNA.second[i] = to;
            DNA.first[i] = getComplement(to);
            ++count;
        }
        if (count == n)
            break;
    }
}

void Genome::largeMutations(const std::string &from, const std::string &to)
{
    size_t pos = RNA.find(from);
    if (pos != std::string::npos)
    {
        RNA.replace(pos, from.length(), to);
    }

    size_t pos1 = DNA.first.find(from);
    size_t pos2 = DNA.second.find(from);

    if (pos1 != std::string::npos && pos2 != std::string::npos)
    {
        if (pos1 <= pos2)
        {
            std::string firstStrandMutation = DNA.first;
            std::string secondStrandMutation = "";
            firstStrandMutation.replace(pos1, from.length(), to);
            for (char c : firstStrandMutation)
            {
                secondStrandMutation += getComplement(c);
            }
            DNA = {firstStrandMutation, secondStrandMutation};
        }
        else
        {
            std::string firstStrandMutation = "";
            std::string secondStrandMutation = DNA.second;

            secondStrandMutation.replace(pos2, from.length(), to);

            for (char c : secondStrandMutation)
            {
                firstStrandMutation += getComplement(c);
            }
            DNA = {firstStrandMutation, secondStrandMutation};
        }
    }
    else if (pos1 != std::string::npos)
    {
        std::string firstStrandMutation = DNA.first;
        std::string secondStrandMutation = "";
        firstStrandMutation.replace(pos1, from.length(), to);
        for (char c : firstStrandMutation)
        {
            secondStrandMutation += getComplement(c);
        }
        DNA = {firstStrandMutation, secondStrandMutation};
    }
    else if (pos2 != std::string::npos)
    {
        std::string firstStrandMutation = "";
        std::string secondStrandMutation = DNA.second;
        secondStrandMutation.replace(pos2, from.length(), to);
        for (char c : secondStrandMutation)
        {
            firstStrandMutation += getComplement(c);
        }
        DNA = {firstStrandMutation, secondStrandMutation};
    }
}

void Genome::reverseMutation(const std::string &target)
{
    size_t pos = RNA.find(target);
    if (pos != std::string::npos)
    {
        std::string reversed(target.rbegin(), target.rend());
        RNA.replace(pos, target.length(), reversed);
    }

    pos = DNA.first.find(target);
    if (pos != std::string::npos)
    {
        std::string firstStrandReversed(target.rbegin(), target.rend());
        DNA.first.replace(pos, target.length(), firstStrandReversed);

        std::string secondStrandMutation;
        for (char c : firstStrandReversed)
        {
            secondStrandMutation = getComplement(c) + secondStrandMutation;
        }
        DNA.second.replace(DNA.second.size() - pos - target.length(), target.length(), secondStrandMutation);
    }
}

int Genome::count_unlinked_dna_points() const {
    int unlinked_points = 0;

    if (DNA.first.length() != DNA.second.length()) {
        return -1; // Return -1 if the DNA strands have different lengths, indicating an error
    }

    for (size_t i = 0; i < DNA.first.length(); ++i) {
        char base1 = DNA.first[i];
        char base2 = DNA.second[i];

        // Check if the base pair is not complementary
        if (!((base1 == 'A' && base2 == 'T') || (base1 == 'T' && base2 == 'A') ||
              (base1 == 'C' && base2 == 'G') || (base1 == 'G' && base2 == 'C'))) {
            unlinked_points++;
        }
    }

    return unlinked_points;
}

 void Genome::get_base_pairs_count(int& at_pairs, int& cg_pairs) const {
    at_pairs = 0;
    cg_pairs = 0;

    if (DNA.first.length() != DNA.second.length()) {
        return; // If the DNA strands have different lengths, do not count the base pairs
    }

    for (size_t i = 0; i < DNA.first.length(); ++i) {
        char base1 = DNA.first[i];
        char base2 = DNA.second[i];

        if ((base1 == 'A' && base2 == 'T') || (base1 == 'T' && base2 == 'A')) {
            at_pairs++;
        } else if ((base1 == 'C' && base2 == 'G') || (base1 == 'G' && base2 == 'C')) {
            cg_pairs++;
        }
    }
}

void Genome::swap_substring(int start_index, Genome& other, int other_start_index, int length) {
    if (start_index + length > DNA.first.length() || other_start_index + length > other.DNA.first.length()) {
        return; // Return if the substrings exceed the bounds of their respective DNA strands
    }

    // Swap the substrings in both DNA strands
    std::string temp1 = DNA.first.substr(start_index, length);
    std::string temp2 = DNA.second.substr(start_index, length);

    DNA.first.replace(start_index, length, other.DNA.first.substr(other_start_index, length));
    DNA.second.replace(start_index, length, other.DNA.second.substr(other_start_index, length));

    other.DNA.first.replace(other_start_index, length, temp1);
    other.DNA.second.replace(other_start_index, length, temp2);
}

bool Genome::is_complementary_palindrome(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        char left_comp = getComplement(s[right]);
        char right_comp = getComplement(s[left]);

        if (s[left] != left_comp || s[right] != right_comp) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

std::vector<std::string> Genome::find_complementary_palindromes(int min_length){
    std::vector<std::string> palindromes;
    int len = DNA.first.length();

    for (int window = min_length; window <= len; ++window) {
        for (int i = 0; i <= len - window; ++i) {
            std::string substr = DNA.first.substr(i, window);
            if (is_complementary_palindrome(substr)) {
                palindromes.push_back(substr);
            }
        }
    }

    return palindromes;
}



