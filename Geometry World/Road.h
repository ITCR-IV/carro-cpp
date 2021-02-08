#pragma once
struct Road {
	Direction direction = DOWN;
	int newdir = direction;
	float X_displacement = 0;
	float Y_displacement = 0;
	bool changing =	false;
	int UPdisplacements = 0;
	int DOWNdisplacements = 0;
	int RIGHTdisplacements = 0;
	int LEFTdisplacements = 0;
	int queued_displacements = 0;
	bool lluvia = false;
	bool neblina = false;
	bool diaynoche;//dia true, noche false, afecta las luces y colores del mapa
}road;

// MATRICES:
//___________________________________________________________________
char horizontal[45];
char vertical[24];
char upright[29][57];
char upleft[29][57];
char downright[29][57];
char downleft[29][57];

//cuadrícula: cuadrados 8x14px 8 las columnas y 14 las líneas
//líneas = lastY+4 = 46
//columnas = lastX+4 = 130
const int map_lines = 46;
const int map_columns = 130;

char map[map_lines][map_columns];
bool boolmap[map_lines][map_columns];

void LoadMatrices() {

	FILE *file;
	fopen_s(&file, "ASCII ART READ.txt", "r");
	if (NULL == file) {
		printf("Couldn't open the archive with the road's textures");
		return;
	}

	fgets(horizontal, 46, file);
	horizontal[44] = '\0';

	for (int line = 0; line < 23; line++) {
		char character[5];
		fgets(character, 5, file);
		vertical[line] = character[0];
	} vertical[23] = '\0';

	for (int line = 0; line < 29; line++) {
		fgets(upright[line], 58, file);
		upright[line][56] = '\0';
	}

	for (int line = 0; line < 29; line++) {
		fgets(upleft[line], 58, file);
		upleft[line][56] = '\0';
	}

	for (int line = 0; line < 29; line++) {
		fgets(downright[line], 58, file);
		downright[line][56] = '\0';
	}

	for (int line = 0; line < 29; line++) {
		fgets(downleft[line], 58, file);
		downleft[line][56] = '\0';
	}

	fclose(file);


	//initialize map
	for (int line = 0; line < map_lines; line++) {
		for (int column = 0; column < map_columns; column++) {
			map[line][column] = ' ';
		}
	}
	for (int line = 0; line < map_lines; line++) {
		int c = 0;
		for (int column = (map_columns / 2) - 22; column <= ((map_columns / 2) + 21); column++) {
			map[line][column] = horizontal[c];
			boolmap[line][column] = true;
			c++;
		}
	}
}

//up=1 down=2, right=3, left=4
void changeUp() {
	if (road.newdir == road.direction) {
		road.newdir = randomint(RIGHT, LEFT);
		road.queued_displacements = map_lines;
	}
	if (road.queued_displacements == 0) {
		if (road.newdir == 3) {
			road.direction = RIGHT;
		}
		else {
			road.direction = LEFT;
		}
		road.changing = false;
	}
	int c = 0;
	for (int column = 0; column < map_columns; column++) {
		//UP->RIGHT
		if (road.newdir == RIGHT) {
			if (column<map_columns / 2 - 21 - 1 || column>map_columns / 2 + 22 + 11) { //ni idea sobre el +11
				if (column > map_columns / 2 + 22 + 11 && road.queued_displacements - 18 + 7 >= 0 && road.queued_displacements - 18 + 7 < 23) {
					map[0][column] = vertical[road.queued_displacements - 18 + 7];
					boolmap[0][column] = true;
				}
				else {
					map[0][column] = ' ';
					boolmap[0][column] = false;
				}
			}
			else {
				if (road.queued_displacements - 11 >= 0) { //el if para que pare de pintar después de la curva
					if (road.queued_displacements - 11 >= 28) { //-18+7=-11 //este es el if para pintar la calle antes de llegar a la curva
						if (c < 44) { //este if es para que no se salga de los márgenes de la calle ya que la curva es más ancha que la calle
							map[0][column] = horizontal[c];
							boolmap[0][column] = true;
							c++;
						}
						else {
							map[0][column] = ' ';
							boolmap[0][column] = false;
						}
					}
					else {
						map[0][column] = upright[road.queued_displacements - 18 + 7][c]; //46 (cantidad de líneas en el mapa) - 18 = 28 (cantidad de líneas en matriz de curva) el + es para alinearlo después de eso
						boolmap[0][column] = true;
						c++;
					}
				}
				else {
					map[0][column] = ' ';
					boolmap[0][column] = false;
				}
			}
		}
		//UP->LEFT
		else {
			if (column<map_columns / 2 - 21 - 1|| column>map_columns / 2 + 22 + 11) { //ni idea sobre el +11
				if (column < map_columns / 2 - 21 - 1 && road.queued_displacements - 18 + 7 >= 0 && road.queued_displacements - 18 + 7 < 23) {
					map[0][column] = vertical[road.queued_displacements - 18 + 7];
					boolmap[0][column] = true;
				}
				else {
					map[0][column] = ' ';
					boolmap[0][column] = false;
				}
			}
			else {
				if (road.queued_displacements - 11 >= 0) { //el if para que pare de pintar después de la curva
					if (road.queued_displacements - 11 >= 28) { //-18+7=-11 //este es el if para pintar la calle antes de llegar a la curva
						if (c < 44) { //este if es para que no se salga de los márgenes de la calle ya que la curva es más ancha que la calle
							map[0][column] = horizontal[c];
							boolmap[0][column] = true;
							c++;
						}
						else {
							map[0][column] = ' ';
							boolmap[0][column] = false;
						}
					}
					else {
						map[0][column - 12] = upleft[road.queued_displacements - 18 + 7][c]; //46 (cantidad de líneas en el mapa) - 18 = 28 (cantidad de líneas en matriz de curva) el + es para alinearlo después de eso
						boolmap[0][column] = true;
						if (column > map_columns / 2 + 21) {
							boolmap[0][column] = false;
						}
						c++;
					}
				}
				else {
					map[0][column] = ' ';
					boolmap[0][column] = false;
				}
			}
		}
	}
	road.queued_displacements--;
}

void changeDown() {
	if (road.newdir == road.direction) {
		road.newdir = randomint(RIGHT, LEFT);
		road.queued_displacements = map_lines;
	}
	if (road.queued_displacements == 0) {
		if (road.newdir == 3) {
			road.direction = RIGHT;
		}
		else {
			road.direction = LEFT;
		}
		road.changing = false;
	}
	int c = 0;
	for (int column = 0; column < map_columns; column++) {
		//DOWN->RIGHT
		if (road.newdir == RIGHT) {
			if (column<map_columns / 2 - 21 - 1 || column>map_columns / 2 + 22 + 11) {
				if (column > map_columns / 2 + 22 + 11 && map_lines - (road.queued_displacements + 6 + 6) >= 0 && map_lines - (road.queued_displacements + 6 + 6) < 23) { //extra +6 is extra displacement to fit
					map[map_lines - 1][column] = vertical[map_lines - (road.queued_displacements + 6 + 6)];
					boolmap[map_lines - 1][column] = true;
				}
				else {
					map[map_lines - 1][column] = ' ';
					boolmap[map_lines - 1][column] = false;
				}
			}
			else {
				if (map_lines - (road.queued_displacements + 6) < 29) {
					if (map_lines - (road.queued_displacements + 6) < 0) {
						if (c < 44) { //este if es para que no se salga de los márgenes de la calle ya que la curva es más ancha que la calle
							map[map_lines - 1][column] = horizontal[c];
							boolmap[map_lines - 1][column] = true;
							c++;
						}
						else {
							map[map_lines - 1][column] = ' ';
							boolmap[map_lines - 1][column] = false;
						}
					}
					else {
						map[map_lines - 1][column] = downright[map_lines - (road.queued_displacements + 6)][c]; //+ is displacement to fit
						boolmap[map_lines - 1][column] = true;
						c++;
					}
				}
				else {
					map[map_lines - 1][column] = ' ';
					boolmap[map_lines - 1][column] = false;
				}
			}
		}
		//DOWN->LEFT
		else {
			if (column<map_columns / 2 - 21 - 1 || column>map_columns / 2 + 22 + 11) {
				if (column < map_columns / 2 - 21 - 1 && map_lines - (road.queued_displacements + 6 + 6) >= 0 && map_lines - (road.queued_displacements + 6 + 6) < 23) { //extra +6 is extra displacement to fit
					map[map_lines - 1][column] = vertical[map_lines - (road.queued_displacements + 6 + 6)];
					boolmap[map_lines - 1][column] = true;
				}
				else {
					map[map_lines - 1][column] = ' ';
					boolmap[map_lines - 1][column] = false;
				}
			}
			else {
				if (map_lines - (road.queued_displacements + 6) < 29) {
					if (map_lines - (road.queued_displacements + 6) < 0) {
						if (c < 44) { //este if es para que no se salga de los márgenes de la calle ya que la curva es más ancha que la calle
							map[map_lines - 1][column] = horizontal[c];
							boolmap[map_lines - 1][column] = true;
							c++;
						}
						else {
							map[map_lines - 1][column] = ' ';
							boolmap[map_lines - 1][column] = false;
						}
					}
					else {
						map[map_lines - 1][column - 12] = downleft[map_lines - (road.queued_displacements + 6)][c]; //+ is displacement to fit ; also - on map[][column-]
						boolmap[map_lines - 1][column - 12] = true;
						c++;
					}
				}
				else {
					map[map_lines - 1][column] = ' ';
					boolmap[map_lines - 1][column] = false;
				}
			}
		}
	}
	road.queued_displacements--;
}

void changeRight() {
	if (road.newdir == road.direction) {
		road.newdir = randomint(UP, DOWN);
		road.queued_displacements=map_columns;
	}
	if (road.queued_displacements == 0) {
		if (road.newdir == 1) {
			road.direction = UP;
		}
		else {
			road.direction = DOWN;
		}
		road.changing = false;
	}
	int l = 0;
	for (int line = 0; line < map_lines; line++) {
		//RIGHT->DOWN:
		if (road.newdir == DOWN) {
			if (line<(map_lines / 2 - 14 + 2) || line>(map_lines / 2 + 13 + 2)) {
				if (line > (map_lines / 2 + 13 + 2) && 98 - road.queued_displacements < 56 && 98 - road.queued_displacements >= 0 + 12) { //si las líneas están directamnte debajo de la curva hace un excpeción para poner calle; también la condición "road.queued_displacements - 43 >= 0" para que no siga imprimiendo vertical después de que se acaba la calle
					map[line][map_columns - 1] = horizontal[98 - road.queued_displacements - 12]; //el - es para que empiece con un valor de 0
					boolmap[line][map_columns - 1] = true;
				}
				else {
					map[line][map_columns - 1] = ' '; //pone espacios donde no hay ni pich
					boolmap[line][map_columns - 1] = false;
				}
			}
			else {
				if (98 - road.queued_displacements < 56) {  //130-32=98
					if ((130 - (road.queued_displacements + 32)) < 0) {
						map[line][map_columns - 1] = vertical[l];
						boolmap[line][map_columns - 1] = true;
						if (l > 22) {
							boolmap[line][map_columns - 1] = false;
						}
						l++;
					}
					else {
						map[line][map_columns - 1] = upleft[l][130 - (road.queued_displacements + 32)]; //el 32 lo saqué manual pero en el diagrama sería x
						boolmap[line][map_columns - 1] = true;
						l++;
					}
				}
				else {
					map[line][map_columns - 1] = ' ';
					boolmap[line][map_columns - 1] = false;
				}
			}
		}
		//RIGHT->UP:
		else {
			if (line<(map_lines / 2 - 14 + 2) || line>(map_lines / 2 + 13 + 3)) {
				if (line < (map_lines / 2 - 14 + 2) && 98 - road.queued_displacements < 56 && 98 - road.queued_displacements >= 0 + 12) { //si las líneas están directamnte debajo de la curva hace un excpeción para poner calle; también la condición "road.queued_displacements - 43 >= 0" para que no siga imprimiendo vertical después de que se acaba la calle
					map[line][map_columns - 1] = horizontal[98 - road.queued_displacements - 12]; //el - es para que empiece con un valor de 0
					boolmap[line][map_columns - 1] = true;
				}
				else {
					map[line][map_columns - 1] = ' ';
					boolmap[line][map_columns - 1] = false;
				}
			}
			else {
				if (98 - road.queued_displacements < 56) {
					if ((130 - (road.queued_displacements + 32)) < 0) {
						map[line][map_columns - 1] = vertical[l];
						l++;
					}
					else {
						map[line - 6][map_columns - 1] = downleft[l][130 - (road.queued_displacements + 32)];
						l++;
					}
					if (line<map_lines/2 +11) {
						boolmap[line][map_columns - 1] = true;
					}
					else {
						boolmap[line][map_columns - 1] = false;
					}
				}
				else {
					map[line][map_columns - 1] = ' ';
					boolmap[line][map_columns - 1] = false;
				}
			}
		}
	}
	road.queued_displacements--;
}

void changeLeft() {
	if (road.newdir == road.direction) {
		road.newdir = randomint(UP, DOWN);
		road.queued_displacements = map_columns;
	}
	if (road.queued_displacements == 0) {
		if (road.newdir == 1) {
			road.direction = UP;
		}
		else {
			road.direction = DOWN;
		}
		road.changing = false;
	}
	int l = 0;
	int x = map_columns / 2 - 34; //ver diagrama en cuaderno para entender
	for (int line = 0; line < map_lines; line++) { //itera todas las líneas de arriba hacia abajo
		//LEFT->DOWN
		if (road.newdir == DOWN) {
			if (line<(map_lines / 2 - 14 + 2) || line>(map_lines / 2 + 13 + 2)) { //revisa las líneas por encima y debajo de la curva
				if (line > (map_lines / 2 + 13 + 2) && road.queued_displacements < map_columns - (x + 12) && road.queued_displacements - 43 >= 0) { //si las líneas están directamnte debajo de la curva hace un excpeción para poner calle; también la condición "road.queued_displacements - 43 >= 0" para que no siga imprimiendo vertical después de que se acaba la calle
					map[line][0] = horizontal[-(road.queued_displacements - (map_columns - x - 12)) - 1];
					boolmap[line][0] = true;
				}
				else {
					map[line][0] = ' '; //pone espacios donde no hay ni pich
					boolmap[line][0] = false;
				}
			}
			else {
				if (road.queued_displacements - 43 >= 0) { //este if es para que pare de imprimir cuando ya hace la curva
					if (road.queued_displacements >= map_columns - x) { //imprime calle antes de llegar a curva
						map[line][0] = vertical[l];
						boolmap[line][0] = true;
						if (l > 22) {
							boolmap[line][0] = false;
						}
						l++;
					}
					else {
						map[line][0] = upright[l][road.queued_displacements - 43]; //-43 es deplazamiento pa que calce sort of
						boolmap[line][0] = true;
						l++;

					}
				}
				else {
					map[line][0] = ' ';
					boolmap[line][0] = false;
				}
			}
		}
		//LEFT->UP
		else {
			if (line<(map_lines / 2 - 14 + 2) || line>(map_lines / 2 + 13 + 3)) { //revisa las líneas por encima y debajo de la curva
				if (line < (map_lines / 2 - 14 + 2) && road.queued_displacements < map_columns - (x + 12) && road.queued_displacements - 43 >= 0) { //si las líneas están directamnte debajo de la curva hace un excpeción para poner calle; también la condición "road.queued_displacements - 43 >= 0" para que no siga imprimiendo vertical después de que se acaba la calle
					map[line][0] = horizontal[-(road.queued_displacements - (map_columns - x - 12)) - 1]; //hacerlo para cuando se va hacia arriba también!!
					boolmap[line][0] = true;
				}
				else {
					map[line][0] = ' '; //pone espacios donde no hay ni pich
					boolmap[line][0] = false;
				}
			}
			else {
				if (road.queued_displacements - 43 >= 0) { //este if es para que pare de imprimir cuando ya hace la curva
					if (road.queued_displacements >= map_columns - x) { //imprime calle antes de llegar a curva
						map[line][0] = vertical[l];
						boolmap[line][0] = true;
						if (l > 22) {
							boolmap[line][0] = false;
						}
						l++;
					}
					else {
						map[line - 6][0] = downright[l][road.queued_displacements + 14 - 57]; //14-57 = -43 ????
						boolmap[line][0] = true;
						if (line >map_lines/2 +10) {
							boolmap[line][0] = false;
						}
						l++;

					}
				}
				else {
					map[line][0] = ' ';
					boolmap[line][0] = false;
				}
			}
		}
	}
	road.queued_displacements--;
}

void rollchange() {
	if (randomint(1, 100) == 1) {
		road.changing = true;
	}
}

void moveMap(float speed, double angle) {
	//UP:
	for (int d = road.UPdisplacements; d > 0; d--) {
		for (int line = map_lines - 1; line > 0; line--) {
			for (int column = 0; column < map_columns; column++) {
				map[line][column] = map[line - 1][column];
				boolmap[line][column] = boolmap[line - 1][column];
			}
		}
		if (road.changing) {
			changeUp();
		}
		else {
			int c = 0;
			for (int column = 0; column < map_columns; column++) {
				if (column < (map_columns / 2) - 22 || column >(map_columns / 2) + 21) {
					map[0][column] = ' ';
					boolmap[0][column] = false;
				}
				else {
					map[0][column] = horizontal[c];
					boolmap[0][column] = true;
					c++;
				}
			}
			rollchange();
		}
		road.UPdisplacements--;
	}

	//DOWN:
	for (int d = road.DOWNdisplacements; d > 0; d--) {
		for (int line = 0; line < map_lines - 1; line++) {
			for (int column = 0; column < map_columns; column++) {
				map[line][column] = map[line + 1][column];
				boolmap[line][column] = boolmap[line + 1][column];
			}
		}
		if (road.changing) {
			changeDown();
		}
		else {
			int c = 0;
			for (int column = 0; column < map_columns; column++) {
				if (column < (map_columns / 2) - 22 || column >(map_columns / 2) + 21) {
					map[map_lines - 1][column] = ' ';
					boolmap[map_lines - 1][column] = false;
				}
				else {
					map[map_lines - 1][column] = horizontal[c];
					boolmap[map_lines - 1][column] = true;
					c++;
				}
			}
			rollchange();
		}
		road.DOWNdisplacements--;
	}

	//RIGHT:
	for (int d = road.RIGHTdisplacements; d > 0; d--) {
		for (int column = 0; column < map_columns - 1; column++) {
			for (int line = 0; line < map_lines; line++) {
				map[line][column] = map[line][column + 1];
				boolmap[line][column] = boolmap[line][column + 1];
			}
		}
		if (road.changing) {
			changeRight();
		}
		else {
			int l = 0;
			for (int line = 0; line < map_lines; line++) {
				if (line < (map_lines / 2) - 12 || line >(map_lines / 2) + 10) {
					map[line][map_columns - 1] = ' ';
					boolmap[line][map_columns - 1] = false;
				}
				else {
					map[line][map_columns - 1] = vertical[l];
					boolmap[line][map_columns - 1] = true;
					l++;
				}
			}
			rollchange();
		}
		road.RIGHTdisplacements--;
	}

	//LEFT:
	for (int d = road.LEFTdisplacements; d > 0; d--) {
		for (int column = map_columns - 1; column > 0; column--) {
			for (int line = 0; line < map_lines; line++) {
				map[line][column] = map[line][column - 1];
				boolmap[line][column] = boolmap[line][column - 1];
			}
		}
		if (road.changing) {
			changeLeft();
		}
		else {
			int l = 0;
			for (int line = 0; line < map_lines; line++) {
				if (line < (map_lines / 2) - 12 || line >(map_lines / 2) + 10) {
					map[line][0] = ' ';
					boolmap[line][0] = false;
				}
				else {
					map[line][0] = vertical[l];
					boolmap[line][0] = true;
					l++;
				}
			}
			rollchange();
		}
		road.LEFTdisplacements--;
	}
}

bool checkRoad(float x, float y) {
	int column = floor((x-160) / 8)+2;
	int line = floor(y / 14)+2;
	return boolmap[line][column];
}

void drawMap(ALLEGRO_FONT* ASCII) {
	char character[2] = { ' ','\0' };
	if (road.diaynoche) {
		for (int line = 0; line < map_lines; line++) {
			for (int column = 0; column < map_columns; column++) {
				character[0] = map[line][column];
				al_draw_text(ASCII, al_map_rgb(0, 0, 0), ((column - 2) * 8) + road.X_displacement + 160, ((line - 2) * 14) + road.Y_displacement, NULL, character);
			}
		}
	}
	if (!road.diaynoche) {
		for (int line = 0; line < map_lines; line++) {
			for (int column = 0; column < map_columns; column++) {
				character[0] = map[line][column];
				al_draw_text(ASCII, al_map_rgb(255, 255, 255), ((column - 2) * 8) + road.X_displacement + 160, ((line - 2) * 14) + road.Y_displacement, NULL, character);
			}
		}
	}
}

void drawboolMap(ALLEGRO_FONT* ASCII) {
	char character[2] = { ' ','\0' };
	for (int line = 0; line < map_lines; line++) {
		for (int column = 0; column < map_columns; column++) {
			if (boolmap[line][column]) {
				character[0] = 'r';
			}
			else {
				character[0] = ' ';
			}
			al_draw_text(ASCII, al_map_rgb(255, 255, 255), ((column - 2) * 8) + road.X_displacement+160, ((line - 2) * 14) + road.Y_displacement, NULL, character);
		}
	}
}
