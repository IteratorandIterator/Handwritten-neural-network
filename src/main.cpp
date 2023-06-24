#include"neuralnet.h"
#include"utils.h"
#include<string>
#include<fmt/core.h>
#include<fmt/color.h>

float ErrorTS = 0.00001;
//unsigned PracticeM = 4000;
double ErrorR = 0;

int main() {
	Utilis U(57, 1);
	fmt::print("{}\n", "U");
	Net NET(U, 0.4, 1.f, 0.1);
	fmt::print("{}\n", "NET");

	NET.Train();
	NET.Predict("spamtest.csv");

	return 0;
}




