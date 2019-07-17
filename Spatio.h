#pragma once

#include <iostream>
#include <memory>
#include <tuple>


#include "SpatioData.h"

namespace Spatio
{
	
	class SpatioBoard;
	class SpatioGame;
	class SpatioData;

	class SpatioData
	{
		friend class SpatioGame;

	private:
		static const int kMinoData[19][4];
	};

	class SpatioBoard
	{
		friend class SpatioGame;

	public:
		int** arr;
	private:
		int* data;
		int row_max_, col_max_;

	public:
		SpatioBoard(int row, int col);
		SpatioBoard(const SpatioBoard& obj);
		~SpatioBoard();
	private:
		void dest();
		void init();
	};

	class SpatioGame
	{
	private:
		SpatioBoard* board_;
		int turn_;

	public:
		SpatioGame(SpatioBoard* board);
		SpatioGame(const SpatioGame& game);
		~SpatioGame();

	public:
		// return true if action is valid and executed
		bool Action(int row, int col, int n);
		bool IsOver();
		SpatioBoard* GetBoard() const;
		int GetState();
		int GetTurn() const;
		std::tuple<int , int> GetSize();
	
	private:
		bool IsOverSub(SpatioBoard* test, int row, int col, int* count);
	};
}
