#include<iostream>
using namespace std;

//#define NAME_SIZE 32
//
///*
//구조체 : 관련있는 변수들을 모아서 하나의 새로운 타입을 만들어주는 기능이다.
//사용자정의 변수 타입이다.
//형태 : strunc 구조체명 {}; 형태로 구성된다.
//배열과 구조체의 공통점 :
//1.데이터의 집합니다.
//2.연속된 메모리 블럭에 해당한다.구조체 멤버들은 연속된 메모리 블럭으로
//잡히게 된다.
//*/
//
//struct _tagStudent
//{
//	char	strName[NAME_SIZE];
//	int		iNumber;
//	int		iKor;
//	int		iEng;
//	int		iMath;
//	int		iTotal;
//	float	fAvg;
//
//};
//
//int main()
//{
//	_tagStudent tStudent = {};
//	_tagStudent tStudentarr[100] = {};
//
//	//구조체 멤버에 접근할때는 .을 이용해서 접근하게 된다.
//	tStudent.iKor = 100;
//
//	//tStudent.strName = "이정기";
//	//문자열을 배열에 넣어줄 때에는 단순 대입으로는 불가능하다
//	//strcpy_s라는 함수를 이용해서 문자열을 복사해 주어야 한다.
//	strcpy_s(tStudent.strName, "이정기");
//
//	//strcat_s 함수는 문자열을 붙여주는 기능이다.
//	//오른쪽에 있는 문자열을 왼쪽에 붙여준다
//	strcat_s(tStudent.strName, "아무개 ");
//
//	//strcmp 함수는 두 문자열을 비교하여 같을 경우 0을 반환하고 다를 경우
//	//0이 아닌 값을 반환한다.
//	strcpy_s(tStudent.strName, "이정기");
//
//	cout << "비교할 이름을 입력하세요 " << endl;
//	char strName2[NAME_SIZE] = {};
//	cin >> strName2;
//
//	if (strcmp(tStudent.strName, strName2) == 0)
//	{
//		cout << "학생을 찾았습니다. " << endl;
//	}
//	else
//	{
//		cout << "학생이 없습니다. " << endl;
//	}
//
//	//문자열의 끝은 항상 0(NULL)로 끝나야 한다.그런데 쓰레기값이 들어가 있는
//	//상태에서 아래처럼 각 배열 요소에 값을 넣어주게 되면 그 값이 출력되고
//	//넣어주지 않은 부분은 쓰레기값으로 그대로 출력된다.왜냐하면 출력할때
//	//문자열의 끝을 인식할 수 없기 때문이다.
//
//	cout << "이름 길이: " << strlen(tStudent.strName) << endl;
//	cout << "이름 길이: " << sizeof(tStudent.strName) << endl;
//	
//
//	cout << "이름 :" << tStudent.strName << endl;
//	cout << "학번 :" << tStudent.iNumber << endl;
//	cout << "국어 :" << tStudent.iKor << endl;
//	cout << "영어 :" << tStudent.iEng << endl;
//	cout << "수학 :" << tStudent.iMath << endl;
//	cout << "총점 :" << tStudent.iTotal << endl;
//	cout << "평균 :" << tStudent.fAvg << endl;
//
//	return 0;
//}

//학생 관리 프로그램
#define NAME_SIZE		32
#define STUDENT_MAX		10
#define ADDRESS_SIZE	128
#define PHONE_SIZE		14

struct _tagStudent
{
	char	strName[NAME_SIZE];
	char	strAddrss[ADDRESS_SIZE];
	char	strPhoneNumber[PHONE_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};


int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	//배열에 추가된 개수를 지정할 변수를 만들어준다.
	int iStudentConut = 0;
	int iStdNumber = 1;
	char strSearchName[NAME_SIZE] = {};

	while (true)
	{
		system("cls");

		//메뉴를 출력하라.
		cout << "1. 학생등록 " << endl;
		cout << "2. 학생삭제  " << endl;
		cout << "3. 학생탐색 " << endl;
		cout << "4. 학생출력 " << endl;
		cout << "5. 종료 " << endl;
		cout << "메뉴를 선택하세요 :";
		int iMenu;
		cin >> iMenu;

		//cin은 만약 오른쪽에 int변수가 오면 정수를 입력해야 한다.오른쪽에
		//오는 변수 타입에 맞춰서 값을 입력해야 하는데 실수로 정수가 아닌
		//문자를 입력할 경우 에러가 발생한다.
		//그렇게 때문에 예외처리로 에러가 발생했는지를 여기에서 체크하여
		//에러가 발생하면 cin내부의 에러버퍼를 비워주고 cin내부에 입력버퍼가 있는데
		//입력버퍼는 입력한 값을 저장 해놓고 그 값을 변수에 넣어주는 역할을 한다.
		//이 입력버퍼에 \n이 남아있으므로 버퍼를 순회햐여 \n을 지워준다.
		//버퍼 : 임시저장공간이다.
		//먼저 에러를 체크한다.
		//먼저 에러를 체크한다.cin.fail()을 했을때 입력에러가 발생했을
		//경우 true를 반환한다.
		if (cin.fail())
		{
			//에러버퍼를 비워준다.
			cin.clear();

			//입력버퍼에 \n이 남아있으므로 입력버퍼를 검색하여 \n을 지워준다.
			//첫번째는 검색하고자 하는 버퍼 크기를 지정한다.넉넉하게 1024
			//바이트로 지정해주었다.두번째는 찾고자 하는 문자를 넣어준다.
			//그래서 입력버퍼 처음부터 \n이 있는 곳까지 찾아서 그부분을
			//모두 지워줘서 다시 입력받을 수 있도록 해준다.
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;

		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "============================학생추가=====================" << endl;

			//등록된 학생이 등록할 수 있는 최대치일 경우 더이상 등록이
			//안되게 막는다.
			if (iStudentConut == STUDENT_MAX)
				break;

			//학생정보를 추가한다.학생정보는,이름,주소,전화번호,
			//국어,영어,수학 점수는 입력받고 학번,총점,평균은 연산을
			//통해 계산해준다.
			//이름을 입력받는다.
			cout << "이름 : ";
			cin >> tStudentArr[iStudentConut].strName;

			cin.ignore(1024, '\n');

			cout << "주소 : ";
			cin.getline(tStudentArr[iStudentConut].strAddrss, ADDRESS_SIZE);

			cout << "전화번호 :";
			cin.getline(tStudentArr[iStudentConut].strPhoneNumber, PHONE_SIZE);

			cout << "국어 :";
			cin >> tStudentArr[iStudentConut].iKor;

			cout << "영어 :";
			cin >> tStudentArr[iStudentConut].iEng;

			cout << "수학 :";
			cin >> tStudentArr[iStudentConut].iMath;

			tStudentArr[iStudentConut].iTotal =
				tStudentArr[iStudentConut].iKor +
				tStudentArr[iStudentConut].iEng +
				tStudentArr[iStudentConut].iMath;
			tStudentArr[iStudentConut].fAvg =
				tStudentArr[iStudentConut].iTotal / 3.f;

			tStudentArr[iStudentConut].iNumber = iStdNumber;

			++iStdNumber;
			++iStudentConut;


			break;
		case MENU_DELETE:
			system("cls");
			cout << "==========================학생출력=========================" << endl;

			cin.ignore(1024, '\n');
			cout << "삭제할 이름을 입력하세요: ";
			cin.getline(strSearchName, NAME_SIZE);

			//등록되어있는 학생 수만틈 반복하여 학생을 찾는다.
			for (int i = 0; i < iStudentConut; ++i)
			{
				//학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0)
				{
					for (int j = i; j < iStudentConut; ++j)
					{
						tStudentArr[i] = tStudentArr[i + 1];
					}
					--iStudentConut;

					cout << "학생을 삭제하였습니다 " << endl;
					break;
				}
			}


			break;
		case MENU_SEARCH:
			system("cls");
			cout << "==========================학생출력=========================" << endl;

			cin.ignore(1024, '\n');
			cout << "탐색할 이름을 입력하세요: ";
			cin.getline(strSearchName, NAME_SIZE);

			//등록되어있는 학생 수만큼 반복하며 학생을 찾는다
			for (int i = 0; i < iStudentConut; ++i)
			{
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0)
				{
					cout << "이름 : " << tStudentArr[i].strName << endl;
					cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
					cout << "주소 : " << tStudentArr[i].strAddrss << endl;
					cout << "학번 : " << tStudentArr[i].iNumber << endl;
					cout << "국어 : " << tStudentArr[i].iKor << endl;
					cout << "영어 : " << tStudentArr[i].iEng << endl;
					cout << "수학 : " << tStudentArr[i].iMath << endl;
					cout << "총점 : " << tStudentArr[i].iTotal << endl;
					cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;;
					break;
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "============================학생출력=========================" << endl;

			//등록된 학생 수만틈 반복하며 학생정보를 출력한다.
			for (int i = 0; i < iStudentConut; ++i)
			{
				cout << "이름 : " << tStudentArr[i].strName << endl;
				cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
				cout << "주소 : " << tStudentArr[i].strAddrss << endl;
				cout << "학번 : " << tStudentArr[i].iNumber << endl;
				cout << "국어 : " << tStudentArr[i].iKor << endl;
				cout << "영어 : " << tStudentArr[i].iEng << endl;
				cout << "수학 : " << tStudentArr[i].iMath << endl;
				cout << "총점 : " << tStudentArr[i].iTotal << endl;
				cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;;
			}
			break;
		default:
			cout << " 메뉴를 잘못 선택했습니다. " << endl;
		}

		system("pause");

	}

	return 0;
}
