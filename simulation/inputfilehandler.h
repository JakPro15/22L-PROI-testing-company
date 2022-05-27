#ifndef _INPUTFILEHANDLER_H
#define _INPUTFILEHANDLER_H

#include <fstream>
#include <vector>
#include "../games/abstractgame.h"
#include "../producer/producer.h"
#include "../testingcompany/tester.h"
#include "../testingcompany/manager.h"
#include "outputhandler.h"
#include "simulation.h"

// This class handles the input of the simulation

class InputFileHandler
{
    private:
        // Simulation which this handler is a part of.
        Simulation& sim;

        // Reference to the output handler.
        OutputHandler& out;

        // File containing data on producers.
        std::ifstream producersFile;

        // File containing data on games.
        std::ifstream gamesFile;

        // File containing data on testers.
        std::ifstream testersFile;

        // File containing data on managers.
        std::ifstream managersFile;

        // Number of all producers that were created.
        unsigned int producers;

        // Number of all games that were created.
        unsigned int games;

        // Number of all competetive games that were created.
        unsigned int competetiveGames;

        // Number of all infinite games that were created.
        unsigned int infiniteGames;

        // Number of all roleplaying games that were created.
        unsigned int roleplayingGames;

        // Number of all testers that were created.
        unsigned int testers;

        // Number of all managers that were created.
        unsigned int managers;

    public:
        // Throws exception when file can't be opened.
        InputFileHandler(
            Simulation& sim, OutputHandler& out,
            std::string producersFileName, std::string gamesFileName,
            std::string testersFileName, std::string managersFileName);

        // All files are closed when object is destroyed.
        ~InputFileHandler();

        // Creates next producer from the file and returns a pointer to it
        std::shared_ptr<Producer> createProducer();

        // Creates next game from the file and returns a pointer to it
        std::shared_ptr<AbstractGame> createGame();

        // Creates next tester from the file and returns a pointer to it
        std::shared_ptr<Tester> createTester();

        // Creates next manager from the file and returns a pointer to it
        std::shared_ptr<Manager> createManager();
};

#endif