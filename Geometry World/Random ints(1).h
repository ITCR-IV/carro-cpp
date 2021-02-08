#pragma once

std::random_device seed; //genera el seed
std::default_random_engine randeng(seed()); //se crea el engine que genera los valores aleatorios

int randomint(int min, int max) { //función que retorna un valor de número entero con distribución uniforme entre los valores de mínimo y máximo dados
	std::uniform_int_distribution<int> distribution(min, max); //se define la distribución
	int randint = distribution(randeng); //se le asigna a randint el valor generado por la distribución con randeng de engine
	return randint;
}