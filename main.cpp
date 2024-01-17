#include "main.hpp"


void Template::setWindow() {
	window.create(VideoMode(width, height), "Template", Style::None);
	window.setFramerateLimit(60);
}

void Template::frames() {

	frame++;

	if (frame == 100000) frame = 0;
}

Template::Template() {

	setWindow();
	objects();


	while (window.isOpen())
	{
		events();

		logic();

		displays();

		frames();
	}
}


void Template::events() {
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed) window.close();


		else if (event.type == Event::KeyPressed) {

			if (event.key.code == Keyboard::Escape) {
				window.close();
			}

			else if (event.key.code == Keyboard::A) {
				add.x = -cubeSize;
			}

			else if (event.key.code == Keyboard::D) {
				add.x = cubeSize;
			}

			else if (event.key.code == Keyboard::W) {
				rotate = true;
			}

			else if (event.key.code == Keyboard::S) {
				frame = 0;
			}

			else if (event.key.code == Keyboard::Space) {
				if (gameOver) gameOver = false;
				else gameOver = true;
			}
		}
	}
}

void Template::displays() {

	window.clear(Color::Black);



	window.draw(border);


	for (int i = 0; i < 4; i++) {
		window.draw(cubePreview[i]);
	}

	for (int i = 0; i < cube.size(); i++) {
		window.draw(cube[i]);
	}

	for (int i = 0; i < nextPieceTotal; i++) {
		window.draw(borderNext[i]);
	}

	for (int i = 0; i < nextPieceTotal * 4; i++) {
		window.draw(cubeNext[i]);
	}

	window.draw(scoreTextString);

	window.draw(scoreText);

	if (gameOver) window.draw(gameOverText);



	window.display();
}


void Template::objects() {

	//BORDER
	Color borderColor;

	borderColor.r = 207;
	borderColor.g = 47;
	borderColor.b = 116;

	border.setSize(Vector2f((cubeMaxX + 2) * cubeSize, (cubeMaxY + 2) * cubeSize));
	border.setPosition(Vector2f(0, 0));
	border.setOutlineColor(borderColor);
	border.setOutlineThickness(-cubeSize);
	border.setFillColor(Color::Black);

	//CUBE PREVIEW
	for (int i = 0; i < 4; i++) {

		cubePreview[i].setOutlineThickness(-1);
		cubePreview[i].setOutlineColor(Color::White);
		cubePreview[i].setFillColor(Color::Black);
		cubePreview[i].setSize(Vector2f(cubeSize, cubeSize));
	}

	//CUBE NEXT
	for (int i = 0; i < nextPieceTotal; i++) {
		for (int j = 0; j < 4; j++) {
			cubeNext[i * 4 + j].setSize(Vector2f(cubeSize, cubeSize));
			cubeNext[i * 4 + j].setOutlineThickness(-1);
			cubeNext[i * 4 + j].setOutlineColor(Color::Black);
		}
	}

	//BORDER AROUND CUBE NEXT
	for (int i = 0; i < nextPieceTotal; i++) {
		borderNext[i].setSize(Vector2f(cubeSize * 3, cubeSize * 4));
		borderNext[i].setFillColor(Color::Black);
		borderNext[i].setOutlineThickness(cubeSize * 0.025);
		borderNext[i].setOutlineColor(Color::Cyan);
		borderNext[i].setPosition(Vector2f(cubeSize * (cubeMaxX + 3), cubeSize * (cubeMaxY - 13 + i * 5)));
	}


	//SCORE TEXT
	if (!font.loadFromFile("resources\\fonts\\font-style.ttf")) {
		cout << "\n\t Font not found\n";
		return;
	}

	scoreTextString.setFont(font);
	scoreTextString.setPosition(Vector2f((cubeMaxX + 2.5) * cubeSize, cubeSize * 2));
	scoreTextString.setFillColor(Color::White);
	scoreTextString.setString("Score:");

	scoreText.setFont(font);
	scoreText.setPosition(Vector2f((cubeMaxX + 5) * cubeSize, cubeSize * 2));
	scoreText.setFillColor(Color::White);
	scoreText.setString(to_string(score));


	//GAME OVER TEXT
	gameOverText.setFont(font);
	gameOverText.setPosition(Vector2f((cubeMaxX / 2 - 1) * cubeSize, cubeMaxY * 0.25 * cubeSize));
	gameOverText.setFillColor(Color::White);
	gameOverText.setString("GAME OVER!");


	//OTHERS
	add.x = 0;
	add.y = cubeSize;
}







void Template::spawnPiece() {

	int temp;
	bool findNewPieceType = true;

	pieceType = nextPiece[nextPieceTotal - 1];

	while (findNewPieceType) {

		findNewPieceType = false;
		temp = rand() % 7;

		for (int i = 0; i < nextPieceTotal; i++) {
			if (temp == nextPiece[i]) findNewPieceType = true;
		}
	}

	nextPiece.pop_back();

	nextPiece.insert(nextPiece.begin(), temp);

	setNextPiecePos();




	rotation = 0;

	currentPos.x = cubeMaxX / 2 * cubeSize;
	currentPos.y = 2 * cubeSize;


	start = cube.size();
	end = start + 4;

	int j = 0;
	for (int i = start; i < end; i++) {

		cube.push_back(RectangleShape());
		cubePos.push_back(Vector2f());

		cube[i].setOutlineThickness(-1);
		cube[i].setOutlineColor(Color::Black);
		cube[i].setFillColor(pieceColor[pieceType]);
		cube[i].setSize(Vector2f(cubeSize, cubeSize));

		j++;
	}

	changePiecePos();

	if (checkCollision(0, 0)) {
		gameOver = true; cout << "\n Game Over";
	}

	setPos = true;
}

void Template::changePiecePos() {
	int j = 0;
	for (int i = start; i < end; i++) {

		cubePos[i].x = currentPos.x + cubeSize * pieceMap[pieceType][rotation][j][0];
		cubePos[i].y = currentPos.y + cubeSize * pieceMap[pieceType][rotation][j][1];

		j++;
	}
}

void Template::setPiecePos() {
	setPos = false;

	for (int i = start; i < end; i++) {
		cube[i].setPosition(cubePos[i]);
	}

	setPreviewPos();
}

void Template::setPreviewPos() {

	int n = 1;

	while (!checkCollision(0, n * cubeSize)) {
		n++;
	}

	n--;

	int j = 0;
	for (int i = start; i < end; i++) {
		cubePreview[j].setPosition(Vector2f(cubePos[i].x, cubePos[i].y + n * cubeSize));
		j++;
	}
}

void Template::setNextPiecePos() {

	Vector2f temp;

	for (int i = 0; i < nextPieceTotal; i++) {
		for (int j = 0; j < 4; j++) {

			cubeNext[i * 4 + j].setFillColor(pieceColor[nextPiece[i]]);

			temp.x = cubeSize * (cubeMaxX + 3 + pieceMap[nextPiece[i]][0][j][0]);
			temp.y = cubeSize * (cubeMaxY - 13 + i * 5 + pieceMap[nextPiece[i]][0][j][1]);

			cubeNext[i * 4 + j].setPosition(temp);
		}
	}
}

void Template::rotatePiece() {
	rotate = false;

	rotation++;
	if (rotation == 4) rotation = 0;

	changePiecePos();

	if (checkCollision(add.x, 0)) {
		rotation--;
		if (rotation == -1) rotation = 3;
		changePiecePos();
	}

	setPos = true;
}

void Template::updatePieceSides() {

	if (checkCollision(add.x, 0)) add.x = 0;

	for (int i = start; i < end; i++) {

		cubePos[i].x += add.x;
	}

	currentPos.x += add.x;

	add.x = 0;

	setPos = true;
}

void Template::updatePieceDown() {

	if (checkCollision(0, add.y)) {
		spawnNew = true;
		add.y = 0;
	}

	for (int i = start; i < end; i++) {

		cubePos[i].y += add.y;
	}

	currentPos.y += add.y;

	add.y = cubeSize;

	setPos = true;
}


bool Template::checkCollision(float addX, float addY) {

	for (int i = start; i < end; i++) {

		if (cubePos[i].x + addX == 0 || cubePos[i].x + addX == cubeSize * (cubeMaxX + 1)) return true;

		if (cubePos[i].y + addY == cubeSize * (cubeMaxY + 1)) return true;

		for (int j = 0; j < start; j++) {
			if (cubePos[i].x + addX == cubePos[j].x && cubePos[i].y + addY == cubePos[j].y) return true;
		}
	}

	return false;
}


void Template::checkRows() {

	int pieceRowCount[cubeMaxY] = {};
	int pieceRowPos[cubeMaxY][cubeMaxX] = {};

	int temp;

	//RECORD POSITIONS
	for (int i = 0; i < end; i++) {

		temp = cubePos[i].y / cubeSize - 1;
		pieceRowPos[temp][pieceRowCount[temp]] = i;
		pieceRowCount[temp]++;
	}

	//FIND TO BE REMOVED ROWS
	vector<int> toBeRemoved;

	for (int i = 0; i < cubeMaxY; i++) {
		if (pieceRowCount[i] == cubeMaxX) {
			toBeRemoved.push_back(i);
		}
	}

	if (toBeRemoved.size() > 0) {

		//MOVE PIECES DOWN
		int addY;
		for (int i = cubeMaxY - 2; i >= 0; i--) {
			addY = 0;
			for (int j = 0; j < toBeRemoved.size(); j++) {
				if (i < toBeRemoved[j]) addY++;
				else if (i == toBeRemoved[j]) { addY = 0; break; }
			}

			if (addY != 0) {
				for (int j = 0; j < pieceRowCount[i]; j++) {
					temp = pieceRowPos[i][j];
					cubePos[temp].y += addY * cubeSize;
					cube[temp].setPosition(cubePos[temp]);
				}
			}
		}

		//REMOVE PIECES (HAVE TO REORDER SINCE VECTOR POSITIONS SHIFT DOWN AS DELETED)
		vector<int> removePieces;
		//--RECORD PIECES
		for (int i = 0; i < toBeRemoved.size(); i++) {
			for (int j = 0; j < 10; j++) {
				removePieces.push_back(pieceRowPos[toBeRemoved[i]][j]);
			}
		}

		//--REORDER PIECES FROM MAX TO MIN
		for (int i = 0; i < removePieces.size(); i++) {
			for (int j = i + 1; j < removePieces.size(); j++) {
				if (removePieces[i] < removePieces[j]) {

					temp = removePieces[i];
					removePieces[i] = removePieces[j];
					removePieces[j] = temp;
				}
			}
		}

		//--REMOVE PIECES
		for (int i = 0; i < toBeRemoved.size() * cubeMaxX; i++) {
			cube.erase(cube.begin() + removePieces[i]);
			cubePos.erase(cubePos.begin() + removePieces[i]);
		}

		//ADD SCORE
		score += 10 * 10 * toBeRemoved.size();
		scoreText.setString(to_string(score));
	}
}


void Template::logic() {

	if (spawnNew) {
		spawnNew = false;

		checkRows();

		spawnPiece();
	}

	if (!gameOver) {

		if (frame % 5 == 0) {

			if (add.x != 0) updatePieceSides();

			if (rotate) rotatePiece();

		}

		if (frame % 60 == 0) {

			updatePieceDown();
		}
	}

	if (setPos) setPiecePos();
}



int main()
{

	Template obj;

	return 0;
}