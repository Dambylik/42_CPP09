
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./PmergeMe <sequence of positive integers>" << std::endl;
        return 1;
    }

    PmergeMe sorter;

    try
    {
        sorter.checkInput(argc, argv);

        // Fill the containers before sorting
        sorter.fillVector(argc, argv);
        sorter.fillDeque(argc, argv);

        // VECTOR sorting
        sorter.printBefore();
        double start = getTime();
        vector_t sortedVec = sorter.mergeInsertionSortVector(sorter.getVector());
        sorter.setVector(sortedVec);
        sorter.printAfter();
        sorter.printTime(VECTOR, getTime() - start);

        // DEQUE sorting
        start = getTime();
        deque_t sortedDeque = sorter.mergeInsertionSortDeque(sorter.getDeque());
        sorter.setDeque(sortedDeque);
        sorter.printTime(DEQUE, getTime() - start);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
