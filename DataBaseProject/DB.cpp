//5�� 7�� DB���� ����!
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

			//��ȸ�ڸ޴�
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
			//�˻�
		case 4:
			searchBoss(hstmt,searchBossMenu());
			break;
		case 5:
			break;
		default:
			printf("		�߸��� �Է��Դϴ�.\n");
			printf("		ó������ ���ư��ϴ�.\n");
			system("PAUSE");
			}
			break;

			//���� �޴�
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
			printf("		�߸��� �Է��Դϴ�.\n");
			printf("		ó������ ���ư��ϴ�.\n");
			system("PAUSE");
			}
			break;

			//�����޴�
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
			printf("		�߸��� �Է��Դϴ�.\n");
			printf("		ó������ ���ư��ϴ�.\n");
			system("PAUSE");
			}
			break;

			//�μ��޴�
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
			printf("		�߸��� �Է��Դϴ�.\n");
			printf("		ó������ ���ư��ϴ�.\n");
			system("PAUSE");
			}
			break;
		case 5:
			printf("\n		���α׷��� �����մϴ�.\n\n");
			break;
		default:
			printf("		�߸��� �Է��Դϴ�.\n");
			printf("		ó������ ���ư��ϴ�.\n");
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
	printf("\n\n==============================��ȸ���� System=================================");
	printf("\n\n		1. ��ȸ�� ����\n");
	printf("		2. ���� ����\n");
	printf("		3. ���� ����\n");
	printf("		4. �μ� ����\n");
	printf("		5. ����\n");
	printf("\n		�޴��� �����ϼ��� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

void err(int *s)
{
	int temp=0;
	while(temp!=1){
		fflush(stdin);
		printf("\n		�߸��� �Է��Դϴ�.");
		printf("\n		�ٽ� �Է��ϼ��� : ");
		temp=scanf("%d", s);
	}
}

int bossMenu()
{
	int select;
	system("cls");
	printf("\n\n================================��ȸ�� ����====================================");
	printf("\n\n		1. ��� ��ȸ�� ����\n");
	printf("		2. ��ȸ�� �߰�\n");
	printf("		3. ��ȸ�� ����\n");
	printf("		4. ��ȸ�� �˻�\n");
	printf("		5. ���� �޴�\n");
	printf("\n		�޴��� �����ϼ��� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int	printBoss(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================��� ��ȸ�� ����=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		ssn[16], name[11], address[20], phone[15], grade[11], area[4], depart[8];

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT �ֹε�Ϲ�ȣ,�̸�,�ּ�,��ȭ��ȣ,����,�����ڵ�,�μ��ڵ� from ��ȸ��",SQL_NTS);

	printf("  �ֹε�Ϲ�ȣ    �̸�       �ּ�	  ��ȭ��ȣ   	����	����   �μ�\n");
	while (TRUE) {
		rc = SQLFetch(hstmt);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) break;
		SQLGetData(hstmt, 1, SQL_C_CHAR, ssn, 15, &indicate);
		if(indicate > 0)	ssn[indicate]= 0;
		else				ssn[0]= 0;
		SQLGetData(hstmt, 2, SQL_C_CHAR, name, 10, &indicate);
		SQLGetData(hstmt, 3, SQL_C_CHAR, address, 19, &indicate);
		SQLGetData(hstmt, 4, SQL_C_CHAR, phone, 14, &indicate);  //��� long�̴ϱ� 4byte�ΰ� �˾�
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
	printf("\n\n===============================��ȸ�� �߰�=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char ssn[16], name[11], address[20], phone[15], grade[11], area[4], depart[8];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("��ȸ�� �ֹε�Ϲ�ȣ  (��)881230-1152132\n      �Է� : ");
	scanf("%s",ssn);
	printf("��ȸ�� �̸� (��) ������\n      �Է� : ");
	scanf("%s",name);
	printf("��ȸ�� �ּ� (��) ����� ������\n      �Է� : ");
	scanf("%s",address);
	printf("��ȸ�� ��ȭ��ȣ (��) 010-5542-5482\n      �Է� :  ");
	scanf("%s",phone);
	printf("��ȸ�� ���� (��) ���\n      �Է� : ");
	scanf("%s",grade);
	printf("��ȸ�� �����ڵ� (��) 02\n      �Է� : ");
	scanf("%s",area);
	printf("��ȸ�� �μ��ڵ� (��) EDU004\n      �Է� : ");
	scanf("%s",depart);

	sprintf(strBuf, "insert into ��ȸ�� values ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", ssn, name, address, phone, grade, area, depart);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);

}

int deleteBoss(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================��ȸ�� ����=================================\n\n");
	SQLRETURN rc;

	printBoss(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n������ ���ϴ� ��ȸ�� �ֹε�Ϲ�ȣ�� �Է� : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM ��ȸ�� WHERE �ֹε�Ϲ�ȣ='%s'", temp);
	printf("%s",strBuf);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchBossMenu()
{
	int select=0;
	printf("\n\n		1. �̸����� �˻�\n");
	printf("		2. �ֹε�Ϲ�ȣ�� �˻�\n");
	printf("		3. �����ڵ�� �˻�\n");
	printf("		4. �μ��ڵ�� �˻�\n");
	printf("		5. ���\n\n");
	printf("		���Ͻô� �Է¹���� ���� : ");
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
		printf("		�߸��� �Է��Դϴ�.\n");
		printf("		ó������ ���ư��ϴ�.\n");
		system("PAUSE");
		return 0;
	}
	
	char searchBuf[200];
	char temp[100];
	char selectBuf[50];
	long indicate;
	long count;
	char		ssn[16], name[11], address[20], phone[15], grade[11], area[4], depart[8];

	printf("		�˻��� �Է� : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��
	switch(select){
		case 1:
			strcpy(selectBuf,"�̸�");
			break;
		case 2:
			strcpy(selectBuf,"�ֹε�Ϲ�ȣ");
			break;
		case 3:
			strcpy(selectBuf, "�����ڵ�");
			break;
		case 4:
			strcpy(selectBuf, "�μ��ڵ�");
			break;
	}

	sprintf(searchBuf,"SELECT count(�̸�) FROM ��ȸ�� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	sprintf(searchBuf,"SELECT �ֹε�Ϲ�ȣ, �̸�, �ּ�, ��ȭ��ȣ, ����, �����ڵ�, �μ��ڵ� FROM ��ȸ�� WHERE %s like '%%%s%%'",selectBuf,temp);

	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	system("cls");
	printf("\n\n===============================��ȸ�� �˻�=================================\n\n");
	printf("        '%s'�� �˻� ��� %d�� �˻��Ǿ����ϴ�.\n\n",temp, count);

	rc = SQLFetch(hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("�����Ͱ� �������� �ʽ��ϴ�.\n");
		system("PAUSE");
		return 0;
	}
	printf("  �ֹε�Ϲ�ȣ    �̸�       �ּ�	  ��ȭ��ȣ   	����	����   �μ�\n");
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
// ���� ����
int memberMenu()
{
	int select;
	system("cls");
	printf("\n\n================================���� ����====================================");
	printf("\n\n		1. ��� ���� ����\n");
	printf("		2. ���� �߰�\n");
	printf("		3. ���� ����\n");
	printf("		4. ���� �˻�\n");
	printf("		5. ���� �޴�\n");
	printf("\n		�޴��� �����ϼ��� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int printMember(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================��� ���� ����=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		ssn[11], name[11], address[20], phone[15], grade[8], area[4], depart[8];
	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT ��Ϲ�ȣ,�̸�,�ּ�,��ȭ��ȣ,����,�����ڵ�,�μ��ڵ� from ����",SQL_NTS);


	printf("  ��Ϲ�ȣ     �̸�       �ּ�	         ��ȭ��ȣ       ����    ����   �μ�\n");
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
	printf("\n\n===============================���� �߰�=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char ssn[11], name[11], address[20], phone[15], grade[8], area[4], depart[8];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("���� ��Ϲ�ȣ (��) 2012-0120\n      �Է� : ");
	scanf("%s",ssn);
	printf("���� �̸� (��) ������\n      �Է� : ");
	scanf("%s",name);
	printf("���� �ּ� (��) ����� ������\n      �Է� : ");
	scanf("%s",address);
	printf("���� ��ȭ��ȣ (��) 010-8542-6324\n      �Է� : ");
	scanf("%s",phone);
	printf("���� ���� (��) ���\n      �Է� : ");
	scanf("%s",grade);
	printf("���� �����ڵ� (��) 01\n      �Է� : ");
	scanf("%s",area);
	printf("���� �μ��ڵ� (��) EDU004\n      �Է� : ");
	scanf("%s",depart);

	sprintf(strBuf, "insert into ���� values ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", ssn, name, address, phone, grade, area, depart);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);

}

int deleteMember(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================���� ����=================================\n\n");
	SQLRETURN rc;

	printMember(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n������ ���ϴ� ���� ��Ϲ�ȣ�� �Է� : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM ���� WHERE ��Ϲ�ȣ='%s'", temp);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchMemberMenu()
{
	int select=0;
	printf("\n\n		1. �̸����� �˻�\n");
	printf("		2. ��Ϲ�ȣ�� �˻�\n");
	printf("		3. �����ڵ�� �˻�\n");
	printf("		4. �μ��ڵ�� �˻�\n");
	printf("		5. ���\n\n");
	printf("		���Ͻô� �Է¹���� ���� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchMember(SQLHSTMT hstmt, int select)
{
	if(select == 5)
		return 0;
	else if(select > 5){
		printf("		�߸��� �Է��Դϴ�.\n");
		printf("		ó������ ���ư��ϴ�.\n");
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

	printf("		�˻��� �Է� : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��
	switch(select){
		case 1:
			strcpy(selectBuf,"�̸�");
			break;
		case 2:
			strcpy(selectBuf,"��Ϲ�ȣ");
			break;
		case 3:
			strcpy(selectBuf, "�����ڵ�");
			break;
		case 4:
			strcpy(selectBuf, "�μ��ڵ�");
			break;
	}

	sprintf(searchBuf,"SELECT count(�̸�) FROM ���� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	sprintf(searchBuf,"SELECT ��Ϲ�ȣ, �̸�, �ּ�, ��ȭ��ȣ, ����, �����ڵ�, �μ��ڵ� FROM ���� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	system("cls");
	printf("\n\n==============================���� �˻�=================================\n\n");
	printf("        '%s'�� �˻� ��� %d�� �˻� �Ǿ����ϴ�.\n\n",temp, count);

	rc = SQLFetch(hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("�����Ͱ� �������� �ʽ��ϴ�.\n");
		system("PAUSE");
		return 0;
	}
	printf("  ��Ϲ�ȣ     �̸�       �ּ�	         ��ȭ��ȣ       ����    ����   �μ�\n");
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
	printf("\n\n================================���� ����====================================");
	printf("\n\n		1. ��� ���� ����\n");
	printf("		2. ���� �߰�\n");
	printf("		3. ���� ����\n");
	printf("		4. ���� �˻�\n");
	printf("		5. ���� �޴�\n");
	printf("\n		�޴��� �����ϼ��� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int printArea(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================��� ���� ����=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		areaCode[5], name[11], areaNum[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT �����ڵ�, ������, ��Ϲ�ȣ from ����",SQL_NTS);

	printf("  �����ڵ�     ������      ��Ϲ�ȣ\n");
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
	printf("\n\n===============================���� �߰�=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char areaCode[5], name[11], areaNum[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("�����ڵ� (��) 01\n      �Է� : ");
	scanf("%s", areaCode);
	printf("������ (��) ���\n      �Է� : ");
	scanf("%s",name);
	printf("��Ϲ�ȣ (��) 2012-0012\n      �Է� : ");
	scanf("%s", areaNum);

	sprintf(strBuf, "insert into ���� values ('%s', '%s', '%s');", areaCode, name, areaNum);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);
}


int deleteArea(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================���� ����=================================\n\n");
	SQLRETURN rc;

	printArea(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n������ ���ϴ� ���� �ڵ� �Է� : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM ���� WHERE �����ڵ�='%s'", temp);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchAreaMenu()
{
	int select=0;
	printf("\n\n		1. ���������� �˻�\n");
	printf("		2. �����ڵ�� �˻�\n");
	printf("		3. ��Ϲ�ȣ�� �˻�\n");
	printf("		4. ���\n\n");
	printf("		���Ͻô� �Է¹���� ���� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchArea(SQLHSTMT hstmt, int select)
{
	if(select == 4)
		return 0;
	else if(select > 5){
		printf("		�߸��� �Է��Դϴ�.\n");
		printf("		ó������ ���ư��ϴ�.\n");
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

	printf("		�˻��� �Է� : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��
	switch(select){
		case 1:
			strcpy(selectBuf,"������");
			break;
		case 2:
			strcpy(selectBuf,"�����ڵ�");
			break;
		case 3:
			strcpy(selectBuf, "��Ϲ�ȣ");
			break;
	}

	sprintf(searchBuf,"SELECT count(������) FROM ���� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);


	sprintf(searchBuf,"SELECT �����ڵ�, ������, ��Ϲ�ȣ FROM ���� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("�����Ͱ� �������� �ʽ��ϴ�.\n");
		system("PAUSE");
		return 0;
	}

	system("cls");
	printf("\n\n===============================���� �˻�=================================\n\n");
	printf("        '%s'�� �˻� ��� %d�� �˻��Ǿ����ϴ�.\n\n",temp, count);


	printf("  �����ڵ�     ������      ��Ϲ�ȣ\n");
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
	printf("\n\n================================�μ�����====================================");
	printf("\n\n		1. ��� �μ� ����\n");
	printf("		2. �μ� �߰�\n");
	printf("		3. �μ� ����\n");
	printf("		4. �μ� �˻�\n");
	printf("		5. ���� �޴�\n");
	printf("\n		�޴��� �����ϼ��� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int printDepart(SQLHSTMT hstmt){
	system("cls");
	printf("\n\n===============================��� �μ� ����=================================\n\n");
	SQLRETURN	rc;
	long		indicate;
	char		departCode[8], name[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��

	rc=SQLExecDirect(hstmt, (SQLCHAR*)"SELECT �μ��ڵ�, �μ��� from �μ�",SQL_NTS);

	printf("  �μ��ڵ�     �μ���\n");
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
	printf("\n\n===============================�μ� �߰�=================================\n\n");
	SQLRETURN rc;
	char strBuf[100];
	char departCode[8], name[11];

	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("�μ��ڵ� (��) 01\n      �Է� : ");
	scanf("%s", departCode);
	printf("�μ��� (��) �ʵ��\n      �Է� : ");
	scanf("%s",name);

	sprintf(strBuf, "insert into �μ� values ('%s', '%s');", departCode, name);

	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf,SQL_NTS);
}

int deleteDepart(SQLHSTMT hstmt)
{
	char temp[100];
	char strBuf[200];
	system("cls");
	printf("\n\n===============================�μ� ����=================================\n\n");
	SQLRETURN rc;

	printDepart(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	printf("\n\n������ ���ϴ� �μ� �ڵ� �Է� : ");
	scanf("%s", temp);

	sprintf(strBuf, "DELETE FROM �μ� WHERE �μ��ڵ�='%s'", temp);
	rc = SQLExecDirect(hstmt, (SQLCHAR*)strBuf, SQL_NTS);

	system("PAUSE");

	return 0;
}

int searchDepartMenu()
{
	int select=0;
	printf("\n\n		1. �μ������� �˻�\n");
	printf("		2. �μ��ڵ�� �˻�\n");
	printf("		3. ���\n\n");
	printf("		���Ͻô� �Է¹���� ���� : ");
	if(scanf("%d", &select)!=1)
		err(&select);
	return select;
}

int searchDepart(SQLHSTMT hstmt, int select)
{
	if(select == 3)
		return 0;
	else if(select > 5){
		printf("		�߸��� �Է��Դϴ�.\n");
		printf("		ó������ ���ư��ϴ�.\n");
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

	printf("		�˻��� �Է� : ");
	scanf("%s",temp);

	SQLFreeStmt(hstmt, SQL_CLOSE);
	//StatmentH�� ���� ��� ó��
	switch(select){
		case 1:
			strcpy(selectBuf,"�μ���");
			break;
		case 2:
			strcpy(selectBuf,"�μ��ڵ�");
			break;
	}

	sprintf(searchBuf,"SELECT count(�μ���) FROM �μ� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);
	rc = SQLFetch(hstmt);
	SQLGetData(hstmt, 1, SQL_C_ULONG, &count, 0, &indicate);
	SQLFreeStmt(hstmt, SQL_CLOSE);

	sprintf(searchBuf,"SELECT �μ��ڵ�, �μ��� FROM �μ� WHERE %s like '%%%s%%'",selectBuf,temp);
	rc=SQLExecDirect(hstmt, (SQLCHAR*)searchBuf,SQL_NTS);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO){
		printf("�����Ͱ� �������� �ʽ��ϴ�.\n");
		system("PAUSE");
		return 0;
	}

	system("cls");
	printf("\n\n===============================�μ� �˻�=================================\n\n");
	printf("        '%s'�� �˻� ��� %d�� �˻��Ǿ����ϴ�.\n\n",temp, count);


	printf("  �μ��ڵ�     �μ���\n");
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



