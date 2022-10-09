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
	//% ��������: ��Ϊ0��ʾ��Ĭ��ֵ
	int    nDimension                 = 0;      //% �����������ά��
	int    nParticleNumber            = 0;      //% ������
	double dLearnRateFirst            = 2.5;    //% ѧϰ����1: 2.5
	double dLearnRateSecond           = 2.5;    //% ѧϰ����2: 2.5
	double dWeightIteration           = 0.0;    //% ����Ȩֵ
	int    nInertiaWeightMaxIteration = 40;     //% ������: 40
	double dInertiaWeightIni          = 0.9;    //% ��ʼ����Ȩֵ: 0.9
	double dInertiaWeightEnd          = 0.2;    //% ���չ���Ȩֵ: 0.2
	int    nMaxIteration              = 100;   //% ���������������: 1000
	double dTolerance                 = 1.0e-6; //% ���þ���: 1.0e-6
	//% ������ʼֵ
	vector<vector<double>> v2Location; //% ����λ�� zeros(D, N)
	vector<vector<double>> v2Velocity; //% �����ٶ� zeros(D, N)
	vector<double>         vFitness; //% ÿ�����ӵ���Ӧ�� zeros(1, N)
	vector<vector<double>> v2PesonalBest ; //% �������ŷ��� zeros(D, N)
	vector<double>         vGlobalBest; //% �������ŷ��� zeros(D, 1)
	vector<double>         vPersonalBestError; //% ����������Ӧ�� zeros(1, N)
	double                 dGlobalBestError = 0; //% ����������Ӧ��
	//% ��ΧȦ��
	vector<double> vMaxVelocity; //% �������仯�ٶ�
	vector<double> vMinLocation; //% ������Сֵ
	vector<double> vMaxLocation; //% �������ֵ

	void initial();
	void clear();
	void limit(double MaxVelocity, double MinLocation, double MaxLocation);// ��������ٶ�Ϊλ�÷�Χ
	void limit(vector<double> MaxVelocity, double MinLocation, double MaxLocation);
	void limit(double MaxVelocity, vector<double> MinLocation, double MaxLocation);
	void limit(double MaxVelocity, double MinLocation, vector<double> MaxLocation);
	void limit(double MaxVelocity, vector<double> MinLocation, vector<double> MaxLocation);
	void limit(vector<double> MaxVelocity, vector<double> MinLocation, double MaxLocation);
	void limit(vector<double> MaxVelocity, double MinLocation, vector<double> MaxLocation);
	void limit(vector<double> MaxVelocity, vector<double> MinLocation, vector<double> MaxLocation);
private:
	bool bSuccessInitialize = false;
	void assign_vector(vector<double>& target, const vector<double>& source);//��source��ֵ����target,���㲻��,��������
	void assign_vector(vector<double>& target, double source);//��source��ֵ����target
}PSOCreat;


typedef class ParticleSwarmOptimizationFuction
{
public:
	int nVariable = 0;//��������
	int nResult = 0;//����ֵ����
	int nCoefficient = 0;//ϵ������
	vector<double> vVariable;//����ֵ
	vector<double> vResult;//����ֵ
	vector<double> vCoefficient;//ϵ��ֵ
	void target_function();//������ϵʽ
	void initial(int nVar,int nVal, int nCoef);
	void clear();
	// ��ʵ����
	vector<vector<double>> v2TrueVariable;//��ʵ����ֵ
	vector<vector<double>> v2TrueResult;//��ʵ����ֵ
	void readdata(const string& filename);
}PSOFuction;

class ParticleSwarmOptimization
{
public:
	ParticleSwarmOptimization();
	~ParticleSwarmOptimization();

	PSOCreat* PSO_Data = NULL;
	PSOFuction* PSO_Fun = NULL;

	void initial_check(PSOCreat& PSOCreatStructData, PSOFuction& PSOFunctionHandle);// ��ʼ�������
	void optimize();// �Ż�����
	void clear();// ����ڴ�

private:
	double dResidualSquare = 0.0;
	double dMinRelativeResidual = 0.0;
	double dMaxRelativeResidual = 0.0;
	double dMaxAbsRelativeResidual = 0.0;
	// �������
	void error_estimate();
	// �����nIter�ε����ļ�����Ϣ
	void printInfo(int nIter);
	// ��ʼ�������ٶ���λ��
	void initial();
	// ���������ٶ���λ��
	void refresh();
	// �ٶ���λ�÷�ΧԼ��
	void limited();

};


// ��ȡ����
void readvector(const string& filename, vector<double>& vec);
// ��ȡ����
void readmatrix(const string& filename, vector<vector<double>>& mat);
// �ָ��ַ�����ת��Ϊ����
void string2vector(const string& str, vector<double>& vec);



#endif // !PSO_H

