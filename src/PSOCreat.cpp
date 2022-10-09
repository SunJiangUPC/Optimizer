#include "pso.h"

void PSOCreat::initial()
{
	if (nDimension < 1) {
		printf("ERROR: PSO数据初始化失败,变量数不合理,值为%d.\n", nDimension);
		return;
	}
	if (nParticleNumber < 1) {
		printf("ERROR: PSO数据初始化失败,粒子数不合理,值为%d.\n", nParticleNumber);
		return;
	}
	//% 变量初始值
	v2Location.resize(nDimension); //% 粒子位置 zeros(D, N)
	v2Velocity.resize(nDimension); //% 粒子速度 zeros(D, N)
	v2PesonalBest.resize(nDimension); //% 个体最优方案 zeros(D, N)
	for (int i = 0; i < nDimension; i++) {
		v2Location[i].resize(nParticleNumber);
		v2Velocity[i].resize(nParticleNumber);
		v2PesonalBest[i].resize(nParticleNumber);
	}

	vFitness.resize(nParticleNumber);
	vPersonalBestError.resize(nParticleNumber);
	vGlobalBest.resize(nDimension);
	vMaxVelocity.resize(nDimension);
	vMinLocation.resize(nDimension);
	vMaxLocation.resize(nDimension);
	//
	bSuccessInitialize = true;
}
void PSOCreat::clear()
{
	if (!bSuccessInitialize) {
		printf("WARNING: PSO数据未初始化,无需清除.\n");
	}
	for (int i = 0; i < nDimension; i++) {
		v2Location[i].clear();
		v2Velocity[i].clear();
		v2PesonalBest[i].clear();
		v2Location[i].shrink_to_fit();
		v2Velocity[i].shrink_to_fit();
		v2PesonalBest[i].shrink_to_fit();

	}
	v2Location.clear();
	v2Velocity.clear();
	v2PesonalBest.clear();
	v2Location.shrink_to_fit();
	v2Velocity.shrink_to_fit();
	v2PesonalBest.shrink_to_fit();
	//
	vFitness.clear();
	vPersonalBestError.clear();
	vGlobalBest.clear();
	vMaxVelocity.clear();
	vMinLocation.clear();
	vMaxLocation.clear();
	vFitness.shrink_to_fit();
	vPersonalBestError.shrink_to_fit();
	vGlobalBest.shrink_to_fit();
	vMaxVelocity.shrink_to_fit();
	vMinLocation.shrink_to_fit();
	vMaxLocation.shrink_to_fit();

	bSuccessInitialize = false;
}

void PSOCreat::assign_vector(vector<double>& target, const vector<double>& source)
{
	//将source的值付给target,不足不管,多了舍弃
	int nTargetSize = target.size();
	int nSourceSize = source.size();
	if ((nTargetSize == 0) || (nSourceSize == 0)) {
		return;
	}
	for (int i = 0; i < nSourceSize; i++) {
		if (i >= nTargetSize) {
			break;
		}
		target[i] = source[i];
	}
}

void PSOCreat::assign_vector(vector<double>& target, double source)
{
	//将source的值付给target,不足不管,多了舍弃
	int nTargetSize = target.size();
	if (nTargetSize == 0) {
		return;
	}
	for (int i = 0; i < nTargetSize; i++) {
		target[i] = source;
	}
}

void PSOCreat::limit(double MaxVelocity, double MinLocation, double MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(vector<double> MaxVelocity, double MinLocation, double MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(double MaxVelocity, vector<double> MinLocation, double MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(double MaxVelocity, double MinLocation, vector<double> MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(double MaxVelocity, vector<double> MinLocation, vector<double> MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(vector<double> MaxVelocity, vector<double> MinLocation, double MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(vector<double> MaxVelocity, double MinLocation, vector<double> MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
void PSOCreat::limit(vector<double> MaxVelocity, vector<double> MinLocation, vector<double> MaxLocation)
{
	if (!bSuccessInitialize) {
		printf("ERROR: PSO未初始化.\n");
		return;
	}
	assign_vector(vMaxVelocity, MaxVelocity);
	assign_vector(vMinLocation, MinLocation);
	assign_vector(vMaxLocation, MaxLocation);
}
