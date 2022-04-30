#include "../game.h"
#include "../checkallwhitespace.h"
#include "../exceptions.h"


std::string Game::getUniqueName() const noexcept
{
     return "Game " + std::to_string(id - 10000);
}


void Game::checkId() const
{
     if(id < 10001 or id > 19999)
     {
          throw InvalidId("Game", id);
     }
}


void Game::checkComplexity(AbstractGame::Complexity complexity)
{
     // Check if the value corresponds to an enumerator.
     if(complexity < 0 or complexity > 3)
     {
          throw InvalidComplexity(complexity);
     }
}


Game::Game(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
     bool codeAvailable=false, Price marketPrice=0, unsigned int minTestersAmount=1):
     id(id), title(title), producer(producer), filesSize(filesSize), complexity(complexity),
     codeAvailable(codeAvailable), marketPrice(marketPrice), minTestersAmount(minTestersAmount)
{
     checkId();
     if(checkAllWhitespace(title))
     {
          throw InvalidTitle(title);
     }
     if(filesSize == 0)
     {
          throw InvalidFilesSize();
     }
     checkComplexity(complexity);
     if(minTestersAmount == 0)
     {
          throw InvalidMinTestersAmount();
     }
     // Also InvalidPrice can be thrown by the Price constructor.
}


Game::Game(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
     bool codeAvailable=false, int priceZl=0, int priceGr=0, unsigned int minTestersAmount=1):
     Game(id, title, producer, filesSize, complexity, codeAvailable, Price(priceZl, priceGr), minTestersAmount)
{}


Game::~Game()
{}


int Game::getId() const noexcept
{
     return id;
}


void Game::setTitle(std::string title)
{
     if(checkAllWhitespace(title))
     {
          throw InvalidTitle(title);
     }
     else
     {
          this->title = title;
     }
}


std::string Game::getTitle() const noexcept
{
     return title;
}


void Game::setFilesSize(unsigned int filesSize)
{
     if(filesSize == 0)
     {
          throw InvalidFilesSize();
     }
     else
     {
          this->filesSize = filesSize;
     }
}


unsigned int Game::getFilesSize() const noexcept
{
     return filesSize;
}


void Game::setCodeAvailable(bool codeAvailable) noexcept
{
     this->codeAvailable = codeAvailable;
}


unsigned int Game::getCodeAvailable() const noexcept
{
     return codeAvailable;
}


void Game::setMarketPrice(Price marketPrice)
{
     this->marketPrice = marketPrice;
}


void Game::setMarketPrice(int priceZl, int priceGr)
{
     // Price constructor may throw InvalidPrice.
     this->marketPrice = Price(priceZl, priceGr);
}


Price Game::getMarketPrice() const noexcept
{
     return marketPrice;
}


void Game::setComplexity(AbstractGame::Complexity complexity)
{
     checkComplexity(complexity);
     this->complexity = complexity;
}


AbstractGame::Complexity Game::getComplexity() const noexcept
{
     return complexity;
}


Producer& Game::getProducer() const noexcept
{
     return producer;
}


void Game::setMinTestersAmount(unsigned int minTestersAmount)
{
     if(minTestersAmount == 0)
     {
          throw InvalidMinTestersAmount();
     }
     else
     {
          this->minTestersAmount = minTestersAmount;
     }
}


unsigned int Game::getMinTestersAmount() const noexcept
{
     return minTestersAmount;
}


int Game::getTestingTime() const noexcept
{

}


Price Game::getTestingPrice() const noexcept
{

}


bool Game::operator==(const AbstractGame &game) const noexcept
{

}


bool Game::operator!=(const AbstractGame &game) const noexcept
{

}


std::ostream& operator<<(std::ostream &stream, const Game &game)
{

}

