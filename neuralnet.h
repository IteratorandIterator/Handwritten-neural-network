#include"utils.h"
#include<cmath>
#include<array>
#include<chrono>
#include<thread>
#include<random>
#include<fmt/core.h>

#pragma once

extern float ErrorTS;
float PracticeM = 4000;

class Net{
	private:
		float PS, PSMax, PSMin,/* ErrorTS, PracticeM*/ ErrorR;
		Utilis& UT;
		std::vector<std::vector<float>> Container;
		std::vector<std::vector<float>> Container_For_Pre;

		std::vector<INode*> IArr;
		std::vector<HNode*> HArr;
		ONode* OArr;
		std::vector<std::vector<float>> arr;
		std::vector<float> Exp;
		std::vector<float> Exp_For_Pre;
		std::vector<float> T;

	public:
		Net(Utilis& UT, float PS, float PSMax, float PSMin): 
			UT(UT), PS(PS), PSMax(PSMax), PSMin(PSMin){
				std::mt19937 rd;
    				rd.seed(std::random_device()());
				std::uniform_real_distribution<double> distribution(-1, 1);

				UT.GetDataSet(Container, Exp, "spambase.csv"); // OK-----------------
				UT.Lump(Container);
				std::cout<<"!!!!!\n";
				fmt::print("{}\n", "Read spam finished");

				float HidenNode = UT.GetHNN();
				float InputNode = UT.GetINN();
				float OutputNode = UT.GetONN();
				unsigned All = IArr.size();
				std::cout<<"step1: "<<HidenNode<<"  \n";

						for (unsigned j = 0; j < InputNode; ++j) {
						INode* IN = new INode;
						for (unsigned k = 0; k < HidenNode; ++k) {
							IN->Weight.push_back(distribution(rd));
							IArr.push_back(std::move(IN));
						}
						
					}
					
				fmt::print("{}\n", "step1");

					for (unsigned i = 0; i < HidenNode; ++i) {
						HNode* HN = new HNode;
						HN->Beta = distribution(rd);
						HN->Weight = distribution(rd);
						HArr.push_back(std::move(HN));
					}

				fmt::print("{}\n", "step2");
					ONode* ON = new ONode;
					ON->Beta = distribution(rd);	
					OArr = ON;
				fmt::print("{}\n", "step3");

			} // OK---------------------------------------

		
		float GetLSValue() {
			return std::pow((OArr->Expected - OArr->Value), 2) / 2.f;
		}

		void ReNewPS(float ER) {
			PS = PSMin + PSMax * std::pow((ER - ErrorTS) / (ER + ErrorTS), 2);
			
		}

		void ReNew() {
			unsigned HidenNode = UT.GetHNN();
			float Size = Container.size();
				float T1 = (OArr->Expected - OArr->Value) * OArr->Value * (1 - OArr->Value);
				OArr->Beta -= PS * T1 / Size;
				for (unsigned j = 0; j < HidenNode; ++j) {
					HArr[j]->Weight += PS * HArr[j]->Value * T1 / Size;
					T.push_back( T1 * HArr[j]->Value * (1 - HArr[j]->Value) * HArr[j]->Weight);
					HArr[j]->Beta -= PS * T[j] / Size;
				}

				unsigned InputNode = UT.GetINN();
				for (unsigned j = 0; j < InputNode; ++j) {
					for (unsigned k = 0; k <  HidenNode; ++k) {
						IArr[j]->Weight[k] += PS * IArr[j]->Value * T[k] / Size;
					}
				}

			T.clear();
		}

		void GetHNValue() {
				unsigned HidenNode = UT.GetHNN();
				unsigned InputNode = UT.GetINN();
				unsigned All = IArr.size();			
					for (unsigned j = 0; j < HidenNode; ++j) {
						double temp = 0;
						for (unsigned k = 0; k < InputNode; ++k) {
							temp += IArr[k]->Value * IArr[k]->Weight[j];
						}
						HArr[j]->Value = 1.f / (1.f + std::exp(-(temp - HArr[j]->Beta)));
					}

		} // OK-------------------

		void GetONValue() {
			 	unsigned HidenNode = UT.GetHNN();
				float temp = 0;
				for (unsigned j = 0; j < HidenNode; ++j) {
					temp += HArr[j]->Value * HArr[j]->Weight;
				}
				OArr->Value = 1.f / (1.f + std::exp((OArr->Beta - temp)));
		} // OK----------------------

		void Predict(std::string FileName) {
			UT.GetDataSet(Container_For_Pre, Exp_For_Pre, "spamtest.csv"); // OK-----------------
			UT.Lump(Container_For_Pre);
			UT.Write(Container_For_Pre, Exp_For_Pre);
			float Max_Loss = 0.f;
			unsigned Index = 0;
			for (const std::vector<float>& DataSet: Container_For_Pre) {
				for (unsigned i = 0; i < DataSet.size(); ++i) {
					IArr[i]->Value = DataSet[i];
				}
				OArr->Expected = Exp_For_Pre[Index++];
				GetHNValue();
				GetONValue();
				Max_Loss = GetLSValue();
				std::cout<<"Result: "<<OArr->Value<<"\n";
				std::cout<<"Max_Loss: "<<Max_Loss<<"  "<<"Expected: "<<OArr->Expected<<"\n";
			}
		}

		void Train() {
			for (unsigned i = 0; i < PracticeM; ++i) {
				float Max_Loss = 0.f;
				for (const std::vector<float>& DataSet: Container) {
					for (unsigned j = 0; j < DataSet.size(); ++j) {
						IArr[j]->Value = DataSet[j];
					}

					OArr->Expected = Exp[i];
					GetHNValue();
					GetONValue();
					Max_Loss = std::max(Max_Loss, GetLSValue());
					ReNew();
					ReNewPS(Max_Loss);
				}
					if (Max_Loss < ErrorTS) {
						std::cout<<"Max_Loss: "<<Max_Loss<<"\n";
						return;
					}
			}
		}
};



