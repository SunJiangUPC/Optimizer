// 测试pso算法

#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <iostream>

#include "../src/pso.h"

using namespace std;

int main()
{
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
	

	system("pause");
	return 0;
}

