#include <iostream>
using namespace std;
#define NAME_SIZE 32

enum MAP_THPE
{
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_END
};

enum MAIN_MENU
{
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAtackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldmin;
	int		iGoldmax;
};

int InputInt()
{
	int Input;
	cin >> Input;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		//INT_MAX가 리턴되면 입력이 잘못됐다.
		return INT_MAX;
	}

	return Input;
}

void AddMonster(_tagMonster* pMonsterArr)
{

	int iMap = 0;

	while (true)
	{
		system("cls");
		cout << "1.쉬움 " << endl;
		cout << "2.보통 " << endl;
		cout << "3.어려움 " << endl;
		cout << "4.취소 " << endl;
		cout << "추가할 난이도를 선택하세요 : ";
		iMap = InputInt();

		if (iMap == 4)
			return;

		else if (iMap < 1 || iMap > 4)
			continue;

		//1부터 시작이기 때문에 1을 감소시켜야 사냥터 인덱스가 된다.
		--iMap;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	//몬스터 이름을 입력받는다.
	cout << "이름 : ";
	cin.getline(pMonsterArr[iMap].strName, NAME_SIZE - 1);

	cout << "최소공격력 : ";
	pMonsterArr[iMap].iAttackMin = InputInt();

	cout << "최대공격력 : ";
	pMonsterArr[iMap].iAtackMax = InputInt();

	cout << "최소방어력 : ";
	pMonsterArr[iMap].iArmorMin = InputInt();

	cout << "최대방어력 : ";
	pMonsterArr[iMap].iArmorMax = InputInt();

	cout << "체력 : ";
	pMonsterArr[iMap].iHP = InputInt();
	pMonsterArr[iMap].iHPMax = pMonsterArr[iMap].iHP;

	cout << "마나 : ";
	pMonsterArr[iMap].iMP = InputInt();
	pMonsterArr[iMap].iMPMax = pMonsterArr[iMap].iMP;

	cout << "레벨 : ";
	pMonsterArr[iMap].iLevel = InputInt();

	cout << "획득 경험치 : ";
	pMonsterArr[iMap].iExp = InputInt();

	cout << "획득 최소 골드 : ";
	pMonsterArr[iMap].iGoldmin = InputInt();

	cout << "획득 최대 골드 : ";
	pMonsterArr[iMap].iGoldmax = InputInt();

	cout << "몬스터 추가 완료" << endl;
	system("pause");
}

bool SaveMonster(_tagMonster* pMonsterArr)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "wb");
	if (pFile)
	{
		fwrite(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);

		fclose(pFile);
		return true;
	}
	return true;
}

bool LoadMonster(_tagMonster* pMonsterArr)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "rb");
	if (pFile)
	{
		fread(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);

		fclose(pFile);
		return true;
	}
	return true;
}

void OutputMonster(_tagMonster* pMonster)
{
	//몬스터 정보 출력

	cout << "이름 : " << pMonster->strName << "\t레벨 : " <<
		pMonster->iLevel << endl;

	cout << "공격력 : " << pMonster->iAttackMin << " - " <<
		pMonster->iArmorMax << "\t방어력 :" << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;

	cout << "체력 : " << pMonster->iHP << "/ " << pMonster->iHPMax <<
		"마나 : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;

	cout << "획득 경험치 : " << pMonster->iExp << "\t획득골드 : " <<
		pMonster->iGoldmin << " - " << pMonster->iGoldmax << endl;
}

void Output(_tagMonster* pMonsterArr)
{
	system("cls");


	for (int i = 0; i < MT_END; ++i)
	{
		cout << "******************MONSTER******************" << endl;
		OutputMonster(&pMonsterArr[i]);
		cout << endl;
		cout << endl;
	}

	system("pause");

}

int main()
{
	_tagMonster tMonster[MT_END] = {};

	while (true)
	{
		system("cls");
		cout << "1.몬스터 추가 " << endl;
		cout << "2.읽어오기 " << endl;
		cout << "3.저장 " << endl;
		cout << "4.몬스터 출력  " << endl;
		cout << "5.종료 " << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu = InputInt();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_ADD:
			AddMonster(tMonster);
			break;
		case MM_LOAD:
			LoadMonster(tMonster);
			break;
		case MM_SAVE:
			SaveMonster(tMonster);
			break;
		case MM_OUTPUT:
			Output(tMonster);
			break;
		}
	}

	//자동 저장기능.혹시나 저장을 하지 않을 경우를 대비한다.
	SaveMonster(tMonster);

	return 0;
}