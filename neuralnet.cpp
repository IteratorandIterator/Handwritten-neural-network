#include"neuralnet.h"
#include"utils.h"

extern float ErrorTS;

float Net::GetERValue() {
	float temp = 0;
	for (unsigned i = 0; i < IArr.size(); ++i) 
		temp += std::pow((OArr[i].Expected - OArr[i].Value), 2) / 2;
	return temp / arr.size();
}

void Net::RNewPS(float ER) {
	PS = PSMin + PSMax * std::pow((ER - ErrorTS) / (ER + ErrorTS), 2);
}

void Net::ReNew() {
	unsigned HidenNode = UT.GetHNN();
	for (unsigned i = 0; i < IArr.size(); ++i) {
		R.push_back((OArr[i].Expected - OArr[i].Value) * OArr[i].Value * (1 - OArr[i].Value));
		OArr[i].Beta += -PS * R[i];
		for (unsigned j = 0; j < HidenNode; ++j) {
			HArr[i][j].Weight += PS * HArr[i][j].Value * R[i];
			T[j] = R[i] * HArr[i][j].Value * (1 - HArr[i][j].Value) * HArr[i][j].Weight;
			HArr[i][j].Beta += -PS * T[j];
			}

		unsigned InputNode = UT.GetINN();
		for (unsigned j = 0; j < InputNode; ++j) {
			for (unsigned k = 0; k <  HidenNode; ++k) {
				IArr[i][j].Weight[k] += PS * IArr[i][j].Value * T[j];
			}
		}

	}
	R.clear(); T.clear();
}

void Net::GetHNValue() {
	for (unsigned i = 0; i < IArr.size(); ++i) {
		static unsigned HidenNode = UT.GetHNN();
		static unsigned InputNode = UT.GetINN();
		for (unsigned j = 0; j < HidenNode; ++j) {
			float temp = 0;
			for (unsigned k = 0; k < InputNode; ++k)
				temp += IArr[j][k].Value * IArr[j][k].Weight[j];
			HArr[i][j].Value = Beta(temp);
		}
	}
}

void Net::GetONValue() {
	for (unsigned i = 0; i < IArr.size(); ++i) {
		float temp = 0;
		unsigned HidenNode = UT.GetHNN();
		for (unsigned j = 0; j < HidenNode; ++j)
			temp += HArr[i][j].Value * HArr[i][j].Weight;
		OArr[i].Value = Beta(temp);
	}
}
	
