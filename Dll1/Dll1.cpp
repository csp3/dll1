// $nombredeproyecto$.cpp: define las funciones exportadas de la aplicación DLL.
//
#include "stdafx.h"
#include <windows.h>
#include <direct.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
//#include "enca.h"
using namespace  std;

#define LIBDLL extern "C" _declspec(dllexport)

LIBDLL int Archivojob() {
	//HANDLE CreateFile([In] LPCTSTR lpFileName,[In]DWORD dwDesiredAccess,[In]DWORD dwShareMode,[In-opt]LPSECURITY_ATTRIBUTES lpSecurityAttributes,[In]DWORD dwCreationDisposition,[In]DWORD dwFlagsAndAttributes,[In-opt]HANDLE hTemplateFile);
	//DWORD WINAPI GetCurrentDirectory([In] DWORD  nBufferLength,[Out] LPTSTR lpBuffer);

	TCHAR dirActual[700];
	TCHAR nomArchivo[80] = TEXT("\\agenda.txt");
	DWORD d = GetCurrentDirectory(600, dirActual); // saco el path 
	_tcscat_s(dirActual, 700, nomArchivo); // concateno con nombre-archivo

	HANDLE hfile;
	hfile = CreateFile(dirActual,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hfile == INVALID_HANDLE_VALUE) {
		_tprintf(TEXT("Error al abrir archivo\n"));
	}
	else {
		_tprintf(TEXT("archivo abierto\n"));
		DWORD tamanio = GetFileSize(hfile, NULL); printf("\ntama=%d\n", tamanio);
		TCHAR *strVal = { 0 };
		strVal = (TCHAR *)realloc(strVal, tamanio - sizeof(strVal)); // redimesionar array -- resto el sizeof del strVal inicial
		DWORD wmWritten = 0;
		ReadFile(hfile, strVal, tamanio, &wmWritten, NULL);
		printf("\n\n\n\n%s\n\n", strVal);
	}
	if (CloseHandle(hfile) != 0) {
		_tprintf(TEXT("Archivo cerrado\n"));
	}
	else {
		_tprintf(TEXT("Error %u al cerrar archivo\n"), GetLastError());
	}

	//system("pause");
	printf("\nhola\n");
	return 0;
}

/*
namespace espacio {
	int miclase::Archivojob()
	{
		
	}
}
*/
