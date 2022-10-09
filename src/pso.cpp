#include "pso.h"

ParticleSwarmOptimization::ParticleSwarmOptimization()
{
}
ParticleSwarmOptimization::~ParticleSwarmOptimization()
{
}

void ParticleSwarmOptimization::initial_check(PSOCreat& PSOCreatStructData, PSOFuction& PSOFunctionHandle)
{
	// 初始化并检查
	PSO_Data = &PSOCreatStructData;
	PSO_Fun = &PSOFunctionHandle;
	//
	// --------------------------------------------------------- //
	printf("===============================================================================================================\n");
	printf("==================================                                           ==================================\n");
	printf("==================================                PSO  参  数                ==================================\n");
	printf("==================================                                           ==================================\n");
	printf("===============================================================================================================\n");
	printf("--变量数--粒子数--最大迭代次数--迭代精度--学习因子1--学习因子2--初始惯性权值--最终惯性权值--惯性权值最大迭代次数\n");
	printf("  %d       %d       %d          %.2e     %.2f      %.2f         %.2f          %.2f           %d\n",
		PSO_Data->nDimension,
		PSO_Data->nParticleNumber,
		PSO_Data->nMaxIteration,
		PSO_Data->dTolerance,
		PSO_Data->dLearnRateFirst,
		PSO_Data->dLearnRateSecond,
		PSO_Data->dInertiaWeightIni,
		PSO_Data->dInertiaWeightEnd,
		PSO_Data->nInertiaWeightMaxIteration);
	printf("\n\n");
	//
	bool bSuccessInitial = true;
	if (PSO_Data->v2Location.size() != PSO_Data->nDimension)	{
		bSuccessInitial = false;
	}
	if (PSO_Data->v2Velocity.size() != PSO_Data->nDimension) {
		bSuccessInitial = false;
	}
	if (PSO_Data->v2PesonalBest.size() != PSO_Data->nDimension) {
		bSuccessInitial = false;
	}
	if (PSO_Data->vGlobalBest.size() != PSO_Data->nDimension) {
		bSuccessInitial = false;
	}
	if (PSO_Data->vMaxVelocity.size() != PSO_Data->nDimension) {
		bSuccessInitial = false;
	}
	if (PSO_Data->vMinLocation.size() != PSO_Data->nDimension) {
		bSuccessInitial = false;
	}
	if (PSO_Data->vMaxLocation.size() != PSO_Data->nDimension) {
		bSuccessInitial = false;
	}
	/*for (int i = 0; i < nDimension; i++) {
		v2Location[i].resize(nParticleNumber);
		v2Velocity[i].resize(nParticleNumber);
		v2PesonalBest[i].resize(nParticleNumber);
	}*/
	if (PSO_Data->vFitness.size() != PSO_Data->nParticleNumber) {
		bSuccessInitial = false;
	}
	if (PSO_Data->vPersonalBestError.size() != PSO_Data->nParticleNumber) {
		bSuccessInitial = false;
	}

	//
	if (!bSuccessInitial) {
		printf("ERROR: PSO数据初始化错误.\n");
	}

}

void ParticleSwarmOptimization::clear()
{
	// 清除数据
	PSO_Data = NULL;
	PSO_Fun = NULL;
}

void ParticleSwarmOptimization::optimize()
{
	// 优化计算
	int nCount = 0;
	//printInfo(0);// 打印标头

	for (int nI = 0; nI < PSO_Data->nMaxIteration; nI++) {


		// 输出误差信息
		if (nCount == 0) {
			printf("\n");
			printInfo(0);
		}
		printInfo(nI+1);
		nCount++;
		if (nCount == 20) {
			nCount = 0;
		}
		// 误差判断

	}



}

void ParticleSwarmOptimization::printInfo(int nIter)
{
	// 输出第nIter次迭代的计算信息
	if (nIter == 0) {
		// 输出标头
		printf("    ========----迭代次数--残差平方和--最小相对误差--最大相对误差--最大相对误差(绝对值)----========\n");
	}
	else {
		// 输出统计信息
		printf("                %d          %.2e     %.2e      %.2e         %.2e\n", nIter,
			dResidualSquare, dMinRelativeResidual, dMaxRelativeResidual, dMaxAbsRelativeResidual);
	}
}


