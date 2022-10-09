#include "pso.h"

ParticleSwarmOptimization::ParticleSwarmOptimization()
{
}
ParticleSwarmOptimization::~ParticleSwarmOptimization()
{
}

void ParticleSwarmOptimization::initial_check(PSOCreat& PSOCreatStructData, PSOFuction& PSOFunctionHandle)
{
	// ��ʼ�������
	PSO_Data = &PSOCreatStructData;
	PSO_Fun = &PSOFunctionHandle;
	//
	// --------------------------------------------------------- //
	printf("===============================================================================================================\n");
	printf("==================================                                           ==================================\n");
	printf("==================================                PSO  ��  ��                ==================================\n");
	printf("==================================                                           ==================================\n");
	printf("===============================================================================================================\n");
	printf("--������--������--����������--��������--ѧϰ����1--ѧϰ����2--��ʼ����Ȩֵ--���չ���Ȩֵ--����Ȩֵ����������\n");
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
		printf("ERROR: PSO���ݳ�ʼ������.\n");
	}

}

void ParticleSwarmOptimization::clear()
{
	// �������
	PSO_Data = NULL;
	PSO_Fun = NULL;
}

void ParticleSwarmOptimization::optimize()
{
	// �Ż�����
	int nCount = 0;
	//printInfo(0);// ��ӡ��ͷ

	for (int nI = 0; nI < PSO_Data->nMaxIteration; nI++) {


		// ��������Ϣ
		if (nCount == 0) {
			printf("\n");
			printInfo(0);
		}
		printInfo(nI+1);
		nCount++;
		if (nCount == 20) {
			nCount = 0;
		}
		// ����ж�

	}



}

void ParticleSwarmOptimization::printInfo(int nIter)
{
	// �����nIter�ε����ļ�����Ϣ
	if (nIter == 0) {
		// �����ͷ
		printf("    ========----��������--�в�ƽ����--��С������--���������--���������(����ֵ)----========\n");
	}
	else {
		// ���ͳ����Ϣ
		printf("                %d          %.2e     %.2e      %.2e         %.2e\n", nIter,
			dResidualSquare, dMinRelativeResidual, dMaxRelativeResidual, dMaxAbsRelativeResidual);
	}
}


