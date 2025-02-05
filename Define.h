#ifndef _DEFINE_H_
#define _DEFINE_H_

//
// 25레벨 OR 부분 활동제한 선택
//
#define _ACTIVE_USER		// 부분 활동

//
//
//
//#define KOR_VER
  #define CHN_VER
//  #define ENG_VER

//
//	지역 최강 이벤트을위해 로얄럼블 경기장을 임시로 쓰게한다.	
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
//#define USER_SOCKET_PORT		12000 // 임시코드

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
//VIP莖鑒
#define MAX_VIP_DAY                 20000
//磵빱莖賈莖鑒
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
#define GUILD_MAX_TAX			30 //警속江澗
#define MAX_GUILD_HOUSE_USER	20

#define GUILD_WAR_READY		0		// 길드전 바로 5분전에 발생하는 준비 단계
#define GUILD_WARRING		1		// 지금 길드전중임
#define GUILD_WAR_AFFTER	2		// 길드전이 끝난후

#define FORTRESS_VIOLENCE_WARRING	1	// 민심이 반란중
#define FORTRESS_VIOLENCE_AFFTER	0	// End

#define GUILD_WAR_MAX_MSG_TIMER	6		// 공성전중 남은 시간을 알려준다.

#define GUILD_GUARD_MAX_NUM		6	// 요새를 지키는 경비병으로 최대 6명까지 고용할수있다.
#define _GUILDNPCLIST_DB		24	// 4 * 6

#define GUILD_REPAIR_MAX_NUM	5	// 최대 5개 까지 수리할 NPC가 있다.
#define _GUILDREPAIRLIST_DB		30 // 5 * 6

#define FORTRESS_TARGET_MAX_NUM	4	// 최대 4개 까지 오델로가 있다.
#define GUILD_ATTACK_MAX_NUM	20	// 최대 20개까지 길드전 신청을 받을수 있다
#define _GUILDLIST_DB			80	// 4 * 20

#define GUILDFORTRESS_ATTACK_MAX_NUM	20	// 최대 50개까지 길드전 신청을 받을수 있다
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
#define NPC_WAIT				0x11	// 가상 공간에서 생성하는 몹은 일회성 이므로

#define NPC_PASSIVE				150
#define NPC_ACTIVE				100

//
//	About Map Object
//
#define USER_BAND				10000		// Map 위에 유저가 있다.
#define NPC_BAND				20000		// Map 위에 NPC(몹포함)가 있다.
#define INVALID_BAND			30000		// 잘못된 ID BAND
#define USER_HUFA_BAND			20000
//
//	About Big Mop Size In CELL
//
#define NPC_MAP_SIZE			20

//
//	Defines About Max Value
//
#define MAX_BASIC_ITEM			1000
#define MAX_EVENT				3000  //離댕慤숭event긍뵀 覩迦1000

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
//	시야처리
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
#define STATE_ACCEPTED			0X01   //쌈肝
#define STATE_CONNECTED			0X02   //젯쌈
#define STATE_DISCONNECTED		0X03   //뙤역
#define STATE_GAMESTARTED		0X04   //踏狗역迦
#define STATE_INITED			0X05   //男헝
#define STATE_LOGOUT			0X06   //鬧饋
#define STATE_GAMERESTART		0X07   //路폘

//
//	Event
//
#define MAX_LOGIC_INT			5
#define MAX_EXEC_INT			3
#define MAX_LOGIC_ELSE_INT		20
#define MAX_LOGIC_CHAR_LEN		128
#define MAX_EXEC_CHAR_LEN		128
#define MAX_LOGIC_ELSE_CHAR_LEN 128

#define MONSTER_ATTACK_EVENT_BAND		10000		// 10000번 이상의 이벤트 번호는 몬스터가 공격당했을때 발생한다.

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

//離댕陋구맣鑒
#define MAX_ITEM_UPGRADE_COUNT	o_yehuoini[0]->gaishu		// 현재 0~9까지 업그레이가 가능하다

#define ITEM_NAME_LENGTH		20
#define MAX_THROW_ITEM			5000    //뒈충膠틔岬劤離댕鑒
#define ITEM_MAX_USE_WEAR		150		// 아이템중 쓸수있는 속성들만 모아넣기위해, 이벤트 아이템과 구분
#define ITEM_USER_RIGHT_NUM		3		// 현재 3명까지 아이템에대해 권리를 주장한다.

#define EVENT_ITEM_LENGTH		30		// 이벤트로 발생하는 아이템의 고유번호를 부여할 자리수

#define EVENT_UNIQUE_ITEM_BAND	30000	// 최고랩 유저를위해 특별아이템을 맞춘다.	
#define EVENT_RR_ITEM_BAND		30001

// Upgrade Item
#define BLESSING_WEAPONLESS_WEAR	23	// 축 웨피리스 아이템 웨어 정보	
#define BLESSING_ARMORLESS_WEAR		24	// 축 아머리스 아이템 웨어 정보		

#define NORMAL_WEAPONLESS_WEAR		25	// 일반 웨피리스 아이템 웨어 정보	
#define NORMAL_ARMORLESS_WEAR		26	// 일반 아머리스 아이템 웨어 정보	
	
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
#define SPECIAL_ITEM_BIANLANG	    	1028  //의긴��
#define SPECIAL_ITEM_BIANXIONG		    1029  //襟긴��
#define SPECIAL_ITEM_TS			1044  //磵빱莖賈
#define SPECIAL_ITEM_HX_LS		1035//뼙쥣
#define SPECIAL_ITEM_HX_JS		1289//뼙쑨
#define SPECIAL_ITEM1441		1405  //20禱괜환
#define SPECIAL_ITEM1442		1415  //50禱괜환
#define SPECIAL_ITEM1443		1416  //100禱괜환
#define SPECIAL_ITEM1444		1417  //500禱괜환
#define SPECIAL_ITEM1445		1418  //1000禱괜환
#define SPECIAL_POTION_WEAR		116
#define SPECIAL_ITEM_HIEXP		699
#define SPECIAL_ITEM_MAGICFIND	700
#define SPECIAL_ITEM_KILLREMOVE	701
#define SPECIAL_BIAOZHI		    724

// 전자우표 아이템
#define NORMAL_ITEM_STAMP		714					// zinee 02-11-18

// Revival Item
#define NORMAL_ITEM_REVERSE		807					// 리버스리온 : 버디원 부활 아이템

//
//	Psionic Stone
//
#define PSI_STONE_WEAR			117					// 사이오닉 습득구슬 웨어 정보

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
//	DB에 저장되는 사이오닉
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

const BYTE PSI_BISA_0			=	0x17;					//화극��
const BYTE PSI_BISA_1			=	0x18;					//랬극��
const BYTE PSI_BISA_2			=	0x19;					//숲극��
const BYTE PSI_BISA_3			=	0x1a;					//퓜극��
const BYTE PSI_BISA_4			=	0x53;					//輅꼴극��

const BYTE PSI_ZHAN_SHEN_GONG		=	54;	   //濫�宙캬셍� 붚갠쥣疾
//劤斂撚침랬
const BYTE PSI_JUDGE_FU_SHE_LEN		=	71;					//륑�握� lv10
const BYTE PSI_JUDGE_CALL_YI_TU_LUO		=	72;				//梁뻥怒沽쭈lv20
const BYTE PSI_JUDGE_CONG_RAN		=	73;					//路횝lv30
const BYTE PSI_JUDGE_ATTACK_UP		=	74;					//묑샌제瓊��-츌쌥lv50
const BYTE PSI_JUDGE_WIS_UP		=	75;						//묑샌제瓊��-例제lv50
const BYTE PSI_JUDGE_LI_HU_SHUO_LIAN		=	76;			//쥣산傑졍
const BYTE PSI_JUDGE_CALL_PU_LEI_TA		=	77;				//梁뻥팹잉檢lv90
const BYTE PSI_JUDGE_QIANG_LI_CONG_RAN		=	78;			//퓻제路횝lv100
const BYTE PSI_JUDGE_XI_SHEN_HU_FA		=	79;				//勾�環ㅇ쮔v115
const BYTE PSI_JUDGE_CALL_KE_LAO_SI		=	80;				//梁뻥옹익薑lv125
const BYTE PSI_JUDGE_LEI_XIAN_FENG_BAO		=	81;			//죠落루괬lv130
const BYTE PSI_JUDGE_CALL_YI_XI_SI		=	82;				//梁뻥怒鮫薑lv150
const BYTE PSI_JUDGE_LU_SHA		=	83;						//큼��
//
//	Psionic Success Rate
//
#define SUCCESS_RATE_MIND_SHOCK			25
#define SUCCESS_RATE_PIERCING_SHIELD	10

//
//	E-Body Magic Class
//

#define EBODY_NONE						0			// E-Body 옵션없음
#define EBODY_MOVE_UP					1			// 이동속도 1단계 증가
#define EBODY_ATTACK_DELAY_DOWN			2			// 공격속도 1단계증가
#define EBODY_WEIGHT_UP					3			// 무게 10% 더 듬
#define EBODY_DEFENSE_UP				4			// 방어력 증가
#define EBODY_PSI_RESIST_UP				5			// 사이오닉 방어력 증가

#define EBODY_VITAL_RESIST				6			// 바이탈 크리티컬 데미지 감소			
#define EBODY_BACK_RESIST				7			// 반격 데미지 감소
#define EBODY_WEAPON_BASE_UP			8			// 무기의 기본 데미지 증가
#define EBODY_ATTACK_RATING_UP			9			// 명중률 증가
#define EBODY_PSI_ATTACK_UP				10			// 사이오닉 데미지 증가

#define EBODY_HP_RECOVERY_UP			11			// HP 회복량 중가
#define EBODY_AVOID_RATING_UP			12			// 회피율 중가
#define EBODY_RECOVERY_TIME_UP			13			// 회복속도 증가
#define EBODY_CASTING_DELAY_DOWN		14			// 캐스팅 시간 감소
#define EBODY_PP_RECOVERY_UP			15			// PP 회복량 중가

#define EBODY_STR_TO_DAMAGE				16			// STR 을 데미지로 환산
#define EBODY_STR_TO_WEIGHT				17			// STR 을 무게로 환산
#define EBODY_CON_TO_HP					18			// CON 을 HP 로 환산
#define EBODY_CON_TO_DEFENSE			19			// CON 을방어력으로
#define EBODY_CON_TO_BACK_RESIST		20			// CON 을 반격 데미지 감소로

#define EBODY_CON_TO_VITAL_RESIST		21			// CON 을 바이탈 데미지 감소로
#define EBODY_DEX_TO_ATTACK_RATING		22			// DEX 를 명중률로 
#define EBODY_DEX_TO_AVOID_RATING		23			// DEX 를 회피율로
#define EBODY_DEX_TO_DAMAGE				24			// DEX 를 데미지로
#define EBODY_DEX_TO_BACK_RESIST		25			// DEX 를 반격데미지 감소로

#define EBODY_DEX_TO_VITAL_RESIST		26			// DEX 를 바이탈 데미지 감소로
#define EBODY_VOL_TO_PSI_DAMAGE			27			// VOL 을 사이오닉 데미지로
#define EBODY_VOL_TO_PSI_RESIST			28			// VOL 을 사이오닉 저항력으로
#define EBODY_WIS_TO_PP					29			// WIS 를 PP로 
#define EBODY_WIS_TO_CAST_DOWN			31			// WIS 를 케스팅 시간 감소로

#define EBODY_WIS_TO_DAMAGE				32			// WIS例제긴陶넋묑샌제

#define EBODY_MAGIC_COUNT				33			//샙筠�酌痒轍乭摠�
///
///뼙柯///
#define HUANSHI_MAGIC_COUNT		8 
#define H_ZERO			0
#define H_DEFINE		1
#define H_PSI_DEFINE	2
#define H_HP			3
#define H_HUIBI			4
#define H_PSI_SUB_DAMAGE 5
#define H_END_SUB_DAMAGE 6
#define H_WL_SUB_DAMAGE 7

#define MS_MAGIC_COUNT 13 //넋埼엥橄昑固셕
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
//#define MAGIC_COUNT						38			// 침랬橄昑잚謹
#define STATE_MAGIC_COUNT				8

#define MAGIC_NONE						0//轟
#define MAGIC_STR_UP					1 //제좆藤속
#define MAGIC_CON_UP					2 //竟醴藤속.
#define MAGIC_DEX_UP					3 //츌쌥藤속
#define MAGIC_VOL_UP					4 //例쁜藤속
#define MAGIC_WIS_UP					5 //例제藤속.

#define MAGIC_BACK_ATTACK				6			//럽샌세減
#define MAGIC_EXCITE					7//菫뢸세減
#define MAGIC_IRON_SKIN					8//멀屆튄륀
#define MAGIC_HP_RECOVER_UP				9//菱乖努좟

#define MAGIC_PSI_CONCENTRATION			10			// 침랬쑹錦
#define MAGIC_CASTING_DELAY_DOWN		11//랬減쑹錦
#define MAGIC_PP_CONSUME_DOWN			12//쑹�舟옐�
#define MAGIC_PP_RECOVER_UP				13//聞拳세減

#define MAGIC_VITAL_CRITICAL			14			//누늬세減
#define MAGIC_CRITICAL_GUARD			15    //�졈秉셥�
#define MAGIC_EDGE_CONCENTRATION		16//쑹�注�櫓
#define MAGIC_SP_RECOVER_UP				17//쀼릿세減

#define MAGIC_ATTACK_ACCURACY_SKILL_UP	18			// 앗샌세減
#define MAGIC_FIRE_DOUBLE_ATTACK		19//젯�鴉셥�
#define MAGIC_AVOID_SKILL_UP			20//쥣땡세減
#define MAGIC_MIN_DAMAGE_UP				21//퓜筠댕可

#define MAGIC_DAMAGE_UP					22  //愆�客梔�
#define MAGIC_STATE_ERROR_UP			23	//撞랙몹蘆榴檄
#define MAGIC_STATE_ERROR_DOWN			24			//렝岺몹蘆嫩끽榴檄
#define MAGIC_ALL_SKILL_UP				25//杰唐세減
#define MAGIC_RANGE_UP					26//�牙慶梔� 
#define MAGIC_ATTACK_DELAY_DOWN			27//묑샌醵똑
#define MAGIC_ATTACK_RATING_UP			28//츱櫓쪽
#define MAGIC_AVOID_RATING_UP			29//쀼긁쪽
#define MAGIC_BROKEN_DOWN				30			// 믐崍쪽
#define MAGIC_DEFENSE_UP				31			// 렝徒藤속
#define MAGIC_DURATION_UP				32			// 켐씹昑藤속
#define MAGIC_MAX_HP_UP					33			// �餉篁둣梔�
#define MAGIC_MAX_PP_UP					34			//쑹�儁둣梔�
#define MAGIC_MAX_SP_UP					35			//竟제令藤속

#define MAGIC_PSI_RESIST_UP				36			// 침랬愆�客梔�
#define MAGIC_PSI_ATTACK_UP				37			// 침랬예년藤속

#define MAGIC_ALL_POINT_UP				38			// 杰唐세콘듐藤속
#define MAGIC_HP_RATING_UP				39			// 沂좆藤속겟롸궐

#define MAGIC_ZI_DONG_FANG_HU			41			// 菱땡렝빱
#define MAGIC_WU_SHI_CHUA_CHI			42			// 轟柬누늬

#define MAGIC_PSI_ATTACK_DOWN			43			// 침랬愆�鋼撮�
#define MAGIC_FINALLY_ATTACK_DOWN		44			// 離老愆�鋼撮�
#define MAGIC_PHY_ATTACK_DOWN			45			// 膠잿愆�鋼撮�

#define MAGIC_EXP_3BEI_UP				46			// 삿돤쒔駱令藤속30%

#define MAGIC_FINALLY_ATTACK_UP			48			// 離老愆�客梔� 

#define MAGIC_QIANG_HUA_HUA_FA_UP		49			// 퓻뺏�餉�
#define MAGIC_REN_MI_BU_XI_UP			50			// �荇齎뾰�
#define MAGIC_BAO_FA_UP					51			// 괵랙藤속
#define MAGIC_JIN_ZHUN_UP				52			// 쑹硫藤속

#define MAGIC_COUNT						53			//침랬橄昑잚謹
//
//	Magic Item STATE_ERROR 상태이상 참조
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
#define SKILL_IRON						0//멀屆튄륀
#define SKILL_EXCITE					1//菫뢸
#define SKILL_BACK_ATTACK				2//럽샌세콘
#define SKILL_HP_RECOVER_UP				3//菱乖努좟

#define SKILL_PP_RECOVER_UP				5//聞鋼
#define SKILL_PP_DOWN					6//쑹�舟옐�
#define SKILL_PSI_SUCCESS_UP			7//침랬쑹錦
#define SKILL_CASTING_DOWN				8//랬可댕可

#define SKILL_CONCENTRATION				10//쑹�注�櫓
#define SKILL_CRITICAL_GUARD			11//�졈�
#define SKILL_VITAL_CRITICAL			12//누늬
#define SKILL_SP_RECOVER_UP				13//쀼릿

#define SKILL_MIN_DAMAGE_UP				15//퓜筠랬可
#define SKILL_RE_FIRE_UP				16//젯��
#define SKILL_ATTACK_RATING_UP			17//앗샌
#define SKILL_AVOID_RATING_UP			18//쥣땡

#define SKILL_ASSAULT					20//큼샌
#define SKILL_ABSOLUTE_DEFENSE			21//없뚤렝徒
#define SKILL_PSYCHIC_RESIST			22//침랬예년
#define SKILL_DEFENSE_UP				23//낚섬렝徒

#define SKILL_JUDGE_QIANGHUAHUFA		25				//퓻뺏빱랬빱랬,67%폅듐例제긴냥빱랬묑샌제1-2섬9듐,3-8섬8듐,9-14섬7듐,15-20섬6듐,
#define SKILL_JUDGE_RENMINBUXI			26				//�餉宦뾰� 폅듐78%竟醴瘻냥�餉�1-6섬鹿苟첼섬藤속12%,6섬鹿빈첼섬藤속11%
#define SKILL_JUDGE_BAOFA				27				//괵랙 폅듐10묑샌제藤속10%
#define SKILL_JUDGE_JINGZHUN			28				//쑹硫 폅듐10츱櫓1-6섬鹿첼섬藤속2듐。6섬鹿빈첼섬藤속츱櫓1 

#define SKILL_COUNT						29				//팹繫세콘悧鑒


#define SKILL_130_TI_ZHI_QIANG_HUA		16				//輅꼴竟醴퓻뺏 15竟醴槨폅듐,첼섬속랗듐竟醴 
#define SKILL_130_REN_MI_FU_HA			17				//輅꼴�餉環ㅇ� 輅꼴沂좆폅듐 17%,첼섬藤속2%
#define SKILL_130_MO_FU_KANG_CHI_4		18				//輅꼴예년 37침랬예년 첼섬속4듐
#define SKILL_130_COUNT					19				//130세콘悧鑒

#define SKILL_140_ZHONGJI_FANGYU		12				//140老섐렝徒
#define SKILL_140_WUDI_LIESHA			13				//140轟둔죤��
#define SKILL_140_ZHI_DONG		        14				//140齡땡


////////////////////////////////////////////////////(바꾸기 전 데이터)
#define MAGIC_BROKEN_DOWN_5				5
#define MAGIC_BROKEN_DOWN_11_TO_15		67

/*
/////이전 작업
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
#define		DEFAULT_AT_DELAY	600  //膠잿斂撚묑醵儺넨
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
#define EXEC_SDROB_ITEM			0X6F//膽쁨환
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
#define EXEC_KILL_BABY			0x29			//찡딜녘膠
//#define EXEC_MESSAGE_NONE		0X2A
#define	EXEC_GIVE_YB			0x2A//못禱괜
#define EXEC_GIVE_GOLD			0X2B
#define EXEC_ROB_DN				0X2C
#define EXEC_ROB_LING			0X1A
#define EXEC_RUN_EVENT			0X2D
#define EXEC_ADD_EVENT			0X2E
#define EXEC_DEL_EVENT			0X2F
#define EXEC_RAND_SAY			0X30
#define EXEC_RETURN				0X31
#define EXEC_CHANGE_MAGETYPE	0X32
#define EXEC_GUILD_OPEN			0X33 // 길드설립를 연다.
#define EXEC_ADD_SKILL			0X80
#define EXEC_GIVE_ITEM_ALL		0X81
/********************************************************/
// 2001.5.7 HyperText... 
#define EXEC_STORE_OPEN			0X03 // 아이템 판매 NPC
#define EXEC_REPAIR_OPEN		0X34 // 아이템 수리 NPC 		
#define EXEC_SELL_OPEN			0X35 // 아이템 살 NPC 
#define EXEC_ZONE_MOVE			0X36 // 해당 존으로 실행
#define EXEC_MOVE				0X41 // 같은 존에서 이동 실행
#define EXEC_FT_MOVE			0X3A // 요새안으로 이동	
#define EXEC_FT_PEOPLE			0x3B // 민심 수치를 표현
#define EXEC_FT_REPAIR			0x3C // 민심 수치를 표현
#define EXEC_PSI_STORE_OPEN		0X37 // 해당 사이오닉 판매
#define EXEC_ALL_CURE			0X38 // 모든 HP, PP, SP를 MAX로 만듬
//#define EXEC_CARE				0X39 // 모든 상태이상를 치료
#define EXEC_SC_CHENGXU_KA      0X39//�쓱暈行柳坰趾�
#define EXEC_BANK_OPEN			0x40 // 은행 창구를 연다. 
#define EXEC_GUILD_MARK			0x42 // 길드 문양을 등록
#define EXEC_GUILD_WAREHOUSE_OPEN 0x43 // 길드 창고를 연다.
#define EXEC_EBODY_OPEN			0x44 // E_Body 상점을 오픈한다.	
#define EXEC_UPGRADE_OPEN		0x45
#define EXEC_FIELD_STORE_OPEN	0x46 // 필드상인일때는 분기해야 하므로..따로 정의한다.
#define EXEC_GUILD_SAY			0x47 // 길드에 속한 상인이 상대편 신분에 따라 분기한다...
#define EXEC_GUILD_TAX			0x48 // 길마가 해당 상점에 세금을 조정한다.
#define EXEC_GUILD_SCHEME		0x49 // 길마가 해당 상점에 대한 길드전을 설정한다.
#define EXEC_GUILD_APPLY		0x4A // 다른 길마가 길드전을 신청한다.
#define EXEC_XP_UP				0x4B // XP를 올려줌
#define EXEC_CHECK_GUILD_USER	0x4C // 접속중인 길드유저를 보낸다.	
#define EXEC_CHECK_GUILD_RANK	0x4D // 길드 하우스분양를 위해 순위를 알린다.
#define EXEC_GUARD_BOW			0x4E // 경비병이 유저에게 인사하면서 이벤트 대사를 한다.
#define EXEC_GIVE_EVENT_ITEM	0x4F // 이벤트 상품권과 아이템을 교환한다. 
#define EXEC_ADDRESS_WINDOW		0x50 // 상품권 주소 입력창 띄우기.
#define EXEC_EVENT_ROB_ITEM		0x51 // 상품권 회수 이벤트
#define EXEC_DRESSING			0x52 // 선광 창 띄우기
#define EXEC_ACCOUNT_BANK_OPEN	0x53 // 계정 은행 열기
#define	EXEC_GIVE_DN			0x54 // 유저에게 돈 주기
#define EXEC_SEND_MSG			0x55 // 시스템 메세지 보내기
#define EXEC_GIVE_MAGIC_ITEM	0x56 // 유저에게 매직 아이템을 준다. item 테이블에서 bySpecial항목을 매직옵션에 셋팅하고, iq를 매직으로 바꿔서 준다.
#define EXEC_INPUT_WINDOW		0x57 // 예약가입자에게 시리얼 번호 입력창을... 
#define EXEC_INPUTGAME_WINDOW	0x58 // 예약가입 게임방에게 시리얼 번호 입력창을... 	
//#define EXEC_ADD_GAMETIME_ITEM	0x59 // 상품권을 갖고있는 정액권를 회수한다.
#define EXEC_SC_FUSHU_PIN	0x59    //�쓱暈行琉십阡�
#define EXEC_CHANGE_UPGRADE_ACC 0x5A // 기존의 액세서리를 업그레이드 가능한 액세서리로 교환해준다.
#define EXEC_APPLY_GUILD_RUN	0x5B // 길드마라톤 신청
#define EXEC_RR_ENTER			0x5C // 로얄럼블 입장
#define EXEC_MON_SAY			0x5D // 퀘스트를위해 몹 say를... 	
#define EXEC_SUMMON				0x5E // 퀘스트 몹을 소환한다.
#define EXEC_EBODY_DEFINE		0x5F // EBODY 확인 
#define EXEC_HELPERCURE			0x60 // Helper npc
#define EXEC_GIVE_PSI			0x61 // Gives user PSI
#define EXEC_TRANSFORM			0x62 // lvl 20 quest transform window
#define EXEC_100_1		0x63 // 100섬렝야瘻뻣
#define	EXEC_GIVE_HUFA			0x64        //쥴혤빱랬
#define EXEC_100_3		0x65 // 警속섟긴뫘橄昑
#define EXEC_100_4		0x66 // 橄昑�薨�
#define EXEC_100_5		0x67 //렝야꼼죕뺏
#define EXEC_100_6		0x68  //썩뇜꼼죕뺏
#define RUN_SKILL		0x69  //썩뇜꼼죕뺏
#define EXEC_100_2		0x70 //썩뇜橄昑掘齡
#define EXEC_GO_EMO				0x71	//쏵흙띳침밤끝
#define EXEC_NPC_SAYING			0x72    //녜쉽
#define EXEC_OPEN_YUANBAO		0x73 //댔역橄昑禱괜�絹�
#define EXEC_JUANKUAN           0x74 //얕운3굡쒔駱
#define EXEC_BAOLV              0x75 //얕운3굡妗頓
#define EXCE_GOPK				0x76 //쏵흙PK밤끝
//#define EXCE_ON_WEB	            0x77 //踏狗櫓돨貢女
#define EXEC_PKSAY				0X78 //PK댕힘뚤뺐움
#define	EXEC_SAYSHAREN			0x79	//�궐介州犢걀�
#define EXCE_GOSHAREN			0x83	//�궐介奏鑽還킥�
#define EXEC_NPC_DA				0X84	//뗑꺽댕
#define EXEC_NPC_XIAO			0X85	//뗑꺽鬼
#define EXEC_CHANGE_JOB			0X86			//瘻斂
#define EXEC_STUDY_NEW_JOB_PSI		0X87			//欺劤斂撚침랬
#define EXEC_CAN_GIVE_NEWER_ITEM	0X88			//못豚冀못劤癎陋
#define EXEC_GIVE_NEWER_ITEM		0X89			//못劤癎陋
#define EXEC_GIVE_NEWER_ITEM_FINISH	0X8a			//岬劤鞫刻
#define EXEC_ONLINE_EXCHANGE		0X95			//RMB뚝뻣
#define EXCE_ON_SHOP	0x96 //瞳窟�絹�
#define EXEC_CHANGE_ATTRIBUTE_ITEM		0X97 //겜뵈뻣唐橄昑뵈
#define	EXEC_OFF_JJ			0x82        //菌苟샙솖
#define EXEC_SEND_TOU			0x99 // NPC綱뺐


//	Logic Else Define...
#define LOGIC_LEVEL					0X01
#define LOGIC_EXIST_EVENT			0X02
#define LOGIC_ABSENT_EVENT			0X03
#define LOGIC_EXIST_ITEM			0X04
#define LOGIC_ABSENT_ITEM			0X05
#define LOGIC_CLASS					0x06
#define LOGIC_WEIGHT				0x07
#define LOGIC_CHECK_ITEMSLOT		0x08		
#define LOGIC_EXIST_GM				0x09 // 길드마스터일 경우 통과
#define LOGIC_ZONE_WHO				0x10 // 이동할 존에 유저가 사용중에 있는지 체크
#define LOGIC_KILL_GH				0x11 // 길드하우스 권리를 포기
#define LOGIC_MASS_ZONE_MOVE		0x12 // 
#define LOGIC_TERM					0x13 // 일정 날짜 범위안에서 실행한다.	
#define LOGIC_GUILD_HOUSE_NUMBER	0x14 // 길드하우스 소유길드가 있는지 체크한다.
#define LOGIC_CHECK_CV				0x15 // 시민 등급을 체크한다.
#define LOGIC_EXIST_EVENT_ITEM		0X16 // 상품권을 체크한다.
#define LOGIC_MONEY					0X17 // 돈을 체크한다
#define LOGIC_RAND					0X18 // 확률을 돌려서 확률에 걸리면 통과
#define LOGIC_OVER_GUILD_USER_COUNT 0X19
#define LOGIC_RR_TIME				0X1A // 로얄럼블 입장 가능한 시간인지 체크
#define LOGIC_RR_MAX_USER			0X1B // 로얄럼블 최대 입장수가 아직 안됐는지 체크
#define LOGIC_EXIST_SKILL           0X1C //겟섬欺構痂척세콘
#define LOGIC_VIP					0X1D // NPC쇱꿎삔逃
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
#define USER_ABILITY_NUM		5		// 기본 상태 능력치 종류

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
#define MAGIC_NUM				11		// 매직 속성 슬롯

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
const BYTE	REMODEL2_ITEM		= 10;//뢴겟섟陋구
const BYTE	MAGIC2_ITEM			= 11;//융겟섬
const BYTE	RARE2_ITEM			= 12;//쏜겟섬
const BYTE	GUARTIANSHI_ITEM	= 14;
const BYTE  SUPER_EBODY_ITEM	= 15;				//낚섬샙筠	
const BYTE	RARE3_ITEM			= 18;//130

const BYTE	EVENT_SP1_ITEM	= 201;		// 이벤트를 위해 떨어지는 백화점 상품권 아이템	
const BYTE	EVENT_SP2_ITEM	= 202;		// 이벤트를 위해 떨어지는 문화 상품권 아이템	
const BYTE	EVENT_DEF_ITEM	= 243;		// 이벤트를 위해 떨어지는 방어구 교환 아이템	
const BYTE	EVENT_ATT_ITEM	= 242;		// 이벤트를 위해 떨어지는 무기 교환 아이템	
const BYTE	EVENT_POT_ITEM	= 205;		// 이벤트를 위해 떨어지는 물약 교환 아이템	

const BYTE	EVENT_ITEM_MOON		= 220;	// 보름달
const BYTE	EVENT_ITEM_SONGPEON	= 221;	// 송편
const BYTE	EVENT_ITEM_BOX		= 222;	// 선물상자

const BYTE	EVENT_ATT7_ITEM	= 240;		// 설날 이벤트를위해 
const BYTE	EVENT_DEF7_ITEM	= 241;		// 
const BYTE	EVENT_ATT6_ITEM	= 244;		// 
const BYTE	EVENT_DEF6_ITEM	= 245;		// 
const BYTE	EVENT_ATT4_ITEM	= 246;		// 
const BYTE	EVENT_DEF4_ITEM	= 247;		// 
const BYTE	EVENT_ATT3_ITEM	= 248;		// 
const BYTE	EVENT_DEF3_ITEM	= 249;		// 
const BYTE  EVENT_INIT_STAT_ITEM = 250;	// 극약
const BYTE  EVENT_USER_GAME_TIME = 252; // 개인 정액제

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
const BYTE	MATERIAL_ITEM			= 16; //개조 아이템을 위한 
const UINT	MATERIAL_MAGIC_UP_ITEM	= 625; //업그레이드를 위한 매직 아이템 = 자브롤
const UINT	MATERIAL_RARE_UP_ITEM	= 626; //업그레이드를 위한 레어 아이템 = 칼로이만
const UINT	MATERIAL_REMODEL_UP_ITEM	= 861;//개조 업그레이드를 위한 아이템 = 타레롤
const UINT	MATERIAL_EBODY_UP_ITEM	= 1236;//개조 업그레이드를 위한 아이템 = 타레롤

//
//	Item Upgrade Cost
//
#define ATTACK_UPGRADE_COST		200000	//	Weapon Upgrade Cost
#define DEFENSE_UPGRADE_COST	100000	//	Defense Upgrade Cost
#define ACCESSORI_UPGRADE_COST	10000	//	Accessori Upgrade Cost
#define ITEM_REMODELING_COST	50000	//	Item Remodeling Cost
#define ITEM_REMAGIC_COST		200000	//	침랬加陋롤痰
#define EBODY_UPGRADE_COST		200000	//	EBody Upgrade Cost
#define EBODY_IDENTIFY_COST		100000	//	EBody Indentify Cost
#define ATTACKCHAO_UPGRADE_COST		1000000	//	낚쥣낚쑨�薨떱儺�
#define DEFENSEWANG_UPGRADE_COST	1000000	//	쑨쥣�薨떱儺�


//
//	EBody 관련 소모 XP
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
const short GUARDANT_RANT	= 11;  //加鳩
const short	ANGEL_RANK		= 12;	//莖賈

#define CITY_RANK_INTERVAL	5;

#define USER_PK_TICKS		25000	//凜츰珂쇌

#define GUILD_HOUSE_MAX_NUM	7		// 첫번째 0은 제외, 6개 길드 하우스

#define UPDATE_GUILD_INVEN_TIME		12
#define UPDATE_GUILD_CITY_TIME		1

#define SYSTEM_GUILD_BAND	900000

//
// User Event Max Num
// 痰빵慤숭離댕令
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

#define ITEMLOG_BLESS_USE				33		// 축 아이템 비스무리한 아이템을 사용할대
#define ITEMLOG_SPECIAL_USE_POTION		34		// 특별한 소모성 물약을 사용할때

#define ITEMLOG_PSI_STONE				35		// 사이오닉 습득구슬 사용시 로그번호

#define ITEMLOG_ACC_USE					36		// 소모성 악세사리가 사라질때
#define ITEMLOG_REMAGIC_DELETE			37		// 리매직 시스템으로 아이템 삭제

#define ITEMLOG_DEAD_DELETE				38		// PK 로 인해 아이템이 사라질때

#define ITEMLOG_EBODY_ADDER_DELETE		39		// EBody 업그레이드로 에이더를 소비한다.
#define ITEMLOG_EBODY_BASE_DELETE		40		// EBody 업그레이드 실패로 베이스를 삭제한다.
#define ITEMLOG_EBODY_UPGRADE_SUCCESS	41		// EBody 업그레이드 성공

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
#define MAX_ACCESSORI		4			// 최대 악세사리 갯수
#define	RANDOM_PROTECT		30			// 서포트 귀걸이의 크리티컬 무시 확율
#define	GUARDIAN_SLOT		1


//yskang 0.4 운영자 로그기록 옵션
//0:접속아이피 1:대화 2:아이템 제공정보 3:PK정보
#define CONNECT_IP		0
#define CHAT_LOG		1
#define ITEM_LOG		2
#define	PKINFO_LOG		3
#define CALL_USER_LOG	4

#endif