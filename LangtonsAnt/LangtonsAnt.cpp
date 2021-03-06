// LangtonsAnt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;
struct Ant
{
	int x=0;
	int y=0;
};
struct Position
{
	int x = 0;
	int y = 0;
};
struct Velocity
{
	int x = 0;
	int y = 0;
};
Velocity velocity;
Position particle;

Ant ant;
bool moveX=true;
bool moveY;
void makeGame(vector<vector<bool>>&, vector<bool>&);

void allWhite(vector<vector<bool>>& game, vector<bool>& row);

void allBlack(vector<vector<bool>>& game, vector<bool>& row);

void force_field(int g_x, int g_y);
void inertia(int, int, const vector<vector<bool>>&);
void initializer(int density, int g_x, int g_y, int init_v_x, int init_v_y, vector<vector<bool>>&, vector<bool>&);
void seeder(vector<vector<bool>>&, vector<bool>&);
void moveAnt(vector<vector<bool>>&, vector<bool>&);
void display(const vector<vector<bool>>&, const vector<bool>&);

int main()
{
	vector<vector<bool>> game;
	vector<bool>row(30, false);
	ant.x = 15;
	ant.y = 15;
	cout << "Welcome to Langton's Ant\n\nAlex Mair 2021" << endl;
	this_thread::sleep_for(2s);
	cout << "Choose 1- all white squares 2 - all black squares 3 - arbitrary initial starting pattern" << endl;
	int op;
	cin >> op;
	switch (op)
	{
	case 1:
		allWhite(game, row);
		break;
	case 2:
		allBlack(game, row);
		break;
	case 3:
		makeGame(game, row);
		initializer(50, 0, 2, -1, 2, game, row);
		break;
	default:
		break;
	}
	display(game, row);
	this_thread::sleep_for(1s);
	system("CLS");
	while (true)
	{

		moveAnt(game, row);
		display(game, row);
		system("CLS");
	}
    return 0;
}

void display(const vector<vector<bool>>& game, const vector<bool>& row)
{
	for (size_t i = 0; i < game.size(); i++)
	{
		for (size_t j = 0; j < row.size(); j++)
		{
			if (ant.y == i && ant.x == j)
			{
				cout << "( )";
			}
			else if (game[i][j])
			{
				cout << "#";
			}
			
			else
			{

				cout << " ";

			}

		}
		cout << endl;
	}
}
void moveAnt(vector<vector<bool>>& game, vector<bool>& row)
{
	if (ant.x == 0)
	{
		ant.x = row.size() - 2;
	}
	if (ant.x == row.size() - 1)
	{
		ant.x = 1;
	}
	
	if (ant.y == 0)
	{
		ant.y = row.size() - 2;
	}
	if (ant.y == row.size() - 1)
	{
		ant.y = 1;
	}
	if (ant.x >= 0 && ant.x < row.size() && ant.y >= 0 && ant.y < game.size())
	{

		if (game[ant.y][ant.x] && moveX)
		{
			game[ant.y][ant.x] = false;
			ant.y += 1;
			moveY = true;

		}
		if (!game[ant.y][ant.x] && moveX)
		{
			game[ant.y][ant.x] = true;
			ant.y -= 1;
			moveY = true;
		}

		if (game[ant.y][ant.x] && moveY)
		{
			game[ant.y][ant.x] = false;
			ant.x += 1;
			moveX = true;
		}
		if (!game[ant.y][ant.x] && moveY)
		{
			game[ant.y][ant.x] = true;
			ant.x -= 1;
			moveX = true;
		}
	}
}

void makeGame( vector<vector<bool>>& game, vector<bool>& row)
{
	
		game.assign(30, row);
	
}
void allWhite(vector<vector<bool>>& game, vector<bool>& row)
{
	row.assign(30, true);
	game.assign(30, row);

}
void allBlack(vector<vector<bool>>& game, vector<bool>& row)
{
	row.assign(30, false);
	game.assign(30, row);

}
void force_field(int g_x, int g_y)
{
	velocity.x += g_x;
	velocity.y += g_y;
}

void inertia(int g_x, int g_y, const vector<vector<bool>> &game)
{
	if (particle.x + velocity.x >= game.size() - 1
		|| particle.x + velocity.x <= 0)
	{
		velocity.x = -velocity.x - g_x;
	}
	if (particle.y + velocity.y >= game.size() - 1
		|| particle.y + velocity.y <= 0)
	{
		velocity.y = -velocity.y - g_y;
	}
	particle.x += velocity.x;
	particle.y += velocity.y;
}
void initializer(int density, int g_x, int g_y, int init_v_x, int init_v_y, vector<vector<bool>> &game, vector<bool > &row)
{
	//this works by "shooting" a virtual projectile into the game space,
	//applying an arbitrary force field to it and taking snapshots as it bounces around
	velocity.x = init_v_x;
	velocity.y = init_v_y;
	for (size_t i = 0; i < density; i++)
	{
		inertia(g_x, g_y, game);
		force_field(g_x, g_y);
		//this function takes the requisit snapshots, which become live cells
		seeder(game, row);
	}
}
void seeder(vector<vector<bool>>& game, vector<bool>& row)
{
	for (size_t i = 0; i < game.size(); i++)
	{
		for (size_t j = 0; j < row.size(); j++)
		{
			if (i == particle.x && j == particle.y)
			{
				game[i][j] = true;
			}
		}
	}
}

