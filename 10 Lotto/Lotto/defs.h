#ifndef _LOTTO_Hd_
#define _LOTTO_Hd_

#define NPLAYER 5
#define NAMES 20
#define NBETS 3
#define NFIVE 5
#define NTWO 2
#define SWIFT 8
#define BRANCH 3
#define ACCNUM 17
#define PESEL 10
#define STATISTICARR 60
#define FIFTY 50

typedef	enum Month{ Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec } month;						//!!!!!!!!!!!!!!!!!!!
typedef	enum Day{ Mon, Tue, Wed, Thu, Fri, Sat, Sun } day;
typedef enum Sex{ male, female } sex;

typedef struct tagTime
{
	int nYear;
	int nDayInMonth;
	Month month;
	Day day;
} Time;

typedef struct tagJackPotBets
{
	int* pArrTwo;
	int* pArrFive;
} JackPotBets;

typedef struct tagBankCode
{
	char pSwift[SWIFT];
	char pBankBranch[BRANCH];	
} BankCode;

typedef struct tagIbanCode
{
	char pPL[NTWO];								//!!!!!!!!!!!!!!!!!!!!!
	char pControl[NTWO];
	char pBank[SWIFT];
	char pAccNum[ACCNUM];
} IbanCode;

typedef struct tagBank
{
	BankCode BCode;
	IbanCode ICode;
} Bank;

typedef struct tagLottoPlayer
{
	char pFirstName[NAMES];
	char pSurName[NAMES];
	Sex sex;
	char pPesel[PESEL];
	Bank bankID;
	Time Date;
	JackPotBets* Bets;
	int nBetsSize;
	int nBetsMaxS;
} LottoPlayer;

#endif