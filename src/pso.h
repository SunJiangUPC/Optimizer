#ifndef PSO_H
#define PSO_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

typedef class ParticleSwarmOptimizationCreat
{
public:
	//% 基础设置: 不为0表示有默认值
	int    nDimension                 = 0;      //% 变量数，求解维度
	int    nParticleNumber            = 0;      //% 粒子数
	double dLearnRateFirst            = 2.5;    //% 学习因子1: 2.5
	double dLearnRateSecond           = 2.5;    //% 学习因子2: 2.5
	double dWeightIteration           = 0.0;    //% 惯性权值
	int    nInertiaWeightMaxIteration = 40;     //% 最大次数: 40
	double dInertiaWeightIni          = 0.9;    //% 初始惯性权值: 0.9
	double dInertiaWeightEnd          = 0.2;    //% 最终惯性权值: 0.2
	int    nMaxIteration              = 100;   //% 允许的最大迭代次数: 1000
	double dTolerance                 = 1.0e-6; //% 设置精度: 1.0e-6
	//% 变量初始值
	vector<vector<double>> v2Location; //% 粒子位置 zeros(D, N)
	vector<vector<double>> v2Velocity; //% 粒子速度 zeros(D, N)
	vector<double>         vFitness; //% 每个粒子的适应度 zeros(1, N)
	vector<vector<double>> v2PesonalBest ; //% 个体最优方案 zeros(D, N)
	vector<double>         vGlobalBest; //% 整体最优方案 zeros(D, 1)
	vector<double>         vPersonalBestError; //% 个体最优适应度 zeros(1, N)
	double                 dGlobalBestError = 0; //% 整体最优适应度
	//% 范围圈定
	vector<double> vMaxVelocity; //% 参数最大变化速度
	vector<double> vMinLocation; //% 参数最小值
	vector<double> vMaxLocation; //% 参数最大值

	void initial();
	void clear();
	void limit(double MaxVelocity, double MinLocation, double MaxLocation);// 限制最大速度为位置范围
	void limit(vector<double> MaxVelocity, double MinLocation, double MaxLocation);
	void limit(double MaxVelocity, vector<double> MinLocation, double MaxLocation);
	void limit(double MaxVelocity, double MinLocation, vector<double> MaxLocation);
	void limit(double MaxVelocity, vector<double> MinLocation, vector<double> MaxLocation);
	void limit(vector<double> MaxVelocity, vector<double> MinLocation, double MaxLocation);
	void limit(vector<double> MaxVelocity, double MinLocation, vector<double> MaxLocation);
	void limit(vector<double> MaxVelocity, vector<double> MinLocation, vector<double> MaxLocation);
private:
	bool bSuccessInitialize = false;
	void assign_vector(vector<double>& target, const vector<double>& source);//将source的值付给target,不足不管,多了舍弃
	void assign_vector(vector<double>& target, double source);//将source的值付给target
}PSOCreat;


typedef class ParticleSwarmOptimizationFuction
{
public:
	int nVariable = 0;//变量个数
	int nResult = 0;//函数值个数
	int nCoefficient = 0;//系数个数
	vector<double> vVariable;//变量值
	vector<double> vResult;//函数值
	vector<double> vCoefficient;//系数值
	void target_function();//函数关系式
	void initial(int nVar,int nVal, int nCoef);
	void clear();
	// 真实数据
	vector<vector<double>> v2TrueVariable;//真实变量值
	vector<vector<double>> v2TrueResult;//真实函数值
	void readdata(const string& filename);
}PSOFuction;

class ParticleSwarmOptimization
{
public:
	ParticleSwarmOptimization();
	~ParticleSwarmOptimization();

	PSOCreat* PSO_Data = NULL;
	PSOFuction* PSO_Fun = NULL;

	void initial_check(PSOCreat& PSOCreatStructData, PSOFuction& PSOFunctionHandle);// 初始化并检查
	void optimize();// 优化计算
	void clear();// 清楚内存

private:
	double dResidualSquare = 0.0;
	double dMinRelativeResidual = 0.0;
	double dMaxRelativeResidual = 0.0;
	double dMaxAbsRelativeResidual = 0.0;
	// 误差评价
	void error_estimate();
	// 输出第nIter次迭代的计算信息
	void printInfo(int nIter);
	// 初始化粒子速度与位置
	void initial();
	// 更新粒子速度与位置
	void refresh();
	// 速度与位置范围约束
	void limited();

};


// 读取数组
void readvector(const string& filename, vector<double>& vec);
// 读取矩阵
void readmatrix(const string& filename, vector<vector<double>>& mat);
// 分割字符串并转换为数组
void string2vector(const string& str, vector<double>& vec);



#endif // !PSO_H

