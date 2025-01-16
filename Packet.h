#ifndef _PACKET_H_
#define _PACKET_H_

#define ACCOUNT_LENGTH		12
#define PASSWORD_LENGTH		12
#define CHAR_NAME_LENGTH	30
#define	CHAR_NAME_LENGTH_CLIENT 16
#define GUILD_MARK_SIZE		384
#define GUILD_MAP_COUNT		40 //  40��
#define TEL_NAME_LENGTH		20
#define SHOP_NAME_LENGTH	18

#define CLASS_NUM			4
#define NEW_CLS_NUM			5				//�������ٲ�ʦ

#define SKILL_NUM			5
#define SKILL_LEVEL			41

//#define SKILL_NAME_LENGTH	14

#define EQUIP_ITEM_NUM		10
#define	INVENTORY_NUM		24
//#define QUICK_ITEM		5
#define EBODY_NUM			4
#define GUARDIAN_NUM		1
#define TOTAL_SKILL_NUM			(CLASS_NUM * SKILL_NUM)
//#define TOTAL_CLASS_SKILL_NUM	(SKILL_NUM * SKILL_LEVEL)

#define TOTAL_PSI_NUM		84

#define MAX_ITEM_NUM		255			// �ϳ��� ���Դ� �����Ҽ��ִ� �ִ밪
#define BANK_MAX_ITEM		1000		// �ѽ��Դ� �����Ҽ� �ִ� ��
#define ACCOUNT_BANK_MAX_ITEM	32767	// ���� ���࿡ �ѽ��Դ� �����Ҽ� �ִ� ��

#define TOTAL_BANK_ITEM_NUM 48
#define TOTAL_ACCOUNT_BANK_ITEM_NUM 150

#define TOTAL_PERSONALSHOP_ITEM_NUM 7

#define TOTAL_INVEN_MAX		((EQUIP_ITEM_NUM + INVENTORY_NUM))
#define TOTAL_ITEM_NUM		((EQUIP_ITEM_NUM + INVENTORY_NUM + EBODY_NUM + 1 + 1))
//#define TOTAL_ITEM_SLOT_NUM ((EQUIP_ITEM_NUM + INVENTORY_NUM + QUICK_ITEM))
//#define TOTAL_USER_ITEM_NUM	((TOTAL_ITEM_NUM + EBODY_ITEM))

#define _SKILL_SIZE			((sizeof(short) + sizeof(BYTE)))
#define _ITEM_SIZE			((sizeof(short) * 5) + (sizeof(BYTE) * 11) + (sizeof(BYTE)))
#define _PSI_SIZE			((sizeof(short) + sizeof(BYTE)))
#define _SKILLINFO_SIZE		((sizeof(BYTE) + sizeof(DWORD)))

#define USER_SKILL_LEN		(_SKILL_SIZE * TOTAL_SKILL_NUM)
#define USER_ITEM_LEN		(_ITEM_SIZE * TOTAL_ITEM_NUM)

#define USER_SKILLINFO_LEN	(_SKILLINFO_SIZE * TOTAL_SKILL_NUM)

#define EQUIP_SLOT			0
#define INVENTORY_SLOT		1
//#define QUICK_SLOT			2
#define TRADE_SLOT			3
#define BANK_SLOT			4
#define GUILD_SLOT			5
#define ACCOUNT_BANK_SLOT	6

#define BRAWL				0		// Character Making �� ���Ǵ� Ŭ���� ����
#define STAFF				1
#define	EDGED				2
#define FIREARMS			3
#define JUDGE				4		//�ٲ�
#define NOCLASS				5
#define ALL_JOBS			31		//����ְҵ����

#define JUDGE_ITEM			16		// ����
#define BRAWL_ITEM			8		// Item Table �� ���ǵ� Ŭ���� ����
#define STAFF_ITEM			4
#define	EDGED_ITEM			2
#define FIREARMS_ITEM		1

#define MAX_MOVE_TIME		100

#define ATTACK_UPGRADE_BAND		16	
#define ATTACK_UPGRADE_PSI_BAND	4	
#define DEFENSE_UPGRADE_BAND	4	

const BYTE SUCCESS				=	1;
const BYTE FAIL					=	0;
const BYTE SUCCESS_ZONE_CHANGE	=	2;

const BYTE ERR_1				=	1;
const BYTE ERR_2				=	2;
const BYTE ERR_3				=	3;
const BYTE ERR_4				=	4;
const BYTE ERR_5				=	5;
const BYTE ERR_6				=	6;
const BYTE ERR_7				=	7;
const BYTE ERR_8				=	8;
const BYTE ERR_9				=	9;
const BYTE ERR_10				=	10;
const BYTE ERR_11				=	11;
const BYTE ERR_12				=	12;
const BYTE UNKNOWN_ERR			=	255;

const BYTE ERR_SHORT_ATTACK_DELAY	= 0;
const BYTE ERR_TOO_LONG_DISTANCE	= 1;
const BYTE ERR_BROKEN				= 2;
const BYTE ERR_EMPTY_BULLET			= 3;
const BYTE ERR_EMPTY_ENERGE			= 4;
const BYTE ERR_EMPTY_SP				= 5;

const BYTE INFO_MODIFY			=	1;
const BYTE INFO_DELETE			= 	2;
const BYTE INFO_TOWNPOTAL		=   3;
const BYTE INFO_TOWNPOTAL_DELETE=	4;

const BYTE ITEM_INFO_MODIFY		=	1;
const BYTE ITEM_INFO_DELETE		=	2;
const BYTE ITEM_INFO_PICKUP		=	3;

const BYTE NORMAL_CHAT			=	1;
const BYTE WHISPER_CHAT			=	2;
const BYTE SHOUT_CHAT			=	3;
const BYTE GUILD_CHAT			=	4;
const BYTE BUDDY_CHAT			=	5;
const BYTE BUDDY_INVITE			=	6;
const BYTE BUDDY_OFF			=	7;
const BYTE MOP_CHAT				=	10;
const BYTE WHISPER_OK			=	11;
const BYTE WHISPER_DENY			=	12;

const BYTE CALL_CHAT			=	15;		// Ư������ ��ȯ
const BYTE REMOTE_CHAT			=	16;		// Ư������ Ư����ǥ�� ���� �̵�
const BYTE MOP_CALL_CHAT		=	17;		// Ư���� Ư����ǥ�� ���� �̵�

const BYTE GUILD_INVITE			=	18;		// ��� ����
const BYTE GUILD_DISPERSE		=	19;		// ��� �ػ�
const BYTE GUILD_OFF			=	20;		// ��� Ż��
const BYTE GUILD_KICK_OUT		=	21;		// �渶�� ���� �߹�

const BYTE ITEM_MODE_CHAT		=	22;		// ������ �ޱ� �³�, ������ ǥ��

const BYTE OP_CLOAK_ON			=	23;		// ��� �������
const BYTE OP_CLOAK_OFF			=	24;		// ��� ������ ������...
const BYTE ALL_CHAT				=	25;		// ��ü �����ڿ��� �޼����� ������.
const BYTE GUILD_FIELD_WAR		=   26;		// ��� ��带 ���� �ʵ����� ��û�Ѵ�.
const BYTE GUILD_SURRENDER		=   27;		// ��� ��带 ���� �׺��Ѵ�.
const BYTE PK_COUNT_CHAT		=	28;
const BYTE COPY_TELEPORT		=	29;		// ������ ����� ���� �̵��Ѵ�.
const BYTE GUILD_USER_CHECK		=	30;		// ��ü ���� ��ϸ� �����ش�.
const BYTE GUILD_WAR_APPLY_LIST =	31;		// ������ ��û�� ��ü ��� ����� �����ش�.
const BYTE GUILD_FORTRESS_DOOR	=	32;		// ��Ʈ���� ������ ���� �ݴ´�.
const BYTE GUILD_DEPUTE_POWER	=	33;		// �渶 ������ �α渶���� ����
const BYTE GUILD_STOP_POWER		=	34;		// �α渶 ������ ����
const BYTE GUILD_USER_INFO_CALL =	35;		//yskang 0.2
const BYTE GUILD_CALL_CHAT		=	36;		//yskang 0.2 ��Ʈ������ ������ �ִ� ���¯�� Ư�� ������ ��ȯ�Ѵ�.

const BYTE SYSTEM_SPECIAL		=	0;		// Ư�� ����
const BYTE SYSTEM_NORMAL		=	1;		// �Ϲ� ����
const BYTE SYSTEM_ERROR			=	2;		// ��������
const BYTE SYSTEM_NPC			=	3;		// NPC ��ȭ
const BYTE SYSTEM_ANNOUNCE		=	4;		// ��� �޼��� ����
const BYTE SYSTEM_DISCONNECT	=	5;		// �ð� ����� ��������	
const BYTE SYSTEM_CESHIA        =	6;

// Hit Mark List (Skill List)
const BYTE HIT_NONE				=	0;
const BYTE HIT_DAMAGE_C			=	1;
const BYTE HIT_VITAL_C			=	2;
const BYTE HIT_DELAY_C			=	3;
const BYTE HIT_CONCENTRATE		=	4;
const BYTE HIT_PSY_ACCLIMATE	=	5;
const BYTE HIT_FAST_CAST		=	6;
const BYTE HIT_WEAPON_ACCLIMATE	=	7;
const BYTE HIT_FAST_ATTACK		=	8;
const BYTE HIT_OUT_RANGE		=	9;
const BYTE HIT_STRAFE			=	10;
const BYTE HIT_BROKEN			=	11;
const BYTE HIT_FIXED			=	12;
const BYTE HIT_OVERHIT			=	13;
const BYTE HIT_FIRE				=	14;
const BYTE HIT_ICE				=	15;
const BYTE HIT_LIGHT			=	16;
const BYTE HIT_NUMB				=	17;
const BYTE HIT_POISON			=	18;
const BYTE HIT_C_GUARD			=	19;

const BYTE PSI_TELEPORT			=	7;

const BYTE BBS_NOT_OWNER		=	2;
const BYTE BBS_CONTENTS_DELETE	=	3;

// �����̻� ����
//#define _ABNORMAL_DB			5

const BYTE ABNORMAL_TIME			=	0;
const BYTE PSI_ONE_TIME				=	1;
const BYTE PSI_TWO_TIME				=	2;
const BYTE PSI_THREE_TIME			=	3;
const BYTE TRANS					=   4;

const BYTE ABNORMAL_BYTE_NONE		=	0;
const BYTE ABNORMAL_BYTE_POISON		=	1;
const BYTE ABNORMAL_BYTE_CONFUSION	=	2;
const BYTE ABNORMAL_BYTE_PARALYSIS	=	3;
const BYTE ABNORMAL_BYTE_BLIND		=	4;
const BYTE ABNORMAL_BYTE_LIGHT		=	5;
const BYTE ABNORMAL_BYTE_FIRE		=	6;
const BYTE ABNORMAL_BYTE_COLD		=	7;

const DWORD ABNORMAL_NONE			=	0;
const DWORD ABNORMAL_POISON			=	1;
const DWORD ABNORMAL_CONFUSION		=	1 << 2;
const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
const DWORD ABNORMAL_BLIND			=	1 << 4;
const DWORD ABNORMAL_LIGHT			=	1 << 5;
const DWORD ABNORMAL_FIRE			=	1 << 6;
const DWORD ABNORMAL_COLD			=	1 << 7;
const DWORD ABNORMAL_HASTE			=	1 << 8;
const DWORD ABNORMAL_SHIELD			=	1 << 9;
const DWORD ABNORMAL_HIDE			=	1 << 10;
const DWORD ABNORMAL_DEX_UP			=	1 << 11;
const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
const DWORD ABNORMAL_BERSERKER		=	1 << 15;
const DWORD ABNORMAL_HIEXP			=	1 << 16;
const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
const DWORD ABNORMAL_NOCHAT			=	1 << 18;

const DWORD ABNORMAL_FASTRUN		=	1 << 19;
const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
const DWORD ABNORMAL_PIERCING_SHIELD=	1 << 23;
const DWORD ABNORMAL_PAOBUTING		=	1 << 27;
const DWORD ABNORMAL_FUDAI			=	1 << 26; // ����ͼ��
const DWORD ABNORMAL_JIANYU			=	1 << 28;//����
const DWORD ABNORMAL_BIANSHEN		=	1 << 29;//���뾧ʯ
const DWORD ABNORMAL_BIGSHIELD			=	1 << 30;
const DWORD ABNORMAL_VIP	        =	2; //VIP
const DWORD OPERATION_MODE			=	1 << 31;	// ��� ���� �ɼ�


const DWORD STATE_1 = 1 << 0; //����ʹ�û�е״̬
const DWORD STATE_0_1 = 1 << 1;
const DWORD STATE_2 = 1 << 2; 
const DWORD STATE_3 = 1 << 3; 
const DWORD STATE_4 = 1 << 4; // hp up
const DWORD STATE_5 = 1 << 5; //������1
const DWORD STATE_6 = 1 << 6; //�̳��
const DWORD STATE_7 = 1 << 7; //��ʹ
const DWORD STATE_8 = 1 << 8; 
const DWORD STATE_9 = 1 << 9; // hp down
const DWORD STATE_10 = 1 << 10; //
const DWORD STATE_11 = 1 << 11; //ͼƬsp
const DWORD STATE_12 = 1 << 12; //pp
const DWORD STATE_13 = 1 << 13; //Ͷ��
const DWORD STATE_14 = 1 << 14; //�����뾧����
const DWORD STATE_15 = 1 << 15; //�׼����
const DWORD STATE_16 = 1 << 16; //��
const DWORD STATE_17 = 1 << 17; //��
const DWORD STATE_18 = 1 << 18; //���׿�
const DWORD STATE_19 = 1 << 19; //��
const DWORD STATE_20 = 1 << 20; //��
const DWORD STATE_21 = 1 << 21; //exp 2
const DWORD STATE_22 = 1 << 22; //magic up
const DWORD STATE_23 = 1 << 23; //ͼƬxp 3
const DWORD STATE_24 = 1 << 24;//���
const DWORD STATE_25 = 1 << 25; //ͼƬ�۾�
const DWORD STATE_26 = 1 << 26; //����+3
const DWORD STATE_27 = 1 << 27; //ͼƬҩƿMAX
const DWORD STATE_28 = 1 << 28;//����+1
const DWORD STATE_29 = 1 << 29;//����+2
const DWORD STATE_30 = 1 << 30;//ͼƬ����Ķ���
const DWORD STATE_31 = 1 << 31;//����

const DWORD ABNORMAL_CLEAR_STATUS	= (0xFFFFFFFF ^ (ABNORMAL_POISON | ABNORMAL_CONFUSION | ABNORMAL_PARALYSIS | ABNORMAL_BLIND | ABNORMAL_LIGHT | ABNORMAL_FIRE | ABNORMAL_COLD));
const DWORD ABNORMAL_CLEAR_STATUS1	= (0xFFFFFFFF ^ (STATE_1 | STATE_5 | STATE_6 | STATE_7 | STATE_13 | STATE_18 | STATE_21 | STATE_22 | STATE_23 | STATE_24 | STATE_28 | STATE_29 | STATE_30 | STATE_31));
const DWORD	ABNORMAL_CLEAR_PSI_ONE	= (0xFFFFFFFF ^ (ABNORMAL_HASTE | ABNORMAL_SHIELD | ABNORMAL_HIDE | ABNORMAL_DEX_UP | ABNORMAL_MAX_HP_UP | ABNORMAL_FASTRUN | ABNORMAL_PSISHIELD | ABNORMAL_PIERCING_SHIELD | ABNORMAL_MINDSHOCK));
const DWORD ABNORMAL_CLEAR_PSI_TWO	= (0xFFFFFFFF ^ (ABNORMAL_ADAMANTINE | ABNORMAL_MIGHTYWEAPON | ABNORMAL_BERSERKER));
const DWORD ABNORMAL_CLEAR_PSI_THREE= (0xFFFFFFFF ^ (ABNORMAL_MINDGUARD));

const short TYPE_MONEY_SID		=	10000;	// ������ �� ���� �����ϱ����� sid�� ũ�� ��Ҵ�.

//����ְҵħ��״̬
const DWORD JUDGE_PSI_NONE			=   0;

//0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
const DWORD JUDGE_ABNORMAL_18 = 1<<18;					//��������������
//0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00
const DWORD JUDGE_ABNORMAL_20 = 1<<20;					//��������

const DWORD New_Status_1	= 1<<0;//��ɫ��ȭ����
const DWORD New_Status_2	= 1<<1;//�����ƶ��ٶȼӿ�ͼƬ
const DWORD New_Status_3	= 1<<2;//��ʮ��ͼƬ����ҽԺ��־
const DWORD New_Status_4	= 1<<3;//ʮ���ͷ���
const DWORD New_Status_5	= 1<<4;//PCEXP20%����
const DWORD New_Status_6	= 1<<5;//PCEXP30%����
const DWORD New_Status_7	= 1<<6;//PCEXP50%����
const DWORD New_Status_8	= 1<<7;	//����ͷ
const DWORD New_Status_9	= 1<<8;	//����ͷ
const DWORD New_Status_10	= 1<<9;	//�׵�
const DWORD New_Status_11	= 1<<10;//���ӵ�
const DWORD New_Status_12	= 1<<11;//�Ƹ�135
const DWORD New_Status_13	= 1<<12;//�Ʒ�ʦ135
const DWORD New_Status_14	= 1<<13;//�ƽ�ʦ135
const DWORD New_Status_15	= 1<<14;//��ǹ��135
const DWORD New_Status_16	= 1<<15;//��
const DWORD New_Status_17	= 1<<16;//����ͼƬ
const DWORD New_Status_21	= 1<<17;//��������
const DWORD New_Status_19	= 1<<19;//�������
const DWORD New_Status_22	= 1<<21;//��������ϴ�NEW ֻ���Լ��ܿ���
const DWORD New_Status_23	= 1<<22;//����ǰ���C.B.
const DWORD New_Status_24	= 1<<23;//�绰SD
const DWORD New_Status_25	= 1<<24;//�绰A
const DWORD New_Status_26	= 1<<25;//�绰D
const DWORD New_Status_27	= 1<<26;//�绰SD
const DWORD New_Status_28	= 1<<27;//��
const DWORD New_Status_29	= 1<<28;//��
const DWORD New_Status_30	= 1<<29;//��
const DWORD New_Status_31	= 1<<30;//��
const DWORD New_Status_32	= 1<<31;//��

/*
BYTE	NORMAL_ITEM		= 0;
BYTE	REMODEL_ITEM	= 1;
BYTE	MAGIC_ITEM		= 2;
BYTE	RARE_ITEM		= 3;
BYTE	UNIQUE_ITEM		= 4;
BYTE	SET_ITEM		= 5;
BYTE	UPGRADE_ITEM	= 6;
*/

const BYTE HP_POTION			= 1;
const BYTE PP_POTION			= 2;
const BYTE SP_POTION			= 3;
const BYTE ALL_POTION			= 4;
const BYTE SALUTE				= 5;
const BYTE EXP_POTION			= 6;
const BYTE MAGIC_POTION			= 7;
const BYTE KILLREMOVE_POTION	= 8;
const BYTE DEAD_POTION			= 9;
const BYTE XMAS_SALUTE			= 10;
const BYTE YEAR_SALUTE			= 11;
const BYTE YEAR_SALUTE1			= 12;
const BYTE YEAR_SALUTE2			= 13;//�Զ���Ǯ�� 
const BYTE YEAR_SALUTE3			= 14;//����
const BYTE BIAN_SHEN			= 15;//�ҿ�
const BYTE TEST_21				= 21;//��

//#################################################################
//	Zone Server
//#################################################################
const BYTE	SERVER_LOGIN_REQ			= 1;

const BYTE	SERVER_LOGIN_RESULT			= 2;

const BYTE	SERVER_USER_LOGIN_REQ		= 3;

const BYTE	SERVER_USER_LOGIN_RESULT	= 4;

const BYTE	SERVER_DOUBLE_ACCOUNT_CLOSE = 5;

const BYTE	SERVER_DOUBLE_ID_CLOSE		= 6;

const BYTE	SERVER_USER_LOGOUT_REQ		= 7;

const BYTE	SERVER_USER_ZONELOGIN_REQ	= 8;

const BYTE	SERVER_USER_ZONELOGIN_RESULT= 9;

const BYTE	SERVER_USER_WHISPER_ONOFF	= 10;

const BYTE	SERVER_USER_WHISPER_REQ		= 11;

const BYTE	SERVER_USER_WHISPER_RESULT	= 12;

const BYTE	SERVER_USER_GUILD_CHAT		= 13;//�Զ���Ǯ�� 

const BYTE	SERVER_GUILD_NEW			= 14;//����

const BYTE	SERVER_GUILD_DISPERSE		= 15;//����Ч��

const BYTE	SERVER_GUILD_INVITE			= 16;//����Ч��

const BYTE	SERVER_GUILD_OFF			= 17;//��ɫ����Ч��

const BYTE	SERVER_GUILD_MARK			= 18;//��ɫ����Ч��

const BYTE	SERVER_USER_RESTART			= 19;//��Ч��

const BYTE	SERVER_USER_ZONE_LOGOUT		= 20;//����ɫ��ҩЧ��

const BYTE	SERVER_ALIVE				= 21;//��

const BYTE	SERVER_ANNOUNCE				= 22;//��ɫ��ҩЧ��

const BYTE	SERVER_ARK_WINNER			= 23;//ʹ���ػ���ʹЧ��

const BYTE  SERVER_GUILD_SUBMASTER_ON	= 24;//speed����Ч��

const BYTE  SERVER_GUILD_SUBMASTER_OFF	= 25;//attack����Ч��

const BYTE	ZONE_LOGIN_REQ				= 233;
/*
	(C -> S)	// �ٸ� �������� ����ϴ� ������ ��ü������ �Ҷ�  (��ȣȭ ����)

	VarChar		id[ACCOUNT_LENGTH];				// Account ID
	VarChar		pass[PASSWORD_LENGTH];			// Account Password
	VarChar		szCharName[CHAR_NAME_LENGTH];	// CharName

	short		myserver;
*/

const BYTE	ZONE_LOGIN_RESULT			= 234;
/*
	(C <- S)	// Game Login Result  (��ȣȭ ����)

	BYTE		result;			// 01	: Login Success
								// else	: Login Fail

	// ������ ��� ------		// 01	: Invaild ID
								// 02	: DB�� ���� ID
								// 03	: Invalid Zone Number
								// 04	: Invalid Position
								// 05	: ���� ID �����
								// ...
								// 255	: �� �� ���� ����

	short		CurrZone;		// ���� Zone Number
	int			uid;			// User Index
	short		PosX;			// Map �� X ��ǥ
	short		PosY;			// Map �� Y ��ǥ

	BYTE		tDir;			// ���� �����ִ� ����

	BYTE		tTime;			// �ð�(0~24)
	BYTE		tMinute;		// ��  (0~60)


    Varchar		public_key;		// int64
	DWORD		dwSerial;		// �ø��� ���� ��ȣ
*/


// CHAR INFO SERVER
const BYTE CIS_DISCONNECT				= 235;
/*
*/

//#################################################################
//	���� �׽�Ʈ �ڵ��� (2001-11-15)
//#################################################################
const BYTE CHECK_ALIVE_REQ		= 255;
/*
	(C -> S)
*/
const BYTE CHECK_ALIVE_RESULT	= 255;
/*
	(C <- S)
*/

const BYTE CLIENT_TICK			= 254;
/*
	(C -> S) // Speed Hack �� �������� 5�ʸ��� Ŭ���̾�Ʈ���� ������ ������ ��Ŷ
*/

//const BYTE SERVER_TICK_RESULT	= 6;
/*
	(C <- S)
	DWORD	dwTick;				// Server�� ���� Tick.
*/

const BYTE DB_USER_COUNT			= 253;
/*
	(S <- S)						//
*/

const BYTE DB_GUILD_WHEREHOUSE_EVENT_REQ = 252;
/*
	(S <- S)						//
*/

const BYTE DB_GUILD_ITEM_MOVE_REQ	= 251;
/*
	(S <- S)						//
*/

const BYTE ANNOUNCE_NOTICE			= 250;
/*
	(C -> S)						// ��ü������ �ϰ����� ����������
	String		strMsg;
*/

const BYTE ENCRYPTION_PKT			= 249;
/*									// ��ȣȭ�� �ǹ�
*/

const BYTE DB_USER_DEAD				= 248;
/*									// ������ �׾����� �α׸� ����
*/

//#################################################################
//	Information		(1 ~ 9)
//#################################################################

const BYTE USER_INFO			=	1;
/*
	(C <- S)		// Send User Info

	BYTE		Mode;			// 01(INFO_MODIFY)	: �������� ����
								// 02(INFO_DELETE)	: �������� ����
								// 03(INFO_TOWNPOTAL)		 : ������ Ÿ����Ż ��� -> ���� ����
								// 04(INFO_TOWNPOTAL_DELETE) : ������ Ÿ����Ż�� �̵�, ���� ���� ����

	int			uid;			// User index

	// Mode �� INFO_MODIFY �� ��츸 �Ʒ��� ������ ����
	VarChar		szName;			// User Name
	short		nPosX;			// X Position
	short		nPosY;			// Y Position

	DWORD		dwSkin;			// �Ǻλ�(COLORREF)
	DWORD		dwHair;			// �Ӹ���(COLORREF)
	BYTE		byGender;		// ��, ��

	char		szFace[10];		// �󱼸��
								// 1 : �Ӹ�
								// 2 : ��
								// 3 : ��
								// 4 : ��
								// 5 : ��
								// 6 : �Ǽ��縮 1
								// 7 : �Ǽ��縮 2
								// 8~10 : ����

	short		sEquipItem[10];	// 0 = ���
								// 1 = ����
								// 2 = �Ӹ� �׼�����
								// 3 = �� �׼�����
								// 4 = ������ �� ����
								// 5 = ����   �� ����
								// 6 = ������ �Ǽ��縮
								// 7 = ����   �Ǽ��縮
								// 8 = ����
								// 9 = �Ź�
								// �������� �������� ���� ������ id == -1

	short		sHP;
	short		sMaxHP;

	BYTE		tDir;			// �����ִ� ����

	DWORD		dwAbnormal		// �����̻�����(Damaged)

								// const DWORD ABNORMAL_NONE			=	0;
								// const DWORD ABNORMAL_POISON			=	1;
								// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
								// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
								// const DWORD ABNORMAL_BLIND			=	1 << 4;
								// const DWORD ABNORMAL_LIGHT			=	1 << 5;
								// const DWORD ABNORMAL_FIRE			=	1 << 6;
								// const DWORD ABNORMAL_COLD			=	1 << 7;
								// const DWORD ABNORMAL_HASTE			=	1 << 8;
								// const DWORD ABNORMAL_SHIELD			=	1 << 9;
								// const DWORD ABNORMAL_HIDE			=	1 << 10;
								// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
								// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
								// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
								// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
								// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
								// const DWORD ABNORMAL_HIEXP			=	1 << 16;
								// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
								// const DWORD ABNORMAL_NOCHAT			=	1 << 18;

								// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
								// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
								// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
								// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
								// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;

								// const DWORD OPERATION_MODE			=	1 << 31;	// ��� ���� �ɼ�

	short		sCityRank;		// �ùε��

	int			iGuildIndex;	// ��� �ε���
	VarChar		szGuildName;	// ��� �̸�
	short		sVersion;		// ��� ���� ����
	BYTE		tClass;			// Ŭ���� ����
	BYTE		tKillState;		// ���������� �Ǵ�
								// 0 : �������� ����
								// 1 : ������ ����
	
	VarChar		strLoveName		//ȣĪ[��Ī] //-- yskang 0.1

	short		sEBodyItem[4];	// 0 = �Ӹ�
								// 1 = ��
								// 2 = ��
								// 3 = �ٸ�
								// �������� �������� ���� ������ id == -1
*/

const BYTE CHAR_DATA			=	2;
/*
(C <- S)		// Send Character Data

	VarChar		szName;			// User Name

	short		sSTR;			// ��
	short		sCON;			// �ǰ�
	short		sDEX;			// ��ø
	short		sVOL;			// ����
	short		sWIS;			// ����
	short		sAbilitySum;	// �⺻ �ɷ�ġ�� ��

	DWORD		dwSkin;			// �Ǻλ�
	DWORD		dwHair;			// �Ӹ���
	BYTE		Gender;			// ����
	TCHAR		strFace[10];	// �󱼸��

	DWORD		dwExp;			// ����ġ
	DWORD		dwXP;			// ���а���ġ

	short		sSkillPoint;	// ��ų ����Ʈ
	short		sPA;			// ���� ����Ʈ

	short		sMaxHP;			// �ִ� HP
	short		sHP;			// ���� HP
	short		sMaxPP;			// �ִ� PP
	short		sPP;			// ���� PP
	short		sMaxSP;			// �ִ� SP
	short		sSP;			// ���� SP

	DWORD		dwDN;			// ������
	short		sCityRank;		// �ùε��

	short		sLevel;			// ����
	BYTE		byClass;		// Ŭ���� (���� = 0, ������ = 1, ���� = 2, �ѱ� = 3)

	typedef struct _tagSkill	// Skill
	{
		short	sSid;
		BYTE	tLevel;
	}UserSkill[TOTAL_SKILL_NUM];

	BYTE		tHavePsi;		// ���̿��� ��������
	typedef	struct _tagPsionic	// ���̿��� ���������� 1�̻��� ��� ����
	{
		short	sSid;
		BYTE	tOnOff;
	} UserPsi[tHavePsi];

	typedef struct _tagItem		// Item;
	{
		short	sLevel;				// ������ ���� ����@@@@@@@
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;
		BYTE	tMagic[6];		// �����Ӽ�
		BYTE	tIQ;			// Item Quality
	}UserItem[TOTAL_ITEM_NUM];

	short		sEbody[4];		// ������ E_Body sSid, ������ -1

	DWORD		dwExpNext;		// ���� ������ �Ǳ����� �ʿ� ����ġ

	DWORD		dwAbnormal		// �����̻�����(Damaged)

								// const DWORD ABNORMAL_NONE			=	0;
								// const DWORD ABNORMAL_POISON			=	1;
								// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
								// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
								// const DWORD ABNORMAL_BLIND			=	1 << 4;
								// const DWORD ABNORMAL_LIGHT			=	1 << 5;
								// const DWORD ABNORMAL_FIRE			=	1 << 6;
								// const DWORD ABNORMAL_COLD			=	1 << 7;
								// const DWORD ABNORMAL_HASTE			=	1 << 8;
								// const DWORD ABNORMAL_SHIELD			=	1 << 9;
								// const DWORD ABNORMAL_HIDE			=	1 << 10;
								// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
								// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
								// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
								// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
								// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
								// const DWORD ABNORMAL_HIEXP			=	1 << 16;
								// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
								// const DWORD ABNORMAL_NOCHAT			=	1 << 18;
								
								// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
								// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
								// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
								// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
								// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;

								// const DWORD OPERATION_MODE			=	1 << 31;	// ��� ���� �ɼ�

	short		sChangeClass[CLASS_NUM];	// ��������

  	int			iGuildIndex;	// ��� �ε���
	VarChar		szGuildName;	// ��� �̸�
	short		sVersion;		// ��� ���� ����

	short		sMaxWeight;
	short		sCurWeight;
*/

const BYTE NPC_INFO				= 3;
/*
(C <- S)		// Send NPC Info

	BYTE		Mode;			// 01(INFO_MODIFY)	: NPC ���� ����
								// 02(INFO_DELETE)	: NPC ���� ����

	short		nid;			// NPC index
	short		pid;			// NPC Picture Index
	VarChar		szName;			// NPC Name
	short		nPosX;			// X Position
	short		nPosY;			// Y Position
	BYTE		tState;			// NPC ����
								// 00	: NPC Dead
								// 01	: NPC Live

	BYTE		tNpcKind;		// 00	: Monster
								// 01	: NPC

  	short		sMaxHP;			// �ִ� HP
	short		sHP;			// ���� HP

	short		sStepDelay;		// �ȴ� �ӵ� ����

	BYTE		tColor;			// ���� ���� ����

	short		sDimension;		// ���� �ʿ� �����Ҽ� �ִ� ���� ��ȣ
*/

const BYTE	ITEM_INFO			= 4;
/*
	short		sTotalIndex;	// �� ������ ���� ���� ��

	short		sSid;
	short		sPid;
	Varchar		strName;
	Varchar		strText;
	BYTE		byNeedSP;
	DWORD		iDN;
	BYTE		byRLevel;
	BYTE		byClass;
	BYTE		byWear;
	short		sDuration;
	short		sDefense;
	BYTE		byAX;
	BYTE		byAY;
	BYTE		byAZ;
	BYTE		byHitRate;
	BYTE		byCritical;
	short		sAttackDelay;
	BYTE		byRange;
	BYTE		byErrorRate;
	short		sBullNum;
	BYTE		byBullType;
	BYTE		bySubAttack;
	BYTE		bySubDefense;
	BYTE		bySubCure;
	short		sRepairHP;
	short		sRepairPP;
	short		sRepairSP;
	short		sEvent;

	...							// �ش� ����ŭ �ݺ��Ѵ�.
*/

const BYTE	SYSTEM_MSG			= 5;
/*
	(C <- S)		// �������� Ŭ���̾�Ʈ�� �޼����� ������.

	BYTE		type;			// 00 : Ư���� �޼���, �ݵ�� �������� �ϴ°�, �޼��� �ڽ���
								//		Ŭ���̾�Ʈ�� ���������Ѵ� (ERROR MESSAGE).

								// 01 : Normal Message (Infomation Message)
								// 02 : Error Message (�������� ���������� ���� ��)
								// 03 : NPC Message (NPC�� �ϴ� ��)
								// 04 : ��� ��ü ��ũ�� �޼���
								// 05 : Dissconnect Message (���Ⱓ(�ð�)�� ���� �������� ������)
	Varchar		Msg;
*/

const BYTE CLIENT_TIMER			= 6;
/*
	(C -> S)		// Ŭ���̾�Ʈ���� 1���̻� ��Ŷ������ ������ ������.
	// ���ް� ����
*/

const BYTE SET_CLIENT_WORLD		= 7;
/*
	(C <- S)		// ������ �����Ѵ�

	BYTE		type;			// 01 : ���ӻ� �ð�
								// 02 : ��
								// ...

	// 01 : ���ӻ� �ð�
		BYTE		tTime;		// �ð�(0~24)

	// 02 : ��
		BYTE		OnOff;			// 00 : ����
									// 01 : ��

*/

const BYTE CHANGE_ITEM_INFO		= 8;
/*
	(C <- S)		// ���� ���� �����϶� ������.

	int			uid;			// User index

	short		sEquipItem[10];	// 0 = ���
								// 1 = ����
								// 2 = �Ӹ� �׼�����
								// 3 = �� �׼�����
								// 4 = ������ �� ����
								// 5 = ����   �� ����
								// 6 = ������ �Ǽ��縮
								// 7 = ����   �Ǽ��縮
								// 8 = ����
								// 9 = �Ź�
								// �������� �������� ���� ������ id == -1
*/

const BYTE USERINFO_REQ			= 9;
/*
	(C -> S)		// Ư�� USER, NPC�� ������ ��û�Ѵ�.

	int			uid;			// User or NPC ID
*/

//#################################################################
//	Login UI	(10 ~ 29)
//#################################################################

const BYTE SESSION_LOGIN_REQ	=	10;
/*
	(C -> S)		// Session Login Request

	VarChar		id[ACCOUNT_LENGTH];
	VarChar		password[PASSWORD_LENGTH];
*/

const BYTE SESSION_LOGIN_RESULT	=	11;
/*
	(C <- S)		// Session Login Result

	BYTE		result;			// 01 	: Login Success
								// else	: Login Fail
	// ������ ���
	// ������ �� ����

	// ������ ���
	BYTE		error_code;		// 01	: �������� �ʴ� ID
								// 02	: Password ����ġ
								// 03	: ���� Account �����
								// ...
								// 255	: �� �� ���� ����
*/

const BYTE ACCOUNT_LOGIN_REQ =		12;
/*
	(C -> S)		// Account Login (��ȣȭ ����)

	VarChar		id[ACCOUNT_LENGTH];
	short		myserver;		//	1 - ��ī�罺
									2 - ���ĵ���
									3 - ��������
									4 - �ʸ���
									5 - �ƽ�Ʈ
									6 - �׶���
									7 - �似�콺
									8 - �ж��
									9 - ���̳�Ʈ
									10- Ÿ����	
*/

const BYTE ACCOUNT_LOGIN_RESULT =	13;
/*
	(C <- S)	// Account Login Result (��ȣȭ ����)

	BYTE		result;			// 01	: Account Login Success
								// else : Account Login Fail
	// ������ ��� -------
	BYTE		nErrorCode;		// 01	: Invaild Account
								// 02	: ���� �������� �̹� �������� �����Ͽ� �ֽ��ϴ�.
								// ...
								// 255	: �˼� ���� ����

	// ������ ��� -------
	BYTE		nChar;			// Exist Character Number

	// nChar >= 1 �ΰ�� nChar�� ����ŭ �ݺ�
	{
	BYTE		nIndex;						// Character Index
	VarChar		szName[CHAR_NAME_LENGTH];	// 01 ��° Character
	short		STR;
	short		CON;
	short		DEX;
	short		VOL;
	short		WIS;
	DWORD		Skin;			// �Ǻλ�
	DWORD		Hair;			// �Ӹ���
	BYTE		bGender;		// ��, ��
	Varchar		szFace[10];		// �󱼸��

	BYTE		Class;			// ���� = 0, ������ = 1, ���� = 2, �ѱ� = 3
	short		Level;
	short		HP;
	short		PP;
	short		SP;

  	typedef struct _tagSkill	// Skill
	{
		short	sSid;
		BYTE	tLevel;
	}UserSkill[TOTAL_SKILL_NUM];

	char		strWearItem[20];// �����ϰ� �ִ� ������ ����Ʈ
								// �׸���ȣ[2] * EQUIP_ITEM_NUM
								// �׸���ȣ == -1 �̸� �������� ����

	short		sEBodyItem[4];	// 0 = �Ӹ�
								// 1 = ��
								// 2 = ��
								// 3 = �ٸ�
								// �������� �������� ���� ������ id == -1

  	varchar		strIPAddr[20];	// �� ĳ���Ͱ� �پ���� ����
	int			nPort;			// �� ĳ���Ͱ� �پ���� ������ Listen��Ʈ
	}

	short	myserver;
	varchar	strAccount[ACCOUNT_LENGTH];
*/

const BYTE GAME_START_REQ =				14;
/*
	(C -> S)	// Game Login  (��ȣȭ ����)

	VarChar		szCharName[CHAR_NAME_LENGTH];

	short		myserver;		// CharInfoServer���� ���� ��	

	varchar		szAccountID[ACCOUNT_LENGTH+1];

*/

const BYTE GAME_START_RESULT =			15;
/*
	(C <- S)	// Game Login Result  (��ȣȭ ����)

	BYTE		result;			// 01	: Login Success
								// else	: Login Fail

	// ������ ��� ------		// 01	: Invaild ID
								// 02	: DB�� ���� ID
								// 03	: Invalid Zone Number
								// 04	: Invalid Position
								// 05	: ���� ID �����
								// ...
								// 255	: �� �� ���� ����

	short		CurrZone;		// ���� Zone Number
	int			uid;			// User Index
	short		PosX;			// Map �� X ��ǥ
	short		PosY;			// Map �� Y ��ǥ

	BYTE		tDir;			// ���� �����ִ� ����

	BYTE		tTime;			// �ð�(0~24)
	BYTE		tMinute;		// ��  (0~60)

    Varchar		public_key;		// int64
	DWORD		dwSerial;		// �ø��� ���� ��ȣ
*/

const BYTE NEW_ACCOUNT_REQ =		16;
/*
	(C -> S)	// New Session Account Req

	VarChar	szUserID[ACCOUNT_LENGTH];
	VarChar	szPassword[PASSWORD_LENGTH];
	VarChar	szRealName[40];
	VarChar	szSocNo[15];
	VarChar	szAddress[80];
	VarChar	szTel[20];
	VarChar	szEmail[30];
	VarChar	szQuiz01[50];
	VarChar	szAnswer01[50];
*/

const BYTE NEW_ACCOUNT_RESULT =		17;
/*
	(C <- S)	// New Session Account Result
	BYTE	result;				// 01 	: New Account Create Success
								// else	: New Account Create Fail
*/

const BYTE	NEW_CHAR_REQ		= 18;
/*
	(C -> S)	// Make New Character (��ȣȭ ����)
	VarChar		szAccount[ACCOUNT_LENGTH];			// Account
	BYTE		nIndex;								// Char Index (���° ĳ����?)
	VarChar		szCharName[CHAR_NAME_LENGTH];		// Char Name

	DWORD		Skin;				// �Ǻλ�
	DWORD		Hair;				// �Ӹ���
	BYTE		bGender;			// ��, ��
	char		szFace[10];			// �󱼸��
									// 1 : �Ӹ�
									// 2 : ��
									// 3 : ��
									// 4 : ��
									// 5 : ��
									// 6 : �Ǽ��縮 1
									// 7 : �Ǽ��縮 2
									// 8~10 : ����

	BYTE		Class;				// ���� = 0, ������ = 1, ���� = 2, �ѱ� = 3

*/

const BYTE	NEW_CHAR_RESULT		= 19;


const BYTE	DELETE_CHAR_REQ		= 20;
/*
	(C -> S)	// Delete Character (��ȣȭ ����)

	VarChar		szAccount[ACCOUNT_LENGTH];		// Account
	VarChar		szCharName[CHAR_NAME_LENGTH];	// Char Name
	BYTE		nIndex;							// Char Index (���° ĳ����?)
	Varchar		szJumin[13];					// �ֹε�Ϲ�ȣ
	Varchar		szIP[15];						// ������ ��ǻ���� IP
*/

const BYTE	DELETE_CHAR_RESULT	= 21;
/*
	(C <- S)	// Delete Character Result (��ȣȭ ����)
	BYTE		result;				// 01	: Delete Character Success
									// else : Delete Character Fail

	// �����ΰ��
	BYTE		nIndex;				// Character Index

	// ������ ��� -------
	BYTE		nErrorCode;			// 01	: Invaild Account
									// 02	: Invaild Char Name
									// 03	: Invaild Char Index
									// 04	: Database Error
									// 05	: Invalid Jumin Bunho
									// 06	: �ֹι�ȣ�� �z��
									// 07	: ��� �������϶��� ��带 ���� �ػ��ϰ� ����..
									// ...
									// 255	: �˼� ���� ����
*/

const BYTE	LOGOUT_REQ			= 22;
/*
	(C -> S)	// Log Out Req
	// ���ް� ����
*/

const BYTE	REROLL_REQ			= 23;


const BYTE	REROLL_RESULT		= 24;


const BYTE	RESTART_REQ			= 25;
/*
	(C -> S)	// Restart����
*/

const BYTE	RESTART_RESULT		= 26;
/*
	(C <- S)	// RESTART_REQ	Result

	BYTE		result;			// 01	: Restart Success
								// else : Restart Fail
*/

const BYTE	CHECK_ID_REQ		= 27;
/*
	(C -> S)	// Check Character ID Request
	
	VarChar		szCharID[CHAR_NAME_LENGTH];	// ĳ�����̸�
*/

const BYTE	CHECK_ID_RESULT		= 27;		// Packet ��Ȱ��
/*
	(C <- S)	// Check Character ID Result
	
	BYTE		tResult;		// 00 : ���� �̸��� ĳ���Ͱ� �̹� �����մϴ�.
								// 01 : ����Ͻ� �� �ִ� ���̵� �Դϴ�.
*/

//#################################################################
//	CHAT, BBS		(28 ~ 43)
//#################################################################

const BYTE	MOVE_CHAT_REQ		= 28;
/*
	(C -> S)	// Chat Move Req
	short		will_x;				// �����̷��� �ϴ� ��ǥ�� X ��
	short		will_y;				// �����̷��� �ϴ� ��ǥ�� Y ��
*/

const BYTE	MOVE_CHAT_RESULT	= 29;
/*
	(C <- S)	// Chat Move Result

	BYTE		result;				// 01	: Move Success
									// else	: Move Fail

	// ������
	int			uid;				// User Index
	short		will_x;				// �����̷��� �ϴ� ��ǥ�� X ��
	short		will_y;				// �����̷��� �ϴ� ��ǥ�� Y ��
*/

const BYTE	CHAT_REQ			= 30;
/*
	(C -> S)	// Chat Req

	BYTE		Type;				// 01 : Normal Chat
									// 02 : �ӼӸ�
									// 03 : 8 ȭ�� ��ħ
									// 04 : Bunch Chat
									// 05 : Buddy Chat
									// 06 : Buddy ��û
									// 07 : Buddy Ż��
									// 10 : ���� ��� - ������ ����� MOVE_CHAT_RESULT �� ����
									// 11 : �Ӹ����
									// 12 : �Ӹ��ź�
									// 13 : �λ�
									// 14 : ����
									// 15 : ���� ��ȯ		--������ ���ʿ� ����� MOVE_CHAT_RESULT �� ����
									// 16 : ���� ���� �̵�  -- ������ ���ʿ� ����� MOVE_CHAT_RESULT �� ����
									// 17 : ���� ������ó�� ���� ��ȯ
									// 18 : ��� ����
									// 19 : ��� �ػ�
									// 20 : ��� Ż��
									// 21 : ��� �߹�
									// 22 : ������ �ޱ�, �ź�
									// 23 : ��� ����
									// 24 : ��� ���� ����
									// 25 : ��ü ä��	-- ���� ��ڸ� �Ҽ�����...
									// 26 : �ʵ� �����
									// 27 : �ʵ��� �׺�
									// 28 : PK������ ����
									// 29 : 1�� ���� ����
									// 30 : ���� ��� ����
									// 31 : ������ ��û ��带 �����ش�.
									// 32 : ��Ʈ���� ������ ���� �ݴ´�.
									// 33 : ��� ���� �̾�
									// 34 : ��� ���� ����
									// 35 : ��� ����ȯ�� ��������Ʈ
									// 36 : ���� ��ȯ

	VarString	UserID(CHAR_NAME_LENGTH)	// 02�� ��� ID ����

	VarString	Msg;						// �޼���(6, 11, 12, 13, 14 �� ��� �޼��� ����)

	// Ŭ���̾�Ʈ���� �Ľ��ؼ� type���� conversion
	|--------------------------------------------------------------------------------
	|	ä�� ��ɾ� : '/' �� ���۵ȴ�.
	|--------------------------------------------------------------------------------
	|	���		| ���� ��ɾ�	| �ѱ� ��ɾ�	|	����
	|---------------|---------------|------------------------------------------------
	|*	����/����	| /TO ID		| /�Ӹ� ID 		|	�ش� ID�� ���� �ӼӸ� ����, ����
	|	(client)	| /GUILD		| /��� 		|	�ڽ��� ���� �ӼӸ� ����/����(C)
	|				| /BUDDY		| /����			|	�ڽ��� BUDDY �� �ӼӸ� ����/����(C)
	|				| /SHOUT		| /��ħ			|	��ġ�� ��� ����/����(N)
	|---------------|---------------|-------------------------------------------------
	|	�ӼӸ�		| /TO ID Msg	| /�Ӹ� ID Msg	|	�ش� ID ���� �ӼӸ�
	|				| /GUILD Msg	| /���	Msg		|	�ڽ��� ������ ��ü��ȭ
	|				| /BUDDY Msg	| /����	Msg		|	�ڽ��� BUDDY �� �ӼӸ�(C)
	|				| /SHOUT Msg	| /��ħ	Msg		|	����ڸ� �߽����� 8 ȭ�� ��ħ, ���׹̳� �Һ�(C)
	|---------------|---------------|------------------------------------------------
	|	���ã��	| /FI ID		| /ã�� ID		|	������ ID �� ������ ���� üũ
	|				|				| 				|	������ ��Ŷ���� ó���Ѵ�
	|---------------|---------------|------------------------------------------------
	|*	���Űź�	| /EX ID		| /���� ID		|	���Űź� ����/���� (�ش� ID�� ��� �޼��� �ź�)
	|---------------|---------------|------------------------------------------------
	|	�Ӹ����	| /TOY			| /�Ӹ���		|
	|---------------|---------------|------------------------------------------------
	|	�Ӹ��ź�	| /TON			| /�Ӹ���		|
	|---------------|---------------|------------------------------------------------
	|*���Űźθ���Ʈ| /EXLIST		| /���ܸ��		| ���� ���Űź����� ID���� �����ش�.
	|---------------|---------------|------------------------------------------------
	|*����/�Ҹ� ����| /MUSIC		| /����			| ���� ON/OFF(N)
	| (client)		| /SOUND		| /�Ҹ�			| ȿ���� ON/OFF(N)
	|---------------|---------------|------------------------------------------------
	|	�ŷ�		| /TRADE ID		| /�ŷ� ID		| �ش� ID�� ���� �ŷ�â�� ����.(N)
	|---------------|---------------|------------------------------------------------
	|	��ġ		| /MOVE X Y		| /�̵� X Y		| �ش���ġ�� �̵�(N)
	|---------------|---------------|------------------------------------------------
	| �������    | /MOP �̸�     | /�� �̸�      | �ش� �̸��� ���� ��ó�� �̵�
	|---------------|---------------|------------------------------------------------
	| ���ͼ�ȯ	| /MOPCALL �̸�	| /����ȯ �̸�  | �ش� �̸��� ���͸� ��ڱ�ó�� ��ȯ
	|---------------|---------------|------------------------------------------------
	| ���� ��ȯ     | /CALL �̸�    | /��ȯ �̸�    | �ش� �̸��� ������ ��� ��ó�� �̵�
	|---------------|---------------|------------------------------------------------
	| ���� �����̵� | /REMOTE �̸�  | /���� �̸�  X Y | �ش� �̸��� ������ Ư����ġ�� �̵�
	|---------------|---------------|------------------------------------------------
	| ��� ����	| /CLOAKY		| /����			| ��ڸ� ������·� �����.
	|---------------|---------------|------------------------------------------------
	| ���� ���� ����| /CLOAKN		| /����			| ��� ������¿��� �Ϲ� ���·� �����.
	|---------------|---------------|------------------------------------------------
	| ��ü ä��		| /ANNOUNCE		| /��ä			| ������ ��� �������� �޼����� ������.
	|---------------|---------------|------------------------------------------------
	| ���� �ʴ�		| /INVITE �̸�  | /�ʴ� �̸�	 | �ش� �̸��� ������ ���� ���Խ�Ų��.
	|---------------|---------------|------------------------------------------------
	| ���� Ż��		| /LEAVE		| /Ż��			 | �ڽ��� ���𿡼� Ż���Ѵ�.
	|---------------|---------------|------------------------------------------------
	| ���� Ż��		| /LEAVE  �̸�	| /Ż��  �̸�	 | �������� Ư�� ������ ���𿡼� Ż���Ų��.
	|---------------|---------------|------------------------------------------------
	| ��� ������	| /MARK  �̸�	| /����  BMP	 | (Client��ü)��� ������ ����Ѵ�.
	| ��� ����		| /				| /��尡��		 | �ش� ��忡 �����Ѵ�.
	| ��� �ػ�		| /				| /����ػ�		 | �ش� ��带 �ػ��Ѵ�.
	| ��� Ż��		| /				| /���Ż��		 | �ش� ��忡�� Ż���Ѵ�.
	| ��� �߹�		| /				| /����߹�	�̸� | �ش� ��忡�� �渶�� Ư�� ������ Ż���Ų��.
	|---------------|---------------|------------------------------------------------
	| ������ �ޱ�	| /				| /�����۹ޱ�	 | ( ITEM_MODE_CHAT OFF)������ �ޱ�ɼ��� Ȱ��ȭ�Ѵ�.
	| ������ �ź�	| /				| /�����۰ź�	 | ( ITEM_MODE_CHAT ON )������ �źοɼ��� Ȱ��ȭ�Ѵ�.
	|---------------|---------------|------------------------------------------------
	| ��� �ʵ���	| /				| /���� ����̸� | �ش� ��带 ���� �ʵ����� ��û(/���� Guild_ID ����̸�)
	|---------------|---------------|------------------------------------------------
	| �ʵ��� �׺�	| /				| /�׺�			 | �ش� ��带 ���� �׺��� �����Ѵ�.
	|---------------|---------------|------------------------------------------------
	| PK������	����| /PK			| /������		 | ���� ������ PKȽ���� ����.
	|---------------|---------------|------------------------------------------------
	| 1�� ��������	| /COPY			| /ī��	ID		 | ������ �����Ͽ� ������ ��ҷ� �̵��Ѵ�.
	|---------------|---------------|-----------------------------------------------
	| ���� ��ü����|/GUILD		| /����		 | ���� ��ü ����� �����ش�.
	|---------------|---------------|------------------------------------------------
	| ��û��� ���� | /				| /��û���		 | ������� ��û�� ��ü ��� ����� �����ش�.
	|---------------|---------------|------------------------------------------------
	| �������� �ݱ� | /				| /����			 | ��Ʈ���� ������ ���� �ݴ´�.
	|---------------|---------------|------------------------------------------------
	| ������ �ο�	| /endow		| /�ο�			 | �渶�� �α渶�� �����Ѵ�.
	|---------------|---------------|------------------------------------------------
	| ������ ���� | /stop			| /��������		 | �α渶�� �Ǹ��� �ݳ��Ѵ�.

  // * �� �ִ� ��ɾ�� Ŭ���̾�Ʈ���� ��üó��
*/

const BYTE	CHAT_RESULT			= 31;
/*
	(C <- S)	// Chat Result

	BYTE		result;				// 01	: ����
									// else	: ����

	// ������ ���
	BYTE		error_code;			// 01	: ���׹̳� ����(��ġ���� ���)
									// 02	: �Ӹ� �ź���
									// 03	: ��� ���� (�Ӹ�, ���ã���� ���)
									// 04	: ������ ��尡 �ϳ��� ����(��� �Ӹ�)
									// 05	: ������ Buddy�� �ϳ��� ����(Buddy �Ӹ�)
									// 06	: �߸��� �������̵�(�Ӹ�, ���ã���� ���)
									// 07	: �ش� ��尡 �������� �ʴ´�.
									// 08	: �ش� ��忡 ������ ������ �ƴϴ�.
									// 09	: �̹� �ٸ� ��忡 ������ ������.
									// 10	: ��� ¯	������ ����.
									// 11	: �ִ� �ο����� �Ѿ���.
									// 12	: ����尡 �������̴�.
									// ...
									// 255	: �˼� ���� ����

	// ������ ���
	BYTE		Type;				// 01 : Normal Chat
									// 02 : �ӼӸ�
									// 03 : 8 ȭ�� ��ħ
									// 04 : Guild Chat
									// 05 : Buddy Chat
									// 10 : ���ã��
									// 11 : �Ӹ����
									// 12 : �Ӹ��ź�

	int			uid;				// User Index		(Type�� 01~ 10 ���̸� ����)
	VarString	Name;				// Character Name	(Type�� 01~ 10 ���̸� ����)
	VarString	Msg;				// Message			(Type�� 01~ 09 ���̸� ����)
*/

const BYTE	FIND_USER_REQ		= 32;
/*
	(C -> S)	// User �� ���������� Ȯ��

	VarString	UserName[CHAR_NAME_LENGTH]	// User Name
*/

const BYTE	FIND_USER_RESULT	= 33;
/*
	(C <- S)	// Find User Result

	BYTE		result;				// 00	: ����
									// 01	: �߸��� �������̵�
									// 02	: ��� ����
									// ...
									// 255	: �˼� ���� ����

	VarString	UserName;			// Character Name
*/

const BYTE	BBS_OPEN			= 34;
/*
	(C <- S)	// BBS�� Open �Ѵ�.

	short	BBS_NUM;				// BBS Number
	short	nCount;					// �ټ�
	varchar nData;					// �Խù� ������(��ȣ, �ۼ��� ID, �ۼ���, ��ȸ��, ����)
									// int		iIndex,
									// Varchar	strWriter,
									// Varchar	strTime,
									// int		iView,
									// Varchar	strTitle

*/

const BYTE	BBS_NEXT			= 35;
/*
	(C -> S) // BBS�� �Խù� ������ �д´�.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// �а��� �ϴ� �Խù� ������ ���۹�ȣ
*/

const BYTE	BBS_NEXT_RESULT		= 36;
/*
	(C <- S)	// ���� �Խù� ������ ������.

	short	BBS_NUM;				// BBS Number
	short	nCount;					// �ټ�
	varchar nData;					// �Խù� ������(��ȣ, �ۼ��� ID, �ۼ���, ��ȸ��, ����)
									// int		iIndex,
									// Varchar	strWriter,
									// Varchar	strTime,
									// int		iView,
									// Varchar	strTitle
*/

const BYTE	BBS_READ			= 37;
/*
(C -> S) // �Խù��� ������ �д´�.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// �а��� �ϴ� �Խù��� ��ȣ
*/

const BYTE	BBS_READ_RESULT		= 38;
/*
(C <- S) // �Խù��� ������ ������.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// �а��� �ϴ� �Խù��� ��ȣ
	Varchar Writer;					// �ۼ���
	Varchar Title;					// ����
	Varchar Time;					// �ۼ�����
	VarData Contents;				// ����
*/

const BYTE	BBS_WRITE			= 39;
/*
	(C -> S) // �Խù��� �ۼ��Ѵ�.

	short	BBS_NUM;				// BBS Number
	VarChar	Title;					// �Խù� ����
	VarData	Contents;				// �Խù� ����
*/

const BYTE	BBS_EDIT			= 40;
/*
	(C -> S) // �Խù��� �����Ѵ�.

	short	BBS_NUM;				// BBS Number
	int		nIndex;					// �Խù� ��ȣ
	VarChar	Title;					// �Խù� ����
	VarData	Contents;				// �Խù� ����
*/

const BYTE	BBS_ERROR			= 41;
/*
	(C <- S)	// �Խ��� ���õ� ���� ����

	BYTE		result;				// 01	: ����
									// 02	: ���� ����(�ڽ��� �Խù��� �ƴϰų� ��ڰ� �ƴ�)
									// 03	: �Խù��� ������
									// ...
									// 255	: �˼� ���� ����
*/

const BYTE	BBS_DELETE			= 42;
/*
	(C -> S) 	// �Խù��� �����Ѵ�.

	short		BBS_NUM;			// BBS Number
	int			nIndex;				// �Խù� ��ȣ
*/

//#################################################################
//	Item		(43 ~ 63)
//#################################################################
const BYTE	ITEM_BULLNUM		= 43;
/*
	(C <- S)	// �������� ��ź��(��Ƽ���ѷ�)�� ����Ȱ��� �˷��ش�.

	BYTE	tSlot;					// ������ ���Թ�ȣ
	short	sBullBum;				// ����� ��ź��(��Ƽ���ѷ�)
*/

const BYTE	ITEM_DURATION		= 44;
/*
	(C <- S)	// �������� �������� ����Ȱ��� �˷��ش�.

	BYTE	tSlot;					// ������ ���Թ�ȣ
	short	sDuration;				// ����� ������
*/

const BYTE	ITEM_LOAD_REQ		= 45;
/*
	(C -> S) 	// �� �Ǵ� �����Լ� �������� ȹ��

	BYTE	byReqType;				// 1 : ��
									// 2 : ��

	// 1�� ���� ���
	short	sSid;					// ���� �ε���

	// 2�� ���ϰ��
	short	sX;						// �ʿ���
	short	sY;
*/

const BYTE	ITEM_LOAD_RESULT	= 46;
/*
	(S -> C) // ������ �ϰ� �ش� ����Ʈ�� ������.
	BYTE	result;					// 00	: ������ ����(����)
									// 01	: ������

		// 01 ������ ������
		BYTE	ChangedSlotNum;		// ��ȭ�� ������ ����

		typedef struct _tagMoveItem
		{
			BYTE	tSlot;
			short	sLevel;				//@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} MoveItemInfo[ChangedSlotNum];

	// �� ������
	// (C <- S) MONEY_CHANGED�� ����

	// 00 : ���н�
	error_01 : Item Load ������ �����
	error_02 : �߸��� ��ǥ
	error_03 : �켱���� ����
	error_04 : ���Ը� �ʰ��Ͽ���
	error_05 : ����ִ� �κ��� ���� 
	error_08 : �ݴ� Ȯ�� ���� 

	error_06 : ���ɾ������̴�.
	error_07 : �ý��� ���� ����
	error_255 : �˼� ���¿���
*/

const BYTE	ITEM_GIVE_REQ		= 47;
/*
	( C -> S ) // ���濡�� ������, ���� �ٶ�

	BYTE	tType;					// 00	: �ʻ� ����
									// 01	: ���濡�� �ش�

	BYTE	tObject					// 00	: ��
									// 01	: ������
	//  00	: �ʻ� ����

		short		will_x;			// �ʻ󿡼� ��ǥ
		short		will_y;			//

  		//	00	: ���ϰ��
			DWORD	dwDN;				// �� �׼�

		//	01	: �������ϰ��
			BYTE	bySlotId;			// �κ��丮â�� �ε���
			short	sCount				// ��ŭ ����


	//  01	: ���濡�� �ش�(?)

		//	00	: ���ϰ��
			int		uid;				// ���� ����
			DWORD	dwDN;				// �� �׼�

		//	01	: �������ϰ��
			int		uid;				// ���� ����
			BYTE	bySlotId;			// �κ��丮â�� �ε���
			short	sCount				// ��ŭ ����


 // �� ������
// (C <- S) MONEY_CHANGED�� ����
*/

const BYTE	ITEM_GIVE_RESULT	= 48;
/*
	( C <- S ) // ���濡�� �ְ� �Ǵ� �ʿ� ������ �� �κ����� �����.

	BYTE	result;					// 00	: ����
									// 01	: ����

	// 00 ���и�
	BYTE	error;					// 01	: �ټ��ִ� ��밡 ����.
									// 02	: ��� �κ��� ���������� �����ϴ�.
									// 03	: ������ �ź�
									// 04	: �ʻ� �������� ������ ����(?).
									// 05	: �� �κ��� �������� ����.
									// 06	: ��뿡�� ���� ���ټ��� ����.
									// ...
									// 255	: UnKnown Error

	// 01 �����̸�
		typedef struct _tagItem
		{
			byte	bySlot;
			short	sLevel;
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo;

*/


const BYTE	ITEM_TRADE_REQ		= 49;
/*
	( C -> S -> Other C ) // ������..��ȯ�� ���濡�� ��û�Ѵ�

	int			uid;				// ���� uid
	Varchar		UserName;			// ���� �̸�
	BYTE		Mode;				// 00 : ��û���
									// 01 : ��û
									// 02 : �³�
									// 03 : ����
									//...
									// 255: �� �� ���� ����

*/

const BYTE	ITEM_TRADE_RESULT	= 50;
/*
	( Other C -> S -> C ) // ������..��ȯ�� ���濡�� �����Ѵ�

	int			uid;				// ���� uid
	Varchar		UserName;			// ���� �̸�
	BYTE		result;				// 01	: ����(�³�)
									// else	: ����(������...)

	// ������ ���
	BYTE		error_code;			// 01 : ����� ����(���)
									// 02 : �غ�ȵ�
									// 03 : �ٸ������ �ŷ���
									// 04 : ������� ã�� �� ����
									// 05 : �Ÿ��� �ʹ� ������
									// 06 : �ڽ��� ����
									// ...
									// 255: �� �� ���� ����
*/

const BYTE	EXCHANGE_REQ		= 51;
/*
	( C -> S -> C(��δ�))			// ������ ������ ��ȯ�� �Ѵ�.

	int			uid;				// ����� uid

	BYTE		Type;				// 0 = ���
									// 1 = �ڽ��� ��ȯ �³�
									// 2 = ������� ��ȯ �³�
									// 3 = �ڽ��� ������ �ø�
									// 4 = ������� ������ �ø�
									// 5 = �ڽ��� ���� �ø�
									// 6 = ������� ���� �ø�


	// Type �� 3 �� ���
	(C -> S)
	BYTE		tSlotId;			// �κ��丮â�� �ε���		(�ø��� �׸�) �׿ܴ� ������ �׸�
	short		dwCount;			// ��ŭ ����				(�ø��� �׸�)

			(S -> C)
				// Ʈ���̵忡 �ö� ������
			short		sLevel;				// ������ ���� ����		///@@@@@@@@
			short		sItemID;			// ������ �ε���
			short		wDur;				// ������
			short		byBullNum;			// ��ź��
			short		dwCount;			// ��ŭ ����
			BYTE	    tMagic[6];			// �����Ӽ�
			BYTE		tIQ;				// Item Quality

				// �κ��丮���� ������ ������
			BYTE		tSlotId;			// �κ��丮â�� �ε���
			short		sLevel;				// ������ ���� ����
			short		sItemID;			// ������ �ε���
			short		wDur;				// ������
			short		byBullNum;			// ��ź��
			short		dwCount;			// ��ŭ ����
			BYTE	    tMagic[6];			// �����Ӽ�
			BYTE		tIQ;				// Item Quality

	// Type �� 4�� ���
	short		sLevel;				// ������ ���� ����
	short		sItemID;			// ������ �ε���
	short		wDur;				// ������
	short		byBullNum;			// ��ź��
	short		dwCount;			// ��ŭ ����
	BYTE	    tMagic[6];			// �����Ӽ�
	BYTE		tIQ;				// Item Quality

	// Type �� 5 �� ���
	DWORD		dwCount;			// �ŷ��� �ø� �� ���� ��
	DWORD		dwMyMoney;			// �ڱ⿡�� ������

	// Type �� 6 �� ���
	DWORD		dwCount;			// �ŷ��� �ø� �� ���� ��
*/

const BYTE	EXCHANGE_RESULT		= 52;
/*
	( C <- S )						// �����

	BYTE		result;				// 0 = ����
									// 1 = ��ȯ ����
									// 2 = ���� ����
	// ����, ���������� ���
	BYTE		error_code;			// 1	: �߸��� ���� ���̵�
									// 2	: ��ȯ��û�� �� ����ڰ� �ƴ�
									// 3	: �߸��� ������ ����
									// 4 	: �ڽ��� ��ȯ���
									// 5	: Ÿ���� ��ȯ���
									// 6	: �ڽ��� �κ��丮 Ǯ
									// 7	: Ÿ���� �κ��丮 Ǯ
									// ...
									// 255 : UNKNOWN ERROR

	// ��ȯ ������ ���

	// ��������� ���
	DWORD		dwDN				// ������ ����

	BYTE		byItemNumber;		// �� ��ȯ�� ������ �� �Ǵ� ��
		BYTE		bySlotId;			// �κ��丮â�� �ε���
		short		sLevel;				// ������ ���� ����				//@@@@@
		short		sItemID;			// ������ �ε���
		short		sDuration;			// ������
		short		byBullNum;			// ��ź��
		short		sCount				// ��ŭ ���� (��  �Ǵ� ������)
		BYTE	    tMagic[6];			// �����Ӽ�
		BYTE		tIQ;				// Item Quality

		...								// ������ŭ �ݺ��Ѵ�.
*/

const BYTE	ITEM_MOVE_REQ		 = 53;
/*
	( C -> S )						// ������ �̵�( ��)�������, ��������, �κ��丮������ �̵���.. )
	BYTE			tType;			// 0 : �Ϲ� ������(�κ��丮��)
									// 1 : Quick Item ���
									// 2 : Quick Item �̵�, ��� ���

	// 0 : �Ϲ� �����۰��
	BYTE			bySourceSlot;	// ���� �������� �ִ� ���� ��ġ
	BYTE			byDestSlot;		// �ű���� ���� ��ġ

	// 1, 2 �� Ÿ���� Ŭ���̾�Ʈ ��ü ó���Ѵ�.
	>>-----------------------------[ ������ �ڵ� : jjs07 ] ----------------------------->>
	// 1 : Quick Item ���
	BYTE			bySourceSlot;	// �κ��丮 ���� ��ġ
	BYTE			byDestSlot;		// QuickSlotNum ���� ��ġ (0,1,2,3,4)

	// 2 : Quick Item �̵�, ��� ���
	BYTE			bySourceSlot;	// �ش� QuickSlotNum ���� ��ġ
	BYTE			byDestSlot;		// �ű���� ��ġ
									// ��)  ������ = 255
									//		�׿� 0~4���� �̵� ��ȣ
	<<---------------------------------------------------------------------------------<<
*/

const BYTE	ITEM_MOVE_RESULT	 = 54;
/*
	( C <- S )

	BYTE			Result;			// 01 : Success
									// else	: Fail

	// ������ ������ ������
	BYTE			tType;			// 0 : �Ϲ� ������
									// 1 : Quick Item ���				// 1, 2 ���� ���� ����� �ڵ� : jjs07
									// 2 : Quick Item �̵�, ��� ���
									// 3 : ������ Item ���
									// 4 : �Ǹ��� Item ���
									// 5 : ������ Item ���

			// 0 : �Ϲ� ������ ������
			BYTE			ChangedSlotNum;	// ��ȭ�� ������ ����

			typedef struct _tagMoveItem
			{
				byte	bySlot;
				short	sLevel;				// ������ ���� ����//@@@@@@@@@@@
				short	sSid;
				short	sDuration;
				short	sBullNum;
				short	sCount;
				BYTE	tMagic[6];
				BYTE	tIQ;
			} MoveItemInfo[ChangedSlotNum];

			// 1 : Quick Item ��Ͻ�
			BYTE			tQuickSlotNum;	// ����� ���� ��ȣ
			short			sSid;

			// 2 : Quick Item �̵�, ��� ���
			BYTE			tChangedSlotNum;// ��ȭ�� ������ ����

			typedef struct _tagQuickItem
			{
				byte	tSlot;			    // �ش� Quick Slot ��ȣ
				short	sSid;
			} QuickItemInfo[tChangedSlotNum];

		  // 3, 4, 5��� ó��
			BYTE			ChangedSlotNum;	// ��ȭ�� ������ ����

			typedef struct _tagMoveItem
			{
				byte	bySlot;
				short	sLevel;				// ������ ���� ����//@@@@@@@@@
				short	sSid;
				short	sDuration;
				short	sBullNum;
				short	sCount;
				BYTE	tMagic[6];
				BYTE	tIQ;
			} MoveItemInfo[ChangedSlotNum];
*/

const BYTE  ITEM_USE_REQ		= 55;
/*
	(C -> S)	// �������� ��� ��û
	BYTE		tType;			// 01 : ��ȸ�� �Ҹ� ������
								// 02 : ���� ��� ������

	// 01 : ��ȸ�� �Ҹ� ������
	BYTE		tSlot			// ����ϰ��� �ϴ� ������

	// 02 : ���� ��� ������
	BYTE		tSlot;			// ����ϰ��� �ϴ� ������
	BYTE		tSid;			// �������� ��ȣ�� � ��ȣ�� ����Ұų�?

*/
const BYTE  ITEM_USE_RESULT		= 56;
/*
	(C <- S)	// �������� ��� �뺸

	BYTE		tType;			// 00 : ����
								// 01 : ����

	// �����ϰ��
	BYTE		tMode;			// 01  : SP, PP, HP �ѹ��� �������� ä���ش�.
								// 08  : ȥ��ġ��
								// 16  : ����ġ��
								// 32  : �ߵ�ġ��
								// 64  : �÷�ġ��
								// 127 : ��� �����̻�ġ��
								// 100 : ��, �ѿ� ����
								// 101 : ��Ż���
								// 102 : ���� ������
								// 103 : ī��Ĩ ������
	// 01 �϶�
	short		sSP_Refill;		// ȸ���� ��ġ
	short		sHP_Refill;
	short		sPP_Refill;

		typedef struct _tagItem	// ����� ������ ����(�������� ���, �����ִ� �Ѽ�)
		{
			byte	bySlot;
			short	sLevel;				// ������ ���� ����//@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo;

	// 08 16 32 64 127 100 101 103: �϶�
	typedef struct _tagItem
	{
		byte	bySlot;
		short	sLevel;				// ������ ���� ����//@@@@@@@@
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;
		BYTE	tMagic[6];
		BYTE	tIQ;
	} ItemInfo;

	// 102 : ���Ǿ������϶�
	byte		bySlot;			// �κ� ����
	DWORD		dwDN;			// ��÷�ȱݾ�

*/

const BYTE	MONEY_CHANGED		= 57;
/*
	(C <- S)	// ������ ���� �뺸

	BYTE		tType;			// 0 : �ŷ� ���϶�
								// 1 : �׿� ������ �����϶�
	// 0 : �ŷ� ���϶�
	DWORD		dwTradeDN;		// �ŷ� â���� �ݾ�
	DWORD		dwDN;			// ������

	// 1 : �׿� ������ �����϶�
	DWORD	dwDN;				// ������
*/

const BYTE	FIELD_ITEM_INFO		= 58;

/*
	(C <- S)					// �ʻ󿡼� �׿��ִ� ������ ������ ������.

	short		sLoopCount;		// ��ü ������ ��

		BYTE		Mode;			// 01(ITEM_INFO_MODIFY)	: FIELD ITEM ����
									// 02(ITEM_INFO_DELETE)	: FIELD ITEM DEL�� ������ ������
									// 03(ITEM_INFO_PICKUP)	: FIELD ITEM �� �ִ� �����۸� �ݴ´�.

		short		nPosX;			// X Position
		short		nPosY;			// Y Position

		short		sSid;			//(-1)�ϰ�� Item�� ����.
		DWORD		dwCount;
		BYTE		tIQ;			// ���� ���� ���� 1�̻� �׿ܴ� 0��

		// Mode == 03(ITEM_INFO_PICKUP) �� ��� �߰�.
		int			uid;			// �ݴ� ����

*/

/*
const BYTE	ITEM_WEIGHT_CHANGE	= 59;
/*
	(C <- S)					// ������ ���Ժ����� �˸���.

	short		sMaxWeight;		// ���� ����ִ� �ִ빫��
	short		sCurWeight;		// ���� ����
*/

const BYTE	SERVER_TIME_REQ		= 59;
/*
	(C -> S)	// ������ ���ӽð�, ���ýð��� ��û�Ѵ�.

	// �������� ����
*/

const BYTE	SERVER_TIME_RESULT	= 59;
/*
	(C <- S)	// ������ ���ӽð�, ���ýð��� �����ش�.

	short		sYear;
	short		sMonth;
	short		sDay;
	short		sHour;
	short		sMinute;
	short		sSecond;
*/

//#################################################################
//	Game PK Button	(62)
//#################################################################

const BYTE PK_BUTTON_REQ			= 62;

//#################################################################
//	Game Main UI	(63 ~ 88)
//#################################################################
const BYTE	QUESTWINDOW_OPEN_REQ	= 63;
/*
	(C -> S)	// Quest Window Open Request
*/

const BYTE	QUESTWINDOW_OPEN_RESULT	= 63;	// Packet ��Ȱ��
/*
	(C <- S)	// Quest Window Open Result

	short		sCount;				// ������ ����Ʈ�� ����
	
	// sCount > 0 �� ���
	short		sQuestNum[sCount];	// ����Ʈ ��ȣ (sCount ��ŭ �ݺ��ؼ� ������)
*/

const BYTE	TRADE_MODE_REQ		= 64;
/*
	(C -> S)	// Trade Mode On/Off Req
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	TRADE_MODE_RESULT	= 65;
/*
	(C <- S)	// Trade Mode On/Off Result
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE DH_DAMAGE_NUM = 66;
/*
 (S -> c)
 byte 1
 short tarID
 byte 0   monster
      1   user
 short num

*/
const BYTE M_SET_HP = 67;
/*
(S- C)
short nid
dword nid
dword hp
*/

const BYTE	OPEN_EQUIP_REQ		= 68;
/*
	(C -> S)	// Equip/Skill Window Open
	// ���ް� ����
*/

const BYTE	OPEN_EQUIP_RESULT	= 69;
/*
	(C <- S)	// Equip/Skill Window Open Result

	short		WeaponInfo[8];
	BYTE		EvadeInfo[4];

	BYTE		Rate[5];			// ��ų ���� ������
*/

const BYTE	CHANGE_WEAPON_REQ	= 70;
/*
	(C -> S)	// ���� ���� (������ , �޼� ���� ��ȯ)
*/

const BYTE	CHANGE_WEAPON_RESULT= 71;
/*
	(C <- S)	// ���� ���� ���

	BYTE		result;			// 00 : ���� ���� �Ұ���
								// 01 : ���� ( �����ÿ��� UserInfo �߻�)

	// result �� �����϶�
	BYTE		tEnable;		// �ش� ���� ��ų�� ���� �ִ��� �Ǵ�
								// 00 : �� �� ����
								// 01 : �� �� ����

	BYTE		tSkillClass		// �ش� ��ų Ŭ����ǥ��
	typedef struct _tagSkill	// Skill
	{
		short	sSid;		// Skill id
		BYTE	tLevel;		// Level
	}UserSkill[SKILL_NUM];	// SKILL_NUM = 5
*/

const BYTE	SKILL_ONOFF_REQ		= 72;
/*
	(C -> S)	// Ư�� ��ų�� ON/OFF �Ѵ�.

	short		sSid;			// Skill ID
*/

const BYTE	SKILL_ONOFF_RESULT	= 73;
/*
	(C <- S)	// ��ų ON/OFF RESULT

	BYTE		result;			// 00 : Fail
								// 01 : Success
	// ������ ���
	short	sSid;		// Skill id
	BYTE	tLevel;		// Level
	BYTE	tOnOff;		// On/Off ����
*/

const BYTE	PSI_CHANGE_REQ		= 74;
/*
	(C -> S)	// ���̿��� ��ȯ �䱸

	short		sSid;			// Psionic ID
*/

const BYTE	PSI_CHANGE_RESULT	= 75;


const BYTE	LEVEL_UP			= 76;//@@@@@@@@@@@@@@@�ٲ�

const BYTE	LEVEL_DOWN			= 77;
/*
	(C <- S)					// level down
								// ��������� USER_STATUS_SKILL_UP_RESULT + LEVEL_UP ���
*/								// ���߿� �ߺ��Ǵ� ������ ����

const BYTE	USER_STATUS_SKILL_UP_REQ= 78;//@@@@@@@@@@@@@@@�ٲ�
/*
	(C -> S)					// PA, Skill�� �ø���.

	BYTE	tType;				// 01 : PA
								// 02 : Skill


	// 01 : PA �ɷ�ġ ����
		BYTE	tPaMaNum;	// 0~4������ +��ȣ

	// 02 : Skill Level ����
		BYTE	tSkillNum;

*/

const BYTE	USER_STATUS_SKILL_UP_RESULT= 79;//@@@@@@@@@@@@@@@�ٲ�


const BYTE	BUDDY_MODE_REQ			= 80;
/*
	(C -> S)	// BUDDY Mode On/Off Req
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	BUDDY_MODE_RESULT		= 81;
/*
	(C <- S)	// BUDDY Mode On/Off Result
	BYTE		Mode;			// 00	: Off
								// 01	: On
*/

const BYTE	BUDDY_USER_CHANGE		= 82;



//#################################################################
//	Move			(88 ~ 106)
//#################################################################
const BYTE	CHANGE_DIR_REQ		= 88;
/*
	(C -> S)	// ������ȯ �䱸

	BYTE		tDir;			//	3 4 5
								//	2 8 6
								//	1 0 7
*/

const BYTE CHANGE_DIR_RESULT	= 89;
/*
	(S -> C)	// ������ȯ ���

	int			uid;			// User id
	BYTE		tDir;			// ����
*/

const BYTE	MOVE_FIRST_REQ		= 90;
/*
	(C -> S)	// Move First Request

	short		will_x;				// �����̷��� �ϴ� ù ��ǥ�� X ��
	short		will_y;				// �����̷��� �ϴ� ù ��ǥ�� Y ��

	short		end_x;				// �����̷��� ������ ��ǥ�� X ��
	short		end_y;				// �����̷��� ������ ��ǥ�� Y ��
*/

const BYTE	MOVE_FIRST_RESULT	= 91;
/*
	(C <- S)	// Move First Result

	BYTE		result;				// 01	: Move First Success
									// else	: Move First Fail

	// ���н�
	int			uid;				// User Index
	short		cur_x;				// ������ ���� x ��ǥ
	short		cur_y;				// ������ ���� y ��ǥ

	// ������
	int			uid;				// User Index
	short		will_x;				// �����̷��� �ϴ� ù ��ǥ�� X ��
	short		will_y;				// �����̷��� �ϴ� ù ��ǥ�� Y ��

	short		end_x;				// �����̷��� ������ ��ǥ�� X ��
	short		end_y;				// �����̷��� ������ ��ǥ�� Y ��
*/

const BYTE	MOVE_REQ			= 92;
/*
	(C -> S)	// Move Req
	short		will_x;				// �����̷��� �ϴ� ��ǥ�� X ��
	short		will_y;				// �����̷��� �ϴ� ��ǥ�� Y ��
*/

const BYTE	MOVE_RESULT			= 93;
/*
	(C <- S)	// Move Result

	BYTE		result;				// 01	: Move Success
									// else	: Move Fail

	// ���н�
	int			uid;				// User Index
	short		cur_x;				// ������ ���� x ��ǥ
	short		cur_y;				// ������ ���� y ��ǥ

	// ������
	int			uid;				// User Index
	short		will_x;				// �����̷��� �ϴ� ��ǥ�� X ��
	short		will_y;				// �����̷��� �ϴ� ��ǥ�� Y ��
*/


const BYTE	MOVE_END_REQ		= 94;
/*
	(C -> S)	// Move Req
	short		end_x;				// �����̷��� �ϴ� ������ ��ǥ�� X ��
	short		end_y;				// �����̷��� �ϴ� ������ ��ǥ�� Y ��
*/

const BYTE	MOVE_END_RESULT		= 95;
/*
	(C <- S)	// Move Result

	BYTE		result;				// 01	: Move Success
									// else	: Move Fail
	// ���н�
	int			uid;				// User Index
	short		cur_x;				// ������ ���� x ��ǥ
	short		cur_y;				// ������ ���� y ��ǥ

	// ������
	int			uid;				// User Index
	short		end_x;				// �����̷��� �ϴ� ������ ��ǥ�� X ��
	short		end_y;				// �����̷��� �ϴ� ������ ��ǥ�� Y ��
*/

const BYTE	RUN_FIRST_REQ		= 96;
/*
	(C -> S)	// Run First Request

	short		w_x1;				// �ٷ��� ù ��ǥ�� X ��
	short		w_y1;				// �ٷ��� ù ��ǥ�� Y ��
	short		w_x2;				// �ٷ��� 2��° ��ǥ�� X ��
	short		w_y2;				// �ٷ��� 2��° ��ǥ�� X ��

	short		end_x;				// �ٷ��� ������ ��ǥ�� X ��
	short		end_y;				// �ٷ��� ������ ��ǥ�� Y ��
*/

const BYTE	RUN_FIRST_RESULT	= 97;
/*
	(C <- S)	// Run First Result

	BYTE		result;				// 01	: Run First Success
									// else	: Run First Fail
	// ���н�
	int			uid;				// User Index
	short		cur_x;				// ������ ���� x ��ǥ
	short		cur_y;				// ������ ���� y ��ǥ

	// ������
	// w_x2, w_y2 �� -1 �̸� �ι�° ��ǥ�δ� �̵� �Ұ�.
	int			uid;				// User Index
	short		w_x1;				// �ٷ��� ù ��ǥ�� X ��
	short		w_y1;				// �ٷ��� ù ��ǥ�� Y ��
	short		w_x2;				// �ٷ��� 2��° ��ǥ�� X ��
	short		w_y2;				// �ٷ��� 2��° ��ǥ�� X ��

	short		end_x;				// �ٷ��� ������ ��ǥ�� X ��
	short		end_y;				// �ٷ��� ������ ��ǥ�� Y ��
*/

const BYTE	RUN_REQ				= 98;
/*
	(C -> S)	// Run Request

	short		w_x1;				// �ٷ��� ù ��ǥ�� X ��
	short		w_y1;				// �ٷ��� ù ��ǥ�� Y ��
	short		w_x2;				// �ٷ��� 2��° ��ǥ�� X ��
	short		w_y2;				// �ٷ��� 2��° ��ǥ�� X ��

*/

const BYTE	RUN_RESULT			= 99;
/*
	(C <- S)	// Run Result

	BYTE		result;				// 01	: Run Success
									// else	: Run Fail
	// ���н�
	int			uid;				// User Index
	short		cur_x;				// ������ ���� x ��ǥ
	short		cur_y;				// ������ ���� y ��ǥ

	// ������
	// w_x2, w_y2 �� -1 �̸� �ι�° ��ǥ�δ� �̵� �Ұ�.
	int			uid;				// User Index
	short		w_x1;				// �ٷ��� ù ��ǥ�� X ��
	short		w_y1;				// �ٷ��� ù ��ǥ�� Y ��
	short		w_x2;				// �ٷ��� 2��° ��ǥ�� X ��
	short		w_y2;				// �ٷ��� 2��° ��ǥ�� X ��
*/

const BYTE	RUN_END_REQ			= 100;
/*
	(C -> S)	// Run End Request

	short		w_x1;				// �ٷ��� ù ��ǥ�� X ��
	short		w_y1;				// �ٷ��� ù ��ǥ�� Y ��
	short		w_x2;				// �ٷ��� 2��° ��ǥ�� X ��
	short		w_y2;				// �ٷ��� 2��° ��ǥ�� X ��

*/

const BYTE	RUN_END_RESULT		= 101;
/*
	(C <- S)	// Run End Result

	BYTE		result;				// 01	: Run End Success
									// else	: Run End Fail

	// ���н�
	int			uid;				// User Index
	short		cur_x;				// ������ ���� x ��ǥ
	short		cur_y;				// ������ ���� y ��ǥ

	// ������
	// w_x2, w_y2 �� -1 �̸� �ι�° ��ǥ�δ� �̵� �Ұ�.
	int			uid;				// User Index
	short		w_x1;				// �ٷ��� ù ��ǥ�� X ��
	short		w_y1;				// �ٷ��� ù ��ǥ�� Y ��
	short		w_x2;				// �ٷ��� 2��° ��ǥ�� X ��
	short		w_y2;				// �ٷ��� 2��° ��ǥ�� X ��
*/

const BYTE	SET_STAEMINA		= 102;
/*
	(C <- S)	// ���׹̳� ������ �����Ѵ�.

	short		sSP;				// ���׹̳� ��
*/


//#################################################################
//	Battle		(106 ~ 130)
//#################################################################
const BYTE SET_XP					= 106;
/*
	(C <- S)	// XP ������ �����Ѵ�.

	DWORD		dwXP;				// XP ��
*/

const BYTE SET_HP					= 107;
/*
	(C <- S)	// HP ������ �����Ѵ�.

	short		sHP;				// HP ��
*/

const BYTE SET_PP					= 108;
/*
	(C <- S)	// PP ������ �����Ѵ�.

	short		sPP;				// PP ��
*/

const BYTE PSI_ATTACK_REQ			= 109;
/*
	(C -> S)	// Psionic Attack Req

	int			TargetID;			// ���ݴ�� ID
	BYTE		PsionicID;			// ���̿��� sid

	// ���̿����� �ڷ���Ʈ�� ��� ���� (�ڷ���Ʈ ���̵�� PSI_TELEPORT �� ���ǵǾ� ����)
	int			PosX;				// �ڷ���Ʈ�� ��ġ��ǥ X
	int			PosY;				// �ڷ���Ʈ�� ��ġ��ǥ Y
*/

const BYTE PSI_ATTACK_RESULT		= 110;
/*
	(C <- S)	// Psionic Attack Result

	BYTE		bSuccess;			// 00 : Attack Fail
									// 01 : Attack Success

	// Attack Miss, Attack Success �� ��� ����, Fail �� ��� bSuccess ������ �����Ѵ�.
	BYTE		PsionicID;			// ���̿��� sid

	int			SourceID;			// ������ ID
	int			DestID;				// ���� ������ ID
*/

const BYTE ATTACK_REQ				= 111;
/*
	(C -> S)	// Attack Request

	short		TargetID;			// Target ID
*/

const BYTE ATTACK_RESULT			= 112;
/*
	(C <- S)	// Attack Result

	BYTE		bSuccess;			// 00	: Attack Fail
									// 01	: Attack Success
									// 02	: Attack Miss

	// Attack Fail �� ��� �Ʒ��� �����ڵ常 ������.
	BYTE		tError;				// 00	: Too Short Attack Delay
									// 01	: Too Long Distance
									// 02	: �ѱ����
									// 03	: ��ź����
									// 04	: ��Ƽ���� Empty
									// 05	: ���׹̳� ����


	// Attack Success, Attack Miss �� ��쿡�� �Ʒ���Ŷ ����
	int			SourceID;			// ������ ID
	int			DestID;				// ���� ������ ID

	// Attack Success �� ��쿡�� ���� (MISS �� ���� �Ʒ����� ���۾���)

	// �������� �ߴ� ��ų �׼�
	BYTE		tActionNum1;		// ��ų�׼� 1 ����
	BYTE		tSkillAction1[tActionNum1];		// Skill Action (�ش� ��ų �׼�ǥ ����, DEFINE �Ǿ�����)
												// 0 : None
												// 1 : Damage Critical
												// 2 : Vital Critical
												// 3 : Delay Critical
												// 4 : Concentrate (PSI)
												// 5 : PSY Acclimate
												// 6 : Fast Cast
												// 7 : Weapon Acclimate
												// 8 : Fast Attack
												// 9 : Out Range
												// 10: Strafe
												// 11: Broken
												// 12: Fixed
												// 13: Overheat
												// 14: ȭ��������
												// 15: �ñⵥ����
												// 16: ��������
												// 17: ����
												// 18: �ߵ�
												// 19: Guard

	// ������� �ߴ� ��ų �׼�
	BYTE		tActionNum2;		// ��ų�׼� 2 ����
	BYTE		tSkillAction2[tActionNum2];		// Skill Action (�ش� ��ų �׼�ǥ ����, DEFINE �Ǿ�����)

	short		HP;					// ���ݹ������� HP
	short		MaxHP;				// ���ݹ������� �ִ� HP
*/
//yskang 0.3 2002-11-6 ����Ǵ� ��Ŷ...
/*
	(C <- S)	// Attack Result

	BYTE		bSuccess;			// 00	: Attack Fail
							// 01	: ���� ���� ����
							// 02	: ���� ���� ����(���� ���Ѱ�)
							// 03 	: ũ��Ƽ�� ���� ����
							// 04   : ũ��Ƽ�� ���� ����(���� ���Ѱ�)



	// Attack Fail �� ��� �Ʒ��� �����ڵ常 ������.
	BYTE		tError;				// 00	: Too Short Attack Delay
									// 01	: Too Long Distance
									// 02	: �ѱ����
									// 03	: ��ź����
									// 04	: ��Ƽ���� Empty
									// 05	: ���׹̳� ����


	// Attack Success, Attack Miss �� ��쿡�� �Ʒ���Ŷ ����
	int			SourceID;			// ������ ID
	int			DestID;				// ���� ������ ID

	short		HP;					// ���ݹ������� HP
	short		MaxHP;				// ���ݹ������� �ִ� HP
*/


const BYTE	DEAD					= 113;
/*
	(C <-S)		// you are dead!!!

	short		uid;				// USER, NPC ID
	short		posx;				// X Position
	short		posy;				// Y Position
*/

const BYTE	LIVE_REQ				= 114;
/*
	(C -> S)	// Revival Request

	(C <- S)	// ��������� USER_INFO�� �˷��ش�.
*/


const BYTE	PSI_TOWN_POTAL			= 115;
/*
	(C <- S)	// PSI_ATTACK_REQ������ ����� ��ȯ(����ȭ �ʿ�)

	BYTE		tType;				// 00 : Fail
									// 01 : Success

	// �����϶���...
	BYTE	tSuccess				// 00 : ���� ���̴�
									// 01 : �ٸ� ���̴�.

	int		uid;					// ����� uid

	short	nPosX;					// X Position
	short	nPosY;					// Y Position
	short	sZone;					// Load Zone Number
*/

const BYTE	SET_SPEED_MONSTER		= 116;
/*
	(C <- S)	// �̵� �ӵ� ��ȭ�� �˷� �ش�.

	int		uid;					// �� uid
	short	sDelay;					// ��ȭ�� �ӵ��� ǥ��
*/

const BYTE	SET_USER_STATE			= 117;
/*
	(C <- S)	// ���� ���� ��ȭ������ ������.

	int		uid;			// uid
	DWORD	dwAbnormal		// �����̻�����(Damaged)

							// const DWORD ABNORMAL_NONE			=	0;
							// const DWORD ABNORMAL_POISON			=	1;
							// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
							// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
							// const DWORD ABNORMAL_BLIND			=	1 << 4;
							// const DWORD ABNORMAL_LIGHT			=	1 << 5;
							// const DWORD ABNORMAL_FIRE			=	1 << 6;
							// const DWORD ABNORMAL_COLD			=	1 << 7;
							// const DWORD ABNORMAL_HASTE			=	1 << 8;
							// const DWORD ABNORMAL_SHIELD			=	1 << 9;
							// const DWORD ABNORMAL_HIDE			=	1 << 10;
							// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
							// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
							// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
							// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
							// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
							// const DWORD ABNORMAL_HIEXP			=	1 << 16;
							// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
							// const DWORD ABNORMAL_NOCHAT			=	1 << 18;
							
							// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
							// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
							// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
							// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
							// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;
							  
							// const DWORD OPERATION_MODE			=	1 << 31;	// ��� ���� �ɼ�
*/

const BYTE	SET_USER_PK_STATE			= 118;
/*
	(C <- S)	// ���� �ùε�� �Ǵ� PK���¸� ������.

	int		uid;					// uid

	BYTE	tType;					// 01 : ���� �ùε��
									// 02 : ������ �Ͻ����� ī�����¿� �ִ�.

	// 01 : ���� �ùε��
	short	sCityRank;				// -5 ~ 5���� �ùε���� ����

	// 02 : ������ �Ͻ����� ī�����¿� �ִ�.
	BYTE	tPKStatus;				// ���� �Ͻ����� ī������ : 1
									// ���� ī�����¿��� ��� : 0
*/

const BYTE	USE_POTION					= 119;
/*
	(S -> C)	// ���� ��������� ������.

	int		uid;
	BYTE	tType;					// 01 : ü��ȸ����
									// 02 : ���ž�����
									// 03 : ���׹̳�ȸ����
									// 04 : ����ȸ����
									// 05 : ����
									// 06 : ����ġ 2��
									// 07 : �������� 5��
									// 08 : PK ��ġ - 1
									// 09 : �ؾ�

									const BYTE HP_POTION			= 1;
									const BYTE PP_POTION			= 2;
									const BYTE SP_POTION			= 3;
									const BYTE ALL_POTION			= 4;
									const BYTE SALUTE				= 5;
									const BYTE EXP_POTION			= 6;
									const BYTE MAGIC_POTION			= 7;
									const BYTE KILLREMOVE_POTION	= 8;
									const BYTE DEAD_POTION			= 9;

*/

//#################################################################
//	Event		(131 ~ 170)
//#################################################################
const BYTE MAX_HP_EXIT				= 120;
/*
	short		sHP;
	short		sMaxHP;
*/
const BYTE	CLIENT_EVENT			= 131;
/*
	(C -> S)	// ������ Event ������ ��û�Ѵ�.

	BYTE		tType;				// 01 : USER, NPC ID
									// 02 : HyperText

	// 01 : USER, NPC ID
		int			uid;			// USER, NPC ID

	// 02 : HyperText �ش� ������ �߻��ϴ� �̺�Ʈ ��ȣ�� ������.

		short		sZone;			// �ش� �� ��ȣ
		short		sEventNum;		// �̺�Ʈ ��ȣ
*/

const BYTE	STORE_OPEN				= 132;
/*
	(C <- S)	// Ư�� ������ ����. (BUY �������̽�)

	short		sStoreID;			// �������̵�
	short		sRate;				// �ü�(���߿� ������ ���� ������ Ʋ���� ����...)
	short		sCount;				// �Ĵ� �������� �� ����

	typedef struct _tagSellItem		// �Ĵ� �������� ����
	{
		short	sSid;	// Item serial id
		DWORD	dwCost;	// Item cost
	}SellItem[sCount];
*/

const BYTE	BUY_ITEM				= 133;
/*
	(C -> S)	// �������� �����Ѵ�.

	short		sStoreID;			// �������̵�
	short		sCount;				// �����ϴ� �������� �Ѱ���

	typedef struct _tagBuyItem		// ���� �������� ����
	{
		short	sSid;	// Item serial id
		short	sNum;	// Item count
	}BuyItem[sCount];
*/
/*
	(S -> C)	// ��������� ITEM_MOVE_RESULT�� �̿��Ѵ�. tType = 3;(�Ϲݾ�����) +
*/

const BYTE	CLIENT_EVENT_SAY		= 134;
/*
	(C <- S)	// HyperText�� NPC_SAY �����뺸.

	BYTE		result;				// 01	: ����
									// else	: ����

	short		iSayNum;			// Npc Say Number

	BYTE		tCount;				// "%s"�� �� Ƚ��

	typedef struct _tagSay			//
	{
		Varchar	strMsg;				// Message
	}strMsg[tCount];

	// ������ ���

*/

/*
const BYTE	SELL_ITEM_OPEN_REQ		= 134;

	(C -> S)	// �������� ������ �ȱ����� �ȼ��ִ� ��ϰ� ������ ��û�Ѵ�.

	short		sStoreID;
*/

const BYTE	SELL_ITEM_OPEN_RESULT	= 135;
/*
	(C <- S)	// �ش� �������� ��� ��ϰ� ������ �����ش�.

	short		sStoreID;			// ���� ���̵�
	short		sCount;				// �ȼ� �ִ� �������� �Ѱ���

	// sCount > 0 �� ��쿡�� ����
	typedef struct _tagSellInfo
	{
		short	sSlot;		// �ش� ������ �ȼ� �ִ� �����κ��丮�� ���� ��ȣ
		short	sDuration; // ���� ������
		DWORD	dwDN;		// ����
	}SellInfo[sCount];
*/

const BYTE	SELL_ITEM				= 136;
/*
	(C -> S)	// �������� ������ �Ǵ�.

	short		sStoreID;			// �������̵�
	short		sCount;				// �ȷ��� �������� �Ѱ���

	typedef struct _tagSellItem		// ���� �������� ����
	{
		short	sSlot;	// �ش� ������ �ȼ� �ִ� �����κ��丮�� ���� ��ȣ
		short	sNum;	// Item count
	}SellItem[sCount];
*/
/*
	(S -> C)	// ��������� ITEM_MOVE_RESULT�� �̿��Ѵ�. tType = 4;(�Ϲݾ�����) +
*/


//const BYTE	EBODY_IDENTIFY_OPEN	= 137;
/*
	(S -> C)	// Ȯ���� �� �ִ� EBody ����� ������.

	short		sStoreID;
	short		sCount;				// Ȯ���� �� �ִ� EBody�� �Ѱ���

	BYTE		tSlot[sCount];		// Ȯ���� ���� ����

	// EBody Ȯ�� ����� ITEM_MOVE_RESULT �� ������.
*/

const BYTE	REPAIR_ITEM_OPEN_RESULT	= 138;
/*
	(C <- S)	// �ش� �������� ��� ��ϰ� ������ �����ش�.

	short		sStoreID;			// ���� ���̵�
	short		tCount;				// ���� �Ҽ� �ִ� �������� �Ѱ���

	// tCount > 0 �� ��쿡�� ����
	typedef struct _tagRepairInfo
	{
		short	sSlot;				// �ش� �������� �����Ҽ� �ִ� ���� �κ��丮�� ���� ��ȣ
		short	sDuration;			// ���� ������
		DWORD	dwDN;				// ����
	}RepairInfo[tCount];
*/

const BYTE	REPAIR_ITEM				= 139;		
/*
	(C -> S)	// ���� �����۸���� ������.

	short		sStoreID;			// �������̵�

	short		tCount;

	typedef struct _tagRepair
	{
		short	sSlot;				// �ش� �������� �����Ҽ� �ִ� ���� �κ��丮�� ���� ��ȣ
	}Repair[tCount];

*/
/*
	(S -> C)	// ��������� ITEM_MOVE_RESULT�� �̿��Ѵ�. tType = 5;(�Ϲݾ�����)
*/
const BYTE	BUY_PSY_OPEN_RESULT		= 140;
/*
	(C <- S)	// �ش� �������� �����Ҽ��ִ� ����� �����ش�.

	short		sStoreID;			// ���� ���̵�
	short		sPsiCount;			// �������ִ� �� Psi ��

	// sPsiCount > 0 �� ��쿡�� ����
	typedef struct _tagPsiInfo
	{
		short	sSid;				// Psi serial id
	}PsiInfo[sPsiCount];

*/

const BYTE	BUY_PSY_REQ				= 141;
/*
	(C -> S)	// ���̿��� ������ ������

	short		sStoreID;			// ���� ���̵�
	short		sPsiCount;			// �� Psi ��

	// sPsiCount > 0 �� ��쿡�� ����
	typedef struct _tagPsiInfo
	{
		short	sSid;				// Psi serial id
	}PsiInfo[sPsiCount];
*/

const BYTE	BUY_PSY_RESULT			= 142;
/*
	(C <- S)	// ����� �����Ѵ�.

	BYTE		tType;				// 01 : ����
									// else : ����


	// 00 : �����̸�
									//	error 01 : ���� ���̿����� �ڱ� Ŭ������ �´°� ����.
									//	error 02 : ���Կ� �ʿ��� ������ ����.
									//	error 03 : XP�� ���ڶ���.
									//	error 04 : DN�� ���ڶ���.
									//	error 05 : ������ �ִ� �ѵ��� �Ѿ���.
									//	error 06 : �̹� ������ ���̿��и� �����ߴ�.

	// 01 : �����̸�
		short		sPsiCount;			// �� Psi ��

		// sPsiCount > 0 �� ��쿡�� ����
		typedef struct _tagPsiInfo
		{
			short	sSid;				// Psi serial id
		}PsiInfo[sPsiCount];
*/

const BYTE	BANK_OPEN				= 143;
/*
	(C <- S)							// ���࿡ ������ �����۰� ���� ������.

		DWORD		BankDN;				// ���࿡ ������ ��

		BYTE		TotalSlotNum;		// ���࿡ ������ ������ ������ ����

		typedef struct _tagItem
		{
			byte	bySlot;
			short	sLevel;				// ������ ���� ����@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo[TotalSlotNum];
*/

const BYTE	BANK_ITEM_MOVE_REQ		= 144;
/*
	( C -> S )						// ������ �̵�
	BYTE			tType;			// 1 : ���࿡ ������ ����
									// 2 : ���࿡�� ������ ã��
									// 3 : DN �Ա�
									// 4 : DN ���

	// 1 : ���࿡ ������ ����
		BYTE		tSourceSlot;	// ����� �������� �ִ� ���� ��ġ
		short		sCount;

	// 2 : ���࿡�� ������ ã��
		BYTE		tSourceSlot;	// ���࿡ �������� �ִ� ���� ��ġ
		short		sCount;

	// 3 : DN �Ա�
	 	DWORD		dwDN;			// ������
	// 4 : DN ���
		DWORD		dwDN;			// ������
*/

const BYTE	BANK_ITEM_MOVE_RESULT	= 145;
/*
	( C <- S )						// ������ �̵�
	BYTE			tType;			// 0 : ����
									// 1 : ���࿡ ������ ����
									// 2 : ���࿡�� ������ ã��
									// 3 : DN �Ա�
									// 4 : DN ���

	// 1 : ���࿡ ������ ����
	// 2 : ���࿡�� ������ ã��
		typedef struct _tagItem
		{
			byte	bySlot;			// ���� �κ� ���� ��ȣ
			short	sLevel;				// ������ ���� ����@@@@@@@@@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		};

		typedef struct _tagItem
		{
			byte	bySlot;			// ����� �κ� ���� ��ȣ
			short	sLevel;				// ������ ���� ����
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		};

	 // 3 : DN �Ա�
	 // 4 : DN ���
		DWORD		dwDN;			// ���೻ �Ա��� �ѱݾ�
		DWORD		dwDN;			// ������ �ѱݾ�
*/

const BYTE	CURE_RESULT				= 146;
/*
	(C <- S)						// �������� ȸ���� �����̻� ġ�� ����� ������.

	BYTE	tType					// 00 : ����
									// 01 : HP, PP, SPȸ��
									// 02 : �����̻� ġ��
									...
	// 01 : HP, PP, SPȸ��
	short		sHP;				// HP ��
	short		sPP;				// PP ��
	short		sSP;				// SP ��

	// 02 : �����̻� ġ��
	// ����...
*/

const BYTE	HELP_REQ				= 147;
/*
	(C -> S)						// ������ ���� �̺�Ʈ�� ��û�Ѵ�.
*/

const BYTE	ZONE_CHANGE_RESULT		= 148;
/*
	(C <- S)						// �� ü���� ������� ������.

	BYTE	tType;					// 00 : ����
									// 01 : ����
									// 02 : ������ �ٲ㼭 ��ü������ �ؾ��Ѵ�.

	// tType = 00 �϶� ----> �߰��� ������ ��Ŷ����

	// tType = 01 �϶�
	int		uid;					// ����� uid

	short	nPosX;					// X Position
	short	nPosY;					// Y Position
	short	sZone;					// Load Zone Number

	// tType = 02 �϶�  (������ �ٲ�� �ϴ� ���)
	Varchar	strAddress;				// ������ ������ IP Address
	int		iPort;					// ������ ������ Port

*/

const BYTE	EBODY_IDENTIFY_OPEN	= 149;
/*
	(S -> C)	// Ȯ���� �� �ִ� EBody ����� ������.

	short		sStoreID;
	short		sCount;				// Ȯ���� �� �ִ� EBody�� �Ѱ���

	BYTE		tSlot[sCount];		// Ȯ���� ���� ����

	// EBody Ȯ�� ����� ITEM_MOVE_RESULT �� ������.
*/

const BYTE EBODY_IDENTIFY_REQ		= 150;
/*
	(C -> S)	// Ȯ���� �����۸���� ������.

	short		sStoreID;			// �������̵�
	short		tCount;				// �Ѱ���

	BYTE		tSlot[sCount];		// �ش� �������� Ȯ���Ҽ� �ִ� ���� �κ��丮�� ���� ��ȣ��
*/

const BYTE UPGRADE_ITEM_DIALOG		= 152;
/*
	(C <- S)						// ������ ���׷��̵带 ���Ҷ��� ������.

	BYTE	tType;					// ������ ���׷��̵� Ÿ��
									// 0 : ����, ��
									// 1 : �׼�����
									// 2 : �� ���Ǹ���, �� �ƸӸ���
									// 3 : �Ϲ� ���Ǹ���, �Ϲ� �ƸӸ���
									// 4 : ������ ����
									// 5 : Remagic Request with Event
									// 6 : Remagic Request with Event
									// 7 : EBody Upgrade
*/

const BYTE UPGRADE_ITEM_REQ			= 153;
/*
	(C -> S)						// �������� �����ϰ� ���� �Ҷ�...

	BYTE	tType;					// ������ ���׷��̵� Ÿ��
									// 0 : ����, ��
									// 1 : �׼�����
									// 2 : �� ���Ǹ���, �� �ƸӸ���
									// 3 : �Ϲ� ���Ǹ���, �Ϲ� �ƸӸ���
									// 4 : ������ ����
									// 5 : Remagic Request with Event
									// 6 : Remagic Request with Event
									// 7 : EBody Upgrade

	short	sSourceSlot;			// ������ ������ ���Թ�ȣ ( ������ -1 ) 

	short	sItemSlot;				// ����, �Ƹ�, ������� �� Ư�� ���������� ���׷��̵�, �������� �Ҷ�

	short   sMaterialSlot1;			// �����Ӽ� 1�� ���� ��� ( ������ -1 )
	short   sMaterialSlot2;			// �����Ӽ� 1�� ���� ��� ( ������ -1 )
	short   sMaterialSlot3;			// �����Ӽ� 1�� ���� ��� ( ������ -1 )
	short   sMaterialSlot4;			// �����Ӽ� 1�� ���� ��� ( ������ -1 )
*/

const BYTE UPGRADE_ITEM_RESULT		= 154;
/*
	(C <- S)						// ������ ���׷��̵� ����� �˸���.

	BYTE	tType;					// 00 : ����
									// 01 : ����
									// 02 : ��������
									// 03 : ������ ����

	BYTE	tChangedSlotNum;		// ��ȭ�� ������ ����

	typedef struct _tagItem
	{
		byte	bySlot;			// ����� �κ� ���� ��ȣ
		short	sLevel;			// ������ ���� ����
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;
		BYTE	tMagic[6];
		BYTE	tIQ;
	}ChangeItems[tChangedSlotNum];
*/

const BYTE TELEPORT_REQ				= 155;
/*
	(C -> S)						// ���� ������ �����ϰ��ִ� �����ǥ���� �䱸
*/

const BYTE TELEPORT_RESULT			= 156;
/*
	(C <- S)

	BYTE	tCount;

		typedef struct _tagTel
		{
			BYTE	tIndex;			// ����� ���� 
			Varchar	TelName;		// ������ �̸�
			int		nZone;			// ����ȣ //yskang 0.9 handy ����
		};
*/

const BYTE TELEPORT_EDIT_REQ		= 157;
/*
	(C -> S)						// ���� ������ �����ϰ��ִ� �����ǥ�� �Ϻΰ��� ���� �䱸

	BYTE	tType;					// 1 : ������ �߰�
									// 2 : ������ ����

	// 1 : ������ �߰�
	Varchar	TelName;				// ������ �̸�

	// 2 : ������ ����
  	BYTE	tIndex;					// ����� ����
	Varchar	TelName;				// ������ �̸�
*/

const BYTE TELEPORT_EDIT_RESULT		= 158;
/*
	(C <- S)

	BYTE	tSuccess;				// 1 : ����
									// else ����

	// 1 : ����
	BYTE	tType;					// 1 : ������ �߰�
									// 2 : ������ ����

  	BYTE	tIndex;					// ����� ���� 
	Varchar	TelName;				// ������ �̸�
	int		nZone;					// �� ��ȣ //yskang 0.9 handy ����
*/

const BYTE TELEPORT_COPY_REQ		= 159;
/*
	(C -> S)						// �ش� �������� �̵� �������θ� �䱸

	int		uid;					// User Index
	VarChar	strUserName;			// �Բ� �̵���  ��û�� �����̸�

	BYTE	tSlot;					// ����ϰ��� �ϴ� ������
	BYTE	tIndex;					// ����� ����
	Varchar	TelName;				// ������ �̸�
*/

const BYTE TELEPORT_COPY_DIALOG_REQ	= 160;
/*
	(C <- S)						// �ش� �������� �̵� �������θ� �䱸

	BYTE	tType;					// 1 : ��û��
									// else

	int		uid;					// User Index
	VarChar	strUserName;			// �Բ� �̵���  ��û�� �����̸�
*/

const BYTE TELEPORT_COPY_RESULT		= 161;
/*
	(C -> S -> C)					// �̵� ���� ���θ� ����

	BYTE	tType;					// �³� : 1
									// ���� : 2
									// ��� : 3
									// else error

	int		uid;					// User Index
	VarChar	strUserName;			// �Բ� �̵���  ��û�� �����̸�
*/

const BYTE GUARD_BOW				= 162;
/*
	(C <- S)						// ��� �λ縦 �˸���.

	int		uid;					// ��� uid
	BYTE	tDir;					// �����ִ� ����
*/

const BYTE EVENT_UPGRADE_ITEM_REQ   = 163;
/*
	(C -> S)						// ��ǰ�� �̺�Ʈ�� ȸ���Ѵ�.

	BYTE	tEventSlot;				// �̺�Ʈ ��ǰ�� ����
	BYTE	tItemSlot;				// �����ϱ����� �ش� ����
*/

//#################################################################
//	Guild		(170 ~ 200)
//#################################################################
const BYTE  GUILD_DIALOG			= 170;
/*
	(C <- S)						// ��� â�� ���ǿ� �������� ������.
*/

const BYTE GUILD_OPEN_REQ			= 171;
/*
	(C -> S)						// ��� â�� ����

	Varchar		strGuildName;		// ��� �̸�
*/

const BYTE GUILD_OPEN_RESULT		= 172;
/*
	(C <- S)						// ��� â�� ������� ������.

	BYTE		tTYpe;				// 00 : ����
									// 01 : ��� ����

	// 00 : ����
	BYTE		err					//	01 : ���� ���̸� �Ѵ� ����Ī
									//	02 : ��� â�� ������ ���ڶ�
									//	03 : ��� â�� �ڱ��� ���ڶ�
									//	04 : �̹� ����� ��� ��Ī��
									//	05 : �ٸ� ����� �����̴�.
									//	255 : UnKnown Error
	// 01 : ��� ����
	int			iSid;				// ��� �ε���
	VarChar		szGuildName;		// ��� �̸�
*/

const BYTE GUILD_ADD_REQ			= 173;
/*
	(C -> S)						// ���ο� ��尡 �߰��Ǿ� Ŭ���̾�Ʈ ���Ͽ� �߰� �ʿ�.

	int		iGuildID;				// Guild ID
*/

const BYTE GUILD_ADD_RESULT			= 174;
/*
	(C <- S)						// �ش� ��û�� �����ش�.

	BYTE		tType;				// 00 : ����
									// 01 : ����

	// 00 : ����
	BYTE		err					// 01 : �ش� ��尡 ����
									// 255 : UnKnown Error
	// 01 : �ش� ��� ����
	int			iSid;				// ��� �ε���
	Varchar		strGuildName;		// ��� �̸�
	short		sVersion;			// ��幮�� ����
	VarBinary	GuildMark;			// ��� ����

*/

const BYTE GUILD_MARK_ADD_REQ		= 175;
/*
	(C -> S)						// ���ο� ��� ���縦 �߰��Ѵ�.

	VarBinary	GuildMark;			// ��� ����
*/

const BYTE GUILD_MARK_ADD_RESULT	= 176;
/*
	(C <- S)						// �ش� ��û�� �����ش�.

	BYTE		tType;				// 00 : ������ ����.
									// 01 : ����

	// 00 : ����
	BYTE		err					// 01 : ���¯ ������ ����.
									// 02 : ��尡 ����.

	// 01 : ��� ����
	short		sVersion;
*/

const BYTE	GUILD_WAREHOUSE_OPEN	= 177;
/*
	(C <- S)							// ���â�� ������ �����۰� ���� ������.

		DWORD		GuildDN;				// ��� â�� ������ ��

		BYTE		TotalSlotNum;		// ���â�� ������ ������ ������ ����

		typedef struct _tagItem
		{
			byte	bySlot;
			short	sLevel;				// ������ ���� ����@@@
			short	sSid;
			short	sDuration;
			short	sBullNum;
			short	sCount;
			BYTE	tMagic[6];
			BYTE	tIQ;
		} ItemInfo[TotalSlotNum];
*/

const BYTE	GUILD_ITEM_MOVE_REQ		= 178;
/*
	( C -> S )						// ������ �̵�
	BYTE			tType;			// 1 : ��� â�� ������ ����
									// 2 : ��� â���� ������ ã��
									// 3 : DN �Ա�
									// 4 : DN ���

	// 1 : ��� â�� ������ ����
		BYTE		tSourceSlot;	// ����� �������� �ִ� ���� ��ġ
		short		sCount;

	// 2 : ��� â���� ������ ã��
		BYTE		tSourceSlot;	// ��� â�� �������� �ִ� ���� ��ġ
		short		sCount;

	// 3 : DN �Ա�
	 	DWORD		dwDN;			// ������
	// 4 : DN ���
		DWORD		dwDN;			// ������
*/

const BYTE	GUILD_ITEM_MOVE_RESULT	= 179;


const BYTE GUILD_INFO				= 180;	//@@@@@@@@@@@@ �ڸ��� Info�� �־���Ѵ�.


const BYTE GUILD_USER_INFO_REQ		= 181;
/*
	(C -> S)						// ���� �������� ���� ������ �䱸�Ѵ�.
*/

const BYTE GUILD_USER_INFO_RESULT	= 182;
/*
	(C <- S)						// ��� �Ҽӿ� ������ ������.

	BYTE		tType;				// 1 : ��� �Ͽ콺 �ο� ��û ����
									// 2 : ��� �����Ͱ� ���� ��� ����
									// 3 : ��Ʈ���� �渶�� ���� ��ȯ
									// else �Ϲ� ��� ����

	// else �Ϲ� ��� ����
	VarChar		strGuildMaster;		// ��� �������̸�

	BYTE		tCount;				// ���� ��

	typedef struct _tagGuild
	{
		Varchar		strGuilUser;	// ���� �̸�
		short		sLevel;			// ����
	}Guild[tCount];

	// 1 : ��� �Ͽ콺 �ο� ��û ����
	VarChar		strGuildMaster;		// ��� �������̸�
	BYTE		tCount;				// ���� ��

	typedef struct _tagGuild
	{
		Varchar		strGuilUser;	// ���� �̸�
		short		sLevel;			// ����
		int			uid;			// ��� ����

	}Guild[tCount];

  	short		sGuildHouseZone;	// Vertual Room Index
*/

const BYTE GUILD_WAREHOUSE_CLOSE	= 183;
/*	(C -> S)						// ���â�� â�� �ݴ´ٰ� �뺸�Ѵ�.
*/

const BYTE GUILD_TAX_OPEN			= 184;
/*
	(C <- S)						// ���������� ���� ���� ����

	short	sStoreID;				// ��û�Ϸ��� ���� �ε���
	short	sCurTax;				// ���� ����..
*/

const BYTE GUILD_TAX_REQ			= 185;
/*
	(C -> S)						// ���������� ���� ����

	short	sStoreID;
	short	sTax;					// 0 ~ 200%����
*/

const BYTE GUILD_WAR_OPEN			= 186;
/*
	(C <- S)						//

	short	sStoreID;				// ��û�Ϸ��� ���� �ε���
	short	sYear;					// ���� ���� �ð��� �������� ������...
	BYTE	tMon;
	BYTE	tDay;
*/

const BYTE GUILD_WAR_REQ			= 187;
/*
	(C -> S)						// ����� ��¥�� ����

	short	sStoreID;
	short	sYear;					//
	BYTE	tMon;
	BYTE	tDay;
	BYTE	tHour
*/

const BYTE GUILD_WAR_APPLY_OPEN		= 188;
/*
	(C <- S)						// ������� ��û�Ѵ�.

	short	sStoreID;
	VarChar	strGuildName;			// ��� ����̸�
*/

const BYTE GUILD_WAR_APPLY_REQ		= 189;
/*
	(C -> S)						// ������� ��û�Ѵ�.

	short	sStoreID;
*/

const BYTE GUILD_WAR				= 190;
/*
	(C <- S)						// ����� ������ �˸���.

	BYTE	tType;					// 1 : ����� ����..
									// 2 : ����� ����...
									// 3 : ������� �׾ ������ ��Ȱ�Ҷ�...

	BYTE	tGuildWarType;			// 1 : �ʵ���
									// 2 : ������
									// 3 : ������

	short	sAreaIndex;				// ��������(�ʵ����� = 0)

	// 1 : ����� ����ÿ��� �������� �ʴ´�.
	TYPE	tGuildUser;				// 0 : �Ϲ�����
									// 1 : �ش� ���� ����

	// 1 : �ش� ������ ����� �����϶�...
	short	sCount;

	typedef struct _GuildList
	{
		int	iGuildID;				// ������� ������ ����Ʈ

	}GuildList[sCount];

*/

const BYTE GUILD_FIELD_WAR_REQ		= 191;
/*
	(C -> S -> C)					// �ش� �渶���� �ʵ��� �������θ� �䱸

	int		iGuildID;
	VarChar	strGuildName;			// �ʵ����� ��û�� ����̸�
*/

const BYTE GUILD_FIELD_WAR_RESULT	= 192;
/*
	(C -> S -> C)						// �ʵ��� ���� ���θ� ����

	BYTE	tType;					// �³� : 1
									// ���� : 2
*/

const BYTE SIGHT_INFO_COMPRESSED	= 193;
/*
	�� �����?
*/

const BYTE GUILD_HOUSE_APPLY_REQ	= 194;
/*
	(C -> S)						//

	short	sCount;

	typedef struct _UserList
	{
		int uid;					// ��� �Ͽ콺�о翡 ������ ����Ʈ

	}UserList[sCount];

  	short	sGuildHouseZone;		// Vertual Room Index
*/

const BYTE GUILD_FORTRESS_NCIRCLE	= 195;
/*
	(C <- S)						// �������� �ش� N_Circle�� ���� �ٲ��� �˷�..

	BYTE	tType;					// 0 : N_Circle�� �� ��ȭ
									// 1 : �ش� ��Ʈ���� ��� ����

	// 0 : N_Circle�� �� ��ȭ
	int		Uid;
	BYTE	tColor;					// 0 : defalut(�Ķ�)
									// 1 : Non_default(����);

	// 1 : �ش� ��Ʈ���� ��� ����
	int		FortressUid;

	int		Uid1;
	int		Uid2;
	int		Uid3;
	int		Uid4;
*/

const BYTE DEL_GUILD_CHAR_REQ		= 196;
/*
	(S <- S)						//
*/

const BYTE GUILD_INVITE_USER_REQ	= 197;
/*
	(S <- S)						//
*/

const BYTE CHALLENGE_GUILD			= 198;
/*
	(C <- S)						// �������� ��û�� ����̸��� ������.

	short	sCount;

	typedef	struct	_GUILD
	{
		Varchar	strGuildName;
	}GuildInfo[sCount];
*/
const BYTE GUILD_OFF_WITH_THREAD	= 199;		// ��� Ż��

const BYTE	NEW_CHAR_REQ_WITH_THREAD = 200;

const BYTE ADDRESS_WINDOW_OPEN		= 201;		// �ּ��Է�â

const BYTE AREA_ATTACK_RESULT		= 202;		// ���� ����

/*
const BYTE GUILD_WAR_AREA			= 203;		// ���� ����
/*
	(C <- S)						// ����� �������� �˸���.

	BYTE	tType;					// 1 : ������� �����ϴ� �������
									// 2 : ������� �����ϴ� �������
    short	sCount;

	typedef	struct	_GUILD_AREA
	{
		short	Guild_Area_Index;
	}GuildArea[sCount];

*/

const BYTE DRESSING					= 204;		// ����
/*
	(C -> S)
	
	(S -> C)

	BYTE	success/fail

	<success>
	short	slot					// ��ᰡ �ִ� ����
	short	sLevel
	short	sSid
	short	sDuration
	short	sBullNum
	short	sCount
	BYTE	tMagic 6��
	BYTE	tIQ

	<fail>
	none...

*/

const BYTE DRESSING_WINDOW_OPEN		= 205;		// ���� â ����

const BYTE ACCOUNT_BANK_OPEN		= 206;		// ���� ����
/*
	(C -> S)

	none...

	(S -> C)

	byte	ACCOUNT_BANK_OPEN;
	short	store_id;				// ���� ��ȣ - â�� �̿�� ������ ���� ���� �־�� ��
	dword	m_dwAccountBankDN;
	byte	count;

	;;count��ŭ
	{
		byte	slot;
		short	sLevel;
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;

		6��
		{
			byte	tMagic;
		}

		byte	tIQ;

		DWORD	dwCost;				// ���� ������ ã���� �ҿ�Ǵ� ���
	}
*/

const BYTE ACCOUNT_BANK_ITEM_MOVE_RESULT = 207;
/*
	(S -> C)

	BYTE	ACCOUNT_BANK_ITEM_MOVE_RESULT;

	BYTE	result;

	
	if(result == 0)
	{
		return;		// fail
	}
	else if(result == 1 )
	{
		���࿡ ������ �ֱ�

		BYTE	bankslot;
		short	sLevel;
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;

		BYTE	tMagic * 6��
		BYTE	tIQ;

		byte	userslot;
		short	sLevel;
		short	sSid;
		short	sDuration;
		short	sBullNum;
		short	sCount;

		byte	tMagic;
		byte	tIQ;
	}
	else if(result == 2 )
	{
		���࿡�� ������ ����

		DWORD	m_dwDN
		DWORD	m_dwAccountBankDN

		short	bankchangeslotcount		// �����ۻ���� ���࿡�� ���� ���� ����

		bankchangeslotcount ��ŭ
		{
			BYTE	bankslot			// ��ũ���� ���� ���Թ�ȣ
			short	sLevel
			short	sSid
			short	sDuration
			short	sBullNum
			short	sCount
			
			BYTE	tMagic * 6��
			BYTE	tIQ
		}

		short	myinvenchangecount		// �������� ���࿡�� ã���Ƿμ� �ٲ� �� �κ� ���� ����

		myinvenchangecount ��ŭ
		{
			BYTE	myinvenslot			// �κ����� ���� ���Թ�ȣ
			short	sLevel
			short	sSid
			short	sDuration
			short	sBullNum
			short	sCount
			
			BYTE	tMagic * 6��
			BYTE	tIQ
		}
	}
	else if(result == 3 )
	{
		���࿡ ���ֱ�

		DWORD	m_dwAccountBankDN		// ���೻ �Ա��� �ѱݾ�
		DWORD	m_dwDN					// ������ �ѱݾ�
	}
*/
const BYTE SELECT_OVER100_SKILL		= 208;
/*
	(C -> S)

	BYTE	selectedskill (20-21)
*/

const BYTE ACCOUNT_BANK_ITEM_MOVE_REQ = 209;
/*
	(C -> S)

	BYTE	type

	switch(type)
	{
	case BANK_ITEM_INPUT:
	{
		BYTE	tSourceSlot							// ����� �������� �ִ� ���� ��ġ
		short	sCount								// �󸶸�ŭ ����
	}
	case BANK_ITEM_OUTPUT:
	{
		short	store_id
		DWORD	outputdn							// ���࿡�� ã�� ��
		short	slotcount							// ��� ���Կ��� ã�� ����

		slotcount��ŭ
		{
			short	slot							// ���࿡�� ���� ��ȣ
			short	count							// ��� ã�� ����
		}
	}
	case BANK_DN_INPUT:
	{
		DWORD	InputDN								// ���࿡ �Ա��� ��
	}
*/

const BYTE PRE_REG_USER_EVENT_REQ	= 210;
/*
	(S -> C)										// �ش� â�� ����

	(C -> S)										// �ԷµȰ��� ������.
	Varchar		strSerialNum;
	
*/

const BYTE PRE_REG_GAMEROOM_EVENT_REQ= 211;
/*
	(S -> C)										// �ش� â�� ����

	(C -> S)										// �ԷµȰ��� ������.
	Varchar		strSerialNum;
	Varchar		strSocNum;							// ����� ������� �ֹι�ȣ
	
*/

const BYTE ADDRESS_WINDOW_OPEN_NEW		= 212;			// �ּ��Է�â


// �߱��� �������� �ʿ��� ��Ŷ. 
const BYTE ENCRYPTION_START_REQ			= 213;
/*
	(C -> S)										// Before AccountLogin, Encryption Public_Key request;	

	BYTE	tType;									// Zone Server���� CharInfo�������� �����ϴ°��� Client���� ���� �ʿ�
*/
const BYTE ENCRYPTION_START_RESULT		= 214;
/*
	(S -> C)

    Varchar		public_key;		// int64

	BYTE		tType;			//					0 : CharInfoServer, 1 : GameStartReq, 2 : ZonLoginReq
*/

const BYTE GUILD_INVITE_REQ				= 215;
/*
	(C -> S -> C)									// ��� ���� ���θ� �����.

	int			uid;								// ��� ������
*/

const BYTE GUILD_INVITE_RESULT			= 216;
/*
	(C -> S -> C)									// ���� ���θ� ����

	BYTE	tType;									// �³� : 1
													// ���� : �������ϴ� ����ü 2
													// ���� : ��ü�� ��� 3
													// ���� ���� : 4

	int			uid;								// ���� uid

	// ������ �����̸�  : 4
	BYTE		error_code;			// 03	: ��� ���� (�Ӹ�, ���ã���� ���)
									// 06	: �߸��� �������̵�(�Ӹ�, ���ã���� ���)
									// 07	: �ش� ��尡 �������� �ʴ´�.
									// 08	: �ش� ��忡 ������ ������ �ƴϴ�.
									// 09	: �̹� �ٸ� ��忡 ������ ������.
									// 10	: ��� ¯	������ ����.
									// 11	: �ִ� �ο����� �Ѿ���.
									// 12	: ����尡 �������̴�.

*/

/////////////////////////////

//-----------------------------------------------------------------------------------------------------
//--yskang 0.1
//��� ����� ȣĪ�� �ο��ϱ� ���Ͽ� �߰��Ǵ� ��Ŷ
//-----------------------------------------------------------------------------------------------------
const BYTE LOVE_NAME_REQ		= 217;		//���� ȣĪ[��Ī] �߰� �Ǵ� ���� �۾��� �Ѵ�.
/*											//�ڽ��� ȣĪ[��Ī] �߰� �Ǵ� ���� �۾��� �Ѵ�.										
	(C -> S)
	BYTE	bCommand;				//1 ���� 0 ���� 
	// 1 : ���� ȣĪ[��Ī] ����	//<�渶�� 50���� Level�̸� ������ �ʴ´�,�ڽ��̸� 80����...>
	int		uid;					//���� uid �Ǵ� �ڽ��� uid
	Varchar LoveName;				//ȣĪ[��Ī]
	// 0 : ����
	int		uid;
*/


const BYTE LOVE_NAME_RESULT		= 217;
/*
	(C <- S)

	BYTE	tSuccess;				// 1 : ����
									// 0 : ����
	// 0 : ����
	BYTE	error_code;
	01 : ������ ����.
	02 : ã�� ���̵� ����.
	03 : ���� ������ �ƴϴ�.
	04 : ȣĪ[��Ī]�� �߸��Ǿ���.
	05 : ��� ���� �� �� ������.
	06 : ���̴�.
*/
const BYTE LOVE_NAME			= 218; //��Ͻ� ���� ȭ�鿡 �ִ� ������� �����Ѵ�.
/*
	(C <- S)
	int		uid;
	varchar LoveName;
*/

//-----------------------------------------------------------------------------------------------------
// zinee 2002-11-07
// ���� �ý��� ��Ŷ
//-----------------------------------------------------------------------------------------------------

const BYTE MAIL_INFO_REQ			= 219;	// Ŭ���̾�Ʈ���� ���� ���� ��û
/*
	(C -> S)
*/
const BYTE MAIL_INFO_RESULT			= 219;
/*
	(S -> C)
	int		nNewMail			// �� ���� ����
	int		nCurMail			// ���� ���� ����
*/

const BYTE MAIL_SEND_REQ			= 220;	// Ŭ���̾�Ʈ���� ���� ������ ��û
/*
	(C -> S)
	varchar		strRecvID		// ������ ���̵�
	varData		Contents		// ���ϳ���
*/
const BYTE MAIL_SEND_RESULT			= 220;
/*
	(S -> C)
	BYTE	error
	// 0 : ����
	// 1 : ��ǥ����
	// 2 : �������� �ʴ� ���̵�
	// 3 : ���� �ý��� ������


	// ������.
	typedef struct _tagMailItem		// ��ǥ �������� ����
	{
		short	sSlot;	// Item Slot number
		short	sNum;	// Item count
	};
*/
const BYTE MAIL_LIST_REQ			= 221;
/*
	(C -> S)
	int		nIndex		// �а��� �ϴ� ���������� ���۹�ȣ (-1�ϰ�� ó��)
*/
const BYTE MAIL_LIST_RESULT			= 221;
/*
	(S -> C)
	short	nCount			// ����Ʈ ����( ����� �ѹ���û�� �⺻ 20�� )

	Data					// nCount ������ŭ �ݺ� (�ε���,�������̵�,��¥,��������)
	{
		int		nIndex
		varchar	strSendID
		varchar	Date		// ��¥���� 02/11/23 14:34
		BYTE	bRead		// 0: ������ 1: ���� ����
	}
*/
const BYTE MAIL_CONTENTS_REQ		= 222;
/*
	(C -> S)
	int		nIndex			// ������ �ϴ� ������ ������ȣ
*/
const BYTE MAIL_CONTENTS_RESULT		= 222;
/*
	(S -> C)
	BYTE	error
							// 0: ����
							// 1: ã����������
							// 2: �ùٸ��� ���� ��û(�ڱ����� �ƴ�)

	Data					// ������ �������(error==0) ������� ������
	{
		int		nIndex
		vardata	Contents
	}
*/
const BYTE MAIL_DELETE_REQ			= 223;
/*
	(C -> S)
	int		nIndex				// �������� ��ȣ
	
	int		nLastIndex			// �Ǹ����� Data��û �ε���.
*/
const BYTE MAIL_DELETE_RESULT		= 223;
/*
	int		error
								// 0: ����
								// 1: �������� �ʴ� ����
								// 2: �ùٸ��� ���� ����( �ڱ������ �ƴҰ�� )

	// ����������.
	int		nIndex				// ���� ��ȣ

	int		nNewMail			// �� ���� ����
	int		nCurMail			// ���� ���� ����

	int		nCount			// ������ �������� ������ 0 ������ 1
	Data					// 
	{
		int		nIndex		// DELETE_REQ��  nLastIndex�� ���� ��� Index
		varchar	strSendID
		varchar	Date		// ��¥���� 02/11/23 14:34
		BYTE	bRead		// 0: ������ 1: ���� ����
	}
*/

const BYTE REVIVAL_REQ				= 224;
/*
	(S -> C -> S)

	varchar strUserID		// ��Ȱ�����ִ� ���� ���̵�

  	// ������ ������� USER_INFO�� �˷��ش�. LIVE_REQ �� ������� ����.
	// ���н� REVIVAL_ERROR ��Ŷ�� �����Ѵ�.

*/

const BYTE REVIVAL_RESULT			= 225;
/*
	(S -> C)

	// Ŭ���̾�Ʈ�� REVIVAL_REQ ��û�� ������ ��쿡�� ���۵Ǵ� ��Ŷ

	BYTE	error			// 0: ���� -> ������ USER_INFO ��Ŷ�� ���� �ڵ��󰣴�.
							// 1: ��Ȱ���ִ� ������ ����(������ ����ų� ��Ÿ...������)
							// 2: ��Ȱ���ִ� ������ �κ��� ���������� ����.(�ٸ� ������Ȱ�� ���ƴٰų�..)
							// 3: �˼����¿���( ������ ��Ȱ�� ��Ҹ� ��ã�� ��� ���.. )

	/////////////////////////////////////////////////////////////////////////////////////
	// error = 0  : ������ ��� USER_INFO�� ��Ŷ�� Mode�� ������ �����Ͱ� �ڵ��󰣴�.

		int			uid;			// User index

		// Mode �� INFO_MODIFY �� ��츸 �Ʒ��� ������ ����
		VarChar		szName;			// User Name
		short		nPosX;			// X Position
		short		nPosY;			// Y Position

		DWORD		dwSkin;			// �Ǻλ�(COLORREF)
		DWORD		dwHair;			// �Ӹ���(COLORREF)
		BYTE		byGender;		// ��, ��

		char		szFace[10];		// �󱼸��
									// 1 : �Ӹ�
									// 2 : ��
									// 3 : ��
									// 4 : ��
									// 5 : ��
									// 6 : �Ǽ��縮 1
									// 7 : �Ǽ��縮 2
									// 8~10 : ����

		short		sEquipItem[10];	// 0 = ���
									// 1 = ����
									// 2 = �Ӹ� �׼�����
									// 3 = �� �׼�����
									// 4 = ������ �� ����
									// 5 = ����   �� ����
									// 6 = ������ �Ǽ��縮
									// 7 = ����   �Ǽ��縮
									// 8 = ����
									// 9 = �Ź�
									// �������� �������� ���� ������ id == -1

		short		sHP;
		short		sMaxHP;

		BYTE		tDir;			// �����ִ� ����

		DWORD		dwAbnormal		// �����̻�����(Damaged)

									// const DWORD ABNORMAL_NONE			=	0;
									// const DWORD ABNORMAL_POISON			=	1;
									// const DWORD ABNORMAL_CONFUSION		=	1 << 2;
									// const DWORD ABNORMAL_PARALYSIS		=	1 << 3;
									// const DWORD ABNORMAL_BLIND			=	1 << 4;
									// const DWORD ABNORMAL_LIGHT			=	1 << 5;
									// const DWORD ABNORMAL_FIRE			=	1 << 6;
									// const DWORD ABNORMAL_COLD			=	1 << 7;
									// const DWORD ABNORMAL_HASTE			=	1 << 8;
									// const DWORD ABNORMAL_SHIELD			=	1 << 9;
									// const DWORD ABNORMAL_HIDE			=	1 << 10;
									// const DWORD ABNORMAL_DEX_UP			=	1 << 11;
									// const DWORD ABNORMAL_MAX_HP_UP		=	1 << 12;
									// const DWORD ABNORMAL_ADAMANTINE		=	1 << 13;
									// const DWORD ABNORMAL_MIGHTYWEAPON	=	1 << 14;
									// const DWORD ABNORMAL_BERSERKER		=	1 << 15;
									// const DWORD ABNORMAL_HIEXP			=	1 << 16;
									// const DWORD ABNORMAL_MAGICFIND		=	1 << 17;
									// const DWORD ABNORMAL_NOCHAT			=	1 << 18;

									// const DWORD ABNORMAL_FASTRUN			=	1 << 19;
									// const DWORD ABNORMAL_MINDSHOCK		=	1 << 20;
									// const DWORD ABNORMAL_MINDGUARD		=	1 << 21;
									// const DWORD ABNORMAL_PSISHIELD		=	1 << 22;
									// const DWORD ABNORMAL_PIERCING_SHIELD	=	1 << 23;

									// const DWORD OPERATION_MODE			=	1 << 31;	// ��� ���� �ɼ�

		short		sCityRank;		// �ùε��

		int			iGuildIndex;	// ��� �ε���
		VarChar		szGuildName;	// ��� �̸�
		short		sVersion;		// ��� ���� ����
		BYTE		tClass;			// Ŭ���� ����
		BYTE		tKillState;		// ���������� �Ǵ�
									// 0 : �������� ����
									// 1 : ������ ����
		
		VarChar		strLoveName		//ȣĪ[��Ī] //-- yskang 0.1	
*/		

//-----------------------------------------------------------------------------------------------------
// Finito
// 226 - Expression Packet - Client packet asking to send expression info
// 255 - Screen capture packet - Sends server date and time to client.
//-----------------------------------------------------------------------------------------------------

const BYTE EXPRESSION_REQ			= 226;
/*
		short		sExpression	
*/
const BYTE EXPRESSION_OPEN			= 230;
const BYTE TRANSFORM_REQ			= 234;
const BYTE PERSONAL_SHOP_REQ		= 239;
const BYTE SCREEN_CAPTURE_REQ		= 245;
const BYTE PALYER_HEARTBAET_REQ		= 252;//�����
const BYTE PALYER_ONLINE_REQ		= 253;


#define		MAGIC_100_CONVERT_POS	4				//100װ��ת���������λ��
#define		MAGIC_100_ADD_POS		6				//100װ���������ʹ��
#define		MAGIC_100_POS			7				//100����Ƕ�������ڵ�[11]�������е�λ��

#define		MAGIC_BLUE_LOOP			2				//��ɫ
#define		MAGIC_GOLD_LOOP			4				//��ɫ��0,1,2,3,[4]����
#define		MAGIC_GOLD_EX_LOOP		3				//��ɫװ��5,6,7,8
#define		MAGIC_GOLD_EX_POS		6				//

#endif
