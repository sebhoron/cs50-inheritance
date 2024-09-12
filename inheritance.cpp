#include <iostream>
#include <cstdlib>
#include <ctime>

// Each person has two parents and two alleles
struct person
{
    person *parents[2];
    char alleles[2];
};

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main()
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);

    return 0;
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // Allocate memory for new person.
    person *p = new person;

    // Generation with parent data.
    if (generations > 1)
    {
        // Recursively create blood type histories for parents.
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);
        // Randomly assign child alleles based on parents.
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }
    // Generation without parent data.
    else
    {
        // Set parent pointers to NULL.
        p->parents[0] = nullptr;
        p->parents[1] = nullptr;
        // Randomly assign alleles.
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // Return newly created person.
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // Handle base case.
    if (p == nullptr)
    {
        return;
    }

    // Free parents.
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free child.
    delete p;
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case.
    if (p == nullptr)
    {
        return;
    }

    // Print indentation.
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        std::cout << " ";
    }

    // Print person.
    std::cout << "Generation " << generation << ", blood type " << p->alleles[0] << p->alleles[1] << std::endl;
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
