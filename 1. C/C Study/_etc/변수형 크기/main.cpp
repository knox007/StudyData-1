#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <windows.h>
#include <WinDNS.h>
#include <BaseTsd.h>


int _tmain(int argc, _TCHAR* argv[])
{
	//
	SHORT	shMinSHORT = MINSHORT, shMaxSHORT = MAXSHORT;																	// MINSHORT C4309 초기화 중 상수 값이 짤립니다.
	//printf("SHORT		%d	%d			~	%d\n", sizeof(SHORT), shMinSHORT, shMaxSHORT);
	std::cout << "SHORT		" << sizeof(SHORT) << "	" << shMinSHORT << "			~	" << shMaxSHORT << std::endl;
	//std::cout << "SHORT		" << sizeof(SHORT) << "	" << MINSHORT << "			~	" << MAXSHORT << std::endl;			// 잘못된 출력 (MIN : 32768)
	std::cout << "USHORT		" << sizeof(USHORT) << "	" << 0 << "			~	" << (USHORT)MAXINT << std::endl;
	std::cout << std::endl;


	//
	std::cout << "INT		" << sizeof(INT) << "	" << MININT << "		~	" << MAXINT << std::endl;
	INT8	i8MinINT8 = MININT8, i8MaxINT8 = MAXINT8;
	//printf("INT8		%d	%d			~	%d\n", sizeof(INT8), i8MinINT8, i8MaxINT8);										// std::cout 으로 출력 불가
	//std::cout << "INT8		" << sizeof(INT8) << "	" << i8MinINT8 << "			~	" << i8MaxINT8 << std::endl;		// 잘못된 출력 (MIN, MAX 모두 특수문자)
	std::cout << "INT8		" << sizeof(INT8) << "	" << MININT8 << "			~	" << MAXINT8 << std::endl;			// 잘못된 출력 (MIN, MAX 모두 특수문자)
	std::cout << "INT16		" << sizeof(INT16) << "	" << MININT16 << "			~	" << MAXINT16 << std::endl;
	std::cout << "INT32		" << sizeof(INT32) << "	" << MININT32 << "		~	" << MAXINT32 << std::endl;
	std::cout << "INT64		" << sizeof(INT64) << "	" << MININT64 << "	~	" << MAXINT64 << std::endl;
	std::cout << std::endl;


	//
	std::cout << "UINT		" << sizeof(UINT) << "		" << 0 << "		~	" << MAXUINT << std::endl;
	UINT8	i8MaxUINT8 = MAXUINT8;
	printf("UINT8		%d		%d		~	%d\n", sizeof(UINT8), 0, i8MaxUINT8);											// std::cout 으로 출력 불가
	//std::cout << "UINT8		" << sizeof(UINT8) << "		" << 0 << "		~	" << i8MaxUINT8 << std::endl;				// 잘못된 출력 (MAX에 아무것도 안뜸)
	//std::cout << "UINT8		" << sizeof(UINT8) << "		" << 0 << "		~	" << MAXUINT8 << std::endl;					// 잘못된 출력 (MAX에 아무것도 안뜸)
	std::cout << "UINT16		" << sizeof(UINT16) << "		" << 0 << "		~	" << MAXUINT16 << std::endl;
	std::cout << "UINT32		" << sizeof(UINT32) << "		" << 0 << "		~	" << MAXUINT32 << std::endl;
	std::cout << "UINT64		" << sizeof(UINT64) << "		" << 0 << "		~	" << MAXUINT64 << std::endl;
	std::cout << std::endl;


	//
	LONG	lMinLONG = MINLONG;
	std::cout << "LONG		" << sizeof(LONG) << "		" << lMinLONG << "	~	" << MAXLONG << std::endl;
	//std::cout << "LONG		" << sizeof(LONG) << "		" << MINLONG << "	~	" << MAXLONG << std::endl;				// 잘못된 출력 (MINLONG이 2147483648)
	std::cout << "LONG32		" << sizeof(LONG32) << "		" << MINLONG32 << "	~	" << MAXLONG32 << std::endl;
	std::cout << "LONG64		" << sizeof(LONG64) << "	" << MINLONG64 << "	~	" << MAXLONG64 << std::endl;
	std::cout << std::endl;


	//
	std::cout << "ULONG32		" << sizeof(ULONG32) << "		" << 0 << "		~	" << MAXULONG32 << std::endl;
	std::cout << "ULONG64		" << sizeof(ULONG64) << "		" << 0 << "		~	" << MAXULONG64 << std::endl;
	std::cout << std::endl;

	
	//
	bool	bMinbool = 0, bMaxbool = 1;		// 1에 ++를 해도 1, --연산은 불가
	std::cout << "bool		" << sizeof(bool) << "		" << bMinbool << "		~	" << bMaxbool << std::endl;
	BOOL	bMinBOOL = 0, bMaxBOOL = 1;		// INT형처럼 ++, -- 가능
	std::cout << "BOOL		" << sizeof(BOOL) << "		" << bMinBOOL << "		~	" << bMaxBOOL << std::endl;
	std::cout << std::endl;



	//
	std::cout << "BYTE		" << sizeof(BYTE) << std::endl;
	std::cout << std::endl;
	
	
	//
	printf("CHAR		%d		%d(%c)		~	%d(%c)\n", sizeof(CHAR), MINCHAR, MINCHAR, MAXCHAR, MAXCHAR);
	printf("UCHAR		%d		%d(%c)		~	%d(%c)\n", sizeof(UCHAR), 0, 0, UCHAR_MAX, UCHAR_MAX);
	printf("WCHAR		%d		%d(%c)		~	%d(%c)\n", sizeof(WCHAR), 0, 0, WCHAR_MAX, WCHAR_MAX);
	std::cout << std::endl;


	//
	std::cout << "WORD		" << sizeof(WORD) << "		" << MAXWORD << "		unsigned short	 = USHORT" << std::endl;
	std::cout << "DWORD		" << sizeof(DWORD) << "		" << MAXDWORD << "	unsigned long	 = ULONG" << std::endl;
	std::cout << "DWORD32		" << sizeof(DWORD32) << "		" << MAXDWORD32 << "	unsigned int	 = UINT" << std::endl;
	std::cout << "DWORD64		" << sizeof(DWORD64) << "	" << MAXDWORD64 << "	unsigned __int64 = UINT64" << std::endl;
	std::cout << "QWORD		" << sizeof(QWORD) << "	" << std::endl;
	std::cout << std::endl;
	

	//
	std::cout << "FLOAT		크    기 : " << sizeof(float) << std::endl;
	std::cout << "		유효숫자 : " << FLT_DIG << std::endl;
	std::cout << "		최 소 값 : " << FLT_MIN << std::endl;
	//printf("			  %.38f \n", FLT_MIN);							// 소숫점 아래 38자리
	std::cout << "		최 대 값 : " << FLT_MAX << std::endl;
	//printf("			  %f \n", FLT_MAX);								// 소숫점 위 38자리
	std::cout << std::endl;


	//
	std::cout << "DOUBLE		크    기 : " << sizeof(double) << std::endl;
	std::cout << "		유효숫자 : " << DBL_DIG << std::endl;
	std::cout << "		최 소 값 : " << DBL_MIN << std::endl;
	//printf("			  %.308f \n", DBL_MIN);							// 소숫점 아래 308자리
	std::cout << "		최 대 값 : " << DBL_MAX << std::endl;
	//printf("			  %f \n", DBL_MAX);								// 소숫점 위 308자리
	std::cout << std::endl;

	
	/*
	for(char i=MINCHAR; i<=MAXCHAR; ++i)
	{
		printf("	%5d : %c|\n", i, i);

		if(i == MAXCHAR)
			break;
	}
	// 이걸 할 바에 아스키 코드표 참조
	// http://www.powerindex.net/U_convt/ascii/ascii.htm
	// 0 = 48
	// A = 65
	// a = 97
	// 
	*/

	//////////////////////////////////////////////////////////////////////////
	fflush(stdin);
	getchar();
	return 0;
}
