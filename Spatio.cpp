#include "Spatio.h"

namespace Spatio
{
	const int SpatioData::kMinoData[19][4] = {
		   {0,1,2,3},
		   {0,4,8,12},
		   {1,4,5,6},
		   {0,1,2,5},
		   {1,4,5,9},
		   {0,4,5,8},
		   {0,1,4,5},
		   {1,2,4,5},
		   {0,4,5,9},
		   {0,1,5,6},
		   {1,4,5,8},
		   {0,4,8,9},
		   {0,1,5,9},
		   {2,4,5,6},
		   {0,1,2,4},
		   {1,5,8,9},
		   {0,1,4,8},
		   {0,1,2,6},
		   {0,4,5,6}
	};
	SpatioBoard::SpatioBoard(int row, int col)
		:row_max_(row), col_max_(col)
	{
		init();
	}
	SpatioBoard::SpatioBoard(const SpatioBoard& obj)
	{
		row_max_ = obj.row_max_;
		col_max_ = obj.col_max_;

		init();
		for (int i = 0; i < row_max_ * col_max_; i++)
			data[i] = obj.data[i];
	}
	SpatioBoard::~SpatioBoard()
	{
		dest();
	}
	void SpatioBoard::dest()
	{
		if (arr)
			delete[] arr;
		if (data)
			delete[] data;

		arr = nullptr;
		data = nullptr;
	}
	void SpatioBoard::init()
	{
		arr = new int* [row_max_];
		data = new int[row_max_ * col_max_];
		for (int i = 0; i < row_max_ * col_max_; i++)
			data[i] = 0;
		for (int i = 0; i < row_max_; ++i)
			arr[i] = data + i * col_max_;
	}

	SpatioGame::SpatioGame(SpatioBoard* board)
		:board_(board)
	{
		turn_ = 0;
	}
	SpatioGame::SpatioGame(const SpatioGame& game)
	{
		this->board_ = game.GetBoard();
		this->turn_ = game.turn_;
	}
	SpatioGame::~SpatioGame()
	{
		delete board_;
	}
	bool SpatioGame::IsOverSub(SpatioBoard* test, int row, int col, int* count)
	{
		if (row < 0 || col < 0 ||
			row >= test->row_max_ || col >= test->col_max_)
			return false;
		else if (test->arr[row][col] != 0)
			return false;
		else if (*count >= 3)
			return true;
		else
		{
			test->arr[row][col] = -1;
			++(*count);
			return \
				IsOverSub(test, row + 1, col, count) ||
				IsOverSub(test, row - 1, col, count) ||
				IsOverSub(test, row, col + 1, count) ||
				IsOverSub(test, row, col - 1, count);
		}
	}
	bool SpatioGame::Action(int row, int col, int n)
	{
		if (n > 18 || n < 0)
			return false;
		const int* expr = SpatioData::kMinoData[n];

		for (int i = 0; i < 4; i++)
			if (expr[i] / 4 + row >= board_->row_max_ ||
				expr[i] % 4 + col >= board_->col_max_)
				return false;

		for (int i = 0; i < 4; i++)
			if (board_->arr[expr[i] / 4 + row][expr[i] % 4 + col] != 0)
				return false;

		++turn_;

		for (int i = 0; i < 4; i++)
			board_->arr[(expr[i] / 4) + row][(expr[i] % 4) + col] = turn_;

		return true;
	}
	bool SpatioGame::IsOver()
	{
		std::unique_ptr<Spatio::SpatioBoard> test(GetBoard());
		for (int i = 0; i < test->row_max_; i++)
			for (int j = 0; j < test->col_max_; j++)
			{
				std::unique_ptr<int> count(new int(0));
				if (IsOverSub(test.get(), i, j, count.get()))
					return false;
			}
		return true;
	}
	SpatioBoard* SpatioGame::GetBoard() const
	{
		return new SpatioBoard(*board_);
	}
	int SpatioGame::GetState()
	{
		return (IsOver() ? ((turn_ + 1) % 2 + 1) : 0);
	}
	int SpatioGame::GetTurn() const
	{
		return turn_;
	}
	std::tuple<int, int> SpatioGame::GetSize()
	{
		return std::make_tuple(board_->row_max_, board_->col_max_);
	}
}