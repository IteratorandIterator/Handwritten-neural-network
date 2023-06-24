#include<iostream>
#include<vector>

int main() {
	std::vector<std::vector<float>> arr;
	/*for (unsigned i = 0; i < 10; ++i) {
		static std::vector<float> Arr;
		Arr.push_back(i);
		std::cout<<Arr.size()<<"\n";
		arr.push_back(std::move(Arr));
	}
	std::cout<<arr.size()<<"\n";
	for (unsigned i = 0; i < 10; ++i) {
		std::cout<<"----------\n";
		std::cout<<arr[i][0]<<"\n";
	}*/
	/*std::vector<float> A{1,2,3,4};
	arr.push_back(std::move(A));
	std::cout<<A[0]<<"  "<<arr[0][0]<<"\n";*/
	std::cout<<0 + (-0)<<std::endl;
	return 0;
}
