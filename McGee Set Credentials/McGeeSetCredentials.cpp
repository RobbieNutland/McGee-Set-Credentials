// McGeeSetCredentials.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <Windows.h>
#include <wincred.h>
#include <iostream>
//#include <stdlib.h>

using namespace std;

int main()
{
	// ASCII functions (suffix: A)
	/*

	wchar_t* wcUsername = new wchar_t[50]; //max username size of 50 wide chars
	DWORD wcNameSize = sizeof(wchar_t[50]);
	DWORD envResult = GetEnvironmentVariableW(L"USERNAME", wcUsername, wcNameSize);

	char *cUsername = new char[50]; //max username size of 50 chars
	size_t cNameSize = sizeof(char[50]);
	size_t returnedSize;
	wcstombs_s(&returnedSize, cUsername, cNameSize, wcUsername, cNameSize); //converts wide char to char

	char username[60] = "MCGEE\\"; //max username size with domain is 60 chars
	strcat_s(username, sizeof(username), cUsername);
	char *password = "Password";

	_CREDENTIALA archiveCredentialStruct = {
		CRED_FLAGS_PROMPT_NOW,
		CRED_TYPE_DOMAIN_PASSWORD,
		"archive.mcgee.co.uk",
		"Credential for the archive.",
		0,
		512,
		512,(LPBYTE)password,
		CRED_PERSIST_ENTERPRISE,
		0,
		0,
		0,
		username
	};

	BOOL wasSuccessful = CredWriteA(&archiveCredentialStruct, 0);
	if (wasSuccessful){
		cout << "Was Sucessful" << endl;
	}
	else {
		cout << "Wasn't Successful" << endl;
	}

	int error = GetLastError();
	cout << error << endl;

	*/

	// Unicode functions (suffix: W)

	wchar_t wcUsername[50]; //50 chars max

	GetEnvironmentVariableW(L"USERNAME", wcUsername, 50); //param 3: do not use sizeof(wcUsername) because it is 100 bytes due to wchar, but here we need to specify how many characters (50)

	wchar_t username[60] = L"MCGEE\\"; //max 60 characters with domain and username
	wcscat_s(username, wcUsername);
	wchar_t password[256]{ '\0' }; //max 256 characters for password


	char* cUsername = new char[60];
	size_t returnedSize;
	wcstombs_s(&returnedSize, cUsername, 60, username, 59); //converts wchar to char

	cout << "Username: " << cUsername << endl;

	_CREDENTIALW archiveCredentialStruct = {
		CRED_FLAGS_PROMPT_NOW,
		CRED_TYPE_DOMAIN_PASSWORD,
		L"archive.mcgee.co.uk",
		L"Credential for the archive.",
		0,
		NULL,
		512,
		(LPBYTE)password,
		CRED_PERSIST_ENTERPRISE,
		0,
		0,
		0,
		username
	};

	BOOL wasSuccessful = CredWriteW(&archiveCredentialStruct, 0);
	if (wasSuccessful) {
		cout << "Successfully created Windows Credential for 'archive.mcgee.co.uk'." << endl;
	}
	else {
		cout << "Failed to create Windows Credential for 'archive.mcgee.co.uk'." << endl;
	}

	/*

	int error = GetLastError();
	cout << error << endl;

	_CREDENTIALW *readCred;

	BOOL result = CredReadW(L"archive.mcgee.co.uk", CRED_TYPE_DOMAIN_PASSWORD, 0, &readCred);
	cout << "Result: " << result << endl;

	//char *pass = (char*)readCred->CredentialBlob; //can't retrieve passwords for CRED_TYPE_DOMAIN_PASSWORD structs

	DWORD count;

	_CREDENTIALW *hi = new _CREDENTIALW[256];
	int i;
	for (i = 0; i < 256; i++)
		hi[i] = _CREDENTIALW();

	PCREDENTIALW *cred = &hi;

	CredEnumerateW(NULL, 0, &count, &cred);

	*/

	cout << "Press 'Enter' to exit...";
	cin.get(); //pauses console window

    return 0;
}
