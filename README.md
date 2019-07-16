# spatio_api
2-player-abstract-strategy-board-game api

## 1. Spatio
* Spatio is a  2-player-abstract-strategy-boardgame using polyomino, especially tetromino (known as the component of Tetris).
* It is easy-to-learn, hard to master game because branches of possible case increases expotentially as the computing turn increases.

## 2. Rule of Spatio
* 2 Players are needed for this game.
---
#### 2.0. Tetromino
Tetromino | pic
:------:|:-----:
I|![I](https://upload.wikimedia.org/wikipedia/commons/thumb/1/14/Tetromino_I.svg/71px-Tetromino_I.svg.png)
O|![O](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fc/Tetromino_O.svg/39px-Tetromino_O.svg.png)
T|![T](https://upload.wikimedia.org/wikipedia/commons/thumb/4/41/Tetromino_T.svg/54px-Tetromino_T.svg.png)
J|![J](https://upload.wikimedia.org/wikipedia/commons/thumb/f/fd/Tetromino_J.svg/54px-Tetromino_J.svg.png)
L|![L](https://upload.wikimedia.org/wikipedia/commons/thumb/a/aa/Tetromino_L.svg/56px-Tetromino_L.svg.png)
S|![S](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d3/Tetromino_S.svg/56px-Tetromino_S.svg.png)
Z|![Z](https://upload.wikimedia.org/wikipedia/commons/thumb/6/61/Tetromino_Z.svg/53px-Tetromino_Z.svg.png)
#### 2.1. Board
1. **[Board]** is structured with n*m grid.
---
#### 2.2. Action

1. Action means a player should put **a tetromino block** in given **[Board]**.
2. If the **[Action]** is taken, that 4 cells are used. 
3. If there is one or more cell which was used for previous **[Action]**, that **[Action]** is not Valid.
---
#### 2.3. Order
1.  A going-1st player takes an **[Action]**. If it's not possible, 2nd player wins.
2.  A going-2nd player takes an **[Action]**. If it's not possible, 1st player wins.
3.  Go to **1**.
---
## 3. Spatio_api reference

### 3.0. namespace
#### 3.0.1. Spatio
``` cpp
namespace Spatio
```
---
### 3.1. enum
#### 3.1.1. minoCode
``` cpp
enum minoCode {
	I_H = 0,
	I_V,
	T_U,
	T_D,
	T_L,
	T_R,
	O,
	S_H,
	S_V,
	Z_H,
	Z_V,
	L_U,
	L_D,
	L_L,
	L_R,
	J_U,
	J_D,
	J_L,
	J_R = 18
};
```
#### 3.1.2. game_state
``` cpp
enum game_state {
	NOT_OVER = 0,
	GOING_1ST_WIN,
	GOING_2ND_WIN
};
```
---
### 3.2. class
#### 3.2.1. SpatioBoard

``` cpp
public:
	SpatioBoard(int row, int col);
	SpatioBoard(const SpatioBoard& obj);
	~SpatioBoard();
```
##### 3.2.1.1. member variable
``` cpp
public:
	int** arr; // Usage : arr[row][column]
```
#### 3.2.2. SpatioGame
``` cpp
public:
	SpatioGame(SpatioBoard* board);
	SpatioGame(const SpatioGame& game);
	~SpatioGame();
```
##### 3.2.1.1. member variable
``` cpp
private:
	SpatioBoard* board_; // Deallocated in destructor
	int turn_;
```
##### 3.2.1.2. member function
``` cpp
public:
	// return true if action is valid and executed
	bool Action(int row, int col, int n);
	bool IsOver();
	SpatioBoard* GetBoard() const;
	std::tuple<int, int, int, bool, int> GetState();
```
#### 3.3. example:
``` cpp
int row = 5, col = 10;
std::unique_ptr<Spatio::SpatioGame> game(
	new Spatio::SpatioGame(new Spatio::SpatioBoard(row, col))
);
if (game->IsOver())
	std::cout << "Over" << std::endl;
else
	if (game->Action(
		std::get<1>(cmd),
		std::get<2>(cmd),
		std::get<3>(cmd)
	))
		std::cout << "Valid." << std::endl;
	else
		std::cout << "Not Valid." << std::endl;
```
---
