#pragma once

std::random_device seed; //genera el seed
std::default_random_engine randeng(seed()); //se crea el engine que genera los valores aleatorios

int randomint(int min, int max) { //funci�n que retorna un valor de n�mero entero con distribuci�n uniforme entre los valores de m�nimo y m�ximo dados
	std::uniform_int_distribution<int> distribution(min, max); //se define la distribuci�n
	int randint = distribution(randeng); //se le asigna a randint el valor generado por la distribuci�n con randeng de engine
	return randint;
}