#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <random>
#include "treeNode.h"

void usage()
{
    std::cout << "Usage: ./knightsTour.exe {board_size(int)} {1 for closed tour, 0 for first found tour}" << std::endl;
    exit(0);
}

void printBoard(const std::vector<std::vector<int>> &board)
{
    for (const auto &v : board)
    {
        for (const auto &i : v)
            std::cout << std::setw(5) << i;
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        usage();
    else
    {
        int boardSize;
        auto stamp = std::clock();
        std::random_device rd;
        //Get board size from arguments
        std::string bs(argv[1]);
        std::stringstream str(bs);
        str >> boardSize;
        if (!str)
            usage();
        //Get closed tour requirement from arguments
        if (*argv[2] == '1')
            TreeNode::closedTourRequired = true;

        //Initialise board as a 2d vector filled with 0s
        std::vector<std::vector<int>> board(boardSize, std::vector<int>(boardSize));

        //Create first node in tree with starting coordinates of the knight
        TreeNode current(4, 4, board);

        //Process first node. processNode is called recursively on child nodes
        TreeNode::processNode(current, 1, board);

        //Print board after solution is found, or all paths exhausted
        printBoard(board);
        std::cout << "Board size: " << boardSize << "\n";
        std::cout << "Closed tour: " << std::boolalpha << TreeNode::closedTourRequired << "\n";
        std::cout << "Tour completed in: " << std::clock() - stamp << "ms" << std::endl;
    }
}