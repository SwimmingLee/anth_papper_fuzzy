
#ifndef __FUZZY_ANTHRA_H__
#define __FUZZY_ANTHRA_H__


#include <iostream>
#include <string.h>


using namespace std;


#define Z0		0

#define T3		3
#define T2		2
#define T1		1

#define H3		3
#define H2		2
#define H1		1

#define W4		4
#define W3		3
#define W2		2
#define W1		1

#define VH		4
#define H		3
#define M		2
#define L		1

double min(double num1, double num2, double num3);

// Fuzzy 초기화
void initTempPos(double **TempPos);
void initHumPos(double **HumPos);
void initWindPos(double **WindPos);
void initAnthRiskPos(double **AnthRiskPos);

// Fuzzy Rule 초기화
void initFuzzyRules(int **FuzzyRules);

// 퍼지화(fuzzification)
double* Anth_Fuzzification(double temp, double humi, double wind, \
	double **TempPos, double **HumPos, double **WindPos, \
	double **AnthRiskPos, int **FuzzyRules);


// 역퍼지화(defuzzication)
double Anth_DeFuzzification(double * Risk_eval, double **AnthRiskPos);


double min(double num1, double num2, double num3)
{
	double tmp = num1 > num2 ? num2 : num1;
	return tmp > num3 ? num3 : tmp;

}



int get_AnthFuzzy()
{
	int TempPosX = 4, TempPosY = 31;
	int HumPosX = 4, HumPosY = 21;
	int WindPosX = 5, WindPosY = 21;
	int AnthRiskPosX = 5, AnthRiskPosY = 21;
	int FuzzyRulesX = 4, FuzzyRulesY = 46;

	double **TempPos = new double*[TempPosX];
	for (int i = 0; i < TempPosX; ++i)
		TempPos[i] =  new double[TempPosY];

	double **HumPos = new double*[HumPosX];
	for (int i = 0; i < HumPosX; ++i)
		HumPos[i] = new double[HumPosY];

	double **WindPos = new double*[WindPosX];
	for (int i = 0; i < WindPosX; ++i)
		WindPos[i] = new double[WindPosY];

	double **AnthRiskPos = new double*[AnthRiskPosX];
	for (int i = 0; i < AnthRiskPosX; ++i)
		AnthRiskPos[i] = new double[AnthRiskPosY];

	int **FuzzyRules = new int*[FuzzyRulesX];
	for (int i = 0; i < FuzzyRulesX; ++i)
		FuzzyRules[i] = new int[FuzzyRulesY];


	// Fuzzy 초기화
	initTempPos(TempPos);
	initHumPos(HumPos);
	initWindPos(WindPos);
	initAnthRiskPos(AnthRiskPos);

	// Fuzzy Rule 초기화
	initFuzzyRules(FuzzyRules);
	
	// 센서값 데이터 받아오기
	float temp = 25;
	float humi = 90;
	float wind = 2;


	// 퍼지화(fuzzification)
	// 규칙 평가(rule evaluation)
	// ��Ģ  ����
	double * Risk_eval = Anth_Fuzzification(temp, humi, wind, TempPos, HumPos, WindPos, AnthRiskPos, FuzzyRules);

	// 역퍼지화(defuzzication)

	for (int i = 0; i < 21; i++) {
		cout << " Eval " << i << " : " <<  Risk_eval[i] << endl;
	}

	double RiskRate = Anth_DeFuzzification(Risk_eval, AnthRiskPos);

	cout << RiskRate << endl;

	// 동적배열 삭제
	for (int i = 0; i < TempPosX; i++)
	{ delete[] TempPos[i]; }
	delete[] TempPos;

	for (int i = 0; i < HumPosX; i++)
	{
		delete[] HumPos[i];
	}
	delete[] HumPos;


	for (int i = 0; i < WindPosX; i++)
	{
		delete[] WindPos[i];
	}
	delete[] WindPos;


	for (int i = 0; i < AnthRiskPosX; i++)
	{
		delete[] AnthRiskPos[i];
	}
	delete[] AnthRiskPos;

	return 0;
}

void initTempPos(double** TempPos) {
	//double TempPos[4][31];

	//int TempPosY = 31;
	//init TempPos 
	for (int j = 0; j < 4; j++) {
		//memset(TempPos[j], 0, sizeof(TempPos[j]));
		if (j == 0) {
			for (int i = 0; i < 31; i++)
			{
				TempPos[j][i] = (double)(i + 10);
			}
		}
	}//end of Init TempPos

	double Temp1[31] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 0.6, 0.4, \
						0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
						0.0 };

	double Temp2[31] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.4, 0.6, \
						0.8, 1.0, 1.0, 1.0, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0, \
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
						0.0 };

	double Temp3[31] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.4, 0.6, 0.8, \
						1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, \
						1.0 };


	memcpy(TempPos[1], Temp1, sizeof(Temp1));
	memcpy(TempPos[2], Temp2, sizeof(Temp2));
	memcpy(TempPos[3], Temp3, sizeof(Temp3));

}


void initHumPos(double ** HumPos)
{

	//double HumPos[4][21];

	//init HumPos 
	for (int j = 0; j < 4; j++) {
		//memset(HumPos[0], 0, sizeof(HumPos[j]));
		if (j == 0) {
			for (int i = 0; i < 21; i++)
			{
				HumPos[j][i] = i * 5;
			}
		}
	}//end of Init HumPos

	double Hum1[21] = { 1.0, 1.0, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0, 0.0, 0.0, \
					   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
					   0.0 };

	double Hum2[21] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, \
				       1.0, 0.8, 0.6, 0.4, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, \
					   0.0 };

	double Hum3[21] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
					   0.0, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.0, 1.0, 1.0, \
				       1.0 };

	memcpy(HumPos[1], Hum1, sizeof(Hum1));
	memcpy(HumPos[2], Hum2, sizeof(Hum2));
	memcpy(HumPos[3], Hum3, sizeof(Hum3));

	

}



void initWindPos(double** WindPos)
{

	//double WindPos[5][21];

	//init WindPos 
	for (int j = 0; j <= 4; j++) {
		//memset(WindPos[j], 0, sizeof(WindPos[j]));
		if (j == 0) {
			for (int i = 0; i <= 20; i++)
			{
				WindPos[j][i] = i;
			}
		}
	}//end of Init WindPos

	double Wind1[21] = { 1.0, 0.8, 0.5, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
					    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
					    0.0};

	double Wind2[21] = { 0.0, 0.0, 0.0, 0.3, 0.5, 0.8, 1.0, 1.0, 0.8, 0.5, \
				    	0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
						0.0 };

	double Wind3[21] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, \
						0.5, 0.8, 1.0, 1.0, 0.8, 0.5, 0.3, 0.0, 0.0, 0.0, \
						0.0 };

	double Wind4[21] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
						0.0, 0.0, 0.0, 0.0, 0.3, 0.5, 0.8, 1.0, 1.0, 1.0, \
						1.0 };

	memcpy(WindPos[1], Wind1, sizeof(Wind1));
	memcpy(WindPos[2], Wind2, sizeof(Wind2));
	memcpy(WindPos[3], Wind3, sizeof(Wind3));
	memcpy(WindPos[4], Wind4, sizeof(Wind4));
	
}



void initAnthRiskPos(double** AnthRiskPos)
{

	//double AnthRiskPos[5][21];

	//init AnthRiskPos 
	for (int j = 0; j <= 4; j++) {
		//memset(AnthRiskPos[j], 0, sizeof(AnthRiskPos[j]));
		if (j == 0) {
			for (int i = 0; i <= 20; i++)
			{
				AnthRiskPos[j][i] = i * 5;
			}
		}
	}//end of Init AnthRiskPos

	double AnthRisk1[21] = { 1.0, 1.0, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0, 0.0, 0.0, \
							0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
							0.0 };

	double AnthRisk2[21] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.0, 0.8, 0.6, 0.4, \
							0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
							0.0 };

	double AnthRisk3[21] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.4, \
							0.6, 0.8, 1.0, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0, 0.0, \
							0.0 };

	double AnthRisk4[21] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
							0.0, 0.0, 0.0, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.0, \
							1.0 };


	memcpy(AnthRiskPos[1], AnthRisk1, sizeof(AnthRisk1));
	memcpy(AnthRiskPos[2], AnthRisk2, sizeof(AnthRisk2));
	memcpy(AnthRiskPos[3], AnthRisk3, sizeof(AnthRisk3));
	memcpy(AnthRiskPos[4], AnthRisk4, sizeof(AnthRisk4));
	


}


void initFuzzyRules(int **FuzzyRules)
{
	//int FuzzyRules[4][46];

	int FuzzyRule_Temp[46] = { Z0, T3, T3, T3, T3, T3, T3, T3, T3, T3, \
							   T2, T2, T2, T2, T2, T2, T2, T2, T2, T1, \
							   T1, T1, T1, T1, T1, T1, T1, T1, Z0, Z0, \
						   	   Z0, Z0, Z0, Z0, Z0, Z0, Z0, T3, T3, T3, \
							   T2, T2, T2, T1, T1, T1 };

	int FuzzyRule2_Hum[46] = { Z0, H3, H3, H3, H2, H2, H2, H1, H1, H1, \
							   H3, H3, H3, H2, H2, H2, H1, H1, H1, H3, \
							   H3, H3, H2, H2, H2, H1, H1, H1, H3, H3, \
							   H3, H2, H2, H2, H1, H1, H1, H3, H2, H1, \
							   H3, H2, H1, H3, H2, H1 };

	int FuzzyRule_Wind[46] = { W4, W3, W2, W1, W3, W2, W1, W3, W2, W1, \
							   W3, W2, W1, W3, W2, W1, W3, W2, W1, W3, \
							   W2, W1, W3, W2, W1, W3, W2, W1, W3, W2, \
							   W1, W3, W2, W1, W3, W2, W1, Z0, Z0, Z0, \
							   Z0, Z0, Z0, Z0, Z0, Z0 };

	int FuzzyRule_Risk[46] = { VH, VH, VH,  H, VH,  H,  M, VH,  H,  M, \
							   VH,  H,  M, VH,  H,  M,  H,  M,  L,  H, \
							   M,  L,  H,  M,  L,  H,  M,  L,  H,  VH, \
							   VH,  H,  M,  L,  M,  L,  L, VH,  H,  M, \
							   H,  M,  M,  M,  L,  L };

	memcpy(FuzzyRules[0], FuzzyRule_Temp, sizeof(FuzzyRule_Temp));
	memcpy(FuzzyRules[1], FuzzyRule2_Hum, sizeof(FuzzyRule2_Hum));
	memcpy(FuzzyRules[2], FuzzyRule_Wind, sizeof(FuzzyRule_Wind));
	memcpy(FuzzyRules[3], FuzzyRule_Risk, sizeof(FuzzyRule_Risk));

	
}


#define TEMP	0
#define HUMI	1
#define WIND	2
#define RISK	3


double* Anth_Fuzzification(double temp, double humi, double wind, \
	double **TempPos, double** HumPos, double** WindPos, \
	double **AnthRiskPos, int **FuzzyRules)
{
//	double TempPos[4][31];
//	double HumPos[4][21];
//	double WindPos[5][21];
//	double AnthRiskPos[5][21];
//	int FuzzyRules[4][46];

	double* Risk_eval = new double[21];
	//memset(Risk_eval, 0, sizeof(Risk_eval));

	double tempbuffer = 0;
	double humibuffer = 0;
	double windbuffer = 0;

	double minbuffer[46];
	double rule_min_value[21];

	memset(rule_min_value, 0, sizeof(rule_min_value));

	for (int i = 0; i < 46; i++)
	{
		// TempPos[0][i] == temp �� ������ ã�´�.
		// HumPos[0][i] == humi �� ������ ã�´�.
		// WindPos[0][i] == wind �� ������ ã�´�.

		// �׸��� �����̼ǵ� ��� �Ѵ�.
		
		temp = temp > 10 ? temp : 10;
		temp = temp < 40 ? temp : 40;
		humi = humi > 0 ? humi : 0;
		humi = humi < 100 ? humi : 100;
		wind = wind > 0 ? wind : 0;
		wind = wind < 20 ? wind : 20;

		int temp_idx = (int)(temp - 10);
		int humi_idx = (int)humi / 5;
		int wind_idx = (int)wind;

		if (FuzzyRules[TEMP][i] == Z0)
		{
			// ���̺� 1�� ����
			tempbuffer = 1;
		}
		else
		{
			// ���̺� �ش��ϴ� �� �ε��� ���� ����
			int RuleSec = FuzzyRules[TEMP][i];
			tempbuffer = TempPos[RuleSec][temp_idx];
		}

		if (FuzzyRules[HUMI][i] == Z0)
		{
			// ���̺� 1�� ����
			humibuffer = 1;
		}
		else
		{
			// ���̺� �ش��ϴ� �� �ε��� ���� ����
			int RuleSec = FuzzyRules[HUMI][i];
			humibuffer = HumPos[RuleSec][humi_idx];
		}

		if (FuzzyRules[WIND][i] == Z0)
		{
			// ���̺� 1�� ����
			windbuffer = 1;
		}
		else
		{
			// ���̺� �ش��ϴ� �� �ε��� ���� ����
			int RuleSec = FuzzyRules[WIND][i];
			windbuffer = WindPos[RuleSec][wind_idx];
		}

		minbuffer[i] = min(tempbuffer, humibuffer, windbuffer);

		//Rule ��� Ȯ���ϱ�
		cout << "Rule  " << i+1 << " : " << tempbuffer << " : " << humibuffer << " : " << windbuffer  << " : " <<  minbuffer[i] << endl;


		// Rule Section ��� ���ϱ�(VH, H, M, L ���ϱ�)
		int outRuleSec = FuzzyRules[RISK][i];
		
		for (int j = 0; j < 21; j++)
		{
			// �Ҽӵ��� ������ �� ���� ���� ���� 
			double tmp = AnthRiskPos[outRuleSec][j];
			tmp = tmp < minbuffer[i] ? tmp : minbuffer[i];

			//�� ���赵 ��ġ ���̺� �ִ밪�� ����
			if (Risk_eval[j] < tmp)  Risk_eval[j] = tmp;
		}
	
		
	} // end of for (Rule eval)


	return Risk_eval;

}

double Anth_DeFuzzification(double * Risk_eval, double **AnthRiskPos)
{
	//double Risk_eval[21];
	//double AnthRiskPos[5][21];

	double nom = 0; // ����
	double den = 0; // �и�

	for (int i = 0; i < 21; i++)
	{
		den += Risk_eval[i];
		nom += Risk_eval[i] * AnthRiskPos[0][i];
	}


	return den == 0 ? 0 : (double) nom / den;
}

#endif
