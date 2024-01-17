#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


const int cubeMaxX = 10;
const int cubeMaxY = 20;


class Template {
private:

	const int cubeSize = 40;

	float width = cubeSize * (cubeMaxX + 2 + 5);
	float height = cubeSize * (cubeMaxY + 2);

	RenderWindow window;
	
	int frame = 1;

	Event event;

	Font font;

	Text scoreText;
	int score = 0;

	Text gameOverText;

	RectangleShape border;

	vector<RectangleShape> cube;

	vector<Vector2f> cubePos;

	RectangleShape cubePreview[4];

	Color pieceColor[7] = {
		Color::Cyan, Color::Blue, Color::White, Color::Yellow, Color::Green, Color::Magenta, Color::Red
	};



	//pieceType, rotation, cube, pos
	int pieceMap[7][4][4][2]
	{
		{
			{ {1, 0}, {1, 1}, {1, 2}, {1, 3} },
			{ {0, 1}, {1, 1}, {2, 1}, {-1, 1} },
			{ {1, 0}, {1, 1}, {1, 2}, {1, 3} },
			{ {0, 1}, {1, 1}, {2, 1}, {-1, 1} }
		},

		{
			{ {0, 2}, {1, 0}, {1, 1}, {1, 2} },
			{ {0, 0}, {0, 1}, {1, 1}, {2, 1} },
			{ {1, 0}, {1, 1}, {1, 2}, {2, 0} },
			{ {0, 1}, {1, 1}, {2, 1}, {2, 2} }
		},

		{
			{ {1, 0}, {1, 1}, {1, 2}, {2, 2} },
			{ {0, 1}, {1, 1}, {2, 1}, {0, 2} },
			{ {0, 0}, {1, 0}, {1, 1}, {1, 2} },
			{ {2, 0}, {0, 1}, {1, 1}, {2, 1} }
		},

		{
			{ {1, 0}, {2, 0}, {1, 1}, {2, 1} },
			{ {1, 0}, {2, 0}, {1, 1}, {2, 1} },
			{ {1, 0}, {2, 0}, {1, 1}, {2, 1} },
			{ {1, 0}, {2, 0}, {1, 1}, {2, 1} }
		},

		{
			 { {1, 0}, {2, 0}, {0, 1}, {1, 1} },
			 { {1, 0}, {1, 1}, {2, 1}, {2, 2} },
			 { {1, 0}, {2, 0}, {0, 1}, {1, 1} },
			 { {1, 0}, {1, 1}, {2, 1}, {2, 2} }
		},

		{
			 { {0, 0}, {1, 0}, {2, 0}, {1, 1} },
			 { {1, -1}, {0, 0}, {1, 0}, {1, 1} },
			 { {1, -1}, {0, 0}, {1, 0}, {2, 0} },
			 { {1, -1}, {1, 0}, {2, 0}, {1, 1} }
		},

		{
			 { {0, 0}, {1, 0}, {1, 1}, {2, 1} },
			 { {2, 0}, {1, 1}, {2, 1}, {1, 2} },
			 { {0, 0}, {1, 0}, {1, 1}, {2, 1} },
			 { {2, 0}, {1, 1}, {2, 1}, {1, 2} }
		}
	};


	Vector2f currentPos;

	Vector2f add;

	int nextPieceTotal = 3;
	vector<int> nextPiece = {2, 3, 6};

	RectangleShape cubeNext[12];
	Vector2f cubeNextPos[12];


	int pieceType;

	int start, end;

	int rotation = 0;

	bool rotate = false, spawnNew = true, setPos = false;

	bool gameOver = false;
	
public:

	void setWindow();

	void frames();

	void events();

	void displays();

	Template();

	void objects();
	


	void spawnPiece();


	void updatePieceSides();

	void updatePieceDown();

	void changePiecePos();

	void setPiecePos();

	void setPreviewPos();

	void setNextPiecePos();

	void rotatePiece();

	bool checkCollision(float addX, float addY);

	void checkRows();

	void logic();


};

