#include "pso.h"

void PSOFuction::initial(int nVar, int nVal, int nCoef)
{
	nVariable = nVar;
	nResult = nVal;
	nCoefficient = nCoef;
	vVariable.resize(nVariable);
	vResult.resize(nResult);
	vCoefficient.resize(nCoefficient);
}
void PSOFuction::clear()
{
	vVariable.clear();
	vResult.clear();
	vVariable.shrink_to_fit();
	vResult.shrink_to_fit();
	vCoefficient.clear();
	vCoefficient.shrink_to_fit();
}

void PSOFuction::target_function()
{
	//函数关系式
	// 自变量: d, R, Pt, dfw
	// 参数: s1, s2, s3, s4
	// 函数: q = s1 * d. ^ s2 . / (R. ^ s3).*Pt.*dfw. ^ s4;
	vResult[0] = vCoefficient[0] * pow(vVariable[0], vCoefficient[1]) / pow(vVariable[1], vCoefficient[2]) *
		vVariable[2] * pow(vVariable[3], vCoefficient[3]);

}


void PSOFuction::readdata(const string& filename)
{
	// 文本文件格式
	vector<vector<double>> mat;//q = data(:, 1); d = data(:, 2); R = data(:, 3); Pt = data(:, 4); dfw = data(:, 5);
	readmatrix(filename, mat);
	int M = mat.size();
	int N = mat[0].size();
	if (N != 5) {
		printf("ERROR: 读取真实测试数据的长度不足!\n");
	}
	v2TrueVariable.resize(M);//真实变量值
	v2TrueResult.resize(M);//真实函数值
	for (int i = 0; i < M; i++) {
		v2TrueVariable[i].resize(4);
		v2TrueResult[i].resize(1);
	}
	for (int i = 0; i < M; i++) {
		v2TrueVariable[i][0] = mat[i][1];
		v2TrueVariable[i][1] = mat[i][2];
		v2TrueVariable[i][2] = mat[i][3];
		v2TrueVariable[i][3] = mat[i][4];
		v2TrueResult[i][0] = mat[i][0];
	}

}


// 读取数组
void readvector(const string& filename, vector<double>& vec)
{
	// 文本文件格式
	// N: 数组维度
	// b: 数据行, 共N行
	int N = 0;
	ifstream infile(filename);
	string line;
	if (infile) // 有该文件
	{
		// N
		getline(infile, line);

		N = atoi(line.c_str());
		vec.resize(N);
		// b
		for (int i = 0; i < N; i++)
		{
			getline(infile, line);
			vec[i] = atof(line.c_str());
		}
	}
	else // 没有该文件
	{
		printf("no such file\n");
	}
}

// 读取矩阵
void readmatrix(const string& filename, vector<vector<double>>& mat)
{
	// 文本文件格式
	// M: 数组行数
	// N: 数组列数
	// mat: 数据行, 共M行 * N列
	int M = 0, N = 0, num = 0;
	ifstream infile(filename);
	string line;
	vector<double> vec;
	if (infile) // 有该文件
	{
		// M
		getline(infile, line);
		M = atoi(line.c_str());
		// N
		getline(infile, line);
		N = atoi(line.c_str());

		mat.resize(M);
		for (int i = 0; i < M; i++) {
			mat[i].resize(N);
		}
		vec.resize(N);
		// 数据行
		for (int i = 0; i < M; i++)
		{
			getline(infile, line);
			num = string2vector(line, vec);
			if (num != N) {
				printf("ERROR: 转换的数组长度不等于设置N=%d\n", N);
			}
			else {
				for (int j = 0; j < N; j++) {
					mat[i][j] = vec[j];
				}
			}
		}
	}
	else // 没有该文件
	{
		printf("no such file\n");
	}

}

// 分割字符串并转换为数组
int string2vector(const string& str, vector<double>& vec)
{
	char cstr[30];// = "123\tds\nc";
	int j = 0, num = 0;
	bool bStart = false;
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] != ',') && (str[i] != ' ') && (str[i] != '\t') && (str[i] != '\n')) {
			cstr[j] = str[i];
			j++;
			bStart = true;
		}
		else {
			cstr[j] = '\0';
			j = 0;
			if (bStart) {
				bStart = false;
				vec[num] = atof(cstr);
				num++;
			}
		}
	}
	if (bStart) {//最后一个
		bStart = false;
		vec[num] = atof(cstr);
		num++;
	}
	return num;

	// printf("%.4f\n", atof("2.45"));
	// printf("%.4f\n", atof("0.005"));
	// printf("%.4f\n", atof("-22.5"));
	// printf("%.4f\n", atof("1.45e-4"));
	// printf("%.4f\n", atof("1.45e4"));
	// printf("%.4f\n", atof("-1.45e-4"));
	// printf("%.4f\n", atof("-1.45e4"));
	// printf("%.8f\n", atof("-1.45\01234e4"));
}
