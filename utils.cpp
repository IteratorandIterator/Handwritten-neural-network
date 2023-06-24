#include<fstream>
#include<iostream>
#include<vector>
#include"utils.h"

void Utilis::GetDataSet(std::vector<std::vector<INode>>& arr, std::vector<float>& arr2) {
	unsigned Node = InputNode + OutputNode;
	std::ifstream ifs;
	ifs.open("spambase.csv", std::ios::in);
	float temp = 0;
	unsigned Index = 0;
	while (ifs >> temp) {
		std::vector<INode> Arr;
		INode* IN = new INode;
		IN->Value = temp;
		Arr.push_back(std::move(*IN));
		for (unsigned i = 1; i < Node; ++i) {
			ifs >> temp; ifs >> temp;
			INode* IN = new INode;
			IN->Value = temp;
			Arr.push_back(std::move(*IN));
		}
		arr2[Index++] = (Arr.back()).Value;
		Arr.pop_back();
		arr.push_back(std::move(Arr));
	}
}

/*Utilis::GetHNValue(std::vector<float>& arr, float Wij, float Beta_j) {
	float temp = 0;
	for (unsigned i = 0; i < InputNode; ++i) 
		temp += Wij * arr[i];
	return Beta(temp - Beta_j);
}

Utilis::GetONValue(std::vector<float>& arr, float Wjk, float Beta_k) {
	float temp = 0;
	for (unsigned i = 0; i < InputNode; ++i) 
		temp += Wjk * arr[i];
	return Beta(temp - Beta_k);
}*/

/*Utilis::GetLSValue(std::vector<float>& arr, unsigned Index) {
	float temp = 0;
	temp += std::pow((arr[Index] - result), 2);
	return temp / 2;
}*/

/*Utilis::GetTKValue(float expected, float result) {
	return  (expected - result) * result * (1 - result);
}

Utilis::GetTJValue(std::vector<float>& arr, float resultj, float resultk, float Wjk) {
	float temp = 0;
	unsigned index = InputNode + OutputNode;
	for (unsigned i = 0; i < OutputNode; ++i) 
		temp += (arr[index] - resultk) * resultk * (1 - resultk);
	return Wjk * resultj * (1 - resultj) * temp;
}*/

unsigned Utilis::GetINN() {
	return InputNode;
}

unsigned Utilis::GetHNN() {
	return HidenNode;
}

unsigned Utilis::GetONN() {
	return OutputNode;
}

