// McGeeSetCredentials.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <wincred.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{ 
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


	wchar_t *var = L"USERNAME";
	wchar_t envUsername[50]; //max 50 characters for username
	GetEnvironmentVariableW(L"USERNAME", envUsername, sizeof(envUsername));
	char password[256]{'\0'}; //max 256 characters for password

	wchar_t username[60] = L"MCGEE\\"; //max 60 characters with domain and username
	wcscat_s(username, envUsername);

	_CREDENTIALW archiveCred {
		CRED_FLAGS_PROMPT_NOW, //DWORD Flags
		CRED_TYPE_DOMAIN_PASSWORD, //DWORD Type
		L"archive.mcgee.co.uk", //LPWSTR TargetName
		0, //LPWSTR Comment

		//FILETIME struct LastWritten 
		0, //DWORD dwLowDateTime
		0, //DWORD dwHighDateTime

		sizeof(password), //DWORD CredentialBlobSize
		(LPBYTE)password, //LPBYTE CredentialBlob
		CRED_PERSIST_ENTERPRISE, //DWORD Persist
		0, //DWORD AttributeCount
		0, //PCREDENTIAL_ATTRIBUTEW Attributes
		0, //LPSTR TargetAlias
		username //LPWSTR UserName
	};

	CredWriteW(&archiveCred, CRED_PRESERVE_CREDENTIAL_BLOB); //preserves password if target name already exists

	_CREDENTIALW *readCred;

	BOOL result = CredReadW(L"archive.mcgee.co.uk", CRED_TYPE_DOMAIN_PASSWORD, 0, &readCred);
	cout << "Result: " << result << endl;

	//char *pass = (char*)readCred->CredentialBlob; //can't retrieve passwords for CRED_TYPE_DOMAIN_PASSWORD structs

	DWORD *Count = 0;

	_CREDENTIALW *hi = new _CREDENTIALW[256];
	int i;
	for (i = 0; i < 256; i++)
		hi[i] = _CREDENTIALW();

	PCREDENTIALW *cred = &hi;

	CredEnumerateW(
		0,
		CRED_ENUMERATE_ALL_CREDENTIALS,
		Count,
		&cred);

	cin.get(); //Pauses console window

    return 0;
}
