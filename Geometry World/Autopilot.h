#pragma once
//PILOTO AUTOMÁTICO
//____________________________________________________________________________________________________


bool autopilotconditions(user_car ucar) {
	bool condition1 = false;
	bool condition2 = false;
	if (ucar.angle >= 2 * pi) {
		ucar.angle = remainder(ucar.angle, 2 * pi);
	}
	if (ucar.angle < 0) {
		ucar.angle = ucar.angle + 2 * pi;
	}
	switch (road.direction) {
	case UP://angle=3pi/2
		if (ucar.angle > pi) {
			condition1 = true;
		}
		break;

	case DOWN://angle=pi/2
		if (ucar.angle < pi) {
			condition1 = true;
		}
		break;

	case RIGHT://angle=0
		if (ucar.angle > (3 * pi) / 2 || ucar.angle < pi / 2) {
			condition1 = true;
		}
		break;

	case LEFT://angle=pi
		if (ucar.angle < (3 * pi) / 2 || ucar.angle > pi / 2) {
			condition1 = true;
		}
		break;
	}
	if (checkRoad(ucar.pos_X, u_car.pos_Y)) {
		condition2 = true;
	}
	if (condition1 && condition2) {
		return true;
	}
	return false;
}

//esta función asume que el carro está medio direccionado en la dirección correcta
void lookaround(Bot_car bots[2]) {
	if (u_car.angle >= 2 * pi) {
		u_car.angle = remainder(u_car.angle, 2 * pi);
	}
	if (u_car.angle < 0) {
		u_car.angle = u_car.angle + 2 * pi;
	}

	//staying in the middle and turning

	switch (road.direction) {
	case UP://angle=3pi/2
		if (checkRoad(u_car.pos_X, u_car.pos_Y)) {
			if (u_car.angle > ((3 * pi) / 2) + 0.01) {
				u_car.turn = LEFT;
			}
			else if (u_car.angle < ((3 * pi) / 2) - 0.01) {
				u_car.turn = RIGHT;
			}
			else {
				u_car.turn = STOP;
			}
			break;
		}
		else {
			for (int distance = 1; distance <= 1001; distance += 10) {
				//revisa calle a la derecha
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle + (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle + (pi / 2)))) { //revisa a la derecha
					if (u_car.angle >= (7 * pi) / 4) {
						u_car.turn = STOP;

					}
					else {
						u_car.turn = RIGHT;
					}
					break;
				}
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle - (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle - (pi / 2)))) { //revisa a la izquierda
					if (u_car.angle <= (5 * pi) / 4) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = LEFT;
					}
					break;
				}
			}
		}
	case DOWN://angle=pi/2
		if (checkRoad(u_car.pos_X, u_car.pos_Y)) {
			if (u_car.angle > (pi / 2) + 0.01) {
				u_car.turn = LEFT;
			}
			else if (u_car.angle < (pi / 2) - 0.01) {
				u_car.turn = RIGHT;
			}
			else {
				u_car.turn = STOP;
			}
			break;
		}
		else {
			for (int distance = 1; distance <= 1001; distance += 10) {
				//revisa calle a la derecha
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle + (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle + (pi / 2)))) { //revisa a la derecha
					if (u_car.angle >= (3 * pi) / 4) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = RIGHT;
					}
					break;
				}
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle - (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle - (pi / 2)))) { //revisa a la izquierda
					if (u_car.angle <= (1 * pi) / 4) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = LEFT;
					}
					break;
				}
			}
		}
	case RIGHT://angle=0
		if (checkRoad(u_car.pos_X, u_car.pos_Y)) {
			if (u_car.angle > 0.01 && u_car.angle <= pi) {
				u_car.turn = LEFT;
			}
			else if (u_car.angle<(2 * pi) - 0.01 && u_car.angle>pi) {
				u_car.turn = RIGHT;
			}
			else {
				u_car.turn = STOP;
			}
			break;
		}
		else {
			for (int distance = 1; distance <= 1001; distance += 10) {
				//revisa calle a la derecha
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle + (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle + (pi / 2)))) { //revisa a la derecha
					if ((u_car.angle >= (1 * pi) / 4) && (u_car.angle < pi)) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = RIGHT;
					}
					break;
				}
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle - (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle - (pi / 2)))) { //revisa a la izquierda
					if ((u_car.angle <= (7 * pi) / 4) && (u_car.angle >= pi)) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = LEFT;
					}
					break;
				}
			}
		}
	case LEFT://angle=pi
		if (checkRoad(u_car.pos_X, u_car.pos_Y)) {
			if (u_car.angle > pi + 0.01) {
				u_car.turn = LEFT;
			}
			else if (u_car.angle < pi - 0.01) {
				u_car.turn = RIGHT;
			}
			else {
				u_car.turn = STOP;
			}
			break;
		}
		else {
			for (int distance = 1; distance <= 1001; distance += 10) {
				//revisa calle a la derecha
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle + (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle + (pi / 2)))) { //revisa a la derecha
					if (u_car.angle >= (5 * pi) / 4) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = RIGHT;
					}
					break;
				}
				if (checkRoad(u_car.pos_X + distance * cos(u_car.angle - (pi / 2)), u_car.pos_Y + distance * sin(u_car.angle - (pi / 2)))) { //revisa a la izquierda
					if (u_car.angle <= (3 * pi) / 4) {
						u_car.turn = STOP;
					}
					else {
						u_car.turn = LEFT;
					}
					break;
				}
			}
		}
	}




	//looking for bots
	for (int distance = 10; distance <= 50; distance += 10) {
		for (int i = 0; i < 2; i++) {
			if (bots[i].active) {
				//cout << "u_car.pos_X + cos(a)distance: " << u_car.pos_X + cos(u_car.angle)*distance << "\nbots[i].pos_X + 100: " << bots[i].pos_X + 100 << endl;
				if (u_car.pos_X + cos(u_car.angle)*distance <= bots[i].pos_X + 100) {
					if (u_car.pos_X + cos(u_car.angle)*distance >= bots[i].pos_X - 100) {
						if (u_car.pos_Y + sin(u_car.angle)*distance >= bots[i].pos_Y - 100 && u_car.pos_Y - sin(u_car.angle)*distance <= bots[i].pos_Y + 100) {
							u_car.stop = true;
						}
					}
				}
			}
		}
	}
}


void automove(user_car ucar) {
	if (ucar.speed < ucar.maxspeed && ucar.stop == false) {
		accelerate(u_car, FORWARD, u_car.friccion);
	}
	else if (ucar.stop) {
		accelerate(u_car, STOP, u_car.friccion);
	}
	else {
		accelerate(u_car, 0, u_car.friccion);
	}
	if (ucar.turn == STOP) {
		rotate(u_car, 0);
	}
	else if (u_car.turn == RIGHT) {
		rotate(u_car, RIGHT);
	}
	else if (u_car.turn == LEFT) {
		rotate(u_car, LEFT);
	}
}
