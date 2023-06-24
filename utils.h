#include<fstream>
#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<sstream>
#include<fmt/core.h>

#pragma once
#define random(a, b) (rand() % (int)(b-a))+ a + 1
#define Beta(x) (1 / (1 + std::exp(-x)))

struct INode{
	public:
		float Value;
	       	std::vector<float> Weight;
};

struct HNode{
	public:
		float Value, Beta, Weight;
};

struct ONode{
	public:
		float Value, Beta, Expected;
};

class Utilis{
	private:
		unsigned InputNode, HidenNode, OutputNode;
	public:
		Utilis(unsigned InputNode, unsigned OutputNode)
			 :InputNode(InputNode), OutputNode(OutputNode){
				HidenNode = 15;
				fmt::print("{}\n",HidenNode);
		}

		void GetDataSet(std::vector<std::vector<float>>& arr, std::vector<float>& arr2, std::string FileName) {
			fmt::print("{}\n","Read spam begin");
			std::ifstream ifs;
			ifs.open(FileName, std::ios::in);
			float temp = 0;
			std::string LStr;
			while (std::getline(ifs, LStr)) {
					std::vector<float> Arr;
					std::stringstream SS{LStr};
					LStr.clear();
					while (getline(SS, LStr, ',')) {
							Arr.push_back(std::stof(LStr));
					}
					temp = Arr.back();
					arr2.push_back(temp);
					Arr.pop_back();
					arr.push_back(std::move(Arr));
			}
		}

		void Lump(std::vector<std::vector<float>>& arr) {
			std::vector<float> A;
			for (unsigned i = 0; i < arr.size(); ++i) {
				float T = 0;
				for (unsigned j = 0; j < InputNode; ++j)
					T = std::max(T, arr[i][j]);
				A.push_back(T);
			}

			for (unsigned i = 0; i < arr.size(); ++i) {
				for (unsigned j = 0; j < InputNode; ++j)
					arr[i][j] /= A[i];
			}
		}

		void Write(std::vector<std::vector<float>>& arr, std::vector<float> arr2) {
			std::ofstream ofs;
			ofs.open("train.txt", std::ios::out);
			for (unsigned i = 0; i < arr.size(); ++i) {
				for (unsigned j = 0; j < arr[i].size(); ++j) {
					ofs << arr[i][j]<<" ";
				}
				ofs << arr2[i]<<"\n";
			}
		}

		
		unsigned GetINN() {
			return InputNode;
		}
		unsigned GetHNN() {
			return HidenNode;
		}
		unsigned GetONN() {
			return OutputNode;
		}
};


