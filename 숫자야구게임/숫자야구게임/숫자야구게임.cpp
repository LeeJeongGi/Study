#include<iostream>
#include<time.h>

using namespace std;

/*
숙제 : 야구게임 만들기
1~9사이의 랜덤한 숫자 3개를 얻어온다.단 숫자는 중복되어서는 안된다
3개의 숫자는 ***의 형태로 출력되고 이 3개의 숫자를 맞추는 게임이다
사용자는 이 3개의 숫자를 맞출때까지 걔속해서 3개씩 숫자를입력한다.
만약 맞춰야할 숫자가 7 3 8 일 경우
사용자는 3개의 숫자를 계속 입력한다.
입력 : 1 2 3를 입력했을 경우 1 2 3 는 맞춰야할 숫자중 아무것도 없으므로 out을 출력한다
입력 : 7 8 9 를 입력했을 경우 7은 맞춰야할 숫자중 있고 위치도 같으므로 스트라이크이다.

즉 이렇게 출력을 하고 입력을 받으면서 최종적으로 3개의 숫자들 자리까지 모두 일치하게
입력하면 게임이 종료된다
*/

//1. 1~9까지 숫자 3개를 얻어온다.
//2. ***출력.(중복 x)
//3. 
int main()
{
	srand((unsigned int)time(0));
	int iNum[3] = { 0 };
	int My_num[3] = { 0 };

	int Ball = 0, Strike = 0;

	while (1)
	{
		cout << "정답은 ? :";
		for (int i = 0; i < 3; ++i)
		{
			iNum[i] = rand() % 9 + 1;

			cout << iNum[i] << " ";
		}
		cout << endl;
		cout << "****************************" << endl;
		cout << "* * *" << endl;

		if (iNum[0] == iNum[1] || iNum[0] == iNum[2] || iNum[1] == iNum[2])
		{
			cout << "중복된 숫자를 입력하지 마세요." << endl;
			continue;
		}
		else
			break;

	}
	while (1)
	{
		
		cout << "정답을 입력해주세요" << endl;
		cin >> My_num[0] >> My_num[1] >> My_num[2];

		if (My_num[0] == My_num[1] || My_num[0] == My_num[2] || My_num[1] == My_num[2])
		{
			cout << "중복된 숫자를 입력하였습니다." << endl;
			continue;
		}
		else if (My_num[0] < 0 || My_num[0]>9 || My_num[1] < 0 || My_num[1]>9 || My_num[2] < 0 || My_num[2]>9)
		{
			cout << "숫자를 잘못 입력하였습니다." << endl;
			continue;
		}
		else if (My_num[0] == 0 || My_num[1] == 0 || My_num[2] == 0)
		{
			cout << "0을 입력하지 말아주세요" << endl;
			continue;
		}

		Strike = 0;
		Ball = 0;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (iNum[i] == My_num[j])
				{
					if (i == j)
						++Strike;
					else
						++Ball;
					break;
				}
			}
		}

		if (Strike == 3)
		{
			cout << "정답을 맞췄습니다." << endl;
			break;
		}
		else if (Strike == 0 && Ball == 0)
		{
			cout << "Out" << endl;
		}

		else
		{
			cout << Strike << "Strike" << " " << Ball << "Ball" << endl;
		}
	}

	return 0;
}