// 测试pso算法

#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <iostream>

#include "../src/pso.h"

using namespace std;

int main()
{
	vector<int> a = { 1,2,3,4,5,6,7,8,8,9,9,9,90,1,2,4,4 };
	printf("Begin: size = %zd\n", a.size());
	printf("Begin: capacity = %zd\n", a.capacity());
	a.clear();
	printf("Clear: size = %zd\n", a.size());
	printf("Clear: capacity = %zd\n", a.capacity());
	a.shrink_to_fit();
	printf("Clear2: size = %zd\n", a.size());
	printf("Clear2: capacity = %zd\n", a.capacity());
	a.~vector();
	printf("Deconstruct: size = %zd\n", a.size());
	printf("Deconstruct: capacity = %zd\n", a.capacity());

	// PSO 数据
	vector<double> MaxVelLimit = { 0.2,0.2,0.2,0.2 };
	vector<double> MinLocLimit = { -4,-2,-2,-3 };
	vector<double> MaxLocLimit = { 4,2,2,3.0 };
	ParticleSwarmOptimizationCreat PSOData;
	PSOData.nDimension = 4;
	PSOData.nParticleNumber = 20;
	PSOData.nMaxIteration = 100;
	PSOData.dTolerance = 1.0e-2;
	PSOData.initial();
	PSOData.limit(MaxVelLimit, MinLocLimit, MaxLocLimit);

	// PSO 优化函数
	ParticleSwarmOptimizationFuction PSOFunctionSet;
	PSOFunctionSet.initial(4, 1, 4);
	string filename = "./example/test_pso_1_data.dat";
	PSOFunctionSet.readdata(filename);

	// PSO 优化
	ParticleSwarmOptimization PSO;
	PSO.initial_check(PSOData, PSOFunctionSet);

	PSO.optimize();

	//
	PSOData.clear();
	PSOFunctionSet.clear();
	PSO.clear();

	//
	string str = "23  56.3  4.0 1.2e-4";
	vector<double> vec(4, 0);
	string2vector(str, vec);


	std::random_device rd;
	std::mt19937 gen(rd());
	for (int n = 0; n < 10; ++n) {
		std::cout << std::generate_canonical<double, 10>(gen) << ' ';
	}

	system("pause");
	return 0;
}

