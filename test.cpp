#include <iostream>
#include <iomanip>
#include <memory>
#include <tuple>
#include <Windows.h>
#include <random>
#include <string>
#include <vector>

#include "Spatio.h"

std::tuple<char, int, int, int> getCommand()
{
	std::cout << ">>";

	std::string command;

	do
		std::getline(std::cin, command);
	while (command.length() == 0);

	std::vector<std::string> input_vec;

	int range1 = 0, range2 = 0;
	for (auto& ch : command)
	{
		range2++;
		if (ch == ' ')
		{
			input_vec.push_back(
				command.substr(range1, range2 - range1 - 1)
			);
			range1 = range2;
		}
	}
	input_vec.push_back(command.substr(range1, range2));
	while(input_vec.size() < 4)
		input_vec.push_back(std::string("-1"));

	char ch0;
	int i1, i2, i3;

	ch0 = input_vec[0].at(0);
	i1 = atoi(input_vec[1].c_str());
	i2 = atoi(input_vec[2].c_str());
	i3 = atoi(input_vec[3].c_str());

	return std::make_tuple(ch0, i1, i2, i3);
}

void setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(info.wAttributes & 0xf0) | (color & 0xf));
}

inline int randIntMt(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

const char* stateCode[3] = {
	"NOT_OVER",
	"GOING_1ST_WIN",
	"GOING_2ND_WIN"
};

void printBoard(Spatio::SpatioGame* game)
{
	bool flag = false;
	std::unique_ptr<Spatio::SpatioBoard> board(game->GetBoard());
	auto size = game->GetSize();

	std::cout << "Turn : " << game->GetTurn() << std::endl;
	std::cout << stateCode[game->GetState()] << std::endl;
	for (int i = 0; i < std::get<0>(size); i++)
	{
		for (int j = 0; j < std::get<1>(size); j++)
		{
			int temp;
			if (board->arr[i][j] == 0)
				temp = 7;
			else
				temp = board->arr[i][j] % 6 + 1;
			setFontColor(temp);
			std::cout << std::setw(2);
			std::cout << board->arr[i][j];
		}
		std::cout << std::endl;
	}
	setFontColor(0x7);
}


int main(int argc, char** argv)
{
	int row = 10, col = 20;

	std::unique_ptr<Spatio::SpatioGame> game(
		new Spatio::SpatioGame(new Spatio::SpatioBoard(row, col))
	);

	while (true)
	{
		printBoard(game.get());
		auto cmd = getCommand();

		bool exit = false;
		switch (std::get<0>(cmd))
		{
		case 'a':
			if (game->Action(
				std::get<1>(cmd),
				std::get<2>(cmd),
				std::get<3>(cmd)
			))
				std::cout << "Valid." << std::endl;
			else
				std::cout << "Not Valid." << std::endl;
			break;
		case 'r'://random action which is valid
			if (game->IsOver())
				std::cout << "Over" << std::endl;
			else
				while (!game->Action(
					randIntMt(0, row),
					randIntMt(0, col),
					randIntMt(0, 18)
				));
			break;
		case 'o':
			if (game->IsOver()) std::cout << "Over" << std::endl;
			else std::cout << "Not Over" << std::endl;
			break;
		case 'x':
			exit = true;
			break;
		default:
			std::cout << "invalid command." << std::endl;
			break;
		}
		if (exit)
			break;
	}
	return 0;
}
