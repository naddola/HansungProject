//5월 7일 DB연동 시작!
#include <windows.h> 
#include <stdio.h>

#include "sql.h" 
#include "sqlext.h" 

#pragma warning(disable : 4996)

int displayMenu();
void err(int *s);

int bossMenu();
int	printBoss(SQLHSTMT hstmt);
void insertBoss(SQLHSTMT hstmt);
int deleteBoss(SQLHSTMT hstmt);
int searchBossMenu();
int searchBoss(SQLHSTMT hstmt, int select);

int memberMenu();
int printMember(SQLHSTMT hstmt);
void insertMember(SQLHSTMT hstmt);
int deleteMember(SQLHSTMT hstmt);
int searchMemberMenu();
int searchMember(SQLHSTMT hstmt, int select);

int areaMenu();
int printArea(SQLHSTMT hstmt);
void insertArea(SQLHSTMT hstmt);
int deleteArea(SQLHSTMT hstmt);
int searchAreaMenu();
int searchArea(SQLHSTMT hstmt, int select);

int departMenu();
int printDepart(SQLHSTMT hstmt);
void insertDepart(SQLHSTMT hstmt);
int deleteDepart(SQLHSTMT hstmt);
int searchDepartMenu();
int searchDepart(SQLHSTMT hstmt, int select);



int main(int argc, char* argv[]){
	SQLHENV		henv;	
	SQLHDBC		hdbc;	
	SQLHSTMT	hstmt;	
	SQLRETURN	rc;

	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	rc = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
	SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (void*)5, 0);
	rc = SQLConnect(hdbc, (SQLCHAR*)"UniversityDBODBC", SQL_NTS, 
		(SQLCHAR*)"jmLee", SQL_NTS, (SQLCHAR*)"xxxx", SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) goto DONE1;
	rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) goto DONE2;

	int select;

	do{
		select = displayMenu();
		switch(select){

			//목회자메뉴
		case 1:
			switch(bossMenu()){
		case 1:
			printBoss(hstmt);
			system("PAUSE");
			break;
		case 2: 
			insertBoss(hstmt);
			break;
		case 3:
			deleteBoss(hstmt);
			break;
			//검색
		case 4:
			searchBoss(hstmt,searchBossMenu());
			break;
		case 5:
			break;
		default:
			printf("		잘못된 입력입니다.\n");
			printf("		처음으로 돌아갑니다.\n");
			system("PAUSE");
			}
			break;

			//성도 메뉴
		case 2:
			switch(memberMenu()){
		case 1:
			printMember(hstmt);
			system("PAUSE");
			break;
		case 2:
			insertMember(hstmt);
			break;
		case 3:
			deleteMember(hstmt);
			break;
		case 4:
			searchMember(hstmt, searchMemberMenu());
			break;
		case 5:
			break;
		default:
			printf("		잘못된 입력입니다.\n");
			printf("		처음으로 돌아갑니다.\n");
			system("PAUSE");
			}
			break;

			//구역메뉴
		case 3:
			switch(areaMenu()){
		case 1:
			printArea(hstmt);
			system("PAUSE");
			break;
		case 2:
			insertArea(hstmt);
			break;
		case 3:
			deleteArea(hstmt);
			break;
		case 4:
			searchArea(hstmt, searchAreaMenu());
			break;
		case 5:
			break;
		default:
			printf("		잘못된 입력입니다.\n");
			printf("		처음으로 돌아갑니다.\n");
			system("PAUSE");
			}
			break;

			//부서메뉴
		case 4:
			switch(departMenu()){
		case 1:
			printDepart(hstmt);
			system("PAUSE");
			break;
		case 2:
			insertDepart(hstmt);
			break;
		case 3:
			deleteDepart(hstmt);
			break;
		case 4:
			searchDepart(hstmt, searchDepartMenu());
			break;
		case 5:
			break;
		default:
			printf("		잘못된 입력입니다.\n");
			printf("		처음으로 돌아갑니다.\n");
			system("PAUSE");
			}
			break;
		case 5:
			printf("\n		프로그램을 종료합니다.\n\n");
			break;
		default:
			printf("		잘못된 입력입니다.\n");
			printf("		처음으로 돌아갑니다.\n");
			system("PAUSE");
		}
	}while(select!=5);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

DONE2:
	SQLDisconnect(hdbc);
DONE1:
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return 0;
}

int displayMenu()
{
	int select;
	system("cls");
	printf("\n\n==============================교회관리 System=================================");
	printf("\n\n		1. 목회자 관리\n");
	printf("		2. 성도 관리\n");
	printf("		3. 구역 관리\n");
	printf("		4. 부서 관리\n");
	printf("		5. 종료\n");
	printf("\n		메뉴를 선택하세요 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

void err(int *s)
{
	int temp=0;
	while(temp!=1){
		fflush(stdin);
		printf("\n		잘못된 입력입니다.");
		printf("\n		다시 입력하세요 : ");
		temp=scanf("%d", s);
	}
}

int bossMenu()
{
	int select;
	system("cls");
	printf("\n\n================================목회자 관리====================================");
	printf("\n\n		1. 모든 목회자 보기\n");
	printf("		2. 목회자 추가\n");
	printf("		3. 목회자 삭제\n");
	printf("		4. 목회자 검색\n");
	printf("		5. 이전 메뉴\n");
	printf("\n		메뉴를 선택하세요 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int	printBoss(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================모든 목회자 보기=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		ssn[16], name[11], address[20], phone[15], grade[11], area[4], depart[8];

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT 주민등록번호,이름,주소,전화번호,직위,구역코드,부서코드 from 목회자",SQL_NTS);

	printf("  주민등록번호    이름       주소	  전화번호   	직위	구역   부서\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, ssn, 15, &indicate);
		if(indicate > 0)	ssn[indicate]= 0;
		else				ssn[0]= 0;
		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, address, 19, &indicate);
		SQLGetData(hstmt, 4, SQL_C_CHAR, phone, 14, &indicate);  //얘는 long이니까 4byte인거 알아
		SQLGetData(hstmt, 5, SQL_C_CHAR, grade, 10, &indicate);
		SQLGetData(hstmt, 6, SQL_C_CHAR, area, 3, &indicate);
		SQLGetData(hstmt, 7, SQL_C_CHAR, depart, 7, &indicate);
		printf("%15s|%8s|%13s|%14s|%10s|%3s|%7s|\n",ssn, name, address, phone, grade, area, depart);
	}
	printf("\n");
	return 0;
}

void insertBoss(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================목회자 추가=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char ssn[16], name[11], address[20], phone[15], grade[11], area[4], depart[8];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("목회자 주민등록번호  (예)881230-1152132\n      입력 : ");
	scanf("%s",ssn);
	printf("목회자 이름 (예) 전떵개\n      입력 : ");
	scanf("%s",name);
	printf("목회자 주소 (예) 서울시 강서구\n      입력 : ");
	scanf("%s",address);
	printf("목회자 전화번호 (예) 010-5542-5482\n      입력 :  ");
	scanf("%s",phone);
	printf("목회자 직위 (예) 목사\n      입력 : ");
	scanf("%s",grade);
	printf("목회자 구역코드 (예) 02\n      입력 : ");
	scanf("%s",area);
	printf("목회자 부서코드 (예) EDU004\n      입력 : ");
	scanf("%s",depart);

	sprintf(strBuf, "insert into 목회자 values ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", ssn, name, address, phone, grade, area, depart);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);

}

int deleteBoss(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================목회자 삭제=================================\n\n");
	SQLRETURN rc;

	printBoss(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n삭제를 원하는 목회자 주민등록번호을 입력 : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM 목회자 WHERE 주민등록번호='%s'", temp);
	printf("%s",strBuf);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchBossMenu()
{
	int select=0;
	printf("\n\n		1. 이름으로 검색\n");
	printf("		2. 주민등록번호로 검색\n");
	printf("		3. 구역코드로 검색\n");
	printf("		4. 부서코드로 검색\n");
	printf("		5. 취소\n\n");
	printf("		원하시는 입력방법을 선택 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchBoss(SQLHSTMT hstmt, int select)
{
	SQLRETURN	rc;

	if(select==5)
		return 0;
	else if(select > 5){
		printf("		잘못된 입력입니다.\n");
		printf("		처음으로 돌아갑니다.\n");
		system("PAUSE");
		return 0;
	}
	
	char searchBuf[200];
	char temp[100];
	char selectBuf[50];
	long indicate;
	long count;
	char		ssn[16], name[11], address[20], phone[15], grade[11], area[4], depart[8];

	printf("		검색어 입력 : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리
	switch(select){
		case 1:
			strcpy(selectBuf,"이름");
			break;
		case 2:
			strcpy(selectBuf,"주민등록번호");
			break;
		case 3:
			strcpy(selectBuf, "구역코드");
			break;
		case 4:
			strcpy(selectBuf, "부서코드");
			break;
	}

	sprintf(searchBuf,"SELECT count(이름) FROM 목회자 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	sprintf(searchBuf,"SELECT 주민등록번호, 이름, 주소, 전화번호, 직위, 구역코드, 부서코드 FROM 목회자 WHERE %s like '%%%s%%'",selectBuf,temp);

	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	system("cls");
	printf("\n\n===============================목회자 검색=================================\n\n");
	printf("        '%s'의 검색 결과 %d개 검색되었습니다.\n\n",temp, count);

	rc = SQLFetch(hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("데이터가 존재하지 않습니다.\n");
		system("PAUSE");
		return 0;
	}
	printf("  주민등록번호    이름       주소	  전화번호   	직위	구역   부서\n");
	while (TRUE) {
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, ssn, 15, &indicate);
		if(indicate > 0)	ssn[indicate]= 0;
		else				ssn[0]= 0;
		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, address, 19, &indicate);
		SQLGetData(hstmt, 4, SQL_C_CHAR, phone, 14, &indicate);
		SQLGetData(hstmt, 5, SQL_C_CHAR, grade, 10, &indicate);
		SQLGetData(hstmt, 6, SQL_C_CHAR, area, 3, &indicate);
		SQLGetData(hstmt, 7, SQL_C_CHAR, depart, 7, &indicate);
		printf("%15s|%8s|%13s|%14s|%10s|%3s|%7s|\n",ssn, name, address, phone, grade, area, depart);
		rc = SQLFetch(hstmt);
	}
	printf("\n");
	system("PAUSE");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// 성도 관리
int memberMenu()
{
	int select;
	system("cls");
	printf("\n\n================================성도 관리====================================");
	printf("\n\n		1. 모든 성도 보기\n");
	printf("		2. 성도 추가\n");
	printf("		3. 성도 삭제\n");
	printf("		4. 성도 검색\n");
	printf("		5. 이전 메뉴\n");
	printf("\n		메뉴를 선택하세요 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int printMember(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================모든 성도 보기=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		ssn[11], name[11], address[20], phone[15], grade[8], area[4], depart[8];
	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT 등록번호,이름,주소,전화번호,직위,구역코드,부서코드 from 성도",SQL_NTS);


	printf("  등록번호     이름       주소	         전화번호       직위    구역   부서\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, ssn, 10, &indicate);

		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, address, 19, &indicate);
		SQLGetData(hstmt, 4, SQL_C_CHAR, phone, 14, &indicate);
		if(indicate > 0)	phone[indicate]= 0;
		else				phone[0]= 0;
		SQLGetData(hstmt, 5, SQL_C_CHAR, grade, 7, &indicate);
		SQLGetData(hstmt, 6, SQL_C_CHAR, area, 3, &indicate);
		SQLGetData(hstmt, 7, SQL_C_CHAR, depart, 7, &indicate);

		printf("%10s |%8s |%13s |%14s |%7s |%5s |%7s |\n",ssn, name, address, phone, grade, area, depart);
	}
	printf("\n");
	return 0;
}

void insertMember(SQLHSTMT hstmt)
{
	system("cls");
	printf("\n\n===============================성도 추가=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char ssn[11], name[11], address[20], phone[15], grade[8], area[4], depart[8];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("성도 등록번호 (예) 2012-0120\n      입력 : ");
	scanf("%s",ssn);
	printf("성도 이름 (예) 전떵개\n      입력 : ");
	scanf("%s",name);
	printf("성도 주소 (예) 서울시 강서구\n      입력 : ");
	scanf("%s",address);
	printf("성도 전화번호 (예) 010-8542-6324\n      입력 : ");
	scanf("%s",phone);
	printf("성도 직위 (예) 장로\n      입력 : ");
	scanf("%s",grade);
	printf("성도 구역코드 (예) 01\n      입력 : ");
	scanf("%s",area);
	printf("성도 부서코드 (예) EDU004\n      입력 : ");
	scanf("%s",depart);

	sprintf(strBuf, "insert into 성도 values ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", ssn, name, address, phone, grade, area, depart);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);

}

int deleteMember(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================성도 삭제=================================\n\n");
	SQLRETURN rc;

	printMember(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n삭제를 원하는 성도 등록번호을 입력 : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM 성도 WHERE 등록번호='%s'", temp);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchMemberMenu()
{
	int select=0;
	printf("\n\n		1. 이름으로 검색\n");
	printf("		2. 등록번호로 검색\n");
	printf("		3. 구역코드로 검색\n");
	printf("		4. 부서코드로 검색\n");
	printf("		5. 취소\n\n");
	printf("		원하시는 입력방법을 선택 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchMember(SQLHSTMT hstmt, int select)
{
	if(select == 5)
		return 0;
	else if(select > 5){
		printf("		잘못된 입력입니다.\n");
		printf("		처음으로 돌아갑니다.\n");
		system("PAUSE");
		return 0;
	}
	SQLRETURN	rc;

	long count;
	char searchBuf[200];
	char temp[100];
	char selectBuf[50];
	long indicate;
	char ssn[11], name[11], address[20], phone[15], grade[8], area[4], depart[8];

	printf("		검색어 입력 : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리
	switch(select){
		case 1:
			strcpy(selectBuf,"이름");
			break;
		case 2:
			strcpy(selectBuf,"등록번호");
			break;
		case 3:
			strcpy(selectBuf, "구역코드");
			break;
		case 4:
			strcpy(selectBuf, "부서코드");
			break;
	}

	sprintf(searchBuf,"SELECT count(이름) FROM 성도 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	sprintf(searchBuf,"SELECT 등록번호, 이름, 주소, 전화번호, 직위, 구역코드, 부서코드 FROM 성도 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	system("cls");
	printf("\n\n==============================성도 검색=================================\n\n");
	printf("        '%s'의 검색 결과 %d개 검색 되었습니다.\n\n",temp, count);

	rc = SQLFetch(hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("데이터가 존재하지 않습니다.\n");
		system("PAUSE");
		return 0;
	}
	printf("  등록번호     이름       주소	         전화번호       직위    구역   부서\n");
	while (TRUE) {
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, ssn, 10, &indicate);

		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, address, 19, &indicate);
		SQLGetData(hstmt, 4, SQL_C_CHAR, phone, 14, &indicate);
		if(indicate > 0)	phone[indicate]= 0;
		else				phone[0]= 0;
		SQLGetData(hstmt, 5, SQL_C_CHAR, grade, 7, &indicate);
		SQLGetData(hstmt, 6, SQL_C_CHAR, area, 3, &indicate);
		SQLGetData(hstmt, 7, SQL_C_CHAR, depart, 7, &indicate);
		printf("%10s |%8s |%13s |%14s |%7s |%5s |%7s |\n",ssn, name, address, phone, grade, area, depart);
		rc = SQLFetch(hstmt);
	}
	printf("\n");
	system("PAUSE");
	return 0;
}

int areaMenu()
{
	int select;
	system("cls");
	printf("\n\n================================구역 관리====================================");
	printf("\n\n		1. 모든 구역 보기\n");
	printf("		2. 구역 추가\n");
	printf("		3. 구역 삭제\n");
	printf("		4. 구역 검색\n");
	printf("		5. 이전 메뉴\n");
	printf("\n		메뉴를 선택하세요 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int printArea(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================모든 구역 보기=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		areaCode[5], name[11], areaNum[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT 구역코드, 구역명, 등록번호 from 구역",SQL_NTS);

	printf("  구역코드     구역명      등록번호\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, areaCode, 4, &indicate);

		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, areaNum, 10, &indicate);

		printf("%6s     |%8s   |%12s   |\n",areaCode, name, areaNum);
	}
	printf("\n");
	return 0;
}

void insertArea(SQLHSTMT hstmt)
{
	system("cls");
	printf("\n\n===============================구역 추가=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char areaCode[5], name[11], areaNum[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("구역코드 (예) 01\n      입력 : ");
	scanf("%s", areaCode);
	printf("구역명 (예) 사랑\n      입력 : ");
	scanf("%s",name);
	printf("등록번호 (예) 2012-0012\n      입력 : ");
	scanf("%s", areaNum);

	sprintf(strBuf, "insert into 구역 values ('%s', '%s', '%s');", areaCode, name, areaNum);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);
}


int deleteArea(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================구역 삭제=================================\n\n");
	SQLRETURN rc;

	printArea(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n삭제를 원하는 구역 코드 입력 : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM 구역 WHERE 구역코드='%s'", temp);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchAreaMenu()
{
	int select=0;
	printf("\n\n		1. 구역명으로 검색\n");
	printf("		2. 구역코드로 검색\n");
	printf("		3. 등록번호로 검색\n");
	printf("		4. 취소\n\n");
	printf("		원하시는 입력방법을 선택 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchArea(SQLHSTMT hstmt, int select)
{
	if(select == 4)
		return 0;
	else if(select > 5){
		printf("		잘못된 입력입니다.\n");
		printf("		처음으로 돌아갑니다.\n");
		system("PAUSE");
		return 0;
	}
	SQLRETURN	rc;

	char searchBuf[200];
	char temp[100];
	char selectBuf[50];
	long indicate;
	long count;
	char areaCode[5], name[11], areaNum[11];

	printf("		검색어 입력 : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리
	switch(select){
		case 1:
			strcpy(selectBuf,"구역명");
			break;
		case 2:
			strcpy(selectBuf,"구역코드");
			break;
		case 3:
			strcpy(selectBuf, "등록번호");
			break;
	}

	sprintf(searchBuf,"SELECT count(구역명) FROM 구역 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);


	sprintf(searchBuf,"SELECT 구역코드, 구역명, 등록번호 FROM 구역 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("데이터가 존재하지 않습니다.\n");
		system("PAUSE");
		return 0;
	}

	system("cls");
	printf("\n\n===============================구역 검색=================================\n\n");
	printf("        '%s'의 검색 결과 %d개 검색되었습니다.\n\n",temp, count);


	printf("  구역코드     구역명      등록번호\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, areaCode, 4, &indicate);

		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, areaNum, 10, &indicate);

		printf("%6s     |%8s   |%12s   |\n",areaCode, name, areaNum);
	}
	printf("\n");
	system("PAUSE");
	return 0;
}



int departMenu()
{
	int select;
	system("cls");
	printf("\n\n================================부서관리====================================");
	printf("\n\n		1. 모든 부서 보기\n");
	printf("		2. 부서 추가\n");
	printf("		3. 부서 삭제\n");
	printf("		4. 부서 검색\n");
	printf("		5. 이전 메뉴\n");
	printf("\n		메뉴를 선택하세요 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int printDepart(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================모든 부서 보기=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		departCode[8], name[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT 부서코드, 부서명 from 부서",SQL_NTS);

	printf("  부서코드     부서명\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, departCode, 7, &indicate);

		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);

		printf("  %6s   |%9s |\n",departCode, name);
	}
	printf("\n");
	return 0;
}


void insertDepart(SQLHSTMT hstmt)
{
	system("cls");
	printf("\n\n===============================부서 추가=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char departCode[8], name[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("부서코드 (예) 01\n      입력 : ");
	scanf("%s", departCode);
	printf("부서명 (예) 초등부\n      입력 : ");
	scanf("%s",name);

	sprintf(strBuf, "insert into 부서 values ('%s', '%s');", departCode, name);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);
}

int deleteDepart(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================부서 삭제=================================\n\n");
	SQLRETURN rc;

	printDepart(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n삭제를 원하는 부서 코드 입력 : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM 부서 WHERE 부서코드='%s'", temp);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchDepartMenu()
{
	int select=0;
	printf("\n\n		1. 부서명으로 검색\n");
	printf("		2. 부서코드로 검색\n");
	printf("		3. 취소\n\n");
	printf("		원하시는 입력방법을 선택 : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchDepart(SQLHSTMT hstmt, int select)
{
	if(select == 3)
		return 0;
	else if(select > 5){
		printf("		잘못된 입력입니다.\n");
		printf("		처음으로 돌아갑니다.\n");
		system("PAUSE");
		return 0;
	}
	SQLRETURN	rc;

	char searchBuf[200];
	char temp[100];
	char selectBuf[50];
	long indicate;
	long count;
	char departCode[8], name[11];

	printf("		검색어 입력 : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH에 붙은 찌꺼기 처리
	switch(select){
		case 1:
			strcpy(selectBuf,"부서명");
			break;
		case 2:
			strcpy(selectBuf,"부서코드");
			break;
	}

	sprintf(searchBuf,"SELECT count(부서명) FROM 부서 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	sprintf(searchBuf,"SELECT 부서코드, 부서명 FROM 부서 WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("데이터가 존재하지 않습니다.\n");
		system("PAUSE");
		return 0;
	}

	system("cls");
	printf("\n\n===============================부서 검색=================================\n\n");
	printf("        '%s'의 검색 결과 %d개 검색되었습니다.\n\n",temp, count);


	printf("  부서코드     부서명\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, departCode, 7, &indicate);

		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);

		printf("  %6s   |%9s |\n",departCode, name);
	}
	printf("\n");
	system("PAUSE");
	return 0;
}



