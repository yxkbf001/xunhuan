#ifndef _DEFINE_H_
#define _DEFINE_H_

//
// 25���� OR �κ� Ȱ������ ����
//
#define _ACTIVE_USER		// �κ� Ȱ��

//
//
//
//#define KOR_VER
  #define CHN_VER
//  #define ENG_VER

//
//	���� �ְ� �̺�Ʈ������ �ξⷳ�� ������� �ӽ÷� �����Ѵ�.	
//
//#define _EVENT_RR

//
//	MAX VALUE DEFINE
//
#define _MAX_DWORD				0xFFFFFFFF
#define _MAX_INT				0x7FFFFFFF
#define _MAX_SHORT				0x7FFF

//
//	Defines About Communication
//
//#define USER_SOCKET_PORT		12000 // �ӽ��ڵ�

#define OVL_RECEIVE				0X01
#define OVL_SEND				0X02
#define OVL_CLOSE				0X03

#define PACKET_START1			0XAA
#define PACKET_START2			0X55
#define PACKET_END1				0X55
#define PACKET_END2				0XAA

//#define RECV_BUF_SIZE			8192 * 5
//#define SEND_BUF_SIZE			8192 * 5
#define RECV_BUF_SIZE			10000
#define SEND_BUF_SIZE			10000


//
//	Define CriticalSection Spin Count
//
#define SPIN_COUNT				4000

//
//	About City
//
#define SANAD					0
//VIP����
#define MAX_VIP_DAY                 20000
//�ػ���ʹ����
#define MAX_TianShi_DAY             20000
//
//
//	About USER
//
#define USER_DEAD				0X00
#define USER_LIVE				0X01

//
//	About GUILD
//
#define MAX_GUILD				30000
#define MAX_GUILD_USER			50
#define GUILD_WAR_PREPARE		0
#define GUILD_WAR_DECISION		1
#define GUILD_MAX_TAX			30 //���˰��
#define MAX_GUILD_HOUSE_USER	20

#define GUILD_WAR_READY		0		// ����� �ٷ� 5������ �߻��ϴ� �غ� �ܰ�
#define GUILD_WARRING		1		// ���� ���������
#define GUILD_WAR_AFFTER	2		// ������� ������

#define FORTRESS_VIOLENCE_WARRING	1	// �ν��� �ݶ���
#define FORTRESS_VIOLENCE_AFFTER	0	// End

#define GUILD_WAR_MAX_MSG_TIMER	6		// �������� ���� �ð��� �˷��ش�.

#define GUILD_GUARD_MAX_NUM		6	// ����� ��Ű�� ������� �ִ� 6����� ����Ҽ��ִ�.
#define _GUILDNPCLIST_DB		24	// 4 * 6

#define GUILD_REPAIR_MAX_NUM	5	// �ִ� 5�� ���� ������ NPC�� �ִ�.
#define _GUILDREPAIRLIST_DB		30 // 5 * 6

#define FORTRESS_TARGET_MAX_NUM	4	// �ִ� 4�� ���� �����ΰ� �ִ�.
#define GUILD_ATTACK_MAX_NUM	20	// �ִ� 20������ ����� ��û�� ������ �ִ�
#define _GUILDLIST_DB			80	// 4 * 20

#define GUILDFORTRESS_ATTACK_MAX_NUM	20	// �ִ� 50������ ����� ��û�� ������ �ִ�
#define _GUILDFORTRESSLIST_DB			200	// 4 * 50

#define GUILD_VIRTUAL_WAR_START	16
#define GUILD_VIRTUAL_WAR_END	17
#define GUILD_HOUSE_DAY			18

#define GUILD_FIELD_WARRING		1
#define GUILD_STORE_WARRING		2
#define GUILD_FOTRESS_WARRING	3		
//
//	About NPC
//
#define NPC_NUM					200
#define NPC_DEAD				0X00
#define NPC_LIVE				0X01
#define NPC_ATTACKING			0X02
#define NPC_ATTACKED			0X03
#define NPC_ESCAPE				0X04
#define NPC_STANDING			0X05
#define NPC_MOVING				0X06
#define NPC_TRACING				0X07
#define NPC_FIGHTING			0X08
#define NPC_STRATEGY			0x09
#define NPC_BACK				0x10
#define NPC_WAIT				0x11	// ���� �������� �����ϴ� ���� ��ȸ�� �̹Ƿ�

#define NPC_PASSIVE				150
#define NPC_ACTIVE				100

//
//	About Map Object
//
#define USER_BAND				10000		// Map ���� ������ �ִ�.
#define NPC_BAND				20000		// Map ���� NPC(������)�� �ִ�.
#define INVALID_BAND			30000		// �߸��� ID BAND
#define USER_HUFA_BAND			20000
//
//	About Big Mop Size In CELL
//
#define NPC_MAP_SIZE			20

//
//	Defines About Max Value
//
#define MAX_BASIC_ITEM			1000
#define MAX_EVENT				3000  //����¼�event��� ԭʼ1000

//
//	To Who ???
//
#define TO_ALL					0X01
#define TO_ZONE					0X02
#define TO_ME					0X03
#define TO_INSIGHT				0X04

#define SEND_USER				0
#define SEND_INSIGHT			1
#define SEND_ZONE				2
#define SEND_ALL				3
#define SEND_RANGE				4
#define SEND_SCREEN				5

//
//	�þ�ó��
//
#define	SCREEN_X				15
#define	SCREEN_Y				19

//#define SIGHT_SIZE_X			10
//#define SIGHT_SIZE_Y			10
#define SIGHT_SIZE_X			12
#define SIGHT_SIZE_Y			12

#define DIR_H					1
#define DIR_L					-1
#define DIR_OUTSIDE				3

//
//	State Value
//
#define STATE_ACCEPTED			0X01   //����
#define STATE_CONNECTED			0X02   //����
#define STATE_DISCONNECTED		0X03   //�Ͽ�
#define STATE_GAMESTARTED		0X04   //��Ϸ��ʼ
#define STATE_INITED			0X05   //����
#define STATE_LOGOUT			0X06   //ע��
#define STATE_GAMERESTART		0X07   //����

//
//	Event
//
#define MAX_LOGIC_INT			5
#define MAX_EXEC_INT			3
#define MAX_LOGIC_ELSE_INT		20
#define MAX_LOGIC_CHAR_LEN		128
#define MAX_EXEC_CHAR_LEN		128
#define MAX_LOGIC_ELSE_CHAR_LEN 128

#define MONSTER_ATTACK_EVENT_BAND		10000		// 10000�� �̻��� �̺�Ʈ ��ȣ�� ���Ͱ� ���ݴ������� �߻��Ѵ�.

//
//	PSI limit Number
//
#define BRAWL_PSI_NUM			2
#define STAFF_PSI_NUM			7
#define	EDGED_PSI_NUM			2
#define FIREARMS_PSI_NUM		2
#define NOCLASS_PSI_NUM			3

#define	DEFAULT_PSI_DELAY		30000

//
//  Item
//
#define TYPE_MONEY				0
#define TYPE_ITEM				1

//���װ������
#define MAX_ITEM_UPGRADE_COUNT	o_yehuoini[0]->gaishu		// ���� 0~9���� ���׷��̰� �����ϴ�

#define ITEM_NAME_LENGTH		20
#define MAX_THROW_ITEM			5000    //������Ʒˢ�������
#define ITEM_MAX_USE_WEAR		150		// �������� �����ִ� �Ӽ��鸸 ��Ƴֱ�����, �̺�Ʈ �����۰� ����
#define ITEM_USER_RIGHT_NUM		3		// ���� 3����� �����ۿ����� �Ǹ��� �����Ѵ�.

#define EVENT_ITEM_LENGTH		30		// �̺�Ʈ�� �߻��ϴ� �������� ������ȣ�� �ο��� �ڸ���

#define EVENT_UNIQUE_ITEM_BAND	30000	// �ְ� ���������� Ư���������� �����.	
#define EVENT_RR_ITEM_BAND		30001

// Upgrade Item
#define BLESSING_WEAPONLESS_WEAR	23	// �� ���Ǹ��� ������ ���� ����	
#define BLESSING_ARMORLESS_WEAR		24	// �� �ƸӸ��� ������ ���� ����		

#define NORMAL_WEAPONLESS_WEAR		25	// �Ϲ� ���Ǹ��� ������ ���� ����	
#define NORMAL_ARMORLESS_WEAR		26	// �Ϲ� �ƸӸ��� ������ ���� ����	
	
//
//	Quick Item Use
//
#define QUICK_ITEM_SP			1
#define QUICK_ITEM_PP			2	
#define QUICK_ITEM_HP			4
#define QUICK_ITEM_ALLREPAIR	7
#define QUICK_ITEM_CONFUSE		8
#define QUICK_ITEM_PALSY		16
#define QUICK_ITEM_POISON		32
#define QUICK_ITEM_VISION		64
#define QUICK_ITEM_ALLCURE		127
#define QUICK_ITEM_BULL			100
#define QUICK_ITEM_POTAL		101
#define EVENT_ITEM_LOTTERY		102
#define QUICK_ITEM_TELEPORT		103
#define	EVENT_ITEM_DEADPOISON	104
#define QUICK_ITEM_SALUTE		113	

#define NORMAL_SALUTE_SID		850
#define XMAS_SALUTE_SID			874
#define YEAR_SALUTE_SID			875

//
//	Moon Event Item
//
#define EVENTITEM_WEAR_MOON		115

//
//	Invasion Event Item
//
#define EVENTITEM_WEAR_INVASION	120


//
//	Special Potion
//
#define SPECIAL_ITEM_BIANLANG	    	1028  //�Ǳ���
#define SPECIAL_ITEM_BIANXIONG		    1029  //�ܱ���
#define SPECIAL_ITEM_TS			1044  //�ػ���ʹ
#define SPECIAL_ITEM_HX_LS		1035//����
#define SPECIAL_ITEM_HX_JS		1289//�þ�
#define SPECIAL_ITEM1441		1405  //20Ԫ��ȯ
#define SPECIAL_ITEM1442		1415  //50Ԫ��ȯ
#define SPECIAL_ITEM1443		1416  //100Ԫ��ȯ
#define SPECIAL_ITEM1444		1417  //500Ԫ��ȯ
#define SPECIAL_ITEM1445		1418  //1000Ԫ��ȯ
#define SPECIAL_POTION_WEAR		116
#define SPECIAL_ITEM_HIEXP		699
#define SPECIAL_ITEM_MAGICFIND	700
#define SPECIAL_ITEM_KILLREMOVE	701
#define SPECIAL_BIAOZHI		    724

// ���ڿ�ǥ ������
#define NORMAL_ITEM_STAMP		714					// zinee 02-11-18

// Revival Item
#define NORMAL_ITEM_REVERSE		807					// ���������� : ����� ��Ȱ ������

//
//	Psionic Stone
//
#define PSI_STONE_WEAR			117					// ���̿��� ���汸�� ���� ����

#define PSI_STONE_FAST_RUN			706					
#define PSI_STONE_MIND_SHOCK		707
#define PSI_STONE_MIND_GUARD		708
#define PSI_STONE_PSI_SHIELD		709
#define PSI_STONE_PIERCING_SHIELD	710
#define PSI_STONE_BAO_YAN			1123
#define PSI_STONE_BA_QI				1124
#define PSI_STONE_CHAO_FAN_TAN		1549
#define PSI_STONE_CHAO_FENG_LI		1550
#define PSI_STONE_CHAO_YI_NENG		1551
#define PSI_STONE_CHAO_DUO_CHONG	1552
#define PSI_STONE_CHONG_RAN     	1737
#define PSI_STONE_LI_HU_SHUO_LIAN     	1739 


//
//	DB�� ����Ǵ� ���̿���
//
#define PSIONIC_HASTE				1
#define PSIONIC_SHIELD				6
#define PSIONIC_DEXUP				11
#define PSIONIC_HPUP				12

#define PSIONIC_ADAMANTINE			13
#define PSIONIC_MIGHTYWEAPON		14
#define PSIONIC_BERSERKER			15

//
//	Quest Psionic
//
#define PSIONIC_FAST_RUN			16
#define PSIONIC_MIND_SHOCK			17
#define PSIONIC_MIND_GUARD			18
#define PSIONIC_PSI_SHIELD			19
#define PSIONIC_PIERCING_SHIELD		20
#define	PSIONIC_BAO_YAN				35
#define PSIONIC_BA_QI				36
#define PSIONIC_CHAO_FAN_TAN        64
#define PSIONIC_CHAO_FENG_LI        65
#define PSIONIC_CHAO_YI_NENG        66
#define PSIONIC_CHAO_DUO_CHONG        67
#define PSIONIC_CHONG_RAN           73
#define PSIONIC_LI_HU_SHUO_LIAN     	76 

const BYTE PSI_BISA_0			=	0x17;					//ȭ��ɱ
const BYTE PSI_BISA_1			=	0x18;					//����ɱ
const BYTE PSI_BISA_2			=	0x19;					//����ɱ
const BYTE PSI_BISA_3			=	0x1a;					//ǹ��ɱ
const BYTE PSI_BISA_4			=	0x53;					//�ٲñ�ɱ

const BYTE PSI_ZHAN_SHEN_GONG		=	54;	   //ս��ļ��� �ڰ�����
//��ְҵħ��
const BYTE PSI_JUDGE_FU_SHE_LEN		=	71;					//������ lv10
const BYTE PSI_JUDGE_CALL_YI_TU_LUO		=	72;				//�ٻ���Ϳ��lv20
const BYTE PSI_JUDGE_CONG_RAN		=	73;					//��ȼlv30
const BYTE PSI_JUDGE_ATTACK_UP		=	74;					//����������-����lv50
const BYTE PSI_JUDGE_WIS_UP		=	75;						//����������-����lv50
const BYTE PSI_JUDGE_LI_HU_SHUO_LIAN		=	76;			//�������
const BYTE PSI_JUDGE_CALL_PU_LEI_TA		=	77;				//�ٻ�������lv90
const BYTE PSI_JUDGE_QIANG_LI_CONG_RAN		=	78;			//ǿ����ȼlv100
const BYTE PSI_JUDGE_XI_SHEN_HU_FA		=	79;				//��������lv115
const BYTE PSI_JUDGE_CALL_KE_LAO_SI		=	80;				//�ٻ�����˹lv125
const BYTE PSI_JUDGE_LEI_XIAN_FENG_BAO		=	81;			//����籩lv130
const BYTE PSI_JUDGE_CALL_YI_XI_SI		=	82;				//�ٻ�����˹lv150
const BYTE PSI_JUDGE_LU_SHA		=	83;						//ŭɱ
//
//	Psionic Success Rate
//
#define SUCCESS_RATE_MIND_SHOCK			25
#define SUCCESS_RATE_PIERCING_SHIELD	10

//
//	E-Body Magic Class
//

#define EBODY_NONE						0			// E-Body �ɼǾ���
#define EBODY_MOVE_UP					1			// �̵��ӵ� 1�ܰ� ����
#define EBODY_ATTACK_DELAY_DOWN			2			// ���ݼӵ� 1�ܰ�����
#define EBODY_WEIGHT_UP					3			// ���� 10% �� ��
#define EBODY_DEFENSE_UP				4			// ���� ����
#define EBODY_PSI_RESIST_UP				5			// ���̿��� ���� ����

#define EBODY_VITAL_RESIST				6			// ����Ż ũ��Ƽ�� ������ ����			
#define EBODY_BACK_RESIST				7			// �ݰ� ������ ����
#define EBODY_WEAPON_BASE_UP			8			// ������ �⺻ ������ ����
#define EBODY_ATTACK_RATING_UP			9			// ���߷� ����
#define EBODY_PSI_ATTACK_UP				10			// ���̿��� ������ ����

#define EBODY_HP_RECOVERY_UP			11			// HP ȸ���� �߰�
#define EBODY_AVOID_RATING_UP			12			// ȸ���� �߰�
#define EBODY_RECOVERY_TIME_UP			13			// ȸ���ӵ� ����
#define EBODY_CASTING_DELAY_DOWN		14			// ĳ���� �ð� ����
#define EBODY_PP_RECOVERY_UP			15			// PP ȸ���� �߰�

#define EBODY_STR_TO_DAMAGE				16			// STR �� �������� ȯ��
#define EBODY_STR_TO_WEIGHT				17			// STR �� ���Է� ȯ��
#define EBODY_CON_TO_HP					18			// CON �� HP �� ȯ��
#define EBODY_CON_TO_DEFENSE			19			// CON ����������
#define EBODY_CON_TO_BACK_RESIST		20			// CON �� �ݰ� ������ ���ҷ�

#define EBODY_CON_TO_VITAL_RESIST		21			// CON �� ����Ż ������ ���ҷ�
#define EBODY_DEX_TO_ATTACK_RATING		22			// DEX �� ���߷��� 
#define EBODY_DEX_TO_AVOID_RATING		23			// DEX �� ȸ������
#define EBODY_DEX_TO_DAMAGE				24			// DEX �� ��������
#define EBODY_DEX_TO_BACK_RESIST		25			// DEX �� �ݰݵ����� ���ҷ�

#define EBODY_DEX_TO_VITAL_RESIST		26			// DEX �� ����Ż ������ ���ҷ�
#define EBODY_VOL_TO_PSI_DAMAGE			27			// VOL �� ���̿��� ��������
#define EBODY_VOL_TO_PSI_RESIST			28			// VOL �� ���̿��� ���׷�����
#define EBODY_WIS_TO_PP					29			// WIS �� PP�� 
#define EBODY_WIS_TO_CAST_DOWN			31			// WIS �� �ɽ��� �ð� ���ҷ�

#define EBODY_WIS_TO_DAMAGE				32			// WIS������Զ�̹�����

#define EBODY_MAGIC_COUNT				33			//��е����������Ŀ
///
///��ʯ///
#define HUANSHI_MAGIC_COUNT		8 
#define H_ZERO			0
#define H_DEFINE		1
#define H_PSI_DEFINE	2
#define H_HP			3
#define H_HUIBI			4
#define H_PSI_SUB_DAMAGE 5
#define H_END_SUB_DAMAGE 6
#define H_WL_SUB_DAMAGE 7

#define MS_MAGIC_COUNT 13 //��������ͳ��
#define Q0_130_0	0
#define QS0_130_0	1
#define QS0_130_1	2
#define QS0_130_2	3
#define FS1_130_3	4
#define FS1_130_4	5
#define FS1_130_5	6
#define JS2_130_6	7
#define JS2_130_7	8
#define JS2_130_8	9
#define QS3_130_9	10
#define QS3_130_10	11
#define QS3_130_11	12
//
//	Magic Item
//
//#define MAGIC_COUNT						38			// ħ����������
#define STATE_MAGIC_COUNT				8

#define MAGIC_NONE						0//��
#define MAGIC_STR_UP					1 //��������
#define MAGIC_CON_UP					2 //��������.
#define MAGIC_DEX_UP					3 //��������
#define MAGIC_VOL_UP					4 //�ǻ�����
#define MAGIC_WIS_UP					5 //��������.

#define MAGIC_BACK_ATTACK				6			//��������
#define MAGIC_EXCITE					7//�˷ܼ���
#define MAGIC_IRON_SKIN					8//����Ƥ��
#define MAGIC_HP_RECOVER_UP				9//����ҽ��

#define MAGIC_PSI_CONCENTRATION			10			// ħ������
#define MAGIC_CASTING_DELAY_DOWN		11//��������
#define MAGIC_PP_CONSUME_DOWN			12//����ǿ��
#define MAGIC_PP_RECOVER_UP				13//ڤ�뼼��

#define MAGIC_VITAL_CRITICAL			14			//���̼���
#define MAGIC_CRITICAL_GUARD			15    //���ܼ���
#define MAGIC_EDGE_CONCENTRATION		16//������
#define MAGIC_SP_RECOVER_UP				17//�ظ�����

#define MAGIC_ATTACK_ACCURACY_SKILL_UP	18			// �ѻ�����
#define MAGIC_FIRE_DOUBLE_ATTACK		19//���似��
#define MAGIC_AVOID_SKILL_UP			20//�鶯����
#define MAGIC_MIN_DAMAGE_UP				21//ǹе��ʦ

#define MAGIC_DAMAGE_UP					22  //��������
#define MAGIC_STATE_ERROR_UP			23	//�շ�����״̬
#define MAGIC_STATE_ERROR_DOWN			24			//��ֹ�����쳣״̬
#define MAGIC_ALL_SKILL_UP				25//���м���
#define MAGIC_RANGE_UP					26//������� 
#define MAGIC_ATTACK_DELAY_DOWN			27//�����ٶ�
#define MAGIC_ATTACK_RATING_UP			28//������
#define MAGIC_AVOID_RATING_UP			29//�ر���
#define MAGIC_BROKEN_DOWN				30			// ������
#define MAGIC_DEFENSE_UP				31			// ��������
#define MAGIC_DURATION_UP				32			// �;�������
#define MAGIC_MAX_HP_UP					33			// ����ֵ����
#define MAGIC_MAX_PP_UP					34			//����ֵ����
#define MAGIC_MAX_SP_UP					35			//����ֵ����

#define MAGIC_PSI_RESIST_UP				36			// ħ����������
#define MAGIC_PSI_ATTACK_UP				37			// ħ����������

#define MAGIC_ALL_POINT_UP				38			// ���м��ܵ�����
#define MAGIC_HP_RATING_UP				39			// Ѫ�����Ӱٷֱ�

#define MAGIC_ZI_DONG_FANG_HU			41			// �Զ�����
#define MAGIC_WU_SHI_CHUA_CHI			42			// ���Ӵ���

#define MAGIC_PSI_ATTACK_DOWN			43			// ħ�����˼���
#define MAGIC_FINALLY_ATTACK_DOWN		44			// �������˼���
#define MAGIC_PHY_ATTACK_DOWN			45			// �������˼���

#define MAGIC_EXP_3BEI_UP				46			// ��þ���ֵ����30%

#define MAGIC_FINALLY_ATTACK_UP			48			// ������������ 

#define MAGIC_QIANG_HUA_HUA_FA_UP		49			// ǿ������
#define MAGIC_REN_MI_BU_XI_UP			50			// ���Ϣ
#define MAGIC_BAO_FA_UP					51			// ��������
#define MAGIC_JIN_ZHUN_UP				52			// ��׼����

#define MAGIC_COUNT						53			//ħ����������
//
//	Magic Item STATE_ERROR �����̻� ����
//
#define MAGIC_STATE_NORMAL				0 
#define MAGIC_STATE_ELECTRIC			1 
#define MAGIC_STATE_COLD				2 
#define MAGIC_STATE_FIRE				4 
#define MAGIC_STATE_CONFUSION			8
#define MAGIC_STATE_PARALISYS			16
#define MAGIC_STATE_POINSON				32  
#define MAGIC_STATE_BLIND				64
#define MAGIC_STATE_ALL					127

//
//	SKILL
//
#define SKILL_IRON						0//����Ƥ��
#define SKILL_EXCITE					1//�˷�
#define SKILL_BACK_ATTACK				2//��������
#define SKILL_HP_RECOVER_UP				3//����ҽ��

#define SKILL_PP_RECOVER_UP				5//ڤ˼
#define SKILL_PP_DOWN					6//����ǿ��
#define SKILL_PSI_SUCCESS_UP			7//ħ������
#define SKILL_CASTING_DOWN				8//��ʦ��ʦ

#define SKILL_CONCENTRATION				10//������
#define SKILL_CRITICAL_GUARD			11//����
#define SKILL_VITAL_CRITICAL			12//����
#define SKILL_SP_RECOVER_UP				13//�ظ�

#define SKILL_MIN_DAMAGE_UP				15//ǹе��ʦ
#define SKILL_RE_FIRE_UP				16//����
#define SKILL_ATTACK_RATING_UP			17//�ѻ�
#define SKILL_AVOID_RATING_UP			18//�鶯

#define SKILL_ASSAULT					20//ŭ��
#define SKILL_ABSOLUTE_DEFENSE			21//���Է���
#define SKILL_PSYCHIC_RESIST			22//ħ������
#define SKILL_DEFENSE_UP				23//��������

#define SKILL_JUDGE_QIANGHUAHUFA		25				//ǿ����������,67%���������ɻ���������1-2��9��,3-8��8��,9-14��7��,15-20��6��,
#define SKILL_JUDGE_RENMINBUXI			26				//������Ϣ ���78%����ת������1-6������ÿ������12%,6���Ժ�ÿ������11%
#define SKILL_JUDGE_BAOFA				27				//���� ���10����������10%
#define SKILL_JUDGE_JINGZHUN			28				//��׼ ���10����1-6����ÿ������2�㡣6���Ժ�ÿ����������1 

#define SKILL_COUNT						29				//��ͨ��������


#define SKILL_130_TI_ZHI_QIANG_HUA		16				//�ٲ�����ǿ�� 15����Ϊ���,ÿ���Ӷ������� 
#define SKILL_130_REN_MI_FU_HA			17				//�ٲ��������� �ٲ�Ѫ����� 17%,ÿ������2%
#define SKILL_130_MO_FU_KANG_CHI_4		18				//�ٲÿ��� 37ħ������ ÿ����4��
#define SKILL_130_COUNT					19				//130��������

#define SKILL_140_ZHONGJI_FANGYU		12				//140�ռ�����
#define SKILL_140_WUDI_LIESHA			13				//140�޵���ɱ
#define SKILL_140_ZHI_DONG		        14				//140�ƶ�


////////////////////////////////////////////////////(�ٲٱ� �� ������)
#define MAGIC_BROKEN_DOWN_5				5
#define MAGIC_BROKEN_DOWN_11_TO_15		67

/*
/////���� �۾�
#define MAGIC_DAMAGE_Y_UP				1
#define MAGIC_DAMAGE_Z_UP				2
#define MAGIC_ACCURACY_UP_5				3
#define MAGIC_CRITICAL_UP_4				4
#define MAGIC_BROKEN_DOWN_5				5
#define MAGIC_MAKE_POISON				6
#define MAGIC_MAKE_PARALYSIS			7
#define MAGIC_MAKE_CONFUSION			8
#define MAGIC_MAKE_BLIND				9
#define MAGIC_MAKE_FIRE					10
#define MAGIC_MAKE_ICE					11
#define MAGIC_MAKE_ELECTRIC				12
#define MAGIC_DURATION_UP_200			13
#define MAGIC_STAFF_GUARD_1				14
#define MAGIC_BRAWL_GUARD_1				15
#define MAGIC_EDGE_GUARD_1				16
#define MAGIC_STAFF_CONCENTRTE_UP_1		17
#define MAGIC_STAFF_PSY_ACCLIMATE_UP_1	18
#define MAGIC_STAFF_FASTCAST_UP_1		19
#define MAGIC_EDGE_WPN_ACCLIMATE_UP_1	20
#define MAGIC_EDGE_FASTATTACK_UP_1		21
#define MAGIC_FIREARM_OUTRANGE_UP_1		22
#define MAGIC_FIREARM_STRAFING_UP_1		23
#define MAGIC_FRIEARM_MECHANIC_UP_1		24
#define MAGIC_BRAWL_FASTATTCK_UP_1		25
#define MAGIC_BRAWL_OVERHEAT_UP_1		26
#define MAGIC_AMMO_UP_4					27
#define MAGIC_ARMORPOINT_UP_1_TO_7		28
#define MAGIC_RANGE_UP_1				29
#define MAGIC_ATTACKDELAY_DN_1_TO_5		30
#define MAGIC_AVOID_POINSON				31
#define MAGIC_AVOID_PARALISYS			32
#define MAGIC_AVOID_CONFUSION			33
#define MAGIC_AVOID_BLIND				34
#define MAGIC_AVOID_FIRE				35
#define MAGIC_AVOID_ICE					36
#define MAGIC_AVOID_ELECTRIC			37
#define MAGIC_AVOID_ALL					38
#define MAGIC_USING_SP_DOWN_1			39
#define MAGIC_STR_UP_1_TO_2				40
#define MAGIC_CON_UP_1_TO_2				41
#define MAGIC_DEX_UP_1_TO_2				42
#define MAGIC_INT_UP_1_TO_2				43
#define MAGIC_VOL_UP_1_TO_2				44
#define MAGIC_WIS_UP_1_TO_2				45
#define MAGIC_EVADE_UP_10_TO_20			46
#define MAGIC_RECOVER_PP_UP_1			47
#define MAGIC_RECOVER_SP_UP_1			48
#define MAGIC_DURATION_UP_100			49
#define MAGIC_DURATION_UP_300			50
#define MAGIC_ARMORPOINT_UP_8_TO_15		51
#define MAGIC_ACCURACY_UP_11_TO_15		52
#define MAGIC_CRITICAL_UP_11_TO_15		53
#define MAGIC_ATTACKDELAY_DN_11_TO_15	54
#define MAGIC_STAFF_ACCURACY_UP_1		55
#define MAGIC_BRAWL_ACCURACY_UP_1		56
#define MAGIC_EDGE_ACCURACY_UP_1		57
#define MAGIC_FIREARM_ACCURACY_UP_1		58
#define MAGIC_EDGE_VITAL_CRITICAL_UP_1	59
#define MAGIC_BRAWL_DEALY_CRITICAL_UP_1	60
#define MAGIC_ALL_SKILL_UP_1			61
#define MAGIC_ALL_SKILL_UP_2			62
#define MAGIC_ATTACKDELAY_DN_6_TO_10	63
#define MAGIC_DURATION_UP_500			64
#define MAGIC_DURATION_UP_700			65
#define MAGIC_CRITICAL_UP_16_TO_20		66
#define MAGIC_BROKEN_DOWN_11_TO_15		67
#define MAGIC_STAFF_ACCURACY_UP_2		68
#define MAGIC_BRAWL_ACCURACY_UP_2		69
#define MAGIC_EDGE_ACCURACY_UP_2		70
#define MAGIC_FIREARM_ACCURACY_UP_2		71
#define MAGIC_STAFF_GUARD_2				72
#define MAGIC_BRAWL_GUARD_2				73
#define MAGIC_EDGE_GUARD_2				74
#define MAGIC_USING_SP_DOWN_2			75
#define MAGIC_STR_UP_3_TO_4				76
#define MAGIC_CON_UP_3_TO_4				77
#define MAGIC_DEX_UP_3_TO_4				78
#define MAGIC_INT_UP_3_TO_4				79
#define MAGIC_VOL_UP_3_TO_4				80
#define MAGIC_WIS_UP_3_TO_4				81
#define MAGIC_EVADE_UP_30_TO_40			82
#define MAGIC_ATTACKDELAY_DN_10			83
#define MAGIC_RECOVER_PP_UP_2			84
#define MAGIC_RECOVER_SP_UP_2			85
#define MAGIC_RANGE_UP_2				86
#define MAGIC_EDGE_VITAL_CRITICAL_UP_2	87
#define MAGIC_BRAWL_DEALY_CRITICAL_UP_2	88
#define MAGIC_BRAWL_FASTATTACK_UP_2		89
#define MAGIC_BRAWL_OVERHEAT_UP_2		90
#define MAGIC_DAMAGE_X_UP_1				91
#define MAGIC_DAMAGE_Y_UP_4_TO_6		92
#define MAGIC_DAMAGE_Z_UP_6_TO_10		93
*/
//
//	Attack
//
#define		DEFAULT_AT_DELAY	600  //����ְҵ�����ӳ�
#define		DEFAULT_SP_DEC		1

const BYTE	ATTACK_FAIL				=	0;
const BYTE	ATTACK_SUCCESS			=	1;
const BYTE	ATTACK_MISS				=	2;
const BYTE	CRITICAL_ATTACK_SUCCESS =	3;//yskang 0.3
const BYTE	CRITICAL_ATTACK_MISS	=	4;//yskang 0.3

const BYTE	ATTACK_MIN		=	15;//20;
const BYTE	ATTACK_MAX		=	90;//80;

#define		DAMAGE_DELAY_C_TIME	2000

//
//	LevelUP Init Value
//
#define SKILL_INIT_VALUE		300
#define PSY_INIT_VALUE			300
#define LEVEL_INIT_VALUE		600

//	Logic Define...
#define LOGIC_POSITION			0X01
#define LOGIC_MEET_NPC			0X02

//	Execution Define...
#define EXEC_LINK				0X01
#define EXEC_SAY				0X02
#define EXEC_SAY_IN				0x03
#define EXEC_GIVE_ITEM			0X04
#define EXEC_ROB_ITEM			0X05
#define EXEC_SDROB_ITEM			0X6F//�Ż�ȯ
#define EXEC_GIVE_MAGIC			0X06
#define EXEC_ROB_MAGIC			0X07
#define EXEC_BBS_OPEN			0X08
#define EXEC_DISAPPEAR			0X09
#define EXEC_RUN_MAGIC			0X0A
#define EXEC_DEAD				0X0B
#define EXEC_CHANGE_LEVEL		0X0C
#define EXEC_CHANGE_GENDER		0X0D
#define EXEC_CHANGE_HP			0X0E
#define EXEC_CHANGE_MP			0X0F
#define EXEC_CHANGE_STR			0X10
#define EXEC_CHANGE_DEX			0X11
#define EXEC_CHANGE_INT			0X12
#define EXEC_CHANGE_WIS			0X13
#define EXEC_CHANGE_CHR			0X14
#define EXEC_CHANGE_CON			0X15
#define EXEC_CHANGE_DMAGIC		0X16
#define EXEC_CHANGE_WMAGIC		0X17
#define EXEC_CHANGE_BMAGIC		0X18
#define EXEC_CHANGE_SWORD		0X19
#define EXEC_CHANGE_SPEAR		0X1A
#define EXEC_CHANGE_AXE			0X1B
#define EXEC_CHANGE_BOW			0X1C
#define EXEC_CHANGE_KNUCKLE		0X1D
#define EXEC_CHANGE_WEAPONMAKE	0X1E
#define EXEC_CHANGE_ARMORMAKE	0X1F
#define EXEC_CHANGE_ACCMAKE		0X20
#define EXEC_CHANGE_POTIONMAKE	0X21
#define EXEC_CHANGE_COOKING		0X22
#define EXEC_SHOW_MAGIC			0X23
#define EXEC_MAKER_OPEN			0X24
#define EXEC_STORAGE_OPEN		0X25
#define EXEC_AUCTION_SELL_OPEN	0X26
#define EXEC_AUCTION_BUY_OPEN	0X27
#define EXEC_SELECT_MSG			0X28
//#define EXEC_MESSAGE_OK			0X29
#define EXEC_KILL_BABY			0x29			//��������
//#define EXEC_MESSAGE_NONE		0X2A
#define	EXEC_GIVE_YB			0x2A//��Ԫ��
#define EXEC_GIVE_GOLD			0X2B
#define EXEC_ROB_DN				0X2C
#define EXEC_ROB_LING			0X1A
#define EXEC_RUN_EVENT			0X2D
#define EXEC_ADD_EVENT			0X2E
#define EXEC_DEL_EVENT			0X2F
#define EXEC_RAND_SAY			0X30
#define EXEC_RETURN				0X31
#define EXEC_CHANGE_MAGETYPE	0X32
#define EXEC_GUILD_OPEN			0X33 // ��弳���� ����.
#define EXEC_ADD_SKILL			0X80
#define EXEC_GIVE_ITEM_ALL		0X81
/********************************************************/
// 2001.5.7 HyperText... 
#define EXEC_STORE_OPEN			0X03 // ������ �Ǹ� NPC
#define EXEC_REPAIR_OPEN		0X34 // ������ ���� NPC 		
#define EXEC_SELL_OPEN			0X35 // ������ �� NPC 
#define EXEC_ZONE_MOVE			0X36 // �ش� ������ ����
#define EXEC_MOVE				0X41 // ���� ������ �̵� ����
#define EXEC_FT_MOVE			0X3A // ��������� �̵�	
#define EXEC_FT_PEOPLE			0x3B // �ν� ��ġ�� ǥ��
#define EXEC_FT_REPAIR			0x3C // �ν� ��ġ�� ǥ��
#define EXEC_PSI_STORE_OPEN		0X37 // �ش� ���̿��� �Ǹ�
#define EXEC_ALL_CURE			0X38 // ��� HP, PP, SP�� MAX�� ����
//#define EXEC_CARE				0X39 // ��� �����̻� ġ��
#define EXEC_SC_CHENGXU_KA      0X39//ɾ�����׳���
#define EXEC_BANK_OPEN			0x40 // ���� â���� ����. 
#define EXEC_GUILD_MARK			0x42 // ��� ������ ���
#define EXEC_GUILD_WAREHOUSE_OPEN 0x43 // ��� â�� ����.
#define EXEC_EBODY_OPEN			0x44 // E_Body ������ �����Ѵ�.	
#define EXEC_UPGRADE_OPEN		0x45
#define EXEC_FIELD_STORE_OPEN	0x46 // �ʵ�����϶��� �б��ؾ� �ϹǷ�..���� �����Ѵ�.
#define EXEC_GUILD_SAY			0x47 // ��忡 ���� ������ ����� �źп� ���� �б��Ѵ�...
#define EXEC_GUILD_TAX			0x48 // �渶�� �ش� ������ ������ �����Ѵ�.
#define EXEC_GUILD_SCHEME		0x49 // �渶�� �ش� ������ ���� ������� �����Ѵ�.
#define EXEC_GUILD_APPLY		0x4A // �ٸ� �渶�� ������� ��û�Ѵ�.
#define EXEC_XP_UP				0x4B // XP�� �÷���
#define EXEC_CHECK_GUILD_USER	0x4C // �������� ��������� ������.	
#define EXEC_CHECK_GUILD_RANK	0x4D // ��� �Ͽ콺�о縦 ���� ������ �˸���.
#define EXEC_GUARD_BOW			0x4E // ����� �������� �λ��ϸ鼭 �̺�Ʈ ��縦 �Ѵ�.
#define EXEC_GIVE_EVENT_ITEM	0x4F // �̺�Ʈ ��ǰ�ǰ� �������� ��ȯ�Ѵ�. 
#define EXEC_ADDRESS_WINDOW		0x50 // ��ǰ�� �ּ� �Է�â ����.
#define EXEC_EVENT_ROB_ITEM		0x51 // ��ǰ�� ȸ�� �̺�Ʈ
#define EXEC_DRESSING			0x52 // ���� â ����
#define EXEC_ACCOUNT_BANK_OPEN	0x53 // ���� ���� ����
#define	EXEC_GIVE_DN			0x54 // �������� �� �ֱ�
#define EXEC_SEND_MSG			0x55 // �ý��� �޼��� ������
#define EXEC_GIVE_MAGIC_ITEM	0x56 // �������� ���� �������� �ش�. item ���̺��� bySpecial�׸��� �����ɼǿ� �����ϰ�, iq�� �������� �ٲ㼭 �ش�.
#define EXEC_INPUT_WINDOW		0x57 // ���డ���ڿ��� �ø��� ��ȣ �Է�â��... 
#define EXEC_INPUTGAME_WINDOW	0x58 // ���డ�� ���ӹ濡�� �ø��� ��ȣ �Է�â��... 	
//#define EXEC_ADD_GAMETIME_ITEM	0x59 // ��ǰ���� �����ִ� ���ױǸ� ȸ���Ѵ�.
#define EXEC_SC_FUSHU_PIN	0x59    //ɾ�����׸���Ʒ
#define EXEC_CHANGE_UPGRADE_ACC 0x5A // ������ �׼������� ���׷��̵� ������ �׼������� ��ȯ���ش�.
#define EXEC_APPLY_GUILD_RUN	0x5B // ��帶���� ��û
#define EXEC_RR_ENTER			0x5C // �ξⷳ�� ����
#define EXEC_MON_SAY			0x5D // ����Ʈ������ �� say��... 	
#define EXEC_SUMMON				0x5E // ����Ʈ ���� ��ȯ�Ѵ�.
#define EXEC_EBODY_DEFINE		0x5F // EBODY Ȯ�� 
#define EXEC_HELPERCURE			0x60 // Helper npc
#define EXEC_GIVE_PSI			0x61 // Gives user PSI
#define EXEC_TRANSFORM			0x62 // lvl 20 quest transform window
#define EXEC_100_1		0x63 // 100������ת��
#define	EXEC_GIVE_HUFA			0x64        //��ȡ����
#define EXEC_100_3		0x65 // ��Ӽ��������
#define EXEC_100_4		0x66 // ��������
#define EXEC_100_5		0x67 //���߲��ϻ�
#define EXEC_100_6		0x68  //������ϻ�
#define RUN_SKILL		0x69  //������ϻ�
#define EXEC_100_2		0x70 //�����������
#define EXEC_GO_EMO				0x71	//�����ħ�㳡
#define EXEC_NPC_SAYING			0x72    //�齱
#define EXEC_OPEN_YUANBAO		0x73 //������Ԫ���̵�
#define EXEC_JUANKUAN           0x74 //���3������
#define EXEC_BAOLV              0x75 //���3������
#define EXCE_GOPK				0x76 //����PK�㳡
//#define EXCE_ON_WEB	            0x77 //��Ϸ�е���ҳ
#define EXEC_PKSAY				0X78 //PK�����Ի���
#define	EXEC_SAYSHAREN			0x79	//ɱ�˿�Ի���
#define EXCE_GOSHAREN			0x83	//ɱ�˿�����ű�
#define EXEC_NPC_DA				0X84	//�Ĳ���
#define EXEC_NPC_XIAO			0X85	//�Ĳ�С
#define EXEC_CHANGE_JOB			0X86			//תְ
#define EXEC_STUDY_NEW_JOB_PSI		0X87			//ѧ��ְҵħ��
#define EXEC_CAN_GIVE_NEWER_ITEM	0X88			//�����������װ
#define EXEC_GIVE_NEWER_ITEM		0X89			//������װ
#define EXEC_GIVE_NEWER_ITEM_FINISH	0X8a			//ˢ����ʾ
#define EXEC_ONLINE_EXCHANGE		0X95			//RMB�һ�
#define EXCE_ON_SHOP	0x96 //�����̵�
#define EXEC_CHANGE_ATTRIBUTE_ITEM		0X97 //�׺ƻ������Ժ�
#define	EXEC_OFF_JJ			0x82        //ж�»���
#define EXEC_SEND_TOU			0x99 // NPC˵��


//	Logic Else Define...
#define LOGIC_LEVEL					0X01
#define LOGIC_EXIST_EVENT			0X02
#define LOGIC_ABSENT_EVENT			0X03
#define LOGIC_EXIST_ITEM			0X04
#define LOGIC_ABSENT_ITEM			0X05
#define LOGIC_CLASS					0x06
#define LOGIC_WEIGHT				0x07
#define LOGIC_CHECK_ITEMSLOT		0x08		
#define LOGIC_EXIST_GM				0x09 // ��帶������ ��� ���
#define LOGIC_ZONE_WHO				0x10 // �̵��� ���� ������ ����߿� �ִ��� üũ
#define LOGIC_KILL_GH				0x11 // ����Ͽ콺 �Ǹ��� ����
#define LOGIC_MASS_ZONE_MOVE		0x12 // 
#define LOGIC_TERM					0x13 // ���� ��¥ �����ȿ��� �����Ѵ�.	
#define LOGIC_GUILD_HOUSE_NUMBER	0x14 // ����Ͽ콺 ������尡 �ִ��� üũ�Ѵ�.
#define LOGIC_CHECK_CV				0x15 // �ù� ����� üũ�Ѵ�.
#define LOGIC_EXIST_EVENT_ITEM		0X16 // ��ǰ���� üũ�Ѵ�.
#define LOGIC_MONEY					0X17 // ���� üũ�Ѵ�
#define LOGIC_RAND					0X18 // Ȯ���� ������ Ȯ���� �ɸ��� ���
#define LOGIC_OVER_GUILD_USER_COUNT 0X19
#define LOGIC_RR_TIME				0X1A // �ξⷳ�� ���� ������ �ð����� üũ
#define LOGIC_RR_MAX_USER			0X1B // �ξⷳ�� �ִ� ������� ���� �ȵƴ��� üũ
#define LOGIC_EXIST_SKILL           0X1C //�ټ�ѧϰʲô����
#define LOGIC_VIP					0X1D // NPC����Ա
#define LOGIC_LING					0X1E 
#define	EXEC_HUISHOU		        0x3E  
//
//	User Define Struct
//
typedef union{
	short int	i;
	BYTE		b[2];
} MYSHORT;

typedef union{
	__int64		i;
	BYTE		b[8];
} MYINT64;


//
//	User Status Value
//
#define USER_ABILITY_NUM		5		// �⺻ ���� �ɷ�ġ ����

#define USER_STR				0
#define USER_CON				1
#define USER_DEX				2
#define USER_VOL				3
#define USER_WIS				4

//
//	User Guild Require
//
#define GUILD_MAKE_LEVEL		50
#define GUILD_MAKE_DN			100000	

//
//	Default Start Position
//
#define DEFAULT_START_X			200
#define DEFAULT_START_Y			550

//
//	Magic Slot Num
//
#define MAGIC_NUM				11		// ���� �Ӽ� ����

//
//	Item Quality
//
const BYTE	NORMAL_ITEM			= 0;
const BYTE	REMODEL_ITEM		= 1;
const BYTE	MAGIC_ITEM			= 2;
const BYTE	RARE_ITEM			= 3;
const BYTE	UNIQUE_ITEM			= 4;
const BYTE	SET_ITEM			= 5;
const BYTE	UPGRADE_ITEM		= 6;
const BYTE	REMODEL_MAGIC_ITEM	= 8;
const BYTE	GUARDIAN_ITEM		= 9;
const BYTE	REMODEL2_ITEM		= 10;//�۰ټ�װ��
const BYTE	MAGIC2_ITEM			= 11;//���ټ�
const BYTE	RARE2_ITEM			= 12;//��ټ�
const BYTE	GUARTIANSHI_ITEM	= 14;
const BYTE  SUPER_EBODY_ITEM	= 15;				//������е	
const BYTE	RARE3_ITEM			= 18;//130

const BYTE	EVENT_SP1_ITEM	= 201;		// �̺�Ʈ�� ���� �������� ��ȭ�� ��ǰ�� ������	
const BYTE	EVENT_SP2_ITEM	= 202;		// �̺�Ʈ�� ���� �������� ��ȭ ��ǰ�� ������	
const BYTE	EVENT_DEF_ITEM	= 243;		// �̺�Ʈ�� ���� �������� �� ��ȯ ������	
const BYTE	EVENT_ATT_ITEM	= 242;		// �̺�Ʈ�� ���� �������� ���� ��ȯ ������	
const BYTE	EVENT_POT_ITEM	= 205;		// �̺�Ʈ�� ���� �������� ���� ��ȯ ������	

const BYTE	EVENT_ITEM_MOON		= 220;	// ������
const BYTE	EVENT_ITEM_SONGPEON	= 221;	// ����
const BYTE	EVENT_ITEM_BOX		= 222;	// ��������

const BYTE	EVENT_ATT7_ITEM	= 240;		// ���� �̺�Ʈ������ 
const BYTE	EVENT_DEF7_ITEM	= 241;		// 
const BYTE	EVENT_ATT6_ITEM	= 244;		// 
const BYTE	EVENT_DEF6_ITEM	= 245;		// 
const BYTE	EVENT_ATT4_ITEM	= 246;		// 
const BYTE	EVENT_DEF4_ITEM	= 247;		// 
const BYTE	EVENT_ATT3_ITEM	= 248;		// 
const BYTE	EVENT_DEF3_ITEM	= 249;		// 
const BYTE  EVENT_INIT_STAT_ITEM = 250;	// �ؾ�
const BYTE  EVENT_USER_GAME_TIME = 252; // ���� ������

#define EVENT_ITEM_BAND		  100		

const BYTE	BREAK_NORMAL	= 100;
const BYTE	BREAK_MAGIC		= 101;
const BYTE	BREAK_REMODEL	= 102;
const BYTE	BREAK_RARE		= 103;
const BYTE	BREAK_UNIQUE	= 104;
const BYTE	BREAK_SET		= 105;

//
//	Item Wear Class
//
const BYTE	ATTACK_ITEM				= 1;
const BYTE	MATERIAL_ITEM			= 16; //���� �������� ���� 
const UINT	MATERIAL_MAGIC_UP_ITEM	= 625; //���׷��̵带 ���� ���� ������ = �ں��
const UINT	MATERIAL_RARE_UP_ITEM	= 626; //���׷��̵带 ���� ���� ������ = Į���̸�
const UINT	MATERIAL_REMODEL_UP_ITEM	= 861;//���� ���׷��̵带 ���� ������ = Ÿ����
const UINT	MATERIAL_EBODY_UP_ITEM	= 1236;//���� ���׷��̵带 ���� ������ = Ÿ����

//
//	Item Upgrade Cost
//
#define ATTACK_UPGRADE_COST		200000	//	Weapon Upgrade Cost
#define DEFENSE_UPGRADE_COST	100000	//	Defense Upgrade Cost
#define ACCESSORI_UPGRADE_COST	10000	//	Accessori Upgrade Cost
#define ITEM_REMODELING_COST	50000	//	Item Remodeling Cost
#define ITEM_REMAGIC_COST		200000	//	ħ��ʥװ����
#define EBODY_UPGRADE_COST		200000	//	EBody Upgrade Cost
#define EBODY_IDENTIFY_COST		100000	//	EBody Indentify Cost
#define ATTACKCHAO_UPGRADE_COST		1000000	//	���鳬����������
#define DEFENSEWANG_UPGRADE_COST	1000000	//	������������


//
//	EBody ���� �Ҹ� XP
//
#define EBODY_UPGRADE_XP	2000
#define EBODY_IDENTIFY_XP	100
#define FANGJUCAILIAOHUA_XP	100


#define UPDATE_TICKS		500000

//
//	City Level
//
#define USER_PK				1

const short CHAONISE_RANK	= 0;	
const short DEATH_RANK		= 1;	
const short EVIL_RANK		= 2;	
const short VILLAIN_RANK	= 3;	
const short CAIN_RANK		= 4;

const short COMMOM_RANK		= 5;

const short CITIZEN_RANK	= 6;	
const short VIUAL_RANK		= 7;	
const short WARRIOR_RANK	= 8;	
const short HERO_RANK		= 9;	
const short SAINT_RANK		= 10;
const short GUARDANT_RANT	= 11;  //ʥ��
const short	ANGEL_RANK		= 12;	//��ʹ

#define CITY_RANK_INTERVAL	5;

#define USER_PK_TICKS		25000	//����ʱ��

#define GUILD_HOUSE_MAX_NUM	7		// ù��° 0�� ����, 6�� ��� �Ͽ콺

#define UPDATE_GUILD_INVEN_TIME		12
#define UPDATE_GUILD_CITY_TIME		1

#define SYSTEM_GUILD_BAND	900000

//
// User Event Max Num
// �û��¼����ֵ
#define MAX_EVENT_NUM		350
//
//	g_DynamicSkillInfo
//
const BYTE	MAX_SKILL_MAGIC_NUM	= SKILL_COUNT;

//
//	Item Data Version
//
#define CURRENT_ITEM_VERSION	1

//
//	ItemLog Type
//
#define ITEMLOG_PICKUP					1
#define ITEMLOG_THROW					2
#define ITEMLOG_GIVE					3
#define ITEMLOG_RECEIVE					4
#define ITEMLOG_EXCHANGE_GIVE			5
#define ITEMLOG_EXCHANGE_RECEIVE		6
#define ITEMLOG_SELL					7
#define ITEMLOG_BUY						8
#define ITEMLOG_ACCOUNT_BANKIN			9
#define ITEMLOG_ACCOUNT_BANKOUT			10
#define ITEMLOG_GUILD_BANKIN			11
#define ITEMLOG_GUILD_BANKOUT			12
#define ITEMLOG_UPGRADE_SUCCESS			13
#define ITEMLOG_UPGRADE_FAIL			14

#define ITEMLOG_MONEY_LOTTERY			15
#define ITEMLOG_MONEY_GIVE				16
#define ITEMLOG_MONEY_THROW				17
#define ITEMLOG_MONEY_PICKUP			18
#define ITEMLOG_EXCHANGE_GIVE_MONEY		19
#define ITEMLOG_EXCHANGE_RECEIVE_MONEY	20
#define ITEMLOG_SELL_MONEY				21
#define ITEMLOG_BUY_MONEY				22
#define ITEMLOG_ACCOUNT_BANKIN_MONEY	23
#define ITEMLOG_ACCOUNT_BANKOUT_MONEY	24
#define ITEMLOG_GUILD_BANKIN_MONEY		25
#define ITEMLOG_GUILD_BANKOUT_MONEY		26

#define ITEMLOG_EVENT_GIVE				27

#define ITEMLOG_DEAD_THROW				28

#define ITEMLOG_BLESS_UPGRADE_SUCCESS	29
#define ITEMLOG_BLESS_UPGRADE_FAIL		30

#define ITEMLOG_REMODEL_SUCCESS			31
#define ITEMLOG_REMODEL_FAIL			32

#define ITEMLOG_BLESS_USE				33		// �� ������ �񽺹����� �������� ����Ҵ�
#define ITEMLOG_SPECIAL_USE_POTION		34		// Ư���� �Ҹ� ������ ����Ҷ�

#define ITEMLOG_PSI_STONE				35		// ���̿��� ���汸�� ���� �α׹�ȣ

#define ITEMLOG_ACC_USE					36		// �Ҹ� �Ǽ��縮�� �������
#define ITEMLOG_REMAGIC_DELETE			37		// ������ �ý������� ������ ����

#define ITEMLOG_DEAD_DELETE				38		// PK �� ���� �������� �������

#define ITEMLOG_EBODY_ADDER_DELETE		39		// EBody ���׷��̵�� ���̴��� �Һ��Ѵ�.
#define ITEMLOG_EBODY_BASE_DELETE		40		// EBody ���׷��̵� ���з� ���̽��� �����Ѵ�.
#define ITEMLOG_EBODY_UPGRADE_SUCCESS	41		// EBody ���׷��̵� ����

//
//	Royal Rumble Define
//

#define RR_EMPTY						-1
#define RR_IDLE							0
#define RR_APPLY						1
#define RR_ENTERING						2
#define RR_ENTERING_END					3
#define RR_START						4
#define RR_END							5

//
//	to detect Event Hacking
//
#define BUY_BLOCK						1
#define SELL_BLOCK						2
#define REPAIR_BLOCK					3
#define CURE_BLOCK						4
#define TEL_BLOCK						5

#define ITEM_MAX_RANGE					16

// Special Accessori
#define MAX_ACCESSORI		4			// �ִ� �Ǽ��縮 ����
#define	RANDOM_PROTECT		30			// ����Ʈ �Ͱ����� ũ��Ƽ�� ���� Ȯ��
#define	GUARDIAN_SLOT		1


//yskang 0.4 ��� �αױ�� �ɼ�
//0:���Ӿ����� 1:��ȭ 2:������ �������� 3:PK����
#define CONNECT_IP		0
#define CHAT_LOG		1
#define ITEM_LOG		2
#define	PKINFO_LOG		3
#define CALL_USER_LOG	4

#endif