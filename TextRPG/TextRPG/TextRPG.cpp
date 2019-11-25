﻿#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;

/*
한번 해보기
1.무기상점에서 파매할 아이템 목록을 만들어주고 해당 목록을 출력해준다.
2.출력할때 앞에 번호를 부여해주고 번호를 입력받아서 해당 번호의 아이템을
구입하게 해준다.가장 마지막 번호에 뒤로가기 기능을 만든다.
단, 가방이 꽉찼거나 돈이 부족할 경우 구매하지 못하게 한다.
3.가방을 선택하면 가방안의 아이템을 보여준다.
*/


enum MAIN_MENU
{
	MM_MODE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_THPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END,

};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK,
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK,
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3

struct _tagItem
{
	char		strName[NAME_SIZE];
	char		strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int			iMin;
	int			iMax;
	int			iPrice;
	int			iSell;
	char		strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory
{
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAtackMin;
	int		iAtackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagInventory tInventory;
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAtackMin;
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

int main()
{
	srand((unsigned int)time(0));

	//게임을 시작할때 플레이어 정보를 설정하게 한다.
	_tagPlayer tPlayer = {};

	//플레이어 이름을 입력받는다.
	cout << "이름 : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1.기사" << endl;
		cout << "2.궁수" << endl;
		cout << "3.마법사" << endl;
		cout << "직업을 선택하세요 :";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (iJob <= JOB_NONE || iJob >= JOB_END)
		{
			iJob = JOB_NONE;
		}
	}


	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		tPlayer.iAtackMin = 5;
		tPlayer.iAtackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHPMax = 500;
		tPlayer.iHP = 500;
		tPlayer.iMP = 100;
		tPlayer.iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		tPlayer.iAtackMin = 10;
		tPlayer.iAtackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHPMax = 400;
		tPlayer.iHP = 400;
		tPlayer.iMP = 200;
		tPlayer.iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		tPlayer.iAtackMin = 15;
		tPlayer.iAtackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHPMax = 300;
		tPlayer.iHP = 300;
		tPlayer.iMP = 300;
		tPlayer.iMPMax = 300;
		break;

	}

	//몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	//고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iAtackMin = 20;
	tMonsterArr[0].iAtackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldmin = 500;
	tMonsterArr[0].iGoldmax = 1500;

	//트롤 생성
	strcpy_s(tMonsterArr[1].strName, "트롤");
	tMonsterArr[1].iAtackMin = 80;
	tMonsterArr[1].iAtackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldmin = 6000;
	tMonsterArr[1].iGoldmax = 8000;

	//드래곤 생성
	strcpy_s(tMonsterArr[2].strName, "드래곤");
	tMonsterArr[2].iAtackMin = 250;
	tMonsterArr[2].iAtackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldmin = 20000;
	tMonsterArr[2].iGoldmax = 50000;

	//상점에서 판매할 아이템 목록을 생성한다.
	_tagItem	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	//각 아이템 정보들을 설정해준다.


	while (true)
	{
		system("cls");
		cout << "******************로비******************" << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 :" << endl;
		int iMenu;
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
			while (true)
			{
				system("cls");
				cout << "******************맵******************" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
				cout << "맵을 선택하세요 :" << endl;
				int iMenu;
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				//이 if문에 속한 break는 맵 메뉴를 돌려주기 위한 while에 속해 있으므로
				//이 while문을 빠져나간다.
				if (iMenu == MT_BACK)
					break;

				//선택한 메뉴에서 1을 빼주면 몬스터 배열의 인덱스가 된다.
				//그렇게 해서 해당 맵의 몬스터를 생성해준다.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true)
				{
					system("cls");
					switch (iMenu)
					{
					case MT_EASY:
						cout << "******************쉬움******************" << endl;
						break;
					case MT_NORMAL:
						cout << "******************보통******************" << endl;
						break;
					case MT_HARD:
						cout << "******************어려움******************" << endl;
						break;
					}

					//플레이어 정보를 출력한다.
					cout << "******************PLAYER******************" << endl;
					cout << "이름 : " << tPlayer.strName << "\t직업 : " <<
						tPlayer.strJobName << endl;

					cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " <<
						tPlayer.iExp << endl;

					cout << "공격력 : " << tPlayer.iAtackMin << " - " <<
						tPlayer.iArmorMax << "\t방어력 :" << tPlayer.iArmorMin <<
						" - " << tPlayer.iArmorMax << endl;

					cout << "체력 : " << tPlayer.iHP << "/ " << tPlayer.iHPMax <<
						"마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

					cout << "보유골드 : " << tPlayer.tInventory.iGold << "GOLD " << endl << endl;

					//몬스터 정보 출력
					cout << "******************MONSTER******************" << endl;
					cout << "이름 : " << tMonster.strName << "\t레벨 : " <<
						tMonster.iLevel << endl;

					cout << "공격력 : " << tMonster.iAtackMin << " - " <<
						tMonster.iArmorMax << "\t방어력 :" << tMonster.iArmorMin <<
						" - " << tMonster.iArmorMax << endl;

					cout << "체력 : " << tMonster.iHP << "/ " << tMonster.iHPMax <<
						"마나 : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;

					cout << "획득 경험치 : " << tMonster.iExp << "\t획득골드 : " <<
						tMonster.iGoldmin << " - " << tMonster.iGoldmax << endl;

					cout << "1.공격 " << endl;
					cout << "2.도망가기 " << endl;
					cout << "메뉴를 선택하세요 :";
					cin >> iMenu;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (iMenu == BATTLE_BACK)
						break;

					switch (iMenu)
					{
					case BATTLE_ATTACK:

					{

						//예를 들어 MIN 5 MAX 15라고 가정할 경우
						//15-5 +1 을 하면 11인된다. 11로 나눈 나머지는 0~10이
						//나오게 되고 여기에 MIN값인 5를 더하게 되면
						//5~15 사이로 값이 나오게 되는것이다.
						int iAttack = rand() % ((tPlayer.iArmorMax - tPlayer.iAtackMin) + 1) +
							tPlayer.iAtackMin;

						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
							tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						//삼항연산자 : a > b ? a : b ;
						iDamage = iDamage < 1 ? 1 : iDamage;

						//몬스터 HP를 감소시킨다
						tMonster.iHP -= iDamage;

						cout << tPlayer.strName << "가 " << tMonster.strName <<
							"에게 " << iDamage << "피해를 입혔습니다 " << endl;

						//몬스터가 죽었을 경우를 처리한다.
						if (tMonster.iHP <= 0)
						{
							cout << tMonster.strName << "몬스터가 사망하였습니다 " << endl;
							tPlayer.iExp += tMonster.iExp;
							int iGold = rand() % (tMonster.iGoldmax - tMonster.iGoldmin + 1) +
								tMonster.iGoldmin;
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << "경험치를 획득하였습니다. " << endl;
							cout << iGold << "Gold를 획득하였습니다. " << endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;
							system("pause");
							break;
						}

						//몬스터가 살아있다면 플레이어를 공격한다.
						iAttack = rand() % ((tMonster.iArmorMax - tMonster.iAtackMin) + 1) +
							tMonster.iAtackMin;

						iArmor = rand() % (tPlayer.iArmorMax - tPlayer.iArmorMin + 1) +
							tPlayer.iArmorMin;

						iDamage = iAttack - iArmor;
						//삼항연산자 : a > b ? a : b ;
						iDamage = iDamage < 1 ? 1 : iDamage;

						//플레이어의 HP를 감소시킨다.
						tPlayer.iHP -= iDamage;
						cout << tMonster.strName << "가 " << tPlayer.strName <<
							"에게 " << iDamage << "피해를 입혔습니다 " << endl;

						//플레이어가 죽었을 경우
						if (tPlayer.iHP <= 0)
						{
							cout << tPlayer.strName << "플레이어가 사망하였습니다. " << endl;

							int iExp = tPlayer.iExp = 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << "경험치를 잃었습니다. " << endl;
							cout << iGold << "Gold를 잃었습니다. " << endl;

							//플레이어의 HP와 MP를 회복한다.
							tPlayer.iHP = tPlayer.iHPMax;
							tPlayer.iMP = tPlayer.iMPMax;
						}
						system("pause");
					}

					break;
					}

				}
			}
			break;
		case MM_STORE:
			while (true)
			{
				system("cls");
				cout << "******************상점******************" << endl;
				cout << "1.무기상점 " << endl;
				cout << "2.방어구상점 " << endl;
				cout << "3.뒤로가기 " << endl;
				cout << "상점을 선택하세요 " << endl;
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == SM_BACK)
					break;

				switch (iMenu)
				{
				case SM_WEAPON:
					while (true)
					{
						system("cls");

						cout << "******************무기상점******************" << endl;

						//판매 목록을 보여준다.
						for (int i = 0; i < STORE_WEAPON_MAX; ++i)
						{
							cout << i + 1 << ".이름: " << tStoreWeapon[i].strName <<
								"\t종류 :" << tStoreWeapon[i].strTypeName << endl;

							cout << "공격력: " << tStoreWeapon[i].iMin << " - " <<
								tStoreWeapon[i].iMax << endl;

							cout << "판매가격: " << tStoreWeapon[i].iPrice <<
								"\t구매가격: " << tStoreWeapon[i].iSell << endl;

							cout << "설명: " << tStoreWeapon[i].strDesc << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ".뒤로가기" << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요: ";
						cin >> iMenu;

						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;

						else if (iMenu < 1 || iMenu > STORE_WEAPON_MAX)
						{
							cout << "잘못 선택하였습니다. " << endl;
							system("pasue");
							continue;
						}

						//상점판매목록 배열의 인덱스를 구해준다.
						int iWeaponIndex = iMenu - 1;

						//인벤토리가 꽉 찼는지 검사한다.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다. " << endl;
							system("pause");
							continue;
						}

						//돈이 부족할 경우
						else if (tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice)
						{
							cout << "보유금액이 부족합니다. " << endl;
							system("pause");
							continue;
						}

						//처음에 iItemCount는 하나도 추가되어있지 않기 때문에 0으로 초기화
						//되어 있으므로 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고
						//카운트가 1이 된다. 다음번에 추가할때는 1번 인덱스에 추가하게 된다.
						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iItemCount;

						//골드를 차감한다.
						tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;

						cout << tStoreWeapon[iWeaponIndex].strName << "아이템을 구매하였습니다." << endl;
						system("pause");

					}


					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");

						cout << "******************방어구상점******************" << endl;

						//판매 목록을 보여준다.
						for (int i = 0; i < STORE_ARMOR_MAX; ++i)
						{
							cout << i + 1 << ".이름: " << tStoreArmor[i].strName <<
								"\t종류 :" << tStoreArmor[i].strTypeName << endl;

							cout << "공격력: " << tStoreArmor[i].iMin << " - " <<
								tStoreArmor[i].iMax << endl;

							cout << "판매가격: " << tStoreArmor[i].iPrice <<
								"\t구매가격: " << tStoreArmor[i].iSell << endl;

							cout << "설명: " << tStoreArmor[i].strDesc << endl << endl;
						}

						cout << STORE_ARMOR_MAX + 1 << ".뒤로가기" << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요: ";
						cin >> iMenu;

						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (iMenu == STORE_ARMOR_MAX + 1)
							break;

						else if (iMenu < 1 || iMenu > STORE_ARMOR_MAX)
						{
							cout << "잘못 선택하였습니다. " << endl;
							system("pasue");
							continue;
						}

						//상점판매목록 배열의 인덱스를 구해준다.
						int iArmorIndex = iMenu - 1;

						//인벤토리가 꽉 찼는지 검사한다.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다. " << endl;
							system("pause");
							continue;
						}

						//돈이 부족할 경우
						else if (tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice)
						{
							cout << "보유금액이 부족합니다. " << endl;
							system("pause");
							continue;
						}

						//처음에 iItemCount는 하나도 추가되어있지 않기 때문에 0으로 초기화
						//되어 있으므로 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고
						//카운트가 1이 된다. 다음번에 추가할때는 1번 인덱스에 추가하게 된다.
						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreArmor[iArmorIndex];
						++tPlayer.tInventory.iItemCount;

						//골드를 차감한다.
						tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;

						cout << tStoreArmor[iArmorIndex].strName << "아이템을 구매하였습니다." << endl;
						system("pause");

					}
					break;
				}


			}
			break;
		case MM_INVENTORY:
			system("cls");

			cout << "******************가방******************" << endl;

			cout << "******************PLAYER******************" << endl;
			cout << "이름 : " << tPlayer.strName << "\t직업 : " <<
				tPlayer.strJobName << endl;

			cout << "레벨 : " << tPlayer.iLevel << "\t경험치 : " <<
				tPlayer.iExp << endl;

			cout << "공격력 : " << tPlayer.iAtackMin << " - " <<
				tPlayer.iArmorMax << "\t방어력 :" << tPlayer.iArmorMin <<
				" - " << tPlayer.iArmorMax << endl;

			cout << "체력 : " << tPlayer.iHP << "/ " << tPlayer.iHPMax <<
				"마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

			cout << "보유골드 : " << tPlayer.tInventory.iGold << "GOLD " << endl << endl;

			for (int i = 0; tPlayer.tInventory.iItemCount; ++i)
			{
				cout << i + 1 << ".이름: " << tPlayer.tInventory.tItem[i].strName <<
					"\t종류 :" << tPlayer.tInventory.tItem[i].strTypeName << endl;

				cout << "공격력: " << tPlayer.tInventory.tItem[i].iMin << " - " <<
					tPlayer.tInventory.tItem[i].iMax << endl;

				cout << "판매가격: " << tPlayer.tInventory.tItem[i].iPrice <<
					"\t구매가격: " << tPlayer.tInventory.tItem[i].iSell << endl;

				cout << "설명: " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
			}

			system("pause");

			break;
		default:
			cout << "잘못 선택하였습니다. " << endl;
			break;
		}
	}

	return 0;
}