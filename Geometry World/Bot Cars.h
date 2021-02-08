#pragma once

struct Bot_car :car {
	Direction bot_dir;
	Direction turn_dir;
	bool active = false;
	bool turning = false;
};

//matriz que guarda los máximo 2 carritos que aparecen en un momento dado en la pantalla
Bot_car bots[2];

void initializeBot(ALLEGRO_BITMAP* bitmap) {
	for (int i = 0; i < 2; i++) {
		if (bots[i].active != true && road.changing==false) {
			Bot_car newcar;
			newcar.active = true;
			newcar.speed = 3;
			newcar.bmp = bitmap;
			int variable = randomint(0, 1);
			int variable2 = randomint(0, 1);

			switch (road.direction) {
			case UP://angle=3pi/2
				newcar.bot_dir = UP;
				newcar.turn_dir = UP;
				newcar.angle = (3*pi) / 2;
				if (variable2 == 1) {
					if (variable == 1) {
						newcar.pos_X = 570;
					}
					else {
						newcar.pos_X = 750;
					}
					newcar.pos_Y = -98;
				}
				else {
					if (variable == 1) {
						newcar.pos_X = 570;
					}
					else {
						newcar.pos_X = 750;
					}
					newcar.pos_Y = 698;
				}
				break;

			case DOWN://angle=pi/2
				newcar.bot_dir = DOWN;
				newcar.turn_dir = DOWN;
				newcar.angle = pi / 2;
				if (variable2 == 1) {
					if (variable == 1) {
						newcar.pos_X = 570;
					}
					else {
						newcar.pos_X = 750;
					}
					newcar.pos_Y = -98;
				}
				else {
					if (variable == 1) {
						newcar.pos_X = 570;
					}
					else {
						newcar.pos_X = 750;
					}
					newcar.pos_Y = 698;
				}
				break;

			case RIGHT://angle=0
				newcar.bot_dir = RIGHT;
				newcar.turn_dir = RIGHT;
				newcar.angle = 0;
				if (variable2 == 1) {
					newcar.pos_X = 162;
					if (variable == 1) {
						newcar.pos_Y = 378;
					}
					else {
						newcar.pos_Y = 216;
					}
				}
				else {
					newcar.pos_X = 1166;
					if (variable == 1) {
						newcar.pos_Y = 378;
					}
					else {
						newcar.pos_Y = 216;
					}
				}
				break;

			case LEFT://angle=pi
				newcar.bot_dir = LEFT;
				newcar.turn_dir = LEFT;
				newcar.angle = pi;
				if (variable2 == 1) {
					newcar.pos_X = 162;
					if (variable == 1) {
						newcar.pos_Y = 378;
					}
					else {
						newcar.pos_Y = 216;
					}
				}
				else {
					newcar.pos_X = 1166;
					if (variable == 1) {
						newcar.pos_Y = 378;
					}
					else {
						newcar.pos_Y = 216;
					}
				}
				break;
			}
			bots[i] = newcar;
		}
	}
}

void checkForTurns(Bot_car &bot) {
	switch (bot.bot_dir) {
	case UP:
		if (checkRoad(bot.pos_X,bot.pos_Y-150)==false && bot.pos_Y - 150 > 0) {
			bot.turning = true;
			bot.turn_dir = RIGHT;
			bot.angledir = 1;
			for (int l = 0; l < map_lines; l++) {
				if (boolmap[l][0]) {
					bot.turn_dir = LEFT;
					bot.angledir = -1;
				}
			}
		}
		break;
	case DOWN:
		if (checkRoad(bot.pos_X, bot.pos_Y + 150)==false && bot.pos_Y+150<600) {
			bot.turning = true;
			bot.turn_dir = RIGHT;
			bot.angledir = -1;
			for (int l = 0; l < map_lines; l++) {
				if (boolmap[l][0]) {
					bot.turn_dir = LEFT;
					bot.angledir = 1;
				}
			}
		}
		break;
	case RIGHT:
		if (checkRoad(bot.pos_X+150, bot.pos_Y)==false && bot.pos_X + 150 < 1068) {
			bot.turning = true;
			bot.turn_dir = DOWN;
			bot.angledir = 1;
			for (int c = 0; c < map_columns; c++) {
				if (boolmap[0][c]) {
					bot.turn_dir = UP;
					bot.angledir = -1;
				}
			}
		}
		break;
	case LEFT:
		if (checkRoad(bot.pos_X-150, bot.pos_Y)==false && bot.pos_X - 150 > 260) {
			bot.turning = true;
			bot.turn_dir = DOWN;
			bot.angledir = -1;
			for (int c = 0; c < map_columns; c++) {
				if (boolmap[0][c]) {
					bot.turn_dir = UP;
					bot.angledir = 1;
				}
			}
		}
		break;
	}
}

void stopTurning(Bot_car &bot) {
	if (bot.angle >= 2 * pi) {
		bot.angle = remainder(bot.angle, 2 * pi);
	}
	if (bot.angle < 0) {
		bot.angle = bot.angle + 2 * pi;
	}
	switch (bot.turn_dir) {
	case UP:
		if (bot.angledir == 1) {
			if (bot.angle >= (3 * pi) / 2) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		else {
			if (bot.angle <= (3 * pi) / 2) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		break;
	case DOWN:
		if (bot.angledir == 1) {
			if (bot.angle >= pi / 2) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		else {
			if (bot.angle <= pi / 2) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		break;
	case RIGHT:
		if (bot.angledir == 1) {
			if (bot.angle >= 0 && bot.angle < pi) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		else {
			if (bot.angle < 2*pi && bot.angle > pi) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		break;
	case LEFT:
		if (bot.angledir == 1) {
			if (bot.angle >= pi) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		else {
			if (bot.angle <= pi) {
				bot.angledir = 0;
				bot.turning = false;
				bot.bot_dir = bot.turn_dir;
			}
		}
		break;
	}
}

void moveBots() {

	for (int i = 0; i < 2; i++) {
		if (bots[i].active) {
			bots[i].pos_X += cos(bots[i].angle)*bots[i].speed;
			bots[i].pos_Y += sin(bots[i].angle)*bots[i].speed;

			bots[i].pos_Y+= 14*road.UPdisplacements;
			bots[i].pos_Y-= 14*road.DOWNdisplacements;
			bots[i].pos_X+= 8*road.LEFTdisplacements;
			bots[i].pos_X-= 8*road.RIGHTdisplacements;
			if (bots[i].turning == false) {
				checkForTurns(bots[i]);
			}
			else {
				stopTurning(bots[i]);
			}

			//updetea ángulo del carro
			//***************************************************************
			if (bots[i].speed >= 2.5 || bots[i].speed <= -2.5) {
				bots[i].angle += degrees(bots[i].angledir*(0.0035*pow(fabs(bots[i].speed) - 30, 2)));
			}
			else {
				bots[i].angle += degrees(bots[i].angledir*(-0.4235*pow(fabs(bots[i].speed) - 2.5, 2) + 2.6468));
			}
			//***************************************************************
		}
	}
}

void drawBots() {
	for (int i = 0; i < 2; i++) {
		if (bots[i].active) {
			al_draw_rotated_bitmap(bots[i].bmp, 26, 23, bots[i].pos_X + road.X_displacement, bots[i].pos_Y + road.Y_displacement, bots[i].angle - pi / 2, 0);
		}
	}
}

void inactivateBots() {
	for (int i = 0; i < 2; i++) {
		if (bots[i].active) {
			if (bots[i].pos_X > 1100 || bots[i].pos_X<162) {
				bots[i].active = false;
			}if (bots[i].pos_Y<-98 || bots[i].pos_Y>698) {
				bots[i].active = false;
			}
		}
	}
}
