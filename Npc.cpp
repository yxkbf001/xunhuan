// Npc.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "USER.h"
#include "Npc.h"

#include "Extern.h"
#include "MAP.h"
#include "BufferEx.h"

#include "Mcommon.h"
#include "scdefine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CRITICAL_SECTION m_CS_EventItemLogFileWrite;

//////////////////////////////////////////////////////////////////////
// Fortress Paket Variable
extern CRITICAL_SECTION m_CS_FortressData;
extern CPtrList				RecvFortressData;
extern long nFortressDataCount;
extern struct drop_info g_DropItem[256][4];

//int surround_x[8] = {-2, -1, 0, 1, 2, 1, 0, -1};
//int surround_y[8] = {0, -1, -2, -1, 0, 1, 2, 1};

int surround_x[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int surround_y[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int g_iMoonEvent = 1;

//#define STEP_DELAY			//440


#define UPDATE_EVENT_INVEN_TIME		12

//////////////////////////////////////////////////////////////////////
//	Inline Function
//
inline int CNpc::GetUid(int x, int y )
{
	MAP* pMap = g_zone[m_ZoneIndex];
	return pMap->m_pMap[x][y].m_lUser;
}

inline BOOL CNpc::SetUid(int x, int y, int id)
{
	MAP* pMap = g_zone[m_ZoneIndex];

	if(pMap->m_pMap[x][y].m_bMove != 0) return FALSE;
	if(pMap->m_pMap[x][y].m_lUser != 0 && pMap->m_pMap[x][y].m_lUser != id ) return FALSE;

	pMap->m_pMap[x][y].m_lUser = id;

	return TRUE;
}

BOOL CNpc::SetUidNPC(int x, int y, int id)
{
	MAP* pMap = g_zone[m_ZoneIndex];

	if(pMap->m_pMap[x][y].m_bMove != 0) return FALSE;
	if(pMap->m_pMap[x][y].m_lUser != 0 && pMap->m_pMap[x][y].m_lUser != id ) return FALSE;

	pMap->m_pMap[x][y].m_lUser = id;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpc::CNpc()
{
	m_NpcVirtualState = NPC_STANDING;
	m_NpcState = NPC_LIVE;

	InitTarget();

	m_ItemUserLevel = 0;
//	m_Delay = 0;			// 다음 상태로 전이되기 까지의 시간( mili/sec )
//	m_dwLastThreadTime = 0;
	m_Delay = 0;
	m_dwLastThreadTime = GetTickCount();

	m_sClientSpeed = 0;		// 클라이언트 애니를 위한 이동 비율
	m_dwStepDelay = 0;		// 다음 팻킷까지의 시간 딜레이
	m_tNpcAttType = 0;		// 공격 성향
	m_tNpcLongType = 0;		// 원거리(1), 근거리(0)
	m_tNpcGroupType = 0;	// 도움을 주는냐(1), 안주는냐?(0)
//	m_tNpcTraceType = 0;	// 끝까지 따라간다(1), 시야에서 없어지면 그만(0)

	m_pPath = NULL;
	m_pOrgMap = NULL;

//	m_pMap = NULL;
	m_lMapUsed = 0;			// 맵 메모리보호

	m_bFirstLive = TRUE;

	m_tWeaponClass = BRAWL;
	m_dwDelayCriticalDamage = 0;
	m_dwLastAbnormalTime	= GetTickCount();

	::ZeroMemory(m_pMap, sizeof(m_pMap));// 일차원 맵으로 초기화한다.

	m_tAbnormalKind = 0;
	m_dwAbnormalTime = 0;

	m_presx = -1;
	m_presy = -1;

	m_lEventNpc = 0;

	m_pGuardStore = NULL;				// 길드전을위해 해당 상점을 가지고 온다.
	m_pGuardFortress = NULL;

	m_tRepairDamaged = 0;
	m_tNCircle = NPC_NCIRCLE_DEF_STATE;
	m_lFortressState = 0;
	m_lDamage = 0;

	m_bSummon = FALSE;
	m_sSummonOrgZ = m_sOrgZ;
	m_sSummonOrgX = m_sOrgX;
	m_sSummonOrgY = m_sOrgY;
	m_SummonZoneIndex = m_ZoneIndex;

	m_bSummonDead = FALSE;
	m_lNowSummoning = 0;

	m_lKillUid = -1;
	m_sQuestSay = 0;

	InitSkill();
	InitUserList();
}

CNpc::~CNpc()
{
	ClearPathFindData();

	InitUserList();
}

//////////////////////////////////////////////////////////////////////
//	NPC 스킬정보를 초기화 한다.
//
void CNpc::InitSkill()
{
	for(int i = 0; i < SKILL_NUM; i++)
	{
		m_NpcSkill[i].sSid = 0;
		m_NpcSkill[i].tLevel = 0;
		m_NpcSkill[i].tOnOff = 0;
	}
}

///////////////////////////////////////////////////////////////////////
//	길찾기 데이터를 지운다.
//
void CNpc::ClearPathFindData()
{
	::ZeroMemory(m_pMap, sizeof(m_pMap));	// 일차원 맵을 위해
/*	int i;

	if(m_pMap)
	{
		int **tmp = m_pMap;
		
		m_pMap = NULL;

		for(i = 0; i < m_vMapSize.cx; i++)
		{
			delete[] tmp[i];
		}
		delete[] tmp;
	}
*/
}

///////////////////////////////////////////////////////////////////////
// NPC 가 처음 생기거나 죽었다가 살아날 때의 처리
//
BOOL CNpc::SetLive(COM* pCom)
{
	NpcTrace(_T("SetLive()"));

	if(m_tRepairDamaged > 0) return FALSE;		 // 공성전중 손상 받았다면 수리될때까지 그대로 유지되어야함...
	if(m_pGuardFortress && m_tGuildWar == GUILD_WARRING)
	{
		if(!m_bFirstLive) return FALSE;
	}
	else m_tGuildWar = GUILD_WAR_AFFTER;		// 모든 몹을 길드전에 대해서 초기화한다...

	if(m_bSummonDead)							// 소환됬었던 몹에 대해서
	{
		m_ZoneIndex = m_TableZoneIndex;
		m_sCurZ		= m_sOrgZ	= m_sTableOrgZ;
		m_sOrgX		= m_sTableOrgX;
		m_sOrgY		= m_sTableOrgY;
		
		m_pOrgMap = g_zone[m_ZoneIndex]->m_pMap;	// MapInfo 정보 셋팅
		
		m_bSummonDead = FALSE;
	}

	// NPC의 HP, PP 초기화 ----------------------//	
	int i = 0, j = 0;
	m_sHP = m_sMaxHP;
	m_sPP = m_sMaxPP;
	NpcDrop=4;
	int iTryLiveCount = 0;

	InitTarget();

	InitUserList();					// 타겟을위한 리스트를 초기화.	

	// NPC 초기위치 결정 ------------------------//
	MAP* pMap = g_zone[m_ZoneIndex];
	
	m_nInitMinX = m_sOrgX - m_sMinX;		if(m_nInitMinX < 1) m_nInitMinX = 1; 
	m_nInitMinY = m_sOrgY - m_sMinY;		if(m_nInitMinY < 1) m_nInitMinY = 1; 
	m_nInitMaxX = m_sOrgX + m_sMaxX;		if(m_nInitMaxX >= pMap->m_sizeMap.cx) m_nInitMaxX = pMap->m_sizeMap.cx - 1;
	m_nInitMaxY = m_sOrgY + m_sMaxY;		if(m_nInitMaxY >= pMap->m_sizeMap.cy) m_nInitMaxY = pMap->m_sizeMap.cy - 1;

	CPoint pt;
	CPoint ptTemp;

	int modify_index = 0;
	char modify_send[2048];	

//	if(m_lEventNpc == 0 && m_sEvent == 1000) return TRUE;//@@@@@@@@@@@@@@@@@@@@@@ Test Code(임시로 몹을 소환하기위해)

	if(m_lEventNpc == 1 && !m_bFirstLive) 
	{
		// 유저에게 NPC 정보전송... 
		// 이유 : 죽은 모습을 보여줘야하기때문에 다음 리젠될 차례가 올때 INFO_DELETE를 보낸다. 
		::ZeroMemory(modify_send, sizeof(modify_send));

		for(int i = 0; i < NPC_NUM; i++)
		{
			if(g_arEventNpcThread[0]->m_ThreadInfo.pNpc[i] != NULL)
			{
				if(g_arEventNpcThread[0]->m_ThreadInfo.pNpc[i]->m_sNid == m_sNid)
				{
					FillNpcInfo(modify_send, modify_index, INFO_DELETE);
					SendInsight(pCom, modify_send, modify_index);

					g_arEventNpcThread[0]->m_ThreadInfo.pNpc[i] = NULL;
					InterlockedExchange(&m_lEventNpc, (LONG)0);
					InterlockedExchange(&g_arEventNpcThread[0]->m_ThreadInfo.m_lNpcUsed[i], (LONG)0);								
					return TRUE;
				}
			}
		}
		return TRUE;
	}

	if(m_tNpcType != NPCTYPE_MONSTER && m_bFirstLive)//NPCTYPE_DOOR || m_tNpcType == NPCTYPE_GUARD)
	{
		m_nInitX = m_sCurX = m_sOrgX;
		m_nInitY = m_sCurY = m_sOrgY;

		pMap->m_pMap[m_sCurX][m_sCurY].m_lUser = m_sNid + NPC_BAND;

//		TRACE("NPC DOOR %s(nid = %d) - %d %d\n", m_strName, m_sNid, m_sCurX, m_sCurY);
		CPoint temp = ConvertToClient(m_sCurX, m_sCurY);
		TRACE("NPC DOOR %s(nid = %d) - %d %d\n", m_strName, m_sNid, temp.x, temp.y);
	}
	else
	{
		while(1)
		{
			i++;
																						
			if(m_lEventNpc == 1)			// 소환몹일경우 되도록이면 처음 지정한 좌표로
			{
				if(pMap->m_pMap[m_sOrgX][m_sOrgY].m_bMove == 0)	
				{ 
					pt.x = m_sOrgX; 
					pt.y = m_sOrgY; 
					
					m_nInitX = m_sCurX = pt.x;
					m_nInitY = m_sCurY = pt.y;
					
					//ptTemp = ConvertToClient(m_sCurX, m_sCurY);
					break;
				}
				else
				{
					pt = FindNearRandomPoint(m_sOrgX, m_sOrgY);
					if(pt.x <= 0 || pt.y <= 0) 
					{
						pt.x = myrand(m_nInitMinX, m_nInitMaxX);
						pt.y = myrand(m_nInitMinY, m_nInitMaxY);
					}
				}
			}
			else
			{
				pt.x = myrand(m_nInitMinX, m_nInitMaxX);
				pt.y = myrand(m_nInitMinY, m_nInitMaxY);

				// Test Code By Youn Gyu 02-08-13 (현재는 주변 25셀로만 제한)
				if( m_sCurZ != 1 && m_sCurZ != 1005 ) // 일단 던젼만 찾는다.
				{
					if(m_tNpcType == NPCTYPE_MONSTER)
					{
						if( !CheckUserForNpc_Live(pt.x, pt.y) )
						{
							iTryLiveCount += 1;
							if(iTryLiveCount >= 20) return FALSE;
							else continue;
						}
					}
				}
				//TRACE("MONSTER %s(nid = %d) - %d %d\n", m_strName, m_sNid, m_sCurX, m_sCurY);
			}
			
			if(pt.x < 0 || pt.x >= pMap->m_sizeMap.cx) continue;
			if(pt.y < 0 || pt.y >= pMap->m_sizeMap.cy) continue;

			if(pMap->m_pMap[pt.x][pt.y].m_bMove != 0 || pMap->m_pMap[pt.x][pt.y].m_lUser != 0)
			{
				if(i >= 100) 
				{
					m_nInitX = m_sCurX = m_sOrgX;
					m_nInitY = m_sCurY = m_sOrgY;
//					TRACE("sid = %d, loop = %d My standing point is invalid x = %d, y = %d\n", m_sSid, i, pt.x, pt.y);
					InterlockedIncrement(&g_CurrentNPCError);
					return FALSE;
//					break;
					
/*					DeleteNPC();// 삭제가 아님...
					TRACE("sid = %d, loop = %d My standing point is invalid x = %d, y = %d\n", m_sSid, i, pt.x, pt.y);
					return FALSE;
*/					
				}
				continue;
			}

			m_nInitX = m_sCurX = pt.x;
			m_nInitY = m_sCurY = pt.y;

//			ptTemp = ConvertToClient(m_sCurX, m_sCurY);
			break;
		}
	}

	SetUid(m_sCurX, m_sCurY, m_sNid + NPC_BAND);

	if(m_sDimension > 0) SetMapTypeBeforeGuildWar(pCom);		// 맵을 셋팅한다.

	// 상태이상 정보 초기화
	m_dwLastAbnormalTime	= GetTickCount();
	m_tAbnormalKind = 0;
	m_dwAbnormalTime = 0;

	// 공성전에서 NPC HP가 수리가 안되어 있으면
//	if(m_pGuardFortress) SetFortressState();
	
	if(m_bFirstLive)	// NPC 가 처음 살아나는 경우
	{
		NpcTypeParser();
		m_tWeaponClass = GetWeaponClass();
		m_bFirstLive = FALSE;

		InterlockedIncrement(&g_CurrentNPC);
	}

	// 몹을 마지막으로 죽인 유저의 uid 초기화
	m_lKillUid = -1;

	// Test Code
//	CString strTemp = m_strName;
//	if(strTemp == "퀸" || strTemp == "그레이트빅풋")m_sHP = 1;

	// 유저에게 NPC 정보전송...
	modify_index = 0;
	::ZeroMemory(modify_send, sizeof(modify_send));
	FillNpcInfo(modify_send, modify_index, INFO_MODIFY);

	SendInsight(pCom, modify_send, modify_index);

	m_presx = -1;
	m_presy = -1;

	SightRecalc(pCom);

	return TRUE;
}


///////////////////////////////////////////////////////////////////
//	NPC 기본적인 성향을 분류, 셋팅한다.
//
void CNpc::NpcTypeParser()
{
	MYSHORT sAI;

	BYTE upTemp = 0;			// 상위 8비트
	BYTE dwTemp = 0;			// 하위 8비트

	sAI.i = (short)m_sAI;

	upTemp = sAI.b[0];
	dwTemp = sAI.b[1];
//	temp = m_sAI;//m_byAI

	m_tNpcAttType = upTemp >> 7;

	upTemp = upTemp << 1;
	m_tNpcLongType = upTemp >> 7;

	upTemp = upTemp << 1;
	m_tNpcGroupType = upTemp >> 7;

	m_iNormalATRatio = m_byIronSkin;
	m_iSpecialATRatio = m_byReAttack;
	m_iMagicATRatio = m_bySubAttack;

	m_tSPATRange = m_byWildShot;

/*
	switch( (int)m_byVitalC )
	{
	case	0:	// 일반만
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = FALSE;
		break;

	case	1:	// 매직만
		m_bCanNormalAT = FALSE;
		m_bCanMagicAT = TRUE;
		m_bCanSPAT = FALSE;
		break;

	case	2:	// 일반, 특수
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	case	3:	// 매직, 특수
		m_bCanNormalAT = FALSE;
		m_bCanMagicAT = TRUE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	case	4:	// 일반, 매직
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = TRUE;
		break;

	case	5:	// 특수만
		m_bCanNormalAT = FALSE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	case	6:	// 일반, 매직, 특수
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = TRUE;
		m_bCanSPAT = TRUE;

		m_tSPATRange = m_byWildShot;
		m_tSPATAI = m_byExcitedRate;
		break;

	default:
		m_bCanNormalAT = TRUE;
		m_bCanMagicAT = FALSE;
		m_bCanSPAT = FALSE;
		break;

	}
*/
}

///////////////////////////////////////////////////////////////////
//	NPC 주변의 적을 찾는다.
//
BOOL CNpc::FindEnemy(COM *pCom)
{
	BOOL bSearch = FALSE;

	if(m_tNpcType == NPCTYPE_NPC || m_tNpcType == NPCTYPE_DOOR || m_tNpcType == NPCTYPE_GUILD_DOOR) return FALSE;
	if(m_tNpcType == NPCTYPE_GUILD_NPC || m_tNpcType == NPCTYPE_GUILD_MARK) return FALSE;

	if(m_byAX == 0 && m_byAZ == 0 ) return FALSE;		// 내가 공격력이 없으면 공격하지 않는다
	if(m_bySearchRange == 0) return FALSE;
	if(m_tNpcType == NPCTYPE_GUARD) bSearch = TRUE;
	if(m_tNpcType == NPCTYPE_GUILD_GUARD)
	{
		if(m_pGuardFortress && m_tRepairDamaged == NPC_DEAD_REPAIR_STATE) return FALSE;
		// 공성전에서 해당 광선포 HP가 0이면 동작 불능임 
		 bSearch = TRUE;
	}

	if(!bSearch && !m_tNpcAttType && m_Target.id < 0 )
	{
		return FALSE;
	}
	else
	{
//		if( (GetTickCount() - m_dLastFind) < (DWORD)1000 )
		if( (GetTickCount() - m_dLastFind) < (DWORD)2000 )
		{
			return FALSE;
		}
	}

	m_dLastFind = GetTickCount();

//	if(m_Target.id != -1) return TRUE;

	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - m_bySearchRange;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - m_bySearchRange;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + m_bySearchRange;
	max_y = m_sCurY + m_bySearchRange;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 2;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 2;

	int ix, iy;
	int target_uid;
	int uid;
	int rank = 0;

	USER *pUser = NULL;
	CNpc *pNpc = NULL;

	int tempLevel = 0, oldLevel = 1000;

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= USER_BAND && target_uid < NPC_BAND )
			{
				uid = target_uid - USER_BAND;

				pUser = GetUser(pCom, uid);
				if( pUser != NULL && pUser->m_bLive == USER_LIVE)
				{
					if( ix != pUser->m_curx || iy != pUser->m_cury )
					{
						continue;
					}

					if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)
					{
						//rank = DEATH_RANK - CITY_RANK_INTERVAL;
						if(pUser->m_sKillCount > 100 || pUser->m_bPkStatus)
						{
							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;							
							return TRUE;
						}
					}
																	// 길드전할때는 상점소유 길드원은 무시
					if(m_tNpcType == NPCTYPE_GUILD_GUARD)	
					{
						if(m_tGuildWar == GUILD_WARRING)
						{
							//if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) continue;
							if(m_pGuardStore) 
							{
								if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) continue;
							}
							else if(m_pGuardFortress)
							{
								if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) continue;
							}

							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;
							return TRUE;
						}
					}

					if(pUser->m_tIsOP == 1) continue;				// 운영자이면 무시...^^
					if(pUser->m_bPShopOpen == TRUE) continue;		// User has personal shop
//					if(pUser->m_dwHideTime > 0) continue;			// 은닉 상태면 무시된다.
					if(pUser->m_bSessionOnline == true)	continue;
					//후공몹...
					if(!m_tNpcAttType)		// 날 공격한 놈을 찾는다.
					{
						if(IsDamagedUserList(pUser) || (m_tNpcGroupType && m_Target.id == target_uid))
						{
							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;
							return TRUE;
						}
					}
					else	// 선공몹...
					{						
						if(IsSurround(ix, iy) == TRUE) continue;	//둘러 쌓여 있으면 무시한다.(원거리, 근거리 무시)

						USER *pTUser;

						pTUser = pCom->GetUserUid(uid);
						if ( pTUser == NULL ) continue;

						tempLevel = pTUser->m_sLevel;

						if(tempLevel <= oldLevel) 
						{
							oldLevel = tempLevel;									
							m_Target.id	= target_uid;
							m_Target.failCount = 0;
							m_Target.x	= ix;
							m_Target.y	= iy;
							return TRUE;
						}
					}
				}
			}
		}
	}

	InitUserList();		// 아무도 없으므로 리스트에 관리하는 유저를 초기화한다.
	InitTarget();

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	주변에 나를 공격한 유저가 있는지 알아본다
//
BOOL CNpc::IsDamagedUserList(USER *pUser)
{
//	int count = m_arDamagedUserList.GetSize();
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return FALSE;

	int sLen = strlen(pUser->m_strUserID);

	if(sLen < 0 || sLen > CHAR_NAME_LENGTH) return FALSE;

	for(int i = 0; i < NPC_HAVE_USER_LIST; i++)
	{
		if(strcmp(m_DamagedUserList[i].strUserID, pUser->m_strUserID) == 0) return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	Target 과 NPC 간 Path Finding을 수행한다.
//
BOOL CNpc::GetTargetPath(COM* pCom)
{
	USER* pUser = GetUser(pCom, m_Target.id - USER_BAND);
	if(pUser == NULL)
	{
		InitTarget();
		return FALSE;
	}
	if(pUser->m_sHP <= 0 || pUser->m_state != STATE_GAMESTARTED || pUser->m_bLive == FALSE)
	{
		InitTarget();
		return FALSE;
	}
/*	if(strcmp(m_Target.szName, pUser->m_strUserID) != 0)
	{
		InitTarget();
		return FALSE;
	}
*/
	int iTempRange = m_bySearchRange;				// 일시적으로 보정한다.
//	if(m_arDamagedUserList.GetSize()) iTempRange *= 2;	// 공격받은 상태면 찾을 범위 증가.
	if(IsDamagedUserList(pUser)) iTempRange *= 2;	// 공격받은 상태면 찾을 범위 증가.
	else iTempRange += 4;
	
	int min_x = m_sCurX - iTempRange;	if(min_x < 0) min_x = 0;
	int min_y = m_sCurY - iTempRange;	if(min_y < 0) min_y = 0;
	int max_x = m_sCurX + iTempRange;	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
	int max_y = m_sCurY + iTempRange;	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

	// 목표점이 Search Range를 벗어나지 않는지 검사
	CRect r = CRect(min_x, min_y, max_x+1, max_y+1);
	if(r.PtInRect(CPoint(pUser->m_curx, pUser->m_cury)) == FALSE) return FALSE;

	// Run Path Find ---------------------------------------------//
	CPoint start, end;
	start.x = m_sCurX - min_x;
	start.y = m_sCurY - min_y;
	end.x = pUser->m_curx - min_x;
	end.y = pUser->m_cury - min_y;

	m_ptDest.x = m_Target.x;
	m_ptDest.y = m_Target.y;

	m_min_x = min_x;
	m_min_y = min_y;
	m_max_x = max_x;
	m_max_y = max_y;

	return PathFind(start, end);
}

////////////////////////////////////////////////////////////////////////////////
//	NPC 가 Path Find 하려는 마지막 점은 현재 알고리즘상 항상 이동불가 좌표이므로
//	마지막 좌표를 수정
//	
//	## 현재(2000-12-12) 패스파인드 알고리즘이 수정되어 이 함수는 필요없음 ##
BOOL CNpc::GetLastPoint(int sx, int sy, int& ex, int& ey)
{
	int i;
	int x = 0, y = 0;
	int nx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int ny[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	
	BOOL bSearchDest = FALSE;
	MAP* pMap = g_zone[m_ZoneIndex];
	for(i = 0; i < sizeof(nx)/sizeof(nx[0]); i++)
	{
		x = ex + nx[i]; 
		if(x >= pMap->m_sizeMap.cx) x--;
		if(x < 0) x = 0;

		y = ey + ny[i];
		if(y >= pMap->m_sizeMap.cy) y--;
		if(y < 0) y = 0;
		
		if(m_pOrgMap[x][y].m_bMove == 0 && m_pOrgMap[x][y].m_lUser == 0) 
		{
			ex = x;
			ey = y;
			bSearchDest = TRUE;
			break;
		}
	}

	if (bSearchDest) return TRUE;

	int nSearchSize = max(abs(sx - ex), abs(sy - ey));
//	ASSERT(nSearchSize);
	
	for (i = nSearchSize; i > 0; i--) 
	{
		x = sx + (ex - sx) * i / nSearchSize;
		y = sy + (ey - sy) * i / nSearchSize;
		
		if ((x + y) % 2 != 0) y++;	//보정

		if(m_pOrgMap[x][y].m_bMove == 0 && m_pOrgMap[x][y].m_lUser == 0) 
		{
			ex = x;
			ey = y;
			bSearchDest = TRUE;
			break;
		}
	}

	if (!bSearchDest) return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC와 Target 과의 거리가 지정 범위보다 작은지 판단
//
BOOL CNpc::IsCloseTarget(COM* pCom, int nRange)
{
	// 혹시나 경비병이 NPC를 공격하게 되면 타겟이 유저가 아니라 NPC일 수 도 있다.
	USER* pUser = GetUser(pCom, m_Target.id - USER_BAND);
	if(pUser == NULL) 
	{
		InitTarget();
		return FALSE;
	}
	if(pUser->m_sHP <= 0 || pUser->m_state != STATE_GAMESTARTED || pUser->m_bLive == FALSE)
	{
		InitTarget();
		return FALSE;
	}

	CPoint ptUser	= ConvertToClient(pUser->m_curx, pUser->m_cury);
	CPoint ptNpc	= ConvertToClient(m_sCurX, m_sCurY);

	//^^ 소마에서는 거리검색이 아니라 맵 검색으로 거리계산 및 잘못된 유저 좌표를 체크하고 있음
	int dx = abs(ptUser.x - ptNpc.x);
	int dy = abs(ptUser.y - ptNpc.y);
	int max_dist = __max(dx, dy);
	
	if(max_dist > nRange * 2) return FALSE; // 클라인트 좌표는 2차이가 한셀이므로 *2를 한다.

	m_Target.x = pUser->m_curx;
	m_Target.y = pUser->m_cury;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC와 Target 과의 거리가 지정 범위보다 작은지 판단
//
BOOL CNpc::IsCloseTarget(USER *pUser, int nRange)
{
	if(pUser == NULL)
	{
		return FALSE;
	}
	if(pUser->m_sHP <= 0 || pUser->m_state != STATE_GAMESTARTED || pUser->m_bLive == FALSE)
	{
		return FALSE;
	}

	CPoint ptUser	= ConvertToClient(pUser->m_curx, pUser->m_cury);
	CPoint ptNpc	= ConvertToClient(m_sCurX, m_sCurY);

	//^^ 소마에서는 거리검색이 아니라 맵 검색으로 거리계산 및 잘못된 유저 좌표를 체크하고 있음
	int dx = abs(pUser->m_curx - m_sCurX);
	int dy = abs(pUser->m_cury - m_sCurY);
	int max_dist = __max(dx, dy);
	
	if(max_dist > nRange * 2) return FALSE;

	InitTarget();
	m_Target.id = pUser->m_uid + USER_BAND;
	m_Target.x = pUser->m_curx;
	m_Target.y = pUser->m_cury;

/*	if(pUser->m_strUserID != NULL)
	{
		m_Target.nLen = strlen(pUser->m_strUserID);

		if(m_Target.nLen <= CHAR_NAME_LENGTH) strncpy(m_Target.szName, pUser->m_strUserID, m_Target.nLen);
		else								  ::ZeroMemory(m_Target.szName, sizeof(m_Target.szName));
	}
*/	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//	Path Find 로 찾은길을 다 이동 했는지 판단
//
BOOL CNpc::IsMovingEnd()
{
	if( m_bRandMove )		// 8방향 선택 움직임일때
	{
		if( m_arRandMove.GetSize() ) return FALSE;

		return TRUE;
	}

	if(!m_pPath) return TRUE;

	int min_x = m_min_x;
	int min_y = m_min_y;

	if((m_sCurX - min_x) == m_vEndPoint.x && (m_sCurY - min_y) == m_vEndPoint.y) return TRUE;

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////
//	해당 uid의 USER* 를 얻는다.
//
USER* CNpc::GetUser(COM* pCom, int uid)
{
	if(!pCom) return NULL;
	//if(uid < 0 || uid >= MAX_USER) return NULL;

	return pCom->GetUserUid(uid);
}

/////////////////////////////////////////////////////////////////////////////////
//	Target 의 위치가 다시 길찾기를 할 정도로 변했는지 판단
//	혼란등의 상태이상 사이오닉이나 스킬등이 지원되면 이 함수를 이용하면 될 듯
//
BOOL CNpc::IsChangePath(COM* pCom, int nStep)
{
	if(!m_pPath) return TRUE;

	CPoint pt;
	GetTargetPos(pCom, pt);
	NODE* pTemp = m_pPath;

	CPoint ptPath[2];
	while(1)
	{
		if(pTemp == NULL) break;

		if(pTemp->Parent) 
		{
			ptPath[0].x = m_min_x + pTemp->x;
			ptPath[0].y = m_min_y + pTemp->y;

			pTemp = pTemp->Parent;			
		}
		else
		{			
			ptPath[1].x = m_min_x + pTemp->x;
			ptPath[1].y = m_min_y + pTemp->y;

			break;
		}
	}

	for(int i = 0; i < 2; i++)
	{
		if(abs(ptPath[i].x - pt.x) <= m_byRange && abs(ptPath[i].y - pt.y) <= m_byRange) return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
//	Target 의 현재 위치를 얻는다.
//
BOOL CNpc::GetTargetPos(COM *pCom, CPoint &pt)
{
	USER* pUser = GetUser(pCom, m_Target.id - USER_BAND);

	if(!pUser) return FALSE;

	pt.x = pUser->m_curx;
	pt.y = pUser->m_cury;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
//	Target 과 NPC 간에 길찾기를 다시한다.
//
BOOL CNpc::ResetPath(COM* pCom)
{
	CPoint pt;
	GetTargetPos(pCom, pt);

	m_Target.x = pt.x;
	m_Target.y = pt.y;

	return GetTargetPath(pCom);
}

/////////////////////////////////////////////////////////////////////////////////
//	Step 수 만큼 타켓을 향해 이동한다.
//
BOOL CNpc::StepMove(COM* pCom, int nStep)
{
//	if(m_tNpcType == NPCTYPE_GUILD_DOOR)	return FALSE;	// 이동안하게...

	if(!m_pPath && !m_bRandMove) return FALSE;
	if(m_NpcState != NPC_MOVING && m_NpcState != NPC_TRACING && m_NpcState != NPC_BACK) return FALSE;
	
	int min_x;
	int min_y;
	int will_x;
	int will_y;

	CPoint ptPre;

	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return FALSE;
	if( !pMap->m_pMap ) return FALSE;

	for(int i = 0; i < nStep; i++)
	{
		if( m_bRandMove )
		{
			if( !m_arRandMove.GetSize() ) return FALSE;

			min_x = m_min_x;
			min_y = m_min_y;

			will_x = min_x + m_arRandMove[0].x;
			will_y = min_y + m_arRandMove[0].y;

			m_arRandMove.RemoveAt( 0 );

			if( will_x >= pMap->m_sizeMap.cx || will_x < 0 || will_y >= pMap->m_sizeMap.cy || will_y < 0 )
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;

				return FALSE;
			}

			if( pMap->m_pMap[will_x][will_y].m_bMove != 0 || pMap->m_pMap[will_x][will_y].m_lUser != 0 )
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;

				return FALSE;
			}

			ptPre.x = m_sCurX;
			ptPre.y = m_sCurY;

			m_sCurX = will_x;
			m_sCurY = will_y;

			// 시야 재계산...
			SightRecalc( pCom );

			break;
		}
		else if(m_pPath->Parent)
		{
			m_pPath = m_pPath->Parent;

			min_x = m_min_x;
			min_y = m_min_y;

			will_x = min_x + m_pPath->x;
			will_y = min_y + m_pPath->y;

			if(will_x >= pMap->m_sizeMap.cx || will_x < 0 || will_y >= pMap->m_sizeMap.cy || will_y < 0) 
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;
				return FALSE;
			}
			
			if(pMap->m_pMap[will_x][will_y].m_bMove != 0 || pMap->m_pMap[will_x][will_y].m_lUser != 0)
			{
				m_vEndPoint.x = m_sCurX - min_x;
				m_vEndPoint.y = m_sCurY - min_y;
				return FALSE;
			}

			ptPre.x = m_sCurX;
			ptPre.y = m_sCurY;

			m_sCurX = will_x;
			m_sCurY = will_y;

			//시야 재계산...
			SightRecalc(pCom);

			break;
		}
		
		return FALSE;
	}

	if(SetUid(m_sCurX, m_sCurY, m_sNid + NPC_BAND))
	{
		pMap->m_pMap[ptPre.x][ptPre.y].m_lUser = 0;
		return TRUE;
	}
	else return FALSE;

//	return SetUid(m_sCurX, m_sCurY, m_sNid + NPC_BAND);
}

//////////////////////////////////////////////////////////////////////////////
//	Target 에 대한 공격 처리
//
int CNpc::Attack(COM *pCom)
{
	if(!pCom) return 10000;

	int ret = 0;
	int nStandingTime = m_sStandTime;

	// 총기계열 일때는 타겟과의 거리계산을 달리해야 한다.
//	if(m_tNpcType != NPCTYPE_GUARD && m_tNpcType != NPCTYPE_GUILD_GUARD)// 경비병이 아니면 시야 계산
//	{
	if(IsCloseTarget(pCom, m_byRange) == FALSE)// Check Code (단지 방어적인 측면에서 넣은 코드)
	{
		if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)
		{
			m_NpcState = NPC_STANDING;
			return 0;
		}
		m_NpcState = NPC_TRACING;			// 공격하고 도망가는 유저를 따라 잡기위해(반응을 좀더 빠르게) 
		return 0;							// IsCloseTarget()에 유저 x, y값을 갱신하고 Delay = 0으로 줌
	}
//	}

	short	sTempHP		= 0;
	CNpc*	pNpc		= NULL;	
	USER*	pUser		= NULL;

	CByteArray	arSkillAction1, arSkillAction2;

	int		nHit = 0;
	int		nAvoid = 0;

	BOOL	bIsHit = FALSE;
	BOOL	bIsCritical = FALSE;

	int		nDamage		= 0;
	int		nDefense	= 0;

	int		iRandom = 0;
//	int		iDefenseDex = 0;
//	double	determine	= 0;
	int		determine = 0;
	int		iDexHitRate = 0, iLevelHitRate = 0;

	int nID = m_Target.id;					// Target 을 구한다.

	// 명중여부 판단 변수 초기화
	bIsHit = FALSE;	
	

	

	// 회피값/명중판정/데미지 계산 -----------------------------------------//
	if(nID >= USER_BAND && nID < NPC_BAND)	// Target 이 User 인 경우
	{
		pUser = GetUser(pCom, nID - USER_BAND);
		
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED)// User 가 Invalid 한 경우
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}

		if(pUser->m_bLive == USER_DEAD)			// User 가 이미 죽은경우
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}

		if(pUser->m_dwNoDamageTime != 0)		// User 가 무적타임에 있을경우
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}
		
		if(pUser->m_bPShopOpen == TRUE)			// User has personal shop 
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}
		if(pUser->m_bSessionOnline == true)			// 잼窟꼇굳밍묑샌
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}

/*	위에서 이미 체크 함
		if(pUser->m_state == STATE_DISCONNECTED)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			return nStandingTime;
		}
*/
		if(m_tNpcType == NPCTYPE_GUILD_GUARD)	
		{
			if(m_tGuildWar == GUILD_WARRING && pUser->m_dwGuild > 0)
			{
				if(m_pGuardStore) 
				{
					if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) return nStandingTime;
				}
				else if(m_pGuardFortress)
				{
					if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) return nStandingTime;
				}
			}
		}
												// 은닉 상태이면 경비병을 제외한 모든 몹에 해당			
//		if(m_tNpcType != NPCTYPE_GUARD && pUser->m_dwHideTime > 0)
//		{
//			InitTarget();
//			m_NpcState = NPC_MOVING;
//			return nStandingTime;
//		}

		if(pUser->m_tIsOP == 1)
		{
			InitTarget();
			m_NpcState = NPC_MOVING;
			return nStandingTime;
		}

		// 회피값 계산 
		nAvoid = pUser->GetAvoid(); //BOSS꼇넜쀼
		
		// 명중여부 판단
		iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5); 
		
		iDexHitRate = (int)( 30.0 * ( (double)m_sDEX/(m_sDEX + pUser->m_sMagicDEX) ) + 15.0 );
		iLevelHitRate = (int)( 70.0 * ( (double)m_byClassLevel/(pUser->m_sLevel + m_byClassLevel) ) + 15.0);
        
		determine = iDexHitRate + iLevelHitRate - (nAvoid+pUser->m_Avoid);
/*
		iDefenseDex = pUser->m_sMagicDEX;
		if(iDefenseDex < 0) iDefenseDex = 0; //방어 코드

		determine = 200 * ((double)m_sDEX / (m_sDEX + iDefenseDex)) * ((double)m_byClassLevel / (m_byClassLevel + pUser->m_sLevel));
		determine = determine - nAvoid;
*/
		if(determine < ATTACK_MIN) determine = ATTACK_MIN;			// 최소 20
		else if(determine > ATTACK_MAX) determine = ATTACK_MAX;		// 최대

		if(iRandom < determine)	bIsHit = TRUE;		// 명중
		

		// 공격 미스
		if(bIsHit == FALSE)					
		{
			SendAttackMiss(pCom, nID);
			return m_sAttackDelay;;
		}

		// 명중이면 //Damage 처리 ----------------------------------------------------------------//

		nDamage = GetFinalDamage(pUser);	// 최종 대미지
		// nDamage += (int)(nDamage * 0.8);//老써諒
		//膠잿�襁┝撮夢融寂狼襁┝撮�
		//nDamage=nDamage-(pUser->m_DynamicMagicItem[5]+pUser->m_DynamicMagicItem[6]);
	//	nDamage=nDamage-(pUser->m_DynamicUserData[MAGIC_PHY_ATTACK_DOWN]+pUser->m_DynamicUserData[MAGIC_FINALLY_ATTACK_DOWN]);
		if(nDamage < 0) nDamage = 15;
		if(pUser->m_tAbnormalKind == ABNORMAL_BYTE_COLD) nDamage += 10;		// 상대편이 냉기 이상이면 데미지 추가

		//흔벎닸瞳빱랬，30%돨섯쪽邱묑샌빱랬
		if(pUser->m_tHuFaType &&pUser->m_nHuFaHP>0)
		{
			nID = nID+USER_HUFA_BAND;
			//�襁┟暄�
			pUser->SendDamageNum(0,nID,(short)nDamage);

			SendAttackSuccess(pCom, nID, bIsCritical, pUser->m_nHuFaHP, pUser->m_nHuFaMaxHP);//yskang 0.3
			if(nDamage > 0)
				pUser->SetHuFaDamage(nDamage);
			if(pUser->m_nHuFaHP>0)
			{
				pUser->HuFaAttack(m_sNid+NPC_BAND);
			}
			return m_sAttackDelay;
		}

		if(nDamage > 0) pUser->SetDamage(nDamage);

		// 방어측 내구도 감소
		pUser->SendDamagedItem(nDamage);
		pUser->SendDamageNum(0,pUser->m_uid+USER_BAND,nDamage);
//		if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ 나중에 고침
		if(pUser->m_lDeadUsed == 1)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			m_Delay = m_sStandTime;

			if(m_NpcVirtualState == NPC_STANDING)
			{
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName);//공용 몬스터일경우 경험치 1%감소
				else				pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);// 경험치와 그외 변화량를 반영한다.
			}
			if(m_tNpcType == NPCTYPE_GUARD) pUser->SendCityRank(1);				// 경비병에게 죽으면 PK 카운트 1 감소
																				// 현재 경비병은 노말 공격만 하므로 이곳에만 추가 
																				// Add by JJS 2002.05.24
		}

		//yskang 0.3 SendAttackSuccess(pCom, nID, arSkillAction1, arSkillAction2, pUser->m_sHP, pUser->m_sMagicMaxHP);
		SendAttackSuccess(pCom, nID, bIsCritical, pUser->m_sHP, pUser->m_sMagicMaxHP);//yskang 0.3
	}

	return m_sAttackDelay;
}

CNpc* CNpc::GetNpc(int nid)
{
	CNpc* pNpc = NULL;

	int nSize = g_arNpc.GetSize();

	if(nid < 0 || nid >= nSize) return NULL;

	for( int i = 0; i < g_arNpc.GetSize(); i++)
	{
		pNpc = g_arNpc[i];
		if( !pNpc ) continue;

		if( pNpc->m_sNid == nid )
		{
			return pNpc;
		}
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////////////
//	NPC 의 공격력을 얻어온다.
//
int CNpc::GetAttack()
{
	int X = m_byAX;
	int Y = m_byAZ;

	return XdY(X, Y);
}

////////////////////////////////////////////////////////////////////////////
//	NPC 의 방어력을 얻어온다.
//
int CNpc::GetDefense()
{
	return m_iDefense;
}

/////////////////////////////////////////////////////////////////////////////
//	Damage 계산, 만약 m_sHP 가 0 이하이면 사망처리
//
BOOL CNpc::SetDamage(int nDamage)
{
	if(m_NpcState == NPC_DEAD) return TRUE;
	if(m_sHP <= 0) return TRUE;
	if(nDamage <= 0) return TRUE;

	m_sHP -= nDamage;

	if( m_sHP <= 0 )
	{
		m_sHP = 0;
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC 사망처리
//
void CNpc::Dead()
{
	long lNpcUid = m_sNid + NPC_BAND;
	if(m_pOrgMap[m_sCurX][m_sCurY].m_lUser == lNpcUid)
	{
		::InterlockedExchange(&m_pOrgMap[m_sCurX][m_sCurY].m_lUser, (LONG)0);
	}
	
	m_sHP = 0;
	m_NpcState = NPC_DEAD;
	
	if(m_bSummon)
	{
		m_bSummonDead = TRUE;
		m_bSummon = FALSE;
	}
	
	if(m_NpcVirtualState == NPC_MOVING)	m_NpcVirtualState = NPC_WAIT;
	
	m_Delay = m_sRegenTime;
	m_bFirstLive = FALSE;
}

//////////////////////////////////////////////////////////////////////////////
//	NPC 사망처리시 경험치 분배를 계산한다.(일반 유저와 버디 사용자구분)
//
void CNpc::SendExpToUserList(COM *pCom)
{
	int i;
	int exp = 0;//, eventExp = 0;
	int totalDamage = 0;
	int firstDamage = 0;
	DWORD plusExp = 0;
	int MaxDamage=0;
	USER *KeypUser=NULL;

	if(m_NpcVirtualState == NPC_WAIT) return;		// 가상공간에서 경험치 없다.
	if(m_tNpcType >= NPCTYPE_GUILD_NPC) return;


	if(InterlockedCompareExchange((long*)&m_lDamage, (long)1, (long)0) == (long)0){
		if(NpcDrop<=0) {
			InterlockedExchange(&m_lDamage, (LONG)0); 
			return;
		}else{
			NpcDrop=NpcDrop-1;
		}

		InterlockedExchange(&m_lDamage, (LONG)0); 
	}
//	if(m_tNpcType == NPCTYPE_GUILD_NPC || m_tNpcType == NPCTYPE_GUILD_DOOR) return;
//	if(m_tNpcType == NPCTYPE_GUILD_GUARD) return;	// 길드전에서 죽은 경비병은 경험치를 안준다.
//	SYSTEMTIME gTime;
//	GetLocalTime(&gTime);	

	USER *pUser = NULL;

	IsUserInSight(pCom);					// 현재 셀범위안에 있느냐?(몹을 기준으로 한 화면 : 플래그 셋팅)

	if(m_DamagedUserList[0].iUid >= 0 && m_DamagedUserList[0].nDamage > 0)	// 첫번째에 유저가 있다면 2배 
	{
		MaxDamage=firstDamage = m_DamagedUserList[0].nDamage;
		m_DamagedUserList[0].nDamage = m_DamagedUserList[0].nDamage * 2;
		
	}
														
	for(i = 0; i < NPC_HAVE_USER_LIST; i++)				// 일단 리스트를 검색한다.
	{												
		if(m_DamagedUserList[i].iUid < 0 || m_DamagedUserList[i].nDamage<= 0) continue;		// 안전코드
		if(m_DamagedUserList[i].bIs == TRUE) pUser = GetUser(pCom, m_DamagedUserList[i].iUid);
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;
		KeypUser=pUser;
		if(abs(pUser->m_sLevel-m_byClassLevel) > o_yehuoini[0]->djxz)  //훙膠宅밍뀌약40섬轟랬삿돤쒔駱掘齡뇹
			 continue;

		totalDamage = m_DamagedUserList[i].nDamage;
		if(MaxDamage<totalDamage){
			MaxDamage=totalDamage;
			KeypUser=pUser;
		}

		if ( (m_sExp / 5) <= 0 ) continue;
	    if ( totalDamage == 0 ) continue;
		if(((m_TotalDamage + firstDamage) /5) <= 0) continue;
		long long t=(long long)(m_sExp / 5) * totalDamage;
		exp =(int)(t/((m_TotalDamage + firstDamage) / 5));

		pUser->m_iCityValue += m_sInclination;
		if(pUser->m_iCityValue > 2000000000) pUser->m_iCityValue = 2000000000;	// 최대값이 없어서 임의로 정했다.
		
		if(pUser->m_iDisplayType != 5 && pUser->m_iDisplayType != 6)
			pUser->GetExpCommon((int)(exp * 1.1));
		else
			pUser->GetExpCommon((int)(exp * 0.8)); //무료 사용자는 경험치를 낮춘다.
		//---------------------------------------------------------------------------------------------
		

	}
	Dead_User_level=0;
	if(KeypUser!=NULL)
		Dead_User_level=KeypUser->m_sLevel;
	
}

//////////////////////////////////////////////////////////////////////////////
//	현재 몹을 기준으로 한 화면 범위안에 있는지 판단
//
void CNpc::IsUserInSight(COM *pCom)
{
	int j;

	USER* pUser = NULL;

	int iSearchRange = m_bySearchRange;						// 임시로 잡았다.
	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - 12;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - 13;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + 12;
	max_y = m_sCurY + 13;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

	int ix, iy;
	int target_uid;
	int uid;
	int iLen = 0;

	for(j = 0; j < NPC_HAVE_USER_LIST; j++)
	{
		m_DamagedUserList[j].bIs = FALSE;
	}

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= USER_BAND && target_uid < NPC_BAND )
			{
				uid = target_uid - USER_BAND;
				for(j = 0; j < NPC_HAVE_USER_LIST; j++)
				{												// 갖고있는 리스트상의 유저와 같다면		
					if(m_DamagedUserList[j].iUid == uid)		// 최종 ID를 비교해서 동일하면	
					{
						pUser = pCom->GetUserUid(uid);		
						if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED || pUser->m_curz != m_sCurZ) continue;
																
						iLen = strlen(pUser->m_strUserID);
						if(iLen <= 0 || iLen > CHAR_NAME_LENGTH) continue;

						if(strcmp(pUser->m_strUserID, m_DamagedUserList[j].strUserID) == 0) 
						{										// 이때서야 존재한다는 표시를 한다.
							m_DamagedUserList[j].bIs = TRUE;
						}
					}
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//	NPC DEAD Packet 을 인근 유저에게 보낸다.
//
int CNpc::SendDead(COM *pCom, int type,BOOL TreeBaoLv)
{
//	ASSERT(pCom);
	if(!pCom) return 0;
	if(m_NpcState != NPC_DEAD || m_sHP > 0) return 0;

	CBufferEx TempBuf;

	CPoint pt = ConvertToClient(m_sCurX, m_sCurY);

	TempBuf.Add(DEAD);
	TempBuf.Add((short)(m_sNid + NPC_BAND));
	TempBuf.Add((short)pt.x);
	TempBuf.Add((short)pt.y);
		
	SendInsight(pCom, TempBuf, TempBuf.GetLength());
	if(type) GiveNpcHaveItem(pCom ,TreeBaoLv);	//딜땜鮫
//	if(( (type)  &&  (abs(Dead_User_level-m_byClassLevel) <=50) )|| m_sEvent!=0)
//		GiveNpcHaveItem(pCom);	// 아이템 떨구기(경비병이면 안떨어트림)
	
	return m_sRegenTime;
}

////////////////////////////////////////////////////////////////////////////////
//	주변에 적이 없거나 수동몹의 경우 임의의 점으로 길찾기를 한 후 움직인다.
//
BOOL CNpc::RandomMove(COM *pCom)
{
	if(m_bySearchRange == 0) return FALSE;
	if(pCom == NULL) return FALSE;

	if(m_tNpcType == NPCTYPE_GUILD_DOOR)	return FALSE;	// 이동안하게...
	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)	return FALSE;	// 이동안하게...
	// NPC 가 초기 위치를 벗어났는지 판단한다.
	BOOL bIsIn = IsInRange();

	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return FALSE;
	if( !pMap->m_pMap ) return FALSE;

	CPoint pt;
	int nLoop = 0;
	int nDestX = -1, nDestY = -1;
	int min_x, min_y, max_x, max_y;
	int temp_minx = 0, temp_miny = 0, temp_maxx = 0, temp_maxy = 0;

	CRect rectIn;

	if(bIsIn)	// NPC 가 초기 위치를 벗어나지 않았으면
	{
/*alisia
		int temp_range = m_bySearchRange / 2;

		min_x = m_sCurX - temp_range;	if(min_x < 0) min_x = 0;
		min_y = m_sCurY - temp_range;	if(min_y < 0) min_y = 0;
		max_x = m_sCurX + temp_range;	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
		max_y = m_sCurY + temp_range;	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

		rectIn.IntersectRect(CRect(m_nInitMinX, m_nInitMinY, m_nInitMaxX, m_nInitMaxY), CRect(min_x, min_y, max_x, max_y));

		nLoop = 0;
		while(1)
		{
			nDestX = myrand(rectIn.left, rectIn.right);
			nDestY = myrand(rectIn.top, rectIn.bottom);

			if(pMap->m_pMap[nDestX][nDestY].m_bMove != 0 || pMap->m_pMap[nDestX][nDestY].m_lUser != 0)
			{
				if(nLoop++ >= 10) 
				{
					TRACE("NOT FIND~~\n");
					return FALSE;
				}
				continue;
			}
			
			break;
		}
alisia*/

		m_bRandMove = TRUE;		// 현재 움직임이 8방향 선택 움직임인지를 나타낸다 - PathFind() 함수 안에서 리셋한다

		m_arRandMove.RemoveAll();

		int axis_x[3];	axis_x[0] = -1;	axis_x[1] = 0;	axis_x[2] = 1;
		int axis_y[3];	axis_y[0] = -1;	axis_y[1] = 0;	axis_y[2] = 1;
		int rand_x, rand_y, rand_d;

		rand_x = myrand( 0, 2 );
		rand_y = myrand( 0, 2 );
		rand_d = myrand( 1, 5 );

		for( int i = 1; i <= rand_d; i++ )
		{
			m_arRandMove.Add( CPoint( axis_x[rand_x] * i, axis_y[rand_y] * i ) );
		}

		m_min_x = m_sCurX;
		m_min_y = m_sCurY;

		return TRUE;
	}
	else		// NPC 가 초기 위치를 벗어났으면
	{
		int x = 0, y = 0;
		
		min_x = m_sCurX;
		min_y = m_sCurY;
		max_x = m_sCurX;
		max_y = m_sCurY;

		if(m_nInitMinX < m_sCurX)	{min_x -= m_bySearchRange;	x += 1;} if(min_x < 0) min_x = 0;
		if(m_nInitMinY < m_sCurY)	{min_y -= m_bySearchRange;	y += 1;} if(min_y < 0) min_y = 0;
		if(m_nInitMaxX > m_sCurX)	{max_x += m_bySearchRange;	x += 1;} if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
		if(m_nInitMaxY > m_sCurY)	{max_y += m_bySearchRange;	y += 1;} if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;
				
		nLoop = 0;
		while(1)
		{
			nDestX = min_x + (rand() % (m_bySearchRange * x + 1)); 
			if(nDestX > max_x) nDestX = max_x;

			nDestY = min_y + (rand() % (m_bySearchRange * y + 1));
			if(nDestY > max_y) nDestY = max_y;

			if(pMap->m_pMap[nDestX][nDestY].m_bMove != 0 || pMap->m_pMap[nDestX][nDestY].m_lUser != 0)
			{
				if(nLoop++ >= 10) return FALSE;
				continue;
			}
			
			break;
		}
	}

	if(nDestX < 0 || nDestY < 0)
	{
		return FALSE;
	}

	// Run Path Find ---------------------------------------------//
	CPoint start, end;
	start.x = m_sCurX - min_x;
	start.y = m_sCurY - min_y;
	end.x = nDestX - min_x;
	end.y = nDestY - min_y;

	if(start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
	{
		return FALSE;
	}

	m_ptDest.x = nDestX;
	m_ptDest.y = nDestY;

	m_min_x = min_x;
	m_min_y = min_y;
	m_max_x = max_x;
	m_max_y = max_y;

	return PathFind(start, end);
}

/////////////////////////////////////////////////////////////////////////////////////
//	NPC 가 초기 생성위치 안에 있는지 검사
//
BOOL CNpc::IsInRange()
{
	// NPC 가 초기 위치를 벗어났는지 판단한다.
//	CRect rect(m_nInitMinX, m_nInitMinY, m_nInitMaxX, m_nInitMaxY);
	
//	return rect.PtInRect(CPoint(m_sCurX, m_sCurY));

	if( m_nInitMinX > m_sCurX || m_nInitMaxX < m_sCurX ) return FALSE;
	if( m_nInitMinY > m_sCurY || m_nInitMaxY < m_sCurY ) return FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
//	시야가 변경됐는지 판단하고 변경됐다면 변경내용을 클라이언트로 전송한다.
//
void CNpc::SightRecalc(COM* pCom)
{
	int sx, sy;

	sx = m_sCurX / SIGHT_SIZE_X;
	sy = m_sCurY / SIGHT_SIZE_Y;

	int dir_x = 0;
	int dir_y = 0;

	if( sx == m_presx && sy == m_presy ) return;
	
	if( m_presx == -1 || m_presy == -1 )
	{
		dir_x = 0;
		dir_y = 0;
	}
	else
	{
		if( sx > m_presx && abs(sx-m_presx) == 1 )		dir_x = DIR_H;
		if( sx < m_presx && abs(sx-m_presx) == 1 )		dir_x = DIR_L;
		if( sy > m_presy && abs(sy-m_presy) == 1 )		dir_y = DIR_H;
		if( sy < m_presy && abs(sy-m_presy) == 1 )		dir_y = DIR_L;
		if( abs(sx-m_presx) > 1 )						dir_x = DIR_OUTSIDE;
		if( abs(sy-m_presy) > 1 )						dir_y = DIR_OUTSIDE;
	}

	int prex = m_presx;
	int prey = m_presy;
	m_presx = sx;
	m_presy = sy;

	SendUserInfoBySightChange(dir_x, dir_y, prex, prey, pCom);
}

//////////////////////////////////////////////////////////////////////////////////////////
//	시야변경으로 인한 유저정보 전송
//
void CNpc::SendUserInfoBySightChange(int dir_x, int dir_y, int prex, int prey, COM *pCom)
{
	int min_x = 0, min_y = 0;
	int max_x = 0, max_y = 0;

	int sx = m_presx;
	int sy = m_presy;

	int modify_index = 0;
	char modify_send[1024];		::ZeroMemory(modify_send, sizeof(modify_send));
	FillNpcInfo(modify_send, modify_index, INFO_MODIFY);

	int delete_index = 0;
	char delete_send[1024];		::ZeroMemory(delete_send, sizeof(delete_send));
	FillNpcInfo(delete_send, delete_index, INFO_DELETE);

	if( prex == -1 || prey == -1 )
	{
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
		return;
	}
	if( dir_x == DIR_OUTSIDE || dir_y == DIR_OUTSIDE )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
		return;
	}
	if( dir_x > 0 )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx+1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
	if( dir_y > 0 )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy+1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
	if( dir_x < 0 )
	{
		min_x = (prex+1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey-1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
	if( dir_y < 0 )
	{
		min_x = (prex-1)*SIGHT_SIZE_X;
		max_x = (prex+2)*SIGHT_SIZE_X;
		min_y = (prey+1)*SIGHT_SIZE_Y;
		max_y = (prey+2)*SIGHT_SIZE_Y;
		SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
		min_x = (sx-1)*SIGHT_SIZE_X;
		max_x = (sx+2)*SIGHT_SIZE_X;
		min_y = (sy-1)*SIGHT_SIZE_Y;
		max_y = (sy)*SIGHT_SIZE_Y;
		SendToRange(pCom, modify_send, modify_index, min_x, min_y, max_x, max_y);
	}
}

////////////////////////////////////////////////////////////////////////////////
//	한화면내의 유저에게만 정보전송
//
void CNpc::SendExactScreen(COM* pCom, TCHAR *pBuf, int nLength)
{
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;
	
	SEND_DATA* pNewData = NULL;
	pNewData = new SEND_DATA;
	if(pNewData == NULL) return;

	pNewData->flag = SEND_SCREEN;
	pNewData->len = nLength;

	::CopyMemory(pNewData->pBuf, pBuf, nLength);

	pNewData->uid = 0;
	pNewData->x = m_sCurX;
	pNewData->y = m_sCurY;
	pNewData->z = m_sCurZ;
	pNewData->zone_index = m_ZoneIndex;

	pCom->Send(pNewData);
	if(pNewData) delete pNewData;
}

///////////////////////////////////////////////////////////////////////////////
//	시야안에 있는 유저에게 데이터 전송
//
void CNpc::SendInsight(COM* pCom, TCHAR *pBuf, int nLength)
{
/*
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;
	
	SEND_DATA* pNewData = NULL;
	pNewData = new SEND_DATA;
	if(pNewData == NULL) return;

	pNewData->flag = SEND_INSIGHT;
	pNewData->len = nLength;

	::CopyMemory(pNewData->pBuf, pBuf, nLength);

	pNewData->uid = 0;
	pNewData->x = m_sCurX;
	pNewData->y = m_sCurY;
	pNewData->z = m_sCurZ;
	pNewData->zone_index = m_ZoneIndex;

	EnterCriticalSection( &(pCom->m_critSendData) );
	pCom->m_arSendData.Add( pNewData );
	LeaveCriticalSection( &(pCom->m_critSendData) );

	PostQueuedCompletionStatus( pCom->m_hSendIOCP, 0, 0, NULL );
*/
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;

	int sx = m_sCurX / SIGHT_SIZE_X;
	int sy = m_sCurY / SIGHT_SIZE_Y;
	
	int min_x = (sx-1)*SIGHT_SIZE_X; if( min_x < 0 ) min_x = 0;
	int max_x = (sx+2)*SIGHT_SIZE_X;
	int min_y = (sy-1)*SIGHT_SIZE_Y; if( min_y < 0 ) min_y = 0;
	int max_y = (sy+2)*SIGHT_SIZE_Y;
	
	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return;
	
	if( max_x >= pMap->m_sizeMap.cx ) max_x = pMap->m_sizeMap.cx - 1;
	if( max_y >= pMap->m_sizeMap.cy ) max_y = pMap->m_sizeMap.cy - 1;
	
	int temp_uid;
	USER* pUser = NULL;

	for( int i = min_x; i < max_x; i++ )
	{
		for( int j = min_y; j < max_y; j++ )
		{				
			temp_uid = pMap->m_pMap[i][j].m_lUser;

			if(temp_uid < USER_BAND || temp_uid >= NPC_BAND) continue;
			else temp_uid -= USER_BAND;
			
			if( temp_uid >= 0 && temp_uid < MAX_USER )
			{
				pUser = pCom->GetUserUid(temp_uid);
				if ( pUser == NULL ) continue;
				
				if( pUser->m_state == STATE_GAMESTARTED )
				{
					if( pUser->m_curx == i && pUser->m_cury == j && pUser->m_curz == m_sCurZ )
					{
						Send( pUser, pBuf, nLength );
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//	현재 NPC 의 위치와 (xpos, ypos) 사이의 거리를 계산
//
BOOL CNpc::GetDistance(int xpos, int ypos, int dist)
{
	if(xpos >= g_zone[m_ZoneIndex]->m_sizeMap.cx || xpos < 0 || ypos >= g_zone[m_ZoneIndex]->m_sizeMap.cy || ypos < 0) return FALSE;

	int dx = abs(xpos - m_sCurX);
	int dy = abs(ypos - m_sCurY);

	if(dx + dy > dist * 2) return FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////
//	NPC 가 가진 아이템을 떨군다.
//밍膠价빈딜돨膠틔셕炬
void CNpc::GiveNpcHaveItem(COM *pCom,BOOL TreeBaoLv)
{
	int temp = 0;
	int iPer = 0, iVal = 0;
	int iRandom;
	int nCount = 1;
	int nDnHap = 0;
    USER *pUser = GetUser(pCom, m_DamagedUserList[0].iUid);

	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED)	// 잘못된 유저아이디이면 에러
	{
		return;
	}
//	SYSTEMTIME gTime;
//	GetLocalTime(&gTime);	

	if(m_NpcVirtualState == NPC_WAIT) return;

/*	if(gTime.wDay > 7 && gTime.wDay < 14)					// 8일부터 13일까지	
	{
		if(m_byClassLevel <= 20)		nCount = 1;
		else if(m_byClassLevel <= 50)	nCount = 2;
		else if(m_byClassLevel <= 70)	nCount = 3;
		else							nCount = 5;
	}
	else
	{
*/
	if(TreeBaoLv ==TRUE || g_sanBaoLv ==TRUE || pUser->m_dwZaiXianTime != 0)		nCount = 3;		//몽앴삶땡角뤠괵뜩�模�陋구
	else							nCount = 2;

	if(m_sEvent== 32000 || m_sEvent== 30007 || m_sEvent== 30009 )                    nCount = 10;
	if( m_sEvent == NPC_EVENT_MOP )				nCount = 16;		// 31000珂딜16숭膠틔
	if( m_sEvent == NPC_EVENT_GREATE_MOP )		nCount = 10;	// 엑스리온 등 특수 몬스터일 경우 10개를 떨어뜨린다.
//	}
/*
	for(int i = 0; i < nCount; i++)
	{
		iRandom = myrand(1, 30);

		if(iRandom < m_tItemPer)
		{

			iRandom = myrand(1, 10000);
			for(int i = 2; i < g_NpcItem.m_nField; i += 2)
			{			
//				iPer = g_NpcItem.m_ppItem[i][m_byClassLevel];
				iPer = g_NpcItem.m_ppItem[i][m_sHaveItem];
				if(iPer == 0) return;
				if(iRandom < iPer)
				{											// 우선 기본테이블를 참조하기위해	
//					temp = g_NpcItem.m_ppItem[i-1][m_byClassLevel];
					temp = g_NpcItem.m_ppItem[i-1][m_sHaveItem];
					iVal = temp;
					if(temp >= g_arItemTable.GetSize()) return;

					if(g_arItemTable[temp]->m_byWear <= 5 || g_arItemTable[temp]->m_byWear == 117 || g_arItemTable[temp]->m_byWear == 20)	// 변형테이블이다.
					{
						iVal = IsTransformedItem(g_arItemTable[temp]->m_sSid);
						if(iVal == -1) iVal = temp;//return;
					}
					if (iVal == 845 || iVal == 909 || iVal == 846 || iVal == 907 || iVal == 908) iVal = 847;
					GiveItemToMap(pCom, iVal, TRUE);
					break;
				}
			}

		}

		else if(iRandom < m_tDnPer)
		{
//			SYSTEMTIME gTime;										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Event Code 기간동안 일시적으로 늘려준다.
//			GetLocalTime(&gTime);

			iPer = g_arDNTable[m_byClassLevel]->m_sMinDn;
			iVal = g_arDNTable[m_byClassLevel]->m_sMaxDn;
			iRandom = myrand(iPer, iVal);
																	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Event Code 기간동안 일시적으로 늘려준다.	

			nDnHap += iRandom;
			//GiveItemToMap(pCom, iRandom, FALSE);
		}
	}
	if(nDnHap > 0 )
	{
      if (nDnHap == 845 || nDnHap == 909 || nDnHap == 846 || nDnHap == 907 || nDnHap == 908) nDnHap = 847;
		GiveItemToMap(pCom, nDnHap, FALSE);
	}
	*/
	int tItemHavePer;
	if(m_sPid>255)
		return;
	int tItemPer=g_DropItem[m_sPid][m_byColor].DropNovelity;
	int tLeechdomPer = g_DropItem[m_sPid][m_byColor].DropLeechdom+tItemPer;
	int tItemN=g_DropItem[m_sPid][m_byColor].n;
	int i;
	//TRACE("鑒좆 %d\n",nCount);
	for(i = 0; i < nCount; i++)
	{
		//TRACE( "i=%d\n",i);
		iRandom = myrand(1, 100);
		//TRACE("踞샙鑒 %d\n",iRandom);
		if(iRandom < tItemPer)
		{
			//TRACE( "膠틔--\n");
			iRandom = myrand(1, 10000)%tItemN;
			tItemHavePer = g_DropItem[m_sPid][m_byColor].novelity[iRandom].per;
			temp = iVal = g_DropItem[m_sPid][m_byColor].novelity[iRandom].code1+g_DropItem[m_sPid][m_byColor].novelity[iRandom].code2*256;
			if(iVal >= g_arItemTable.GetSize()){
				return;
			}
			//if(pUser->m_dwZaiXianTime != 0)//掘齡딜쭝膠틔
			//{
			//	if (iVal == 987) continue;
			//}
			iRandom = myrand(1, 1000);
			if(iRandom < tItemHavePer){	
				if(g_arItemTable[temp]->m_byWear <= 5 || g_arItemTable[temp]->m_byWear == 117 || g_arItemTable[temp]->m_byWear == 20)	// 변형테이블이다.
				{
					iVal = IsTransformedItem(g_arItemTable[temp]->m_sSid);
					if(iVal == -1) iVal = temp;
				}
				
				
			//	TRACE( "膠틔덜쯤 %s,%d\n",g_arItemTable[iVal]->m_strName,iVal);
				GiveItemToMap(pCom, iVal, TRUE);
				
				//break;
			}
		}
		else if(iRandom < tLeechdomPer)//딜융浪
		{
			//TRACE( "융浪--\n");
			if(m_byClassLevel <30)
				iVal=31;
			else if(m_byClassLevel <70)
				iVal=32;
			else if(m_byClassLevel <120)
				iVal=33;
			else
				iVal=227+256*3;
				//iVal=33;
			GiveItemToMap(pCom, iVal, TRUE);
		}else{
			
			//TRACE( "풀--\n");
			int money= g_DropItem[m_sPid][m_byColor].money;
			iRandom =money+(money *myrand(0,15)%15);//15%륫땡
			nDnHap += iRandom;
		
	  }//TRACE( "i=%d\n",i);
	}
	//TRACE( "i=%d----------------------------------------\n",i);
	if(nDnHap > 0 )
	{
		if (nDnHap == 845 || nDnHap == 909 || nDnHap == 846 || nDnHap == 907 || nDnHap == 908) nDnHap = 847;
		GiveItemToMap(pCom, nDnHap, FALSE);
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	아이템중 변형아이템이 있는지 판단한다.
//
int CNpc::IsTransformedItem(int sid)
{
	int iVal = 0;
	int i, j, iRandom;

	for(i = 0; i < g_ValItem.m_nRow; i++)
	{
		if(g_ValItem.m_ppItem[g_ValItem.m_nField-2][i] == sid)		// 맨 마지막 필드에서 아이템 항목(6개 종류)
		{
			iRandom = myrand(1, 100);
			for(j = 2; j < g_ValItem.m_nField; j+= 2)
			{
				iVal = g_ValItem.m_ppItem[j][i];
				if(iRandom < iVal)
				{
					if(sid >= g_arItemTable.GetSize()) return -1;
					else return g_ValItem.m_ppItem[j-1][i];
				}
			}
		}
	}

	return -1;
}

int CNpc::IsMagicItem(COM* pCom, ItemList *pItem, int iTable)
{
    int i = 0, j;
    int iMagicTemp = 1 , iRareTemp = 1;
    int iRandom = myrand( 1, 10000 );

    if(pItem == NULL) return 0;
    int iMagicCount = 0, iCount = 0;
    int nLoop = 0, iType = 0;
    int nEventMoon = 0;
    int nEventSongpeon = 0;
    int nEventBox = 0;
    int iMagicUp = 0;
    
    USER* pUser = NULL;

    if(m_sEvent == NPC_EVENT_MOP)
    {
        iMagicTemp = 0; 
        iRareTemp = 4; 
    }
    else if(m_sEvent == NPC_EVENT_GREATE_MOP)
    {
        iMagicTemp = 0;
        iRareTemp = 8;
    }
    else if(m_sEvent == 30009 || m_sEvent == 30007)
    {
        iMagicTemp = 0;
        iRareTemp = 10000;
    }

    if(m_lKillUid >= 0)   
    {
        pUser = GetUser(pCom, m_lKillUid);
        if(pUser != NULL && pUser->m_state == STATE_GAMESTARTED)
        {
            if(pUser->m_dwMagicFindTime != 0 || pUser->m_isDoubleBAOLV != 0 || g_sanBaoLv == TRUE || pUser->m_dwZaiXianTime != 0)
            {
                iMagicTemp = 0;
                iRareTemp = 10000;
            }
            else if(pUser->m_dwMagicFindTime == 0 || pUser->m_isDoubleBAOLV == 0 || pUser->m_dwZaiXianTime == 0)
            {
                iMagicTemp = 5000;
                iRareTemp = 5000;
            }
        }
    }

    nEventMoon = NPC_RARE_ITEM * iRareTemp + (NPC_EVENT_MOON - NPC_RARE_ITEM);
    nEventSongpeon = nEventMoon + (NPC_EVENT_SONGPEON - NPC_EVENT_MOON);
    nEventBox = nEventSongpeon + (NPC_EVENT_BOX - NPC_EVENT_SONGPEON);

    if(iRandom <= NPC_MAGIC_ITEM * iMagicTemp)
    {
        nLoop = 2;
        iType = MAGIC_ITEM;
    }
    else if((iRandom > NPC_MAGIC_ITEM * iMagicTemp) && (iRandom <= (NPC_RARE_ITEM * iRareTemp + iMagicUp)))    
    { 
        nLoop = 4;
        iType = RARE_ITEM; 
    }    
    else if(0 && iRandom > NPC_RARE_ITEM * iRareTemp && iRandom <= nEventMoon)
    {
        return EVENT_ITEM_MOON;
    }
    else if(0 && iRandom > nEventMoon && iRandom <= nEventSongpeon)
    {
        return EVENT_ITEM_SONGPEON;
    }
    else if(0 && iRandom > nEventSongpeon && iRandom <= nEventBox)
    {
        return EVENT_ITEM_BOX;
    }
    else return NORMAL_ITEM;

    int iTemp = 0;

    if(m_ItemUserLevel <= 20)       iMagicCount = 205;
    else if(m_ItemUserLevel <= 40)  iMagicCount = 205;
    else if(m_ItemUserLevel <= 60)  iMagicCount = 205;
    else                            iMagicCount = 205;

    if(iMagicCount >= g_arMagicItemTable.GetSize()) 
        iMagicCount = g_arMagicItemTable.GetSize() - 1;

    static const int allowSids[] = {
        49, 53, 56, 61, 64, 73, 74, 76, 86, 87, 88, 89, 91, 93, 94, 95, 96, 97,
        105, 106, 107, 109, 110, 113, 117, 120, 125, 128, 129, 130, 132, 135, 
        136, 137, 138, 139, 141, 145
    };
    static const int allowCount = sizeof(allowSids) / sizeof(allowSids[0]);

    while(nLoop > i)
    {
        if(m_sEvent == 32000)
        {
            // 닒豚冀돨橄昑긍뵀櫓踞샙朞嶝寧몸
            int randomIndex = myrand(0, allowCount - 1);
            int targetSid = allowSids[randomIndex];
            
            // 瞳침랬橄昑깊櫓꿴冷뚤壇돨乞多
            bool found = false;
            for(int k = 0; k < iMagicCount; k++)
            {
                if(g_arMagicItemTable[k]->m_sSid == targetSid)
                {
                    iRandom = k;
                    found = true;
                    break;
                }
            }
            
            if(!found || !g_arMagicItemTable[iRandom]->m_tUse) continue;
        }
        else
        {
            // 렷32000慤숭돨뇹잿
            do {
                if(pUser != NULL && pUser->m_iDisplayType != 5 && pUser->m_iDisplayType != 6)
                {
                    if(m_ItemUserLevel <= 20)
                    {
                        iRandom = myrand(0, iMagicCount);
                    }
                    else
                    {
                        iRandom = myrand(41, iMagicCount);
                    }
                }
                else
                {
                    iRandom = myrand(0, iMagicCount);
                }

                // 쇱꿴角뤠角唐槻돨침랬橄昑
                if(iRandom >= g_arMagicItemTable.GetSize()) continue;
                if(!g_arMagicItemTable[iRandom]->m_tUse) continue;

                break;
            } while(true);
        }

        if(CheckClassItem(iTable, iRandom) == FALSE) 
        {
            if(i == 0) continue;
            else if(iType == RARE_ITEM && i <= 3) continue;
            else { i++; continue; }
        }

        for(j = 0; j < 4; j++)
        {
            if (pItem->tMagic[j] < 0 || pItem->tMagic[j] >= iMagicCount) continue;
                
            if(o_yehuoini[0]->chongdie == 0)
            {
                iCount = g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType;
            }
            if(iCount != 0 && iCount == g_arMagicItemTable[iRandom]->m_sSubType)
            {
                iCount = g_arMagicItemTable[pItem->tMagic[j]]->m_sChangeValue;
                if(iCount < g_arMagicItemTable[iRandom]->m_sChangeValue)
                {
                    iTemp = g_arMagicItemTable[pItem->tMagic[j]]->m_tLevel;
                    if(pItem->sLevel - iTemp > 0) pItem->sLevel -= iTemp;
                    pItem->sLevel += g_arMagicItemTable[iRandom]->m_tLevel;
                    pItem->tMagic[j] = iRandom; 

                    if(g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType == MAGIC_DURATION_UP)
                    {
                        iTemp = g_arMagicItemTable[pItem->tMagic[j]]->m_sChangeValue;
                        if(pItem->sDuration - iTemp > 0) pItem->sDuration -= iTemp;
                        pItem->sDuration += g_arMagicItemTable[iRandom]->m_sChangeValue;
                    }
                    break;
                }
                else if(iCount == g_arMagicItemTable[iRandom]->m_sChangeValue) break;
            }

            if(pItem->tMagic[j] > 0) continue;
            else
            { 
                pItem->tMagic[j] = iRandom; i++; 
                if(g_arMagicItemTable[iRandom]->m_tLevel > 0) pItem->sLevel += g_arMagicItemTable[iRandom]->m_tLevel;
                if(g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType == MAGIC_DURATION_UP)
                {
                    pItem->sDuration += g_arMagicItemTable[iRandom]->m_sChangeValue;
                }
                break; 
            }
        }
    }

    return iType;
}
///////////////////////////////////////////////////////////////////////////////////
//	아이템중 매직 아이템을 떨어드릴수있는지 판단
//밍膠딜쭝膠틔융뼝쪽
//int CNpc::IsMagicItem(COM* pCom, ItemList *pItem, int iTable)
//{
//	int i = 0, j;
//	int iMagicTemp = 1 , iRareTemp = 1;
//	int iRandom = myrand( 1, 10000 );
//
//	if(pItem == NULL) return 0;
//	int iMagicCount = 0, iCount = 0;
//	int nLoop = 0, iType = 0;
//	int nEventMoon = 0;
//	int nEventSongpeon = 0;
//	int nEventBox = 0;
//	int iMagicUp=0;
//	
//
//    USER* pUser = NULL;
//
//	/*SYSTEMTIME gTime;										//@@@@@@@@@@@@@@@ Event Code 기간동안 일시적으로 늘려준다.
//	GetLocalTime(&gTime);
//	/*if(gTime.wMonth < 7) { iMagicTemp = 10; iRareTemp = 2; }
//	else if(gTime.wMonth == 7) 
//	{ 
//		if(gTime.wDay <= 7) { iMagicTemp = 10; iRareTemp = 2; } 
//	}
//	*/
///*	if(m_sEvent== 32000){
//		iMagicTemp=0;
//		iRareTemp = 3; 
//	}else*/if(m_sEvent == NPC_EVENT_MOP )				// 현재 빅풋,퀸,스콜피오
//	{
//		iMagicTemp = 0; 
//		iRareTemp = 4; 
//	}
//	else if(m_sEvent == NPC_EVENT_GREATE_MOP)	// 엑스리온
//	{
//		iMagicTemp = 0;  //70
//		iRareTemp = 8;    //75
//	}
//	
//	else if(m_sEvent == 30009 || m_sEvent == 30007)	// 엑스리온
//	{
//		iMagicTemp = 0;  //70
//		iRareTemp = 10000;    //75
//	}
//
//
//	/*if(m_lKillUid >= 0)
//	{
//		pUser = GetUser(pCom, m_lKillUid);
//		if(pUser != NULL && pUser->m_state == STATE_GAMESTARTED)
//		{
//			if(pUser->m_dwMagicFindTime != 0)	// 매직 파인더를 먹은 상태이면
//			{
//					iMagicTemp=0;
//					iMagicUp=10000;
//			}
//		}
//	}*/
//	if(m_lKillUid >= 0)   
//	{
//		pUser = GetUser(pCom, m_lKillUid);
//		if(pUser != NULL && pUser->m_state == STATE_GAMESTARTED)
//		{
//			if(pUser->m_dwMagicFindTime != 0 || pUser->m_isDoubleBAOLV != 0 || g_sanBaoLv == TRUE || pUser->m_dwZaiXianTime != 0)
//			{
//				//iMagicTemp *= o_yehuoini[0]->xyl;  //妗頓珂딜융陋구
//				//iRareTemp *= o_yehuoini[0]->xyh;    //妗頓珂딜쏜陋구
//				iMagicTemp = 0;  //妗頓珂딜융陋구
//				iRareTemp = 10000;    //妗頓珂딜쏜陋구
//			}
//			else if(pUser->m_dwMagicFindTime == 0 || pUser->m_isDoubleBAOLV == 0 || pUser->m_dwZaiXianTime == 0)
//			{
//				//iMagicTemp *= o_yehuoini[0]->lan;  //청唐妗頓珂딜융陋구
//				//iRareTemp *= o_yehuoini[0]->huang;    //청唐妗頓珂딜쏜陋구
//				iMagicTemp = 5000;  //妗頓珂딜융陋구
//				iRareTemp = 5000;    //妗頓珂딜쏜陋구
//			}
//            
//		}
//	}
//
//	nEventMoon		= NPC_RARE_ITEM * iRareTemp + (NPC_EVENT_MOON - NPC_RARE_ITEM);
//	nEventSongpeon	= nEventMoon + (NPC_EVENT_SONGPEON - NPC_EVENT_MOON);
//	nEventBox		= nEventSongpeon + (NPC_EVENT_BOX - NPC_EVENT_SONGPEON);
//
//    if(iRandom <= NPC_MAGIC_ITEM * iMagicTemp)	// 매직
//	{
//		nLoop = 2;
//		iType = MAGIC_ITEM;
//	}
//	else if((iRandom > NPC_MAGIC_ITEM * iMagicTemp) && (iRandom <=( NPC_RARE_ITEM * iRareTemp+iMagicUp)))	
//	{ 
//		nLoop = 4;
//		iType = RARE_ITEM; 
//	}	
//	else if(0 && iRandom > NPC_RARE_ITEM * iRareTemp && iRandom <= nEventMoon)
//	{
//		return EVENT_ITEM_MOON;
//	}
//	else if(0 && iRandom > nEventMoon && iRandom <= nEventSongpeon)
//	{
//		return EVENT_ITEM_SONGPEON;
//	}
//	else if(0 && iRandom > nEventSongpeon && iRandom <= nEventBox)
//	{
//		return EVENT_ITEM_BOX;
//	}
//	else return NORMAL_ITEM;								// 일반아이템
//
//	int iTemp = 0;
//
//	if(m_ItemUserLevel <= 20)       iMagicCount = 205;	//42;	// 딜돨膠틔橄昑왠齡    //neo경굶
//	else if(m_ItemUserLevel <= 40)  iMagicCount = 205;  //106
//	else if(m_ItemUserLevel <= 60)  iMagicCount = 205;  //143
//	else							iMagicCount = 205;    //鑒令督댕,딜돨橄昑督봤
//
//	
//
//	if(iMagicCount >= g_arMagicItemTable.GetSize()) iMagicCount = g_arMagicItemTable.GetSize() - 1;
//
//	while(nLoop > i)										// 무조건 4개속성값을 구한다.
//	{
//		
//		iRandom = myrand(0, iMagicCount);
//		//------------------------------------------------------------------------------------------------
//		//yskang 0.6 유료사용자에게 프리미엄 좋은 옵션의 아이템이 떨어진다.
//		if(pUser != NULL)
//		{
//			if(pUser->m_iDisplayType !=5 && pUser->m_iDisplayType !=6)//유료 사용자이다.
//			{
//				if(m_ItemUserLevel <= 20)
//					iRandom = myrand(0, iMagicCount); //좋은 아이템이 떨어질 확률을 높인다.
//				else
//					iRandom = myrand(41, iMagicCount); 
//			}
//		}
//		
//		if(!g_arMagicItemTable[iRandom]->m_tUse) continue;
//
//		if(CheckClassItem(iTable, iRandom) == FALSE) 
//		{
//			if(i == 0) continue;							// 매직은 기본이 1개
////			else if(iType == RARE_ITEM && i <= 2) continue;	// 掘齡뼝�ノ鮎례轍逃望閏�2係鹿��
//			else if(iType == RARE_ITEM && i <= 3) continue;	// 掘齡뼝�ノ鮎례轍逃望閏�3係鹿��
//			else { i++; continue; }
//		}
//
//		for(j = 0; j < 4; j++)
//		{
//			if (pItem->tMagic[j] < 0 || pItem->tMagic[j] >= iMagicCount) continue;
//				
//			if(o_yehuoini[0]->chongdie == 0)
//			{
//				iCount = g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType;//掘齡膠틔꼇놔路릿橄昑덜쯤
//		    }
//			if(iCount != 0 && iCount == g_arMagicItemTable[iRandom]->m_sSubType)	// 속성이 겹칠수 있으므로 이중 큰값만 선택	
//			{
//				iCount = g_arMagicItemTable[pItem->tMagic[j]]->m_sChangeValue;
//				if(iCount < g_arMagicItemTable[iRandom]->m_sChangeValue)
//				{
//					iTemp = g_arMagicItemTable[pItem->tMagic[j]]->m_tLevel;
//					if(pItem->sLevel - iTemp > 0) pItem->sLevel -= iTemp;
//					pItem->sLevel += g_arMagicItemTable[iRandom]->m_tLevel;
//					pItem->tMagic[j] = iRandom; 
//
//					if(g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType == MAGIC_DURATION_UP)
//					{
//						iTemp = g_arMagicItemTable[pItem->tMagic[j]]->m_sChangeValue;
//						if(pItem->sDuration - iTemp > 0) pItem->sDuration -= iTemp;
//						pItem->sDuration += g_arMagicItemTable[iRandom]->m_sChangeValue; // 내구력 증가 속성은 셋팅될때 
//					}
//					break;
//				}
//				else if(iCount == g_arMagicItemTable[iRandom]->m_sChangeValue) break;
//			}
//
//			if(pItem->tMagic[j] > 0) continue;	// 이미 슬롯에 값이 있으면 넘어감
//			else
//			{ 
//				pItem->tMagic[j] = iRandom; i++; 
//				if(g_arMagicItemTable[iRandom]->m_tLevel > 0) pItem->sLevel += g_arMagicItemTable[iRandom]->m_tLevel;
//				if(g_arMagicItemTable[pItem->tMagic[j]]->m_sSubType == MAGIC_DURATION_UP)
//				{
//					pItem->sDuration += g_arMagicItemTable[iRandom]->m_sChangeValue; // 내구력 증가 속성은 셋팅될때 
//				}
//				break; 
//			}
//		}
////		i++;
//	}
//
//	return iType;
//}
//踞샙磵빱橄昑
void CNpc::shouhu_rand(	ItemList *pMapItem)
{
	int a;

	a=myrand(0,15)%100;
	pMapItem->tIQ=0x09;//磵빱奈��
	switch (a){
		case 0:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 1:pMapItem->tMagic[0]=4; return;//嶠포된섬藤속1 2 3
		case 2:pMapItem->tMagic[0]=7; return;//쉥뚤렘�餉�2 5 10瘻뺏냥菱성�餉�
		case 3:pMapItem->tMagic[0]=10; return;//뚤鷺鍋芚냥2% 5 10�襁�
		case 4:pMapItem->tMagic[0]=13; return;//13 렝徒藤속3 6 10
		case 5:pMapItem->tMagic[0]=16; return;//침랬렝徒藤속3 6 10
		case 6:pMapItem->tMagic[0]=19; return;//쉥둔훙뚤菱성묑샌�襁�2% 3 5 럽�莪슉瑾漑爵�
		case 7:pMapItem->tMagic[0]=22; return;// 댔밍쒔駱令瓊멕2% 3% 5%
		case 8:pMapItem->tMagic[0]=25; return;//쏜귑瓊멕10% 쏜귑瓊멕20% 쏜귑瓊멕50%
		case 9:pMapItem->tMagic[0]=28; return;// 杰唐세콘藤속1  杰唐세콘藤속2  杰唐세콘藤속3
		case 10:pMapItem->tMagic[0]=31; return;//딜쭝膠틔瓊멕2% 딜쭝膠틔瓊멕3% 딜쭝膠틔瓊멕5%
		case 11:pMapItem->tMagic[0]=34; return;//묑샌제藤속10 묑샌제藤속20 묑샌제藤속30
		case 12:pMapItem->tMagic[0]=37; return;//俱혤뚤렘�餉�10 俱혤뚤렘�餉�20 俱혤뚤렘�餉�30
		case 13:pMapItem->tMagic[0]=40; return;//�餉璜梔�10 �餉璜梔�20 �餉璜梔�30
		case 14:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 15:pMapItem->tMagic[0]=13; return;//13 렝徒藤속3 6 10
		case 16:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 17:pMapItem->tMagic[0]=34; return;//묑샌제藤속10 묑샌제藤속20 묑샌제藤속30
		case 18:pMapItem->tMagic[0]=13; return;//13 렝徒藤속3 6 10
		case 19:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 20:pMapItem->tMagic[0]=40; return;//�餉璜梔�10 �餉璜梔�20 �餉璜梔�30
		case 21:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 22:pMapItem->tMagic[0]=13; return;//13 렝徒藤속3 6 10
		case 23:pMapItem->tMagic[0]=40; return;//�餉璜梔�10 �餉璜梔�20 �餉璜梔�30
		case 24:pMapItem->tMagic[0]=40; return;//�餉璜梔�10 �餉璜梔�20 �餉璜梔�30
		case 25:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 26:pMapItem->tMagic[0]=13; return;//13 렝徒藤속3 6 10
		case 27:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		case 28:pMapItem->tMagic[0]=40; return;//�餉璜梔�10 �餉璜梔�20 �餉璜梔�30
		case 29:pMapItem->tMagic[0]=34; return;//묑샌제藤속10 묑샌제藤속20 묑샌제藤속30
		case 30:pMapItem->tMagic[0]=1; return;//愆��2 3 5
		default:
			pMapItem->tMagic[0]=0;return;
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	NPC Item을 맵에 떨군다.
//
void CNpc::GiveItemToMap(COM *pCom, int iItemNum, BOOL bItem, int iEventNum)
{
	int i, iRandom = 0;
	int iType = 0;
	BYTE tEBodySid = 0;

	CPoint pt;
	pt = FindNearRandomPointForItem(m_sCurX, m_sCurY);							// 현재 자기좌표를 제외한 24칸
	if(pt.x <= -1 || pt.y <= -1) return;
	if(pt.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || pt.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) return;

	ItemList *pMapItem = NULL;
	if(InterlockedCompareExchange((long*)&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, (long)1, (long)0) == (long)0)
	{
		pMapItem = new ItemList;

		if(!bItem)					// 돈일 경우
		{
			pMapItem->tType = TYPE_MONEY;
			pMapItem->dwMoney = iItemNum;

			pMapItem->uid[0] = m_iHaveItemUid[0].uid;
			pMapItem->uid[1] = m_iHaveItemUid[1].uid;
			pMapItem->uid[2] = m_iHaveItemUid[2].uid;

			pMapItem->SuccessRate[0] = (BYTE)m_iHaveItemUid[0].nDamage;
			pMapItem->SuccessRate[1] = (BYTE)m_iHaveItemUid[1].nDamage;
			pMapItem->SuccessRate[2] = (BYTE)m_iHaveItemUid[2].nDamage;
			pMapItem->dwTime = GetItemThrowTime();
		}
		else							// 아이템 목록일경우
		{
			if(iItemNum >= g_arItemTable.GetSize())
			{
				if(pMapItem) delete pMapItem;
				return; 
			}
			else
			{
				pMapItem->tType = TYPE_ITEM;
				pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
				pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
				pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
				pMapItem->sCount = 1;
				pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
				for(i = 0; i < MAGIC_NUM; i++) pMapItem->tMagic[i] = 0;	// 나중에 Magic Item 추가할 것
				pMapItem->tIQ = NORMAL_ITEM;
				pMapItem->iItemSerial = 0;

				pMapItem->uid[0] = m_iHaveItemUid[0].uid;				// 우선 순위
				pMapItem->uid[1] = m_iHaveItemUid[1].uid;
				pMapItem->uid[2] = m_iHaveItemUid[2].uid;

				pMapItem->SuccessRate[0] = (BYTE)m_iHaveItemUid[0].nDamage;	// 우선 순위 비율
				pMapItem->SuccessRate[1] = (BYTE)m_iHaveItemUid[1].nDamage;
				pMapItem->SuccessRate[2] = (BYTE)m_iHaveItemUid[2].nDamage;

				pMapItem->dwTime = GetItemThrowTime();
				//GetLocalTime(&pMapItem->ThrowTime);
			
				int iWear = g_arItemTable[iItemNum]->m_byWear;
				
				if(iWear >= 1 && iWear <= 5) 
				{
					iType = IsMagicItem(pCom, pMapItem, iItemNum);
					if(iType == MAGIC_ITEM)
					{
						pMapItem->tIQ = MAGIC_ITEM;	// 매직만 처리...
					}
					else if(iType == RARE_ITEM)
					{
						pMapItem->tIQ = RARE_ITEM;	// 래어만 처리...

// 						int n = pMapItem->tMagic[0] + pMapItem->tMagic[1] + pMapItem->tMagic[2] + pMapItem->tMagic[3];
// 						if(n > 500) {
// 							int iRandom = myrand(1, 100);
// 							//섐틔딜쭝왠齡
// 							if(iRandom < 30){
// 								pMapItem->tMagic[0] = 0;
// 							}
// 						}
						
					}
					else if(iType == EVENT_ITEM_MOON)	// 보름달
					{
						iItemNum = EVENTITEM_SID_MOON;
						pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
						pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
						pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
						pMapItem->sCount = 1;
						pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
						iWear = g_arItemTable[iItemNum]->m_byWear;
					}
					else if(iType == EVENT_ITEM_SONGPEON)	// 송편 또는 월병
					{
						/*
						if(m_byClassLevel < 11) iItemNum = EVENTITEM_SID_SONGPEON_01;
						else if(m_byClassLevel >= 11 && m_byClassLevel < 31) iItemNum = EVENTITEM_SID_SONGPEON_11;
						else if(m_byClassLevel >= 31 && m_byClassLevel < 51) iItemNum = EVENTITEM_SID_SONGPEON_31;
						else if(m_byClassLevel >= 51 && m_byClassLevel < 71) iItemNum = EVENTITEM_SID_SONGPEON_51;
						else if(m_byClassLevel >= 71) iItemNum = EVENTITEM_SID_SONGPEON_71;
						*/
						iItemNum = EVENTITEM_SID_SONGPEON_01;
						
						pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
						pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
						pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
						pMapItem->sCount = 1;
						pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
						iWear = g_arItemTable[iItemNum]->m_byWear;
					}
					else if(iType == EVENT_ITEM_BOX)	// 선물상자
					{
						iItemNum = EVENTITEM_SID_BOX;
						pMapItem->sLevel = g_arItemTable[iItemNum]->m_byRLevel;
						pMapItem->sSid = g_arItemTable[iItemNum]->m_sSid;
						pMapItem->sDuration = g_arItemTable[iItemNum]->m_sDuration;
						pMapItem->sCount = 1;
						pMapItem->sBullNum = g_arItemTable[iItemNum]->m_sBullNum;
						iWear = g_arItemTable[iItemNum]->m_byWear;
					}
				}
				////////////////////////////////////////////////////////////////////////墩�躊�
				else if(iItemNum==818 || iItemNum==733 || iItemNum==735 ){
					byte tMagic=0;
					iRandom = myrand(1, 9);
					switch(iRandom){
						case 1: tMagic=78;break;//렝徒5
						case 2: tMagic=107;break;//제좆5
						case 3: tMagic=108;break;//竟醴5
						case 4: tMagic=109;break;//츌쌥5
						case 5: tMagic=110;break;//例쁜5
                        //case 6: tMagic=111;break;//例제5
						case 6: tMagic=33;break;//쀼긁5
						case 7: tMagic=14;break;//침랬愆��5
						case 8: tMagic=6;break;//愆��5
						case 9: tMagic=31;break;//츱櫓5
					    default: tMagic=0;break;
					}
					pMapItem->tIQ = SET_ITEM;
					pMapItem->tMagic[0] =tMagic;
				}
				 //////////////////////////////////////////////////////////////////////////////
				// 악세사리 처리
				else if(iWear >= 6 && iWear <= 8)	// 看干딜쭝
				{
					pMapItem->tIQ = MAGIC_ITEM;	// 악세사리는 무조건 매직
					pMapItem->tMagic[0] = g_arItemTable[iItemNum]->m_bySpecial;
				}
				
				//else if(iItemNum==1043) //妗頓槿奈�ノ�5
				//{
				//	pMapItem->tIQ = 5;	
				//}
				//else if(iWear == 126) //뵈柯딜쭝....뵨橄昑踞샙.
				//{
				//	iRandom = myrand(1, 1000);
				//	for(i = 0; i < g_arEBodyTable.GetSize(); i++)
				//	{
				//		if(iRandom <= g_arEBodyTable[i]->m_sRandom) 
				//		{
				//			tEBodySid = g_arEBodyTable[i]->m_tSid;
				//			break;
				//		}	
				//	}
				//	pMapItem->tIQ = MAGIC_ITEM;	//
				//	pMapItem->tMagic[0] = tEBodySid;
				//}
				else if(iWear == 126) //뵈柯딜쭝....뵨橄昑踞샙. BOSS怜딜봤橄昑
				{
					if(  m_sEvent== 30007 ||  m_sEvent== 30009  )
					{
						byte tMagic=0;
					    iRandom = myrand(1, 7);
						switch(iRandom){
						case 1: tMagic=5;break; //5예
						case 2: tMagic=14;break;//姦렴2
						case 3: tMagic=16;break;//10제좆
						case 4: tMagic=22;break;//10츱櫓
						case 5: tMagic=23;break;//10쀼긁
						case 6: tMagic=24;break;//10츌쌥
						case 7: tMagic=27;break;//10例쁜
						default: tMagic=0;break;}
						
						pMapItem->tIQ = MAGIC_ITEM;	//
						pMapItem->tMagic[0] = tMagic;
					}else{

						iRandom = myrand(1, 1000);
						for(i = 0; i < g_arEBodyTable.GetSize(); i++)
						{
							if(iRandom <= g_arEBodyTable[i]->m_sRandom) 
							{
								tEBodySid = g_arEBodyTable[i]->m_tSid;
								break;
							}	
						}
						pMapItem->tIQ = MAGIC_ITEM;	//
						pMapItem->tMagic[0] = tEBodySid;
					}
				}
				
				else if(iWear==130)
				{
					shouhu_rand(pMapItem);

				}else if(iWear==143){//뼙柯
					byte tMagic=0;
					iRandom = myrand(1, 6);
					switch(iRandom){
						case 1: tMagic=3;break;
						case 2: tMagic=13;break;
						case 3: tMagic=23;break;
						case 4: tMagic=43;break;
						case 5: tMagic=53;break;
						case 6: tMagic=63;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
					pMapItem->tMagic[5]= 1;

				}else if(iItemNum==1051){//쏵뺏棘튬
					byte tMagic=0;
					iRandom = myrand(1, 3);
					switch(iRandom){
						case 1: tMagic=5;break;//15제
						case 2: tMagic=12;break;//15竟醴
						case 3: tMagic=6;break;//15츌쌥
				        
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==166){//넋埼엥딜쭝橄昑踞샙
					byte tMagic=0;
					iRandom = myrand(1, 44);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						case 4: tMagic=4;break;
						case 5: tMagic=5;break;
						case 6: tMagic=6;break;
						case 7: tMagic=7;break;
						case 8: tMagic=8;break;
						case 9: tMagic=9;break;
						case 10: tMagic=10;break;
						case 11: tMagic=11;break;
						case 12: tMagic=12;break;
						case 13: tMagic=13;break;
						case 14: tMagic=14;break;
						case 15: tMagic=15;break;
						case 16: tMagic=16;break;
						case 17: tMagic=17;break;
						case 18: tMagic=18;break;
						case 19: tMagic=19;break;
						case 20: tMagic=20;break;
						case 21: tMagic=21;break;
						case 22: tMagic=22;break;
						case 23: tMagic=23;break;
						case 24: tMagic=24;break;
						case 25: tMagic=25;break;
						case 26: tMagic=26;break;
						case 27: tMagic=27;break;
						case 28: tMagic=38;break;
						case 29: tMagic=29;break;
						case 30: tMagic=30;break;
						case 31: tMagic=31;break;
						case 32: tMagic=32;break;
						case 33: tMagic=33;break;
						case 34: tMagic=34;break;
						case 35: tMagic=35;break;
						case 36: tMagic=36;break;
						case 37: tMagic=37;break;
						case 38: tMagic=38;break;
						case 39: tMagic=39;break;
						case 40: tMagic=40;break;
						case 41: tMagic=41;break;
						case 42: tMagic=42;break;
						case 43: tMagic=43;break;
						case 44: tMagic=44;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==167){//�雍팠섣컨矩解瘍轢뉘踐鰐轍�
					byte tMagic=0;
					iRandom = myrand(1, 6);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						case 4: tMagic=4;break;
						case 5: tMagic=5;break;
						case 6: tMagic=6;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==168){//�雍팠섣컨國아�踞섦딜쭝橄昑
					byte tMagic=0;
					iRandom = myrand(1, 6);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						case 4: tMagic=4;break;
						case 5: tMagic=5;break;
						case 6: tMagic=6;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==169){//�雍팠섣컨矩輓롄轢뉘踐鰐轍�
					byte tMagic=0;
					iRandom = myrand(1, 6);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						case 4: tMagic=4;break;
						case 5: tMagic=5;break;
						case 6: tMagic=6;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==170){//샙솖맒숭鉤�に轢뉘踐鰐轍�
					byte tMagic=0;
					iRandom = myrand(1, 3);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==171){//샙솖맒숭쑨튬踞섦딜쭝橄昑
					byte tMagic=0;
					iRandom = myrand(1, 3);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==172){//샙솖맒숭욋땐踞섦딜쭝橄昑
					byte tMagic=0;
					iRandom = myrand(1, 3);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iWear==173){//샙솖맒숭콘좆譴옹踞섦딜쭝橄昑
					byte tMagic=0;
					iRandom = myrand(1, 3);
					switch(iRandom){
						case 1: tMagic=1;break;
						case 2: tMagic=2;break;
						case 3: tMagic=3;break;
						default: tMagic=0;break;
					}
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =tMagic;
				
				}else if(iItemNum==1178){   //돔뎐미땍橄昑
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =4;
				
				}else if(iItemNum==1179){  //샴밟미땍橄昑
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =5;
				
				}else if(iItemNum==987){
					pMapItem->tIQ = MAGIC_ITEM;	
					pMapItem->tMagic[0] =59;

				}
			}
		}		

		// 해당 유저에게 알린다.			
	//	pCom->DelThrowItem();
		pCom->SetThrowItem( pMapItem, pt.x, pt.y, m_ZoneIndex );

		::InterlockedExchange(&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, 0);
	}
}

//////////////////////////////////////////////////////////////////////////////////
//	현재 위치를 중심으로 25 셀중 아이템를 떨어질수있는 좌표를 램덤으로 생성
//
CPoint CNpc::FindNearRandomPoint(int x, int y)
{
	CPoint t;
	int i;
	int iX, iY;
	int rand_x = 1, rand_y = 1;

	MAP *pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return CPoint(-1, -1);
	if( !pMap->m_pMap ) return CPoint(-1, -1);

	int dir[25][2];

	//	X					Y
	dir[0][0]  =  0;		dir[0][1] =  0;		// 
	dir[1][0]  = -1;		dir[1][1] =  0;		// 
	dir[2][0]  = -1;		dir[2][1] =  1;		// 
	dir[3][0]  =  0;		dir[3][1] =  1;		// 
	dir[4][0]  =  1;		dir[4][1] =  1;		// 

	dir[5][0]  =  1;		dir[5][1] =  0;		// 
	dir[6][0]  =  1;		dir[6][1] = -1;		// 
	dir[7][0]  =  0;		dir[7][1] = -1;		// 
	dir[8][0]  = -1;		dir[8][1] = -1;		// 
	dir[9][0]  = -2;		dir[9][1] = -1;		// 

	dir[10][0] = -2;		dir[10][1] =  0;	// 
	dir[11][0] = -2;		dir[11][1] =  1;	// 
	dir[12][0] = -2;		dir[12][1] =  2;	// 
	dir[13][0] = -1;		dir[13][1] =  2;	// 
	dir[14][0] =  0;		dir[14][1] =  2;	// 

	dir[15][0] =  1;		dir[15][1] =  2;	// 
	dir[16][0] =  2;		dir[16][1] =  2;	// 
	dir[17][0] =  2;		dir[17][1] =  1;	// 
	dir[18][0] =  2;		dir[18][1] =  0;	// 
	dir[19][0] =  2;		dir[19][1] = -1;	// 

	dir[20][0] =  2;		dir[20][1] = -2;	// 
	dir[21][0] =  1;		dir[21][1] = -2;	// 
	dir[22][0] =  0;		dir[22][1] = -2;	// 
	dir[23][0] = -1;		dir[23][1] = -2;	// 
	dir[24][0] = -2;		dir[24][1] = -2;	// 

	rand_x = myrand(1, 8, TRUE);
	rand_y = myrand(0, 1, TRUE);

	iX = dir[rand_x][rand_y] + x;
	iY = dir[rand_x][rand_y] + y;

	rand_x = iX; rand_y = iY;
		
	if(rand_x >= pMap->m_sizeMap.cx || rand_x < 0 || rand_y >= pMap->m_sizeMap.cy || rand_y < 0) return CPoint(-1, -1);

	if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].m_lUser == 0)
	{
		if( IsMovable( rand_x, rand_y ) )
		{
//			if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].iIndex == -1) return CPoint( rand_x, rand_y );
			return CPoint( rand_x, rand_y );
		}
	}

	rand_x = x, rand_y = y;

	for( i = 1; i < 25; i++)
	{
		iX = rand_x + dir[i][0];
		iY = rand_y + dir[i][1];

		if( iX >= pMap->m_sizeMap.cx || iX < 0 || iY >= pMap->m_sizeMap.cy || iY < 0) continue;

		if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].m_lUser != 0) continue;	// 빈 맵인지 확인한다.

		if( IsMovable( iX, iY ) )
		{
//			if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].iIndex == -1) return CPoint( iX, iY );
			return CPoint( iX, iY );
		}
	}

	return CPoint(-1, -1);
}

CPoint CNpc::FindNearRandomPointForItem(int x, int y)
{
	CPoint t;
	int i;
	int iX, iY;
	int rand_x = 1, rand_y = 1;

	MAP *pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return CPoint(-1, -1);
	if( !pMap->m_pMap ) return CPoint(-1, -1);

	int dir[25][2];

	//	X					Y
	dir[0][0]  =  0;		dir[0][1] =  0;		// 
	dir[1][0]  = -1;		dir[1][1] =  0;		// 
	dir[2][0]  = -1;		dir[2][1] =  1;		// 
	dir[3][0]  =  0;		dir[3][1] =  1;		// 
	dir[4][0]  =  1;		dir[4][1] =  1;		// 

	dir[5][0]  =  1;		dir[5][1] =  0;		// 
	dir[6][0]  =  1;		dir[6][1] = -1;		// 
	dir[7][0]  =  0;		dir[7][1] = -1;		// 
	dir[8][0]  = -1;		dir[8][1] = -1;		// 
	dir[9][0]  = -2;		dir[9][1] = -1;		// 

	dir[10][0] = -2;		dir[10][1] =  0;	// 
	dir[11][0] = -2;		dir[11][1] =  1;	// 
	dir[12][0] = -2;		dir[12][1] =  2;	// 
	dir[13][0] = -1;		dir[13][1] =  2;	// 
	dir[14][0] =  0;		dir[14][1] =  2;	// 

	dir[15][0] =  1;		dir[15][1] =  2;	// 
	dir[16][0] =  2;		dir[16][1] =  2;	// 
	dir[17][0] =  2;		dir[17][1] =  1;	// 
	dir[18][0] =  2;		dir[18][1] =  0;	// 
	dir[19][0] =  2;		dir[19][1] = -1;	// 

	dir[20][0] =  2;		dir[20][1] = -2;	// 
	dir[21][0] =  1;		dir[21][1] = -2;	// 
	dir[22][0] =  0;		dir[22][1] = -2;	// 
	dir[23][0] = -1;		dir[23][1] = -2;	// 
	dir[24][0] = -2;		dir[24][1] = -2;	// 

	rand_x = myrand(1, 8, TRUE);
	rand_y = myrand(0, 1, TRUE);

	iX = dir[rand_x][rand_y] + x;
	iY = dir[rand_x][rand_y] + y;

	rand_x = iX; rand_y = iY;
		
	if(rand_x >= pMap->m_sizeMap.cx || rand_x < 0 || rand_y >= pMap->m_sizeMap.cy || rand_y < 0) return CPoint(-1, -1);

//	if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].m_lUser == 0)
//	{
//		if( IsMovable( rand_x, rand_y ) )
//		{
//			if(g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].iIndex == -1) return CPoint( rand_x, rand_y );
//		}
//	}

	if( g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].m_FieldUse == 0 )
	{
		if( g_zone[m_ZoneIndex]->m_pMap[rand_x][rand_y].iIndex == -1 ) return CPoint( rand_x, rand_y );
	}

	rand_x = x, rand_y = y;

	for( i = 1; i < 25; i++)
	{
		iX = rand_x + dir[i][0];
		iY = rand_y + dir[i][1];

		if( iX >= pMap->m_sizeMap.cx || iX < 0 || iY >= pMap->m_sizeMap.cy || iY < 0) continue;

//		if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].m_lUser != 0) continue;	// 빈 맵인지 확인한다.
		if( g_zone[m_ZoneIndex]->m_pMap[iX][iY].m_FieldUse != 0 ) continue;	// 사용중인지 체크.

//		if( IsMovable( iX, iY ) )
//		{
//			if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].iIndex == -1) return CPoint( iX, iY );
//		}
		if(g_zone[m_ZoneIndex]->m_pMap[iX][iY].iIndex == -1) return CPoint( iX, iY );
	}

	return CPoint(-1, -1);
}

///////////////////////////////////////////////////////////////////////////////////
//	x, y 가 움직일 수 있는 좌표인지 판단
//
BOOL CNpc::IsMovable(int x, int y)
{
	if(x < 0 || y < 0 ) return FALSE;

	if(!g_zone[m_ZoneIndex] ) return FALSE;
	if(!g_zone[m_ZoneIndex]->m_pMap) return FALSE;
	if(x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) return FALSE;
	if(g_zone[m_ZoneIndex]->m_pMap[x][y].m_bMove || g_zone[m_ZoneIndex]->m_pMap[x][y].m_lUser) return FALSE;

	return TRUE;
}
			
//////////////////////////////////////////////////////////////////////////////////////////////
//	NPC 공격 성공
//
void CNpc::SendAttackSuccess(COM *pCom, int tuid, BOOL bIsCritical, short sHP, short sMaxHP)
{
	if(pCom == NULL) return;

	CBufferEx TempBuf;
//	CByteArray arAction1;
//	CByteArray arAction2;
	
	TempBuf.Add(ATTACK_RESULT);
	//--------------------------------------------------
	//yskang 0.3 NPC는 크리티컬 공격이 없다.
	//--------------------------------------------------
	TempBuf.Add(ATTACK_SUCCESS);
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	TempBuf.Add(tuid);
	//----------------------------------------------------

/*	BYTE tAction1 = (BYTE)arAction1.GetSize();
	BYTE tAction2 = (BYTE)arAction2.GetSize();
	int i = 0;

	TempBuf.Add(tAction1);
	if(tAction1 > 0)
	{
		for(i = 0; i < arAction1.GetSize(); i++)
		{
			TempBuf.Add(arAction1[i]);
		}
	}
	TempBuf.Add(tAction2);
	if(tAction2 > 0)
	{
		for(i = 0; i < arAction2.GetSize(); i++)
		{
			TempBuf.Add(arAction2[i]);
		}
	}
	
*/	
	TempBuf.Add((int)sHP);
	TempBuf.Add((int)sMaxHP);

//	SendInsight(pCom, TempBuf, TempBuf.GetLength());
	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());
}

////////////////////////////////////////////////////////////////////////////
//	NPC 공격 미스
//
void CNpc::SendAttackMiss(COM *pCom, int tuid)
{
	CBufferEx TempBuf;
	
	TempBuf.Add(ATTACK_RESULT);
	TempBuf.Add(ATTACK_MISS);
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	TempBuf.Add(tuid);

//	SendInsight(pCom, TempBuf, TempBuf.GetLength());
	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());
}

/////////////////////////////////////////////////////////////////////////
//	NPC 의 무기 계열을 구한다.
//
BYTE CNpc::GetWeaponClass()
{
	BYTE tClass = BRAWL;

	switch (m_byClass)
	{
	case 1:
		tClass = BRAWL;
		break;
		
	case 2:
		tClass = STAFF;
		break;
		
	case 4:
		tClass = EDGED;
		break;
		
	case 8:
		tClass = FIREARMS;
		break;
	}

	return tClass;
}

/////////////////////////////////////////////////////////////////////////////////////
//	공격시마다 스킬성공 여부를 체크한다.
//
void CNpc::IsSkillSuccess(BOOL *bSuccess)
{
	int iOnCount = 0;
	int i = 0;
	
	for(i = 0; i < SKILL_NUM; i++) bSuccess[i] = FALSE;

	for(i = 0; i < SKILL_NUM; i++) 
	{
		if(m_NpcSkill[i].tOnOff == 1) iOnCount++;
	}

	int iRandom = XdY(1, 100);
	int iRate = 0;

	for(i = 0; i < SKILL_NUM; i++)
	{
		iRate = (int)((double)m_sWIS * 0.5 + m_NpcSkill[i].tLevel * 2 - iOnCount * 25 + 50 /* +Magic Bonus*/);		//!Magic

		if(iRandom <= iRate) 
		{
			bSuccess[i] = TRUE;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//	초기 일반 데미지를 얻는다.
//
int CNpc::GetNormalInitDamage()
{
	int nHit = 0;
	int nDamage = 0;
	int xyz = 0;

	xyz = XdY(m_byAX, m_byAY) + m_byAZ;

//  2002-10-17 by Youn Gyu
//	if(m_byClass == FIREARMS) nHit = (int)((double)m_sDEX/3 + 10.5);
//	else					  nHit = (int)((double)m_sSTR/2 + 0.5);

    if(nHit < 0) nHit = 0;

	nDamage = nHit + xyz;
	return nDamage;
}

///////////////////////////////////////////////////////////////////////////////////////
//	초기 크리티컬 데미지를 얻는다.
//
int CNpc::GetCriticalInitDamage(BOOL *bSuccessSkill)
{
	int nDamage = 0;
	int xyz = 0;

	xyz = XdY(m_byAX, m_byAY) + m_byAZ;
/*
	// 보스몹일때 기획에서 알려줄예정...
*/
	return nDamage;

}
///////////////////////////////////////////////////////////////////////////
//	냉기 데미지를 셋팅한다.
//
void CNpc::SetColdDamage()
{
	if(m_tAbnormalKind != ABNORMAL_BYTE_NONE) return;		// 이미 상태이상이 걸려있는 상태이면 리턴

	m_tAbnormalKind = ABNORMAL_BYTE_COLD;
	m_dwAbnormalTime = COLD_TIME;
	m_dwLastAbnormalTime = GetTickCount();
}

///////////////////////////////////////////////////////////////////////////
//	화염데미지를 셋팅한다.
//
void CNpc::SetFireDamage()
{
	if(m_tAbnormalKind != ABNORMAL_BYTE_NONE) return;		// 이미 상태이상이 걸려있는 상태이면 리턴

	m_tAbnormalKind = ABNORMAL_BYTE_FIRE;
	m_dwAbnormalTime = FIRE_TIME;
	m_dwLastAbnormalTime = GetTickCount();
}

/////////////////////////////////////////////////////////////////////////////
//	Damage 계산, 만약 m_sHP 가 0 이하이면 사망처리
//
BOOL CNpc::SetDamage(int nDamage, int uuid, COM *pCom)
{
	if(m_NpcState == NPC_DEAD) return TRUE;
	if(m_sHP <= 0) return TRUE;
	if(nDamage <= 0) return TRUE;

	if(m_tNpcType == NPCTYPE_GUARD) return TRUE;

	if(m_tGuildWar == GUILD_WAR_AFFTER)
	{
		if(m_tNpcType >= NPCTYPE_GUILD_NPC) return TRUE;
//		if(m_tNpcType == NPCTYPE_GUILD_NPC) return TRUE;
//		if(m_tNpcType == NPCTYPE_GUILD_GUARD) return TRUE;
//		if(m_tNpcType == NPCTYPE_GUILD_DOOR) return TRUE;
	}

	if(InterlockedCompareExchange((long*)&m_lDamage, (long)1, (long)0) == (long)0)
	{
		int i;
		int iLen = 0;
		int userDamage = 0;
		ExpUserList *tempUser = NULL;

		int uid = uuid - USER_BAND;

		USER* pUser = GetUser(pCom, uid);
														// 해당 사용자인지 인증
		if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) 
		{
			InterlockedExchange(&m_lDamage, (LONG)0);
			return TRUE;
		}

		iLen = strlen(pUser->m_strUserID);
		if(iLen <= 0 || iLen > CHAR_NAME_LENGTH) 
		{
			InterlockedExchange(&m_lDamage, (LONG)0);
			return TRUE;
		}

		if(m_tGuildWar == GUILD_WARRING)// 길드전이 벌어지는 상점의 상일 경우
		{
			if(m_tNpcType == NPCTYPE_GUILD_NPC)		// 상점과 공성전에서 NPC는 서로 다른 결과를 만들기 때문
			{
//				if(m_pGuardStore) { SetDamagedInGuildWar(nDamage, pUser); InterlockedExchange(&m_lDamage, (LONG)0); return TRUE; }
				if(m_pGuardFortress) { SetDamagedInFortressWar(nDamage, pUser); InterlockedExchange(&m_lDamage, (LONG)0); return TRUE; }
			}
			else if(m_tNpcType == NPCTYPE_GUILD_DOOR)	// 공성전을 위해 특별히	  
			{
				if(m_pGuardFortress) { SetDoorDamagedInFortressWar(nDamage, pUser); InterlockedExchange(&m_lDamage, (LONG)0); return TRUE; }
			}
			else if(m_tNpcType == NPCTYPE_GUILD_GUARD)	// 각 길드에 속한 경비병은 자기길드원으로부터 보호(?)받기위해
			{
				if(pUser->m_dwGuild > 0)
				{
/*					if(m_pGuardStore) 
					{ 
						if(m_pGuardStore->m_iGuildSid == pUser->m_dwGuild)
						{
							InterlockedExchange(&m_lDamage, (LONG)0);
							return TRUE; 
						}
*/					if(m_pGuardFortress) 
					{ 
						if(m_pGuardFortress->m_iGuildSid == pUser->m_dwGuild)
						{
							InterlockedExchange(&m_lDamage, (LONG)0); 
							return TRUE; 
						}
					}
				}
			}
		}

		//if ( pUser->m_byClass==1)
		// {

		//if( m_sEvent == NPC_EVENT_GREATE_MOP || m_sEvent== NPC_EVENT_MOP|| m_sEvent== 30009 || m_sEvent== 30007)		 //흔벎댔BOSS묑샌怜唐틱珂돨50%.
		//{
		//	nDamage = (int)( (double)nDamage * 0.8 );
		//}
		//else
		//	nDamage = (int)( (double)nDamage * 0.8 );

	 //   }

		userDamage = nDamage;
																
		if( (m_sHP - nDamage) < 0 ) userDamage = m_sHP;

		for(i = 0; i < NPC_HAVE_USER_LIST; i++)
		{
			if(m_DamagedUserList[i].iUid == uid)
			{
				if(strcmp(m_DamagedUserList[i].strUserID, pUser->m_strUserID) == 0) 
				{ 
					m_DamagedUserList[i].nDamage += userDamage; 
					goto go_result;
				}
			}
		}

		for(i = 0; i < NPC_HAVE_USER_LIST; i++)				// 인원 제한이 최종 대미지에 영향을 미치나?
		{
			if(m_DamagedUserList[i].iUid == -1)
			{
				if(m_DamagedUserList[i].nDamage <= 0)
				{
					strncpy(m_DamagedUserList[i].strUserID, pUser->m_strUserID, iLen);
					m_DamagedUserList[i].iUid = uid;
					m_DamagedUserList[i].nDamage = userDamage;
					m_DamagedUserList[i].bIs = FALSE;
					break;
				}
			}
		}

go_result:
		m_TotalDamage += userDamage;
		m_sHP -= nDamage;
		
		if( m_sHP <= 0 )
		{
			UserListSort();							// 아이템의 주인이 누군가

			m_ItemUserLevel = pUser->m_sLevel;
			m_sHP = 0;

			InterlockedExchange(&m_lKillUid, (LONG)uid);
			if(m_sPid==190)
				m_sEvent=2;
			// 죽은 몹이 퀘스트에 속한 이벤트 몹인경우 해당 이벤트를 실행
			if(m_sEvent > 0 && m_sEvent <= NPC_QUEST_MOP)	
				pUser->RunQuestEvent(this, m_sCurZ, m_sEvent);
			Dead();
			InterlockedExchange(&m_lDamage, (LONG)0);
			return FALSE;
		}

		ChangeTarget(pUser, pCom);

		InterlockedExchange(&m_lDamage, (LONG)0);
	}
	return TRUE;
}

BOOL CNpc::CheckNpcRegenCount()
{
/*	if(m_NpcState != NPC_DEAD) return FALSE;

	QueryPerformanceCounter((LARGE_INTEGER*)&m_RegenLastCount);

	if((m_RegenLastCount - m_RegenStartCount) >= g_Online_Update_Min_ticks)
	{
		m_RegenStartCount += g_Online_Update_Min_ticks;
		m_RegenCount += 10000;
	}

	if(m_RegenCount >= (DWORD)m_sRegenTime) return TRUE;
*/
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//	타겟이 둘러 쌓여 있으면 다음 타겟을 찾는다.
//
BOOL CNpc::IsSurround(int targetx, int targety)
{
	if(m_tNpcLongType) return FALSE;		//원거리는 통과

	for(int i = 0; i < (sizeof(surround_x) / sizeof(surround_x[0])); i++)		// 주변 8방향
	{
		if(IsMovable(targetx + surround_x[i], targety + surround_y[i])) return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	나를 공격한 유저를 타겟으로 삼는다.(기준 : 렙과 HP를 기준으로 선정)
//
void CNpc::ChangeTarget(USER *pUser, COM* pCom)
{
	if(pCom == NULL) return;
	int preDamage, lastDamage;
	int dist;

	if(m_byAX == 0 && m_byAZ == 0 ) return;		// 내가 공격력이 없으면 공격하지 않는다
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	if(pUser->m_bLive == USER_DEAD) return;
	if(pUser->m_tIsOP == 1) return;		// 운영자는 무시...^^
	if(pUser->m_bPShopOpen == TRUE) return;
    if(pUser->m_bSessionOnline == true)//밍膠꼇묑샌잼窟밈샙돨훙
		return;
	USER *preUser = NULL;
	preUser = GetUser(pCom, m_Target.id - USER_BAND);

	if(pUser == preUser) return;

	if(preUser != NULL && preUser->m_state == STATE_GAMESTARTED)
	{
		if(strcmp(pUser->m_strUserID, preUser->m_strUserID) == 0) return;
		
		preDamage = 0; lastDamage = 0;
		preDamage = GetFinalDamage(preUser, 0);
		lastDamage = GetFinalDamage(pUser, 0); 

		dist = abs(preUser->m_curx - m_sCurX) + abs(preUser->m_cury - m_sCurY);
		if(dist == 0) return;
		preDamage = (int)((double)preDamage/dist + 0.5);
		dist = abs(pUser->m_curx - m_sCurX) + abs(pUser->m_cury - m_sCurY);
		if(dist == 0) return;
		lastDamage = (int)((double)lastDamage/dist + 0.5);

		if(preDamage > lastDamage) return;
	}
		
	m_Target.id	= pUser->m_uid + USER_BAND;
	m_Target.x	= pUser->m_curx;
	m_Target.y	= pUser->m_cury;

/*	if(pUser->m_strUserID != NULL)
	{
		m_Target.nLen = strlen(pUser->m_strUserID);

		if(m_Target.nLen <= CHAR_NAME_LENGTH) strncpy(m_Target.szName, pUser->m_strUserID, m_Target.nLen);
		else								  ::ZeroMemory(m_Target.szName, sizeof(m_Target.szName));
	}
*/										// 어슬렁 거리는데 공격하면 바로 반격
	if(m_NpcState == NPC_STANDING || m_NpcState == NPC_MOVING)
	{									// 가까이 있으면 반격으로 이어지구
		if(IsCloseTarget(pUser, m_byRange) == TRUE)
		{
			m_NpcState = NPC_FIGHTING;
			NpcFighting(pCom);
		}
		else							// 바로 도망가면 좌표를 갱신하고 추적	
		{
			if(GetTargetPath(pCom) == TRUE)	// 반격 동작후 약간의 딜레이 시간이 있음	
			{
				m_NpcState = NPC_TRACING;
				NpcTracing(pCom);
			}
			else
			{
				ToTargetMove(pCom, pUser);
			}
		}
	}
//	else m_NpcState = NPC_ATTACKING;	// 한참 공격하는데 누가 방해하면 목표를 바꿈

	if(m_tNpcGroupType)					// 가족타입이면 시야안에 같은 타입에게 목표 지정
	{
		m_Target.failCount = 0;
		FindFriend();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	NPC 상태별로 분화한다.
//
void CNpc::NpcLive(COM *pCom)
{
	if(SetLive(pCom))
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
        if(m_sEvent == 30009)
		{
			if(m_sCurZ == 36)
			{
				CString strMsg;
				strMsg.Format("岬劤瓊刻：『 %s 』瞳 [ 든끝힛꿔 ] 岬劤죄!", m_strName);//무멩瓊刻
				pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE);
			}
			
			
			if(m_sCurZ == 16)
			{
				CString strMsg;
				strMsg.Format("岬劤瓊刻：『 %s 』瞳  [ �납易닌� ] 岬劤죄!", m_strName);//무멩瓊刻
				pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE);
			}
			if(m_sCurZ == 19)
			{
				CString strMsg;
				strMsg.Format("岬劤瓊刻：『 %s 』瞳  [ 戴힛떪氣 ] 岬劤죄!", m_strName);//무멩瓊刻
				pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE);
			}
			if(m_sCurZ == 400)
			{
				CString strMsg;
				strMsg.Format("岬劤瓊刻：『 %s 』瞳  [ 일빪뒈혐 ] 岬劤죄!", m_strName);//무멩瓊刻
				pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE);
			}
			if(m_sCurZ == 49)
			{
				CString strMsg;
				strMsg.Format("岬劤瓊刻：『 %s 』瞳  [ 땜�슴車� ] 岬劤죄!", m_strName);//무멩瓊刻
				pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE);
			}
			if(m_sCurZ == 12)
			{
				CString strMsg;
				strMsg.Format("岬劤瓊刻：『 %s 』瞳  [ 꿇覩힛꿔 ] 岬劤죄!", m_strName);//무멩瓊刻
				pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_ANNOUNCE);
			}
			
				
		}
	}
	else
	{
		m_NpcState = NPC_LIVE;
		m_Delay = m_sStandTime * 10;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	NPC가 서있는경우.
//
void CNpc::NpcStanding(COM *pCom)
{
	NpcTrace(_T("NpcStanding()"));

	if(RandomMove(pCom) == TRUE)
	{
		m_NpcState = NPC_MOVING;

		if( m_sStandTime > 2500 )
		{
			m_Delay = m_sStandTime - 2000;
		}
		else
		{
			m_Delay = m_sStandTime;
		}

//		m_Delay = m_sStandTime;
//		m_Delay = m_sSpeed;		 // 2001-09-01, jjs07 
		return;
	}

	m_NpcState = NPC_STANDING;

	m_Delay = m_sStandTime;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC가 이동하는 경우.
//
void CNpc::NpcMoving(COM *pCom)
{
	NpcTrace(_T("NpcMoving()"));

	if(m_sHP <= 0) 
	{
		Dead();
		return;
	}

	if(FindEnemy(pCom) == TRUE)		// 적을 찾는다. 
	{
		if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD) 
		{ 
			m_NpcState = NPC_FIGHTING; 
			m_Delay = 0; 
		}
		else 
		{ 
			m_NpcState = NPC_ATTACKING;
			m_Delay = m_sSpeed;
		}
		return;
	}

	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD) // 이동안하게...
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	if(IsMovingEnd())				// 이동이 끝났으면
	{
		m_NpcState = NPC_STANDING;

		//영역 밖에 있으면 서있는 시간을 짧게...
		if(IsInRange())	m_Delay = m_sStandTime;
		else m_Delay = m_sStandTime - 1000;

		if(m_Delay < 0) m_Delay = 0;

		return;
	}

	if(StepMove(pCom, 1) == FALSE)	// 한칸 움직임(걷는동작, 달릴때는 2칸)
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	CBufferEx TempBuf;

	CPoint t = ConvertToClient( m_sCurX, m_sCurY );		// 움직이려는 서버좌표가 클라이언트에서 못움직이는 좌표면 리턴

	if(IsStepEnd())	TempBuf.Add(MOVE_END_RESULT);
	else			TempBuf.Add(MOVE_RESULT);

	TempBuf.Add(SUCCESS);
	TempBuf.Add((int)(NPC_BAND + m_sNid));
	TempBuf.Add((short)t.x);
	TempBuf.Add((short)t.y);

	SendInsight(pCom, TempBuf, TempBuf.GetLength());

	m_Delay = m_sSpeed;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC가 공격하는경우.
//
void CNpc::NpcAttacking(COM *pCom)
{
	NpcTrace(_T("NpcAttacking()"));
	
	int ret = 0;

	if( m_byPsi > 0 && m_byPsi < g_arMonsterPsi.GetSize() )	// 마법이 있는 놈이라면...
	{
		CMonsterPsi* pMagic = g_arMonsterPsi[(int)m_byPsi];

		if( pMagic )
		{
			if( IsCloseTarget( pCom, pMagic->m_byRange ) )
			{
				m_NpcState = NPC_FIGHTING;
				m_Delay = 0;
				return;
			}
		}
	}

	if(IsCloseTarget(pCom, m_byRange))	// 공격할 수 있는만큼 가까운 거리인가?
	{
		m_NpcState = NPC_FIGHTING;
		m_Delay = 0;
		return;
	}

	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD)// 서있는 경비병일때 공격이 실패하면 잠깐 동안 쉬도록한다. 
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime/2;
		return;
	}

	if(GetTargetPath(pCom) == FALSE)
	{
		if(RandomMove(pCom) == FALSE)
		{
			m_NpcState = NPC_STANDING;
			m_Delay = m_sStandTime;
			return;
		}

		m_NpcState = NPC_MOVING;
		m_Delay = m_sSpeed;
		return;
	}

	m_NpcState = NPC_TRACING;
	m_Delay = 0;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC가 유저를 추적하는 경우.
//
void CNpc::NpcTracing(COM *pCom)
{
	NpcTrace(_T("NpcTracing()"));

	if(m_tNpcType == NPCTYPE_GUARD || m_tNpcType == NPCTYPE_GUILD_GUARD) return;

	if(GetUser(pCom, (m_Target.id - USER_BAND)) == NULL)	// Target User 가 존재하는지 검사
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	if( m_byPsi > 0 && m_byPsi < g_arMonsterPsi.GetSize() )	// 마법이 있는 놈이라면...
	{
		CMonsterPsi* pMagic = g_arMonsterPsi[(int)m_byPsi];

		if( pMagic )
		{
			if( IsCloseTarget( pCom, pMagic->m_byRange ) )
			{
				m_NpcState = NPC_FIGHTING;
				m_Delay = 0;
				return;
			}
		}
	}

	if(IsCloseTarget(pCom, m_byRange))						// 근접전을 벌일만큼 가까운 거리인가?
	{
		m_NpcState = NPC_FIGHTING;
		m_Delay = 0;
		return;
	}

	if(IsSurround(m_Target.x, m_Target.y))					// 목표 타겟이 둘러쌓여 있으면 다음 타겟을 찾는다.
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;
		return;
	}

	if(IsChangePath(pCom))									// 길찾기를 다시 할만큼 Target 의 위치가 변했는가?
	{
		if(ResetPath(pCom) == FALSE)// && !m_tNpcTraceType)
		{
			m_NpcState = NPC_STANDING;
			m_Delay = m_sStandTime;
			return;
		}
	}
	
	if(StepMove(pCom, 1) == FALSE)							// 한칸 움직임(걷는동작, 달릴때는 2칸)
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sStandTime;	
		return;
	}

	CBufferEx TempBuf;

	CPoint t = ConvertToClient( m_sCurX, m_sCurY );		// 움직이려는 서버좌표가 클라이언트에서 못움직이는 좌표면 리턴

	if(IsStepEnd())	TempBuf.Add(MOVE_END_RESULT);
	else			TempBuf.Add(MOVE_RESULT);

	TempBuf.Add(SUCCESS);
	TempBuf.Add((int)(NPC_BAND + m_sNid));
	TempBuf.Add((short)t.x);
	TempBuf.Add((short)t.y);

	SendInsight(pCom, TempBuf, TempBuf.GetLength());

	m_Delay = m_sSpeed;
}

/////////////////////////////////////////////////////////////////////////////
//	몹의 속도 변화를 알려 준다.
//
void CNpc::ChangeSpeed(COM *pCom, int delayTime)
{
/*	CBufferEx TempBuf;

	int tempTime = delayTime * NPC_TRACING_STEP;
	
	if(m_Delay > m_sSpeed) m_Delay = m_sSpeed;// 스탠딩 시간이 1000일경우 

	m_Delay = m_Delay + tempTime;			// 10, 50, 100단위로 증.감
	
	if(m_Delay <= 500) m_Delay = 500;		// 최소는 항상 500임	
											// 500을 100%이면 600은 80으로 감소	
	short step = 100 - (m_Delay - 500) * 10/50;

	TempBuf.Add(SET_SPEED_MONSTER);

	TempBuf.Add(m_sNid + NPC_BAND);
	TempBuf.Add(step);

		// NPC 주위의 유저에게 정보전송
	CPoint ptOld;
	if(SightRecalc(ptOld))
	{
		SendRemainSight(pCom, TempBuf, TempBuf.GetLength(), ptOld);
	}
	else SendInsight(pCom, TempBuf, TempBuf.GetLength());
*/
}

/////////////////////////////////////////////////////////////////////////////
//	NPC가 공격하는 경우.
//  唐침랬돨밍痰
void CNpc::NpcFighting(COM *pCom)
{
	NpcTrace(_T("NpcFighting()"));

	if(m_sHP <= 0) 
	{
		Dead();
		return;
	}

	m_dwDelayCriticalDamage = 0;

	int at_type_total3 = m_iNormalATRatio + m_iSpecialATRatio + m_iMagicATRatio;	
	int at_type[300], i;
	for( i = 0; i < m_iNormalATRatio; i++ ) at_type[i] = 1;
	int rand_index = m_iNormalATRatio;
	for( i = rand_index; i < rand_index+m_iSpecialATRatio; i++ )	at_type[i] = 2;
	rand_index += m_iSpecialATRatio;
	for( i = rand_index; i < rand_index+m_iMagicATRatio; i++ )	at_type[i] = 3;
	int at_type_rand = myrand( 0, at_type_total3);	

	if( at_type[at_type_rand] == 3 && m_byPsi > 0)
	{		
		m_Delay = PsiAttack( pCom );				
		if( m_Delay == -1 )
		{
			m_NpcState = NPC_ATTACKING;
			m_Delay = m_sSpeed;				
		}											
		return;
	}
	else if( at_type[at_type_rand] == 2 )
	{
			m_Delay = AreaAttack( pCom );		
			if( m_Delay == -1 )
			{
				m_NpcState = NPC_ATTACKING;
				m_Delay = m_sSpeed;
			}
			return;
	}else	m_Delay = Attack(pCom);		 	
}


/////////////////////////////////////////////////////////////////////////////
//	타겟과의 거리를 사정거리 범위로 유지한다.(셀단위)
//
void CNpc::NpcBack(COM *pCom)
{
	NpcTrace(_T("NpcBack()"));

	if(GetUser(pCom, (m_Target.id - USER_BAND)) == NULL)	// Target User 가 존재하는지 검사
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sSpeed;//STEP_DELAY;
		return;
	}

	if(IsMovingEnd())								// 이동이 끝났으면
	{
		m_Delay = m_sSpeed;
		NpcFighting(pCom);
		return;
	}
	
	if(StepMove(pCom, 1) == FALSE)					// 한칸 움직임(걷는동작, 달릴때는 2칸)
	{
		m_NpcState = NPC_STANDING;
		m_Delay = m_sSpeed;//STEP_DELAY;
		return;
	}

	m_Delay = m_sSpeed;//STEP_DELAY;
}

/////////////////////////////////////////////////////////////////////////////
//	다른 몹과의 연계를 위해서...
//
void CNpc::NpcStrategy(BYTE type)
{
	switch(type)
	{
	case NPC_ATTACK_SHOUT:
		m_NpcState = NPC_TRACING;
		m_Delay = m_sSpeed;//STEP_DELAY;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	시야 범위내의 내동료를 찾는다.
//
void CNpc::FindFriend()
{
	CNpc* pNpc = NULL;

	if(m_bySearchRange == 0) return;

	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - m_bySearchRange;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - m_bySearchRange;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + m_bySearchRange;
	max_y = m_sCurY + m_bySearchRange;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 1;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 1;

	int ix, iy;
	int target_uid;
	int uid;

	int tempLevel = 0, oldLevel = 1000;

	if(m_Target.id == -1) return;

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= NPC_BAND && target_uid < INVALID_BAND)
			{
				uid = target_uid - NPC_BAND;				
				pNpc = g_arNpc[uid];
				if(pNpc == NULL) continue;
									
				if(pNpc->m_tNpcGroupType && m_sNid != uid && pNpc->m_sFamilyType == m_sFamilyType)
				{
//					pNpc->m_Target.nLen = strlen(pNpc->m_Target.szName);	// 이미 목표가 있어서 이미 공격하고 있으면...
//					if(pNpc->m_Target.nLen > 0 && pNpc->m_NpcState == NPC_FIGHTING) continue;
					if(pNpc->m_Target.id >= 0 && pNpc->m_NpcState == NPC_FIGHTING) continue;

					pNpc->m_Target.id = m_Target.id;		// 같은 타입의 동료에게 도움을 요청한다.
					pNpc->m_Target.x = m_Target.x;			// 같은 목표를 공격하자고...
					pNpc->m_Target.y = m_Target.y;

/*					if(m_Target.szName != NULL)
					{
						pNpc->m_Target.nLen = strlen(m_Target.szName);

						if(pNpc->m_Target.nLen <= CHAR_NAME_LENGTH) strncpy(pNpc->m_Target.szName, m_Target.szName, pNpc->m_Target.nLen);
						else								  ::ZeroMemory(pNpc->m_Target.szName, sizeof(pNpc->m_Target.szName));
					}
*/					pNpc->m_Target.failCount = 0;
					pNpc->NpcStrategy(NPC_ATTACK_SHOUT);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	타겟점으로부터 최대한 멀리 떨어진 점을 찾는다.(주의 : 원거리는 속도가 빨라야 한다...안그러면 계속 거리를 유지하다 죽는수가 있다.)
//
BOOL CNpc::GetBackPoint(int &x, int &y)
{
	int ex = m_sCurX;
	int ey = m_sCurY;

	int dx = m_Target.x - m_sCurX;
	int dy = m_Target.y - m_sCurY;

	int min = ( abs(dx) + abs(dy) )/2;
	int max = m_byRange - min;
	int count = myrand(min, max);

	if(count <= 0) return FALSE;							// 0이면 원래 사정거리와 같다.
	if(count >= m_byRange && count > 2) count -= 1;			// 혹시나 몰라서 최대한 억제한다.

	if(dy > 0)
	{
		if(dx > 0)		{ ex -= count; ey -= count; }
		else if(dx < 0)	{ ex += count; ey -= count; }
		else			{ ey -= (count*2); }				// 홀수, 짝수를 맞춘다.
	}
	else if(dy < 0)
	{
		if(dx > 0)		{ ex -= count; ey += count; }
		else if(dx < 0)	{ ex += count; ey += count; }
		else			{ ey += (count*2); }
	}
	else
	{
		if(dx > 0)		{ ex -= (count*2); }
		else			{ ex += (count*2); }
	}

	if(IsMovable(ex, ey) == FALSE)							// 찾은 점이 움질수 없는 곳이라면 8방향으로 탐색
	{
		for(int i = 0; i < (sizeof(surround_x) / sizeof(surround_x[0])); i++)		// 주변 8방향
		{
			if(IsMovable(ex + surround_x[i], ey + surround_y[i])) 
			{
				x = ex; y = ey;
				return TRUE;
			}
		}
	}
	else
	{
		x = ex; y = ey;
		return TRUE;
	}

	return FALSE;									
}

/////////////////////////////////////////////////////////////////////////////
//	유저리스트를 초기화한다.
//
void CNpc::InitUserList()
{
	m_TotalDamage = 0;
	for(int i = 0; i < NPC_HAVE_USER_LIST; i++)
	{
		m_DamagedUserList[i].bIs = FALSE;
		m_DamagedUserList[i].iUid = -1;
		m_DamagedUserList[i].nDamage = 0;
		::ZeroMemory(m_DamagedUserList[i].strUserID, sizeof(m_DamagedUserList[i].strUserID));
	}
/*	int i;
									// 경험치 분배를 위해 관리하던 리스트
	for(i = 0; i < m_arDamagedUserList.GetSize(); i++)
	{
		if(m_arDamagedUserList[i])
		{
			delete m_arDamagedUserList[i];
			m_arDamagedUserList[i] = NULL;
		}
	}
	m_arDamagedUserList.RemoveAll();
*/
}

/////////////////////////////////////////////////////////////////////////////
//	해당 매직 속성이 아이템 계열 및 웨어정보가 맞는지 체크한다.
//
BOOL CNpc::CheckClassItem(int artable, int armagic)
{
	if(artable < 0 || artable >= g_arItemTable.GetSize()) return FALSE;
	if(armagic < 0 || armagic >= g_arMagicItemTable.GetSize()) return FALSE;
	if(armagic==148||armagic==149||armagic==150||armagic==151||armagic==152||armagic==153||armagic==156|| armagic==158 || armagic==162||armagic==164 || armagic==166){
		return FALSE;
	}
	int iWear;

	BYTE armWear = g_arItemTable[artable]->m_byWear;			// 아이템 계열 1: 무기 2~8 : 착용아이템
	BYTE tNeedClass = g_arItemTable[artable]->m_byClass;
	BYTE armMagic = g_arMagicItemTable[armagic]->m_tNeedClass;	// 매직속성 계열

	if(armMagic != 31/*15*/)
	{
		BYTE tTemp = 1;	
		BYTE tFire = 0;
		BYTE tEdge = 0;
		BYTE tStaff = 0;
		BYTE tBrawl = 0;
		BYTE tJudge = 0;

		tFire	 = tTemp & tNeedClass; tTemp = 2; 
		tEdge	 = tTemp & tNeedClass; tTemp = 4;
		tStaff	 = tTemp & tNeedClass; tTemp = 8;
		tJudge   = tTemp & tNeedClass; tTemp = 16;
		tBrawl	 = tTemp & tNeedClass;

		tFire = tFire & armMagic;
		tEdge = tEdge & armMagic;
		tStaff = tStaff & armMagic;
		tBrawl = tBrawl & armMagic;
		tJudge = tJudge & armMagic;

		tTemp = tFire^tEdge^tStaff^tBrawl^tJudge;
		if(!tTemp) return FALSE;
//		if(tNeedClass != armMagic) return FALSE;
	}

	iWear = g_arMagicItemTable[armagic]->m_tWearInfo;		// 웨어 정보로 잘못된 속성이 붙는것을 방지

	if(iWear == 0) return TRUE;
	else if(iWear == 1)											
	{														// 1번이면 무기류에 붙는다.
		if(armWear != 1) return FALSE;
		else return TRUE;
	}
	else if(iWear == 2)										// 2번이면 무기를 제외한 착용아이템에 붙는다.
	{
		if(armWear <= 1 || armWear >= 9) return FALSE;
		else return TRUE;
	}
	else return FALSE;
}

void CNpc::DeleteNPC()
{
	// 지금 몬스터를 지우지 않는다. 단지, 쓰레드 상에서 돌지 못하도록 막기만 한다.
	m_bFirstLive = FALSE;
	m_tNpcType = 2;

	// 나중에 기록하자.
}

//////////////////////////////////////////////////////////////////////////////////
//	최종 데미지를 구한다.
//
int CNpc::GetFinalDamage(USER *pUser, int type)
{
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return 0;

	int iInitDamage = GetNormalInitDamage();
	int iFinalDamage = 0, iFinalTemp = 0;
	
//	int iBasic = (int)((double)(pUser->m_sCON + pUser->m_DynamicUserData[MAGIC_CON_UP])/3 + 0.5);					// 기본멧집
	int iBasic = (int)((double)(pUser->m_sMagicCON + pUser->m_DynamicUserData[MAGIC_CON_UP] + (int)((double)pUser->m_DynamicEBodyData[EBODY_CON_TO_DEFENSE] / 100 * (double)pUser->m_sMagicCON) )/3 + 0.5);				// 기본멧집
	if(iBasic < 0) iBasic = 0;

	BYTE tWeaponClass = 255;
	BOOL bCanUseSkill = pUser->IsCanUseWeaponSkill(tWeaponClass);

	int		iDefense = 1;
	double	dIron = 0;
	double	dShield = 0;
	double	dGuard = 0;
	int		iCAttack = 0;
	double	dAdamantine = 0;
	double	dDefenseUP = 0;
	double	dABDefense = 0;

	int		iIronLevel = 0;
	int		iGuardLevel = 0;
	int		iVitalLevel = 0;
	int		iCounterAttackLevel = 0;
	int		iDefenseUPLevel = 0;
	int		iABDefenseLevel = 0;

	int		iIS = 0;
	int		iCA = 0;

	int i = 0;
	int iRandom = 0;
	int iSkillSid = 0;
	int tClass = tWeaponClass * SKILL_NUM;

	iDefense = pUser->GetDefense();							// 방어구

	//iDefense = (int)((double)iDefense * 0.8); //렝徒怜唐틱珂돨80


	if(tWeaponClass != 255)
	{
		for(i = tClass; i < tClass + SKILL_NUM; i++)	// IronSkill
		{
			iSkillSid = pUser->m_UserSkill[i].sSid;

			if(iSkillSid == SKILL_IRON)					// 1 index
			{
				iIronLevel = pUser->m_UserSkill[i].tLevel;
				if(iIronLevel < 0) iIronLevel = 0;
				
				// 아이템에 의한 스킬 변동 레벨
				if(iIronLevel >= 1) iIronLevel += pUser->m_DynamicUserData[g_DynamicSkillInfo[iSkillSid]]+ pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iIronLevel >= SKILL_LEVEL) iIronLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;

				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iIronLevel)) iIS = 1;
				
				// 아이언스킨에 의한 기본 멧집의 증가
				iBasic = (int)((double)iBasic * (1 + (double)(iIS * g_arSkillTable[iSkillSid]->m_arInc.GetAt(iIronLevel) / 100)) );
			}

			if(iSkillSid == SKILL_CRITICAL_GUARD)					// Critical Guard 11 index
			{
				iGuardLevel = pUser->m_UserSkill[i].tLevel;		
				if(iGuardLevel < 0) iGuardLevel = 0;
				
				// 아이템에 의한 스킬 변동 레벨
				if(iGuardLevel >= 1) iGuardLevel += pUser->m_DynamicUserData[g_DynamicSkillInfo[iSkillSid]]+ pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iGuardLevel >= SKILL_LEVEL) iGuardLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iGuardLevel))
				{				
					//dGuard = (double)(iInitDamage *g_arSkillTable[iSkillSid]->m_arInc.GetAt(iGuardLevel))/100.0;
				}
			}

			if(iSkillSid == SKILL_BACK_ATTACK )					// 반격 2 index
			{
				iCounterAttackLevel = pUser->m_UserSkill[i].tLevel;		
				if(iCounterAttackLevel < 0) iCounterAttackLevel = 0;
				
				// 아이템에 의한 스킬 변동 레벨
				if(iCounterAttackLevel >= 1) iCounterAttackLevel += pUser->m_DynamicUserData[g_DynamicSkillInfo[iSkillSid]] + pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iCounterAttackLevel >= SKILL_LEVEL) iCounterAttackLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;

				if(pUser->GetDistance(m_sCurX, m_sCurY, 1) == FALSE && pUser->m_dwFANTAnTime == 0 ) iCA = 0;
				else
				{ 
					iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
					if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iCounterAttackLevel)) iCA = 1;
				}
				
				  if(m_sEvent < 30000 ) //boss꼇럽샌  럽샌磵빱
				  {
					  iCAttack = (int)(iInitDamage * iCA * (double)((g_arSkillTable[iSkillSid]->m_arInc.GetAt(iCounterAttackLevel)) / 100.0) ); 
				  }
			}
			
			if(iSkillSid == SKILL_ABSOLUTE_DEFENSE)					// Absolute Defense 
			{
				iABDefenseLevel = pUser->m_UserSkill[i].tLevel;		
				if(iABDefenseLevel < 0) iABDefenseLevel = 0;
				
				// 아이템에 의한 스킬 변동 레벨
				if(iABDefenseLevel >= 1) iABDefenseLevel += pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iABDefenseLevel >= SKILL_LEVEL) iABDefenseLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iABDefenseLevel))
				{
					dABDefense = (double)(iDefense * (double)g_arSkillTable[iSkillSid]->m_arInc.GetAt(iABDefenseLevel ) /100.0);
				}
			}
			if(iSkillSid == SKILL_DEFENSE_UP)					// Defense up
			{
				iDefenseUPLevel = pUser->m_UserSkill[i].tLevel;		
				if(iDefenseUPLevel < 0) iDefenseUPLevel = 0;
				
				// 아이템에 의한 스킬 변동 레벨
				if(iDefenseUPLevel >= 1) iDefenseUPLevel += pUser->m_DynamicUserData[MAGIC_ALL_SKILL_UP];
				
				if(iDefenseUPLevel >= SKILL_LEVEL) iDefenseUPLevel = SKILL_LEVEL - 1;
				if(iSkillSid >= g_arSkillTable.GetSize()) continue;
				
				iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5);
				if(iRandom < g_arSkillTable[iSkillSid]->m_arSuccess.GetAt(iDefenseUPLevel))
				{
					dDefenseUP = (double)(iDefense * (double)g_arSkillTable[iSkillSid]->m_arInc.GetAt(iDefenseUPLevel)/100.0);
				}
			}
		}
	}

//	if(pUser->m_dwShieldTime != 0)	dShield = (double)(iInitDamage * 0.2);
	if(pUser->m_bNecklaceOfShield && pUser->m_dwShieldTime != 0)		dShield = (double)(iInitDamage * 0.3);
	else if(pUser->m_bNecklaceOfShield && pUser->m_dwBigShieldTime != 0)	dShield = (double)(iInitDamage * 0.35);
	else if(pUser->m_bNecklaceOfShield || pUser->m_dwShieldTime != 0 )	dShield = (double)(iInitDamage * 0.2);
    else if(pUser->m_dwBigShieldTime !=0 && !pUser->m_bNecklaceOfShield ) dShield = (double)(iInitDamage * 0.25);
	if(pUser->m_bNecklaceOfShield) pUser->SendAccessoriDuration(SID_NECKLACE_OF_SHIELD);
	

	/*if( pUser->m_dwAdamantineTime != 0 ) //꼇瞳셕炬 쏜먼빱뜀   속침랬殮쌈鞫刻橄昑
	{
		dAdamantine = (double)( (double)iDefense * 0.1 );
	}*/

	iDefense = (int)( iDefense + dABDefense + dDefenseUP + dAdamantine );

	iFinalDamage = (int)(iInitDamage - (iDefense + iBasic + dShield + dGuard)); 

	if(iFinalDamage < 0) iFinalDamage = 0;
	if(iFinalDamage <= 15)
	{
		iFinalTemp = iFinalDamage;
		iFinalDamage += (int)((double)iInitDamage * 0.2 + 1.5);	// 최소대미지를 최대 15으로 한다.
		if(iFinalDamage > 15) iFinalDamage = 15;
		iFinalDamage = max(iFinalDamage, iFinalTemp);
	}
	////럽샌磵빱
	// CString str;
	// str.Format( "밍膠럽샌宅콱�襁┌�%d", iFinalDamage);//럽샌磵빱
 //    pUser->SendEventMsg(str.GetBuffer(0));


	if(pUser->m_tAbnormalKind == ABNORMAL_BYTE_COLD) iFinalDamage += 10;


	if(iCAttack > 0 && type) 
	{
		iCA = iCAttack;		// 최종 반격 데미지

		if(iCA > 0)			// 반격이 0보다 클때 유저 리스트에 더하고 분배...
		{
//			pUser->SetCounterAttack(m_sNid, iCA);
			
			// alisia
			int iDamage = iCA;

			if( pUser->GetDistance(m_sCurX, m_sCurY, 2)  || pUser->m_dwFANTAnTime != 0 ) 

			{
				if( SetDamage(iDamage, (pUser->m_uid) + USER_BAND, pUser->m_pCom) == FALSE )
				{
					SendExpToUserList( pUser->m_pCom ); // 경험치 분배!!
					SendDead( pUser->m_pCom );

					if( m_NpcVirtualState == NPC_STANDING )
					{
						CheckMaxValue( pUser->m_dwXP, 1);	// 몹이 죽을때만 1 증가!	
						pUser->SendXP();
					}
				}
			     pUser->SendDamageNum(1,m_sNid + NPC_BAND,(short)iDamage);//화럽샌鞫鑒俚
			     pUser->SendNpcHP(m_sNid + NPC_BAND,m_sHP);	
			}

		}
	}

	return iFinalDamage;
}
//
int CNpc::SetHuFaFinalDamage(USER *pUser, int iDamage)
{
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) 
		return 0;

	if( SetDamage(iDamage, (pUser->m_uid) + USER_BAND, pUser->m_pCom) == FALSE )
	{
		SendExpToUserList( pUser->m_pCom ); 
		SendDead( pUser->m_pCom );

		if( m_NpcVirtualState == NPC_STANDING )
		{
			CheckMaxValue( pUser->m_dwXP, 1);	// 몹이 죽을때만 1 증가!	
			pUser->SendXP();
		}
	}


	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////
//	NPC 정보를 버퍼에 저장한다.
//  NPC친謹
void CNpc::FillNpcInfo(char *temp_send, int &index, BYTE flag)
{
	CPoint t;

	SetByte(temp_send, NPC_INFO, index );
	SetByte(temp_send, flag, index );
	SetShort(temp_send, m_sNid+NPC_BAND, index );

	if(flag != INFO_MODIFY)	return;

	SetShort(temp_send, m_sPid, index);
	SetVarString(temp_send, m_strName, _tcslen(m_strName), index);

	t = ConvertToClient(m_sCurX, m_sCurY);
	
	SetShort(temp_send, t.x, index);
	SetShort(temp_send, t.y, index);

	if(m_sHP <= 0) SetByte(temp_send, 0x00, index);
	else SetByte(temp_send, 0x01, index);

	SetByte(temp_send, m_tNpcType, index);
	SetInt(temp_send, m_sMaxHP, index);
	SetInt(temp_send, m_sHP, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetByte(temp_send , 0x00, index);
	SetShort(temp_send, m_sClientSpeed, index);

	SetByte(temp_send, m_byColor, index);

	if(m_tNpcType == NPCTYPE_GUILD_DOOR) 
	{
		SetShort(temp_send, m_sDimension, index);
	}
	SetShort(temp_send, m_sQuestSay, index);
}

///////////////////////////////////////////////////////////////////////////////////////
//	서버좌표를 클라이언트 좌표로 바꾼다.
//
CPoint CNpc::ConvertToClient(int x, int y)
{
	if(!g_zone[m_ZoneIndex]) return CPoint(-1,-1);

	int tempx, tempy;
	int temph = g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cy / 2 - 1;

	if( y >= g_zone[m_ZoneIndex]->m_sizeMap.cy || x >= g_zone[m_ZoneIndex]->m_sizeMap.cx ) return CPoint(-1,-1);

	tempx = x - temph + y;
	tempy = y - x + temph;

	return CPoint( tempx, tempy );
}

//////////////////////////////////////////////////////////////////////////////////////////
//	일정 영역의 유저에게 데이터를 보낸다.
//
void CNpc::SendToRange(COM *pCom, char *temp_send, int index, int min_x, int min_y, int max_x, int max_y)
{
/*
	if( index <= 0 || index >= SEND_BUF_SIZE ) return;

	SEND_DATA* pNewData = NULL;
	pNewData = new SEND_DATA;

	if( !pNewData ) return;

	pNewData->flag = SEND_RANGE;
	pNewData->len = index;

	::CopyMemory( pNewData->pBuf, temp_send, index );

	pNewData->uid = 0;
	pNewData->z = m_sCurZ;
	pNewData->rect.left		= min_x;
	pNewData->rect.right	= max_x;
	pNewData->rect.top		= min_y;
	pNewData->rect.bottom	= max_y;
	pNewData->zone_index = m_ZoneIndex;

	EnterCriticalSection( &(pCom->m_critSendData) );

	pCom->m_arSendData.Add( pNewData );

	LeaveCriticalSection( &(pCom->m_critSendData) );

	PostQueuedCompletionStatus( pCom->m_hSendIOCP, 0, 0, NULL );
*/

	if( index <= 0 || index >= SEND_BUF_SIZE ) return;

	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return;
	
	int tmin_x = min_x;		if(tmin_x < 0 ) tmin_x = 0;
	int tmax_x = max_x;		if(tmax_x >= pMap->m_sizeMap.cx ) tmax_x = pMap->m_sizeMap.cx - 1;
	int tmin_y = min_y;		if(tmin_y < 0 ) tmin_y = 0;
	int tmax_y = max_y;		if(tmax_y >= pMap->m_sizeMap.cy ) tmax_y = pMap->m_sizeMap.cy - 1;

	int temp_uid;
	USER* pUser = NULL;

	for( int i = tmin_x; i < tmax_x; i++ )
	{
		for( int j = tmin_y; j < tmax_y; j++ )
		{
			temp_uid = pMap->m_pMap[i][j].m_lUser;

			if(temp_uid < USER_BAND || temp_uid >= NPC_BAND) continue;
			else temp_uid -= USER_BAND;

			if( temp_uid >= 0 && temp_uid < MAX_USER )
			{
				pUser = pCom->GetUserUid(temp_uid);
				if ( pUser == NULL ) continue;
				
				if( pUser->m_state == STATE_GAMESTARTED )
				{
					if( pUser->m_curx == i && pUser->m_cury == j && pUser->m_curz == m_sCurZ )
					{
						Send( pUser, temp_send, index);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//	공격대상(Target)을 초기화 한다.
//
inline void CNpc::InitTarget()
{
	m_Target.id = -1;
	m_Target.x = 0;
	m_Target.y = 0;
	m_Target.failCount = 0;
//	m_Target.nLen = 0; 
//	::ZeroMemory(m_Target.szName, sizeof(m_Target.szName));
}

/////////////////////////////////////////////////////////////////////////////////////////
//	PathFind 를 수행한다.
//
BOOL CNpc::PathFind(CPoint start, CPoint end)
{
	m_bRandMove = FALSE;

	if(start.x < 0 || start.y < 0 || end.x < 0 || end.y < 0)
	{
		return FALSE;
	}

	int i, j;

	int min_x, max_x;
	int min_y, max_y;

	min_x = m_min_x;
	min_y = m_min_y;
	max_x = m_max_x;
	max_y = m_max_y;

	if(InterlockedCompareExchange((LONG*)&m_lMapUsed, (long)1, (long)0) == (long)0)
	{
		ClearPathFindData();

		m_vMapSize.cx = max_x - min_x + 1;		
		m_vMapSize.cy = max_y - min_y + 1;

	
/*		m_pMap = new int*[m_vMapSize.cx];

		for(i = 0; i < m_vMapSize.cx; i++)
		{
			m_pMap[i] = new int[m_vMapSize.cy];
		}
*/
		for(i = 0; i < m_vMapSize.cy; i++)
		{
			for(j = 0; j < m_vMapSize.cx; j++)
			{
				if( min_x+j == m_sCurX && min_y+i == m_sCurY )
				{
					m_pMap[j*m_vMapSize.cy + i] = 0;
//					m_pMap[j][i] = 0;
				}
				else
				{
					if(m_pOrgMap[min_x + j][min_y + i].m_bMove || m_pOrgMap[min_x + j][min_y + i].m_lUser != 0 )
					{
//						m_pMap[j][i] = 1;
						m_pMap[j*m_vMapSize.cy + i] = 1;
					}
					else
					{
//						m_pMap[j][i] = 0;
						m_pMap[j*m_vMapSize.cy + i] = 0;
					}
				}
			}
		}

		m_vStartPoint  = start;		m_vEndPoint = end;
		m_pPath = NULL;
		m_vPathFind.SetMap(m_vMapSize.cx, m_vMapSize.cy, m_pMap);

		m_pPath = m_vPathFind.FindPath(end.x, end.y, start.x, start.y);

		::InterlockedExchange(&m_lMapUsed, 0);

		if(m_pPath)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else return FALSE; 

}

/////////////////////////////////////////////////////////////////////////////
//	패스 파인드에서 찾은 경로를 다 이동 했는지 체크
//
BOOL CNpc::IsStepEnd()
{
	if( !m_pPath )	return FALSE;

	if( m_NpcState != NPC_MOVING && m_NpcState != NPC_TRACING ) return FALSE;

	if( !m_pPath->Parent )	return TRUE;

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	NPC 기본정보 초기화
//
void CNpc::Init()
{		
	int i, j;
	m_dLastFind = GetTickCount();
	m_Delay = 0;
	m_dwLastThreadTime = GetTickCount();

	if((m_sOrgX + m_sOrgY) % 2 != 0) m_sOrgX++;
	CPoint pt = ConvertToServer(m_sOrgX, m_sOrgY);

	if(pt.x == -1 || pt.y == -1)
	{
		CString szTemp;
		szTemp.Format(_T("Invalid NPC AXIS : Name = %s, x = %d, y = %d"), m_strName, m_sOrgX, m_sOrgY);
		AfxMessageBox(szTemp);
		InterlockedIncrement(&g_CurrentNPCError);
	}
	else
	{
		m_sTableOrgX = m_sOrgX = pt.x;
		m_sTableOrgY = m_sOrgY = pt.y;

		m_NpcVirtualState = NPC_STANDING;
		
		if(m_sGuild >= NPC_GUILDHOUSE_BAND)			// 도시를 기준으로 0번 도시, 1, 2 이런식으로 진행 m_sGuild = 10000(처음)
		{											// 0번도시 = 사나드 1번도시 = 포트시... 이건 10000번대임
			int index = 0;
			index = GetCityNumForVirtualRoom(m_sCurZ);
			
			if(index >= 0) g_arGuildHouseWar[index]->m_CurrentGuild.arNpcList.Add(m_sNid);

			m_NpcVirtualState = NPC_WAIT;
		}
		else if(m_tNpcType == NPCTYPE_MONSTER && m_sGuild >= FORTRESS_BAND && m_sGuild < NPC_GUILDHOUSE_BAND)	// 이건 1000번대임
		{
			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
				{
					g_arGuildFortress[i]->m_arViolenceNpcList.Add(m_sNid);

					m_NpcVirtualState = NPC_WAIT;

//					m_pGuardFortress = g_arGuildFortress[i];
					break;
				}
			}			
		}

		switch(m_tNpcType)
		{
		case NPCTYPE_GUILD_GUARD: case NPCTYPE_GUILD_NPC:
			{
				if(m_sGuild < FORTRESS_BAND)				// 상점에 속한 경비병이면
				{
					CStore *pStore = NULL;
					for(i = 0; i < g_arStore.GetSize(); i++)
					{
						if(g_arStore[i] == NULL) continue;

						pStore = g_arStore[i];					// 상점 포인터를 얻어온다.(길드전에서 쓰기위해)
						if(pStore->m_sStoreID == (short)m_sGuild) 
						{	
							pStore->m_arNpcList.Add(m_sNid);	// 내 아이디를 상점에 등록한다.
							m_pGuardStore = pStore;	
							break; 
						}
					}
				}
				else											// 요새에 속한 NPC이면...
				{
					for(i = 0; i < g_arGuildFortress.GetSize(); i++)
					{
						if(!g_arGuildFortress[i]) continue;

						if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
						{
							if(m_sEZone >= GUILD_FORTRESS_NPC_BAND)
							{
								for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
								{
									if(InterlockedCompareExchange((long*)&g_arGuildFortress[i]->m_arFortressTarget[j].lUsed, (long)1, (long)0) == (long)0)
									{
										g_arGuildFortress[i]->m_arFortressTarget[j].sTargertID = m_sNid;
										break;
									}
								}
							}
							else if(m_sEZone < GUILD_FORTRESS_NPC_BAND && m_sEZone >= GUILD_REPAIR_NPC_BAND)	// 수리될수 있는 문, 광선포 
							{
								g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
							}

							g_arGuildFortress[i]->m_arNpcList.Add(m_sNid);

							m_pGuardFortress = g_arGuildFortress[i];
							break;
						}
					}
				}
			}
			break;

		case NPCTYPE_GUILD_MARK:
			{
				if(m_sGuild >= 0 && m_sGuild < g_arGuildData.GetSize())
				{
					m_sPid = g_arGuildHouse[m_sGuild]->iGuild;		
					g_arGuildHouse[m_sGuild]->iMarkNpc = m_sNid;
					::ZeroMemory(m_strName, sizeof(m_strName));
				
					if( m_sPid >= 0 && m_sPid < g_arGuildData.GetSize())
					{										// 길드에 동기화를 할필요가 없다.
						if(g_arGuildData[m_sPid])
						{
							int nLen = 0;
							
							m_sMaxHP = g_arGuildData[m_sPid]->m_sVersion;
							nLen = strlen(g_arGuildData[m_sPid]->m_strGuildName);
							if(nLen > 0)
							{							
								strncpy(m_strName, g_arGuildData[m_sPid]->m_strGuildName, nLen);
							}
						}
					}				
				}
			}
			break;

		case NPCTYPE_GUILD_DOOR:
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						if(m_sEZone < GUILD_FORTRESS_NPC_BAND && m_sEZone >= GUILD_REPAIR_NPC_BAND)	// 수리될수 있는 문, 광선포 
						{
							g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
						}

						g_arGuildFortress[i]->m_arNpcList.Add(m_sNid);

						m_pGuardFortress = g_arGuildFortress[i];
						break;
					}
				}
			}
/*
		case NPCTYPE_FORTRESS:
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
						{
							if(InterlockedCompareExchange(&g_arGuildFortress[i]->m_arFortressTarget[j].lUsed, (LONG)1, (LONG)0) == 0)
							{
								g_arGuildFortress[i]->m_arFortressTarget[j].bChange = FALSE;
								g_arGuildFortress[i]->m_arFortressTarget[j].sTargertID = m_sNid;
								m_pGuardFortress = g_arGuildFortress[i];
								break;
							}
						}
					}
				}
			}
			break;
/*
		case NPCTYPE_REPAIR_GUARD:
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
						m_pGuardFortress = g_arGuildFortress[i];
						break;
					}
				}
			}
			break;
*/		}
/*
	else
	{
		m_sOrgX = pt.x;
		m_sOrgY = pt.y;

		m_NpcVirtualState = NPC_STANDING;

		if(m_sGuild >= NPC_GUILDHOUSE_BAND)			// 도시를 기준으로 0번 도시, 1, 2 이런식으로 진행 m_sGuild = 10000(처음)
		{											// 0번도시 = 사나드 1번도시 = 포트시...
			int index = 0;
			index = GetCityNumForVirtualRoom(m_sCurZ);
			
			g_arGuildHouseWar[index]->m_CurrentGuild.arNpcList.Add(m_sNid);

			m_NpcVirtualState = NPC_WAIT;
		}		
		else if(m_tNpcType == NPCTYPE_GUILD_GUARD || m_tNpcType == NPCTYPE_GUILD_NPC)
		{
			if(m_sGuild < FORTRESS_BAND)				// 상점에 속한 경비병이면
			{
				CStore *pStore = NULL;
				for(i = 0; i < g_arStore.GetSize(); i++)
				{
					if(g_arStore[i] == NULL) continue;

					pStore = g_arStore[i];					// 상점 포인터를 얻어온다.(길드전에서 쓰기위해)
					if(pStore->m_sStoreID == (short)m_sGuild) 
					{	
						pStore->m_arNpcList.Add(m_sNid);	// 내 아이디를 상점에 등록한다.
						m_pGuardStore = pStore;	
						break; 
					}
				}
			}
			else											// 요새에 속한 NPC이면...
			{
				for(i = 0; i < g_arGuildFortress.GetSize(); i++)
				{
					if(!g_arGuildFortress[i]) continue;

					if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
					{
						g_arGuildFortress[i]->m_arNpcList.Add(m_sNid);
						m_pGuardFortress = g_arGuildFortress[i];
						break;
					}
				}
			}
		}
		else if(m_tNpcType == NPCTYPE_GUILD_MARK)
		{
			if(m_sGuild >= 0 && m_sGuild < g_arGuildData.GetSize())
			{
				m_sPid = g_arGuildHouse[m_sGuild]->iGuild;		
				g_arGuildHouse[m_sGuild]->iMarkNpc = m_sNid;
				::ZeroMemory(m_strName, sizeof(m_strName));
			
				if( m_sPid >= 0 && m_sPid < g_arGuildData.GetSize())
				{										// 길드에 동기화를 할필요가 없다.
					if(g_arGuildData[m_sPid])
					{
						int nLen = 0;
						
						m_sMaxHP = g_arGuildData[m_sPid]->m_sVersion;
						nLen = strlen(g_arGuildData[m_sPid]->m_strGuildName);
						if(nLen > 0)
						{							
							strncpy(m_strName, g_arGuildData[m_sPid]->m_strGuildName, nLen);
						}
					}
				}				
			}
		}
		else if(m_tNpcType == NPCTYPE_FORTRESS)
		{
			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
				{
					for(j = 0; j < FORTRESS_TARGET_MAX_NUM; j++)
					{
						if(InterlockedCompareExchange(&g_arGuildFortress[i]->m_arFortressTarget[j].lUsed, (LONG)1, (LONG)0) == 0)
						{
							g_arGuildFortress[i]->m_arFortressTarget[j].bChange = FALSE;
							g_arGuildFortress[i]->m_arFortressTarget[j].sTargertID = m_sNid;
							m_pGuardFortress = g_arGuildFortress[i];
							break;
						}
					}
				}
			}
		}
		else if(m_tNpcType == NPCTYPE_REPAIR_GUARD)
		{
			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == (short)(m_sGuild))
				{
					g_arGuildFortress[i]->m_arRepairNpcList.Add(m_sNid);
					m_pGuardFortress = g_arGuildFortress[i];
					break;
				}
			}
		}
*/	}

	m_pOrgMap = g_zone[m_ZoneIndex]->m_pMap;	// MapInfo 정보 셋팅
}

int CNpc::GetCityNumForVirtualRoom(int zone)		// 지금은 도시번호지만 나중에 VirtualRoom이 계속 추가되면..
{													// 바꾸어야 된다. (int zone, int &curGuild)
	int nRet = -1;

	switch(zone)									// 추가할 예정임...
	{
	case 1005:										// 1004존 이면..
		nRet = SANAD;								// 도시는 사나드, m_CurrentGuild = 0번째
		break;

	default:
		break;
	}

	return nRet;
}

////////////////////////////////////////////////////////////////////////////////////
//	Client 좌표를 서버좌표로 변환한다
//
CPoint CNpc::ConvertToServer(int x, int y)
{
	if(!g_zone[m_ZoneIndex]) return CPoint(-1,-1); 

	int tempx, tempy;
	int temph = g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cy / 2 - 1;

	if( y >= g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cy || x >= g_zone[m_ZoneIndex]->m_vMoveCell.m_vDim.cx ) return CPoint(-1,-1);

	if( (x+y)%2 == 0 )
	{
		tempx = temph - ( y / 2 ) + ( x / 2 );

		if( x % 2 ) tempy = ( y / 2 ) + ( ( x / 2 ) + 1 );
		else        tempy = ( y / 2 ) + ( x / 2 );

		return CPoint( tempx, tempy );
	}
	else return CPoint(-1,-1);
}

////////////////////////////////////////////////////////////////////////////////////
//	디버깅을 위해 NPC 정보를 TRACE 한다.
//
void CNpc::NpcTrace(TCHAR *pMsg)
{
	if(g_bDebug == FALSE) return;

	CString szMsg = _T("");
	CPoint pt = ConvertToClient(m_sCurX, m_sCurY);
	szMsg.Format(_T("%s : uid = %d, name = %s, xpos = %d, ypos = %d\n"), pMsg, m_sNid, m_strName, pt.x, pt.y);
	TRACE(szMsg);
}

///////////////////////////////////////////////////////////////////////////////////
//	공격을 당했을때 패스파인딩에 실패하면 유저에게 가까운쪽으로 움직인다.
//
void CNpc::ToTargetMove(COM *pCom, USER *pUser)
{
	if(!pCom) return;
	if(!pUser) return;
	if(!g_zone[m_ZoneIndex]) return;

	int xx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int yy[] = {0, -1, -1, -1, 0, 1, 1, 1};

	CPoint ptUser = ConvertToClient(pUser->m_curx, pUser->m_cury);

	struct _min
	{
		int x, y;
		int value;
	}min;

	int minindex;
	int i, j;

	int dx, dy;
	CPoint ptNew;
	int max_dist;
/*
	int test1[8], test2[8];

	for(i = 0; i < 8; i++)
	{
		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);
		dx = abs(ptUser.x - ptNew.x);
		dy = abs(ptUser.y - ptNew.y);
		test1[i] = dx + dy;
	}
*/	
	for(i = 0; i < sizeof(xx)/sizeof(xx[0]) - 1; i++)
	{
		minindex = i;
		
		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);

		if(ptNew.x <= -1 || ptNew.y <= -1) continue;
		if(ptNew.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || ptNew.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) continue;

		dx = abs(ptUser.x - ptNew.x);
		dy = abs(ptUser.y - ptNew.y);
		max_dist = dx + dy;

		min.value = max_dist;
		min.x = xx[i];
		min.y = yy[i];

		for(j = i + 1; j < sizeof(xx)/sizeof(xx[0]); j++)
		{
			ptNew = ConvertToClient(m_sCurX + xx[j], m_sCurY + yy[j]);

			if(ptNew.x <= -1 || ptNew.y <= -1) continue;
			if(ptNew.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || ptNew.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) continue;

			dx = abs(ptUser.x - ptNew.x);
			dy = abs(ptUser.y - ptNew.y);
			max_dist = dx + dy;

			if(min.value > max_dist)
			{
				min.value = max_dist;
				min.x = xx[j];
				min.y = yy[j];
				minindex = j;
			}
		}

		xx[minindex] = xx[i];
		yy[minindex] = yy[i];

		xx[i] = min.x;
		yy[i] = min.y;
	}
/*
	for(i = 0; i < 8; i++)
	{
		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);
		dx = abs(ptUser.x - ptNew.x);
		dy = abs(ptUser.y - ptNew.y);
		test2[i] = dx + dy;
	}
*/
	MAP* pMap = g_zone[m_ZoneIndex];
	CPoint ptPre(m_sCurX, m_sCurY);
	int will_x, will_y;
	BOOL bMove = FALSE;
	int new_dist = 0, cur_dist = 0;

	CPoint ptCurr = ConvertToClient(m_sCurX, m_sCurY);
	cur_dist = abs(ptUser.x - ptCurr.x) + abs(ptUser.y - ptCurr.y);

	for(i = 0; i < sizeof(xx)/sizeof(xx[0]); i++)
	{
		will_x = m_sCurX + xx[i];
		will_y = m_sCurY + yy[i];

		ptNew = ConvertToClient(m_sCurX + xx[i], m_sCurY + yy[i]);
		new_dist = abs(ptUser.x - ptNew.x) + abs(ptUser.y - ptNew.y);

		if(new_dist > cur_dist) continue;

		if(will_x <= -1 || will_y <= -1) continue;
		if(will_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || will_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) continue;

		if(pMap->m_pMap[will_x][will_y].m_bMove != 0 || pMap->m_pMap[will_x][will_y].m_lUser != 0)
		{
			continue;
		}
		else
		{
			if(InterlockedCompareExchange((LONG*)&m_pOrgMap[will_x][will_y].m_lUser,
				(long)m_pOrgMap[m_sCurX][m_sCurY].m_lUser, (long)0) == (long)0)
			{
				::InterlockedExchange(&m_pOrgMap[m_sCurX][m_sCurY].m_lUser, 0);
				m_sCurX = will_x;
				m_sCurY = will_y;
				SightRecalc(pCom);
				bMove = TRUE;
				break;
			}
			else continue;
		}
	}

	if(!bMove) return;

	CBufferEx TempBuf;
	CPoint t = ConvertToClient(m_sCurX, m_sCurY);		// 움직이려는 서버좌표가 클라이언트에서 못움직이는 좌표면 리턴
	if(t.x <= -1 || t.y <= -1) return;

	TempBuf.Add(MOVE_RESULT);

	TempBuf.Add(SUCCESS);
	TempBuf.Add((int)(NPC_BAND + m_sNid));
	TempBuf.Add((short)t.x);
	TempBuf.Add((short)t.y);

	SendInsight(pCom, TempBuf, TempBuf.GetLength());

	m_Delay = m_sSpeed;
}



void CNpc::EventNpcInit(int x, int y)
{
	m_dwLastThreadTime = GetTickCount();

	m_sOrgX = x;
	m_sOrgY = y;

	m_pOrgMap = g_zone[m_ZoneIndex]->m_pMap;	// MapInfo 정보 셋팅

	m_Delay = 0;
}

///////////////////////////////////////////////////////////////////////////////////
//	길드전을 위해 타입을 바꾼다. 
//
void CNpc::SetGuildType(COM *pCom)
{
/*	int modify_index = 0;
	char modify_send[2048];	

	::ZeroMemory(modify_send, sizeof(modify_send));

	if(m_tGuildWar == GUILD_WARRING)
	{
		m_tNpcAttType = 1;
		if(m_tNpcType == NPCTYPE_GUARD) m_tNpcType = NPCTYPE_GUILD_GUARD;
		else if(m_tNpcType == NPCTYPE_NPC) m_tNpcType = NPCTYPE_GUILD_NPC;

		// 유저에게 NPC 정보전송...
		FillNpcInfo(modify_send, modify_index, INFO_MODIFY);
		SendInsight(pCom, modify_send, modify_index);
	}
	else if(m_tGuildWar == GUILD_WAR_AFFTER)
	{
		m_tNpcAttType = 1;
		if(m_tNpcType == NPCTYPE_GUILD_GUARD) m_tNpcType = NPCTYPE_GUARD;
		else if(m_tNpcType == NPCTYPE_GUILD_NPC) m_tNpcType = NPCTYPE_NPC;

		FillNpcInfo(modify_send, modify_index, INFO_MODIFY);
		SendInsight(pCom, modify_send, modify_index);
	}
*/
}

void CNpc::SetDamagedInGuildWar(int nDamage, USER *pUser)// COM *pCom)
{
	int i, j;
	BOOL flag = FALSE;

	CNpc *pNpc = NULL;
//	int uid = uuid - USER_BAND;
//	USER* pUser = GetUser(pCom, uid);
														// 길드전을 신청한 길드인지 판단.
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	if(pUser->m_dwGuild <= 0 || pUser->m_tGuildWar == GUILD_WAR_AFFTER) return;
	if(pUser->m_dwGuild == m_pGuardStore->m_iGuildSid) return;	// 방어측이 고의로 공격하는것을 방지한다.

	if(m_pGuardStore->m_lUsed == 0) return;				// 길드전이 끝났다.

	for(j = 0; j < GUILD_ATTACK_MAX_NUM; j++)
	{
		if(pUser->m_dwGuild != m_pGuardStore->m_arAttackGuild[j]) continue;

		m_sHP -= nDamage;
		if( m_sHP <= 0 )								// 여기에서 길드전이 끝난다.
		{
			m_sHP = m_sMaxHP;
			if(InterlockedCompareExchange((LONG*)&m_pGuardStore->m_lUsed, (long)0, (long)1) == (long)1)
			{											// 1에서 0으로 만들고 해당 상점전쟁은 끝났음을 알린다.
				if(pUser->StoppingTheGuildWar(m_pGuardStore))
				{										// 해당 NPC에게 알려준다.
					for(i =0; i < m_pGuardStore->m_arNpcList.GetSize(); i++)
					{
						pNpc = GetNpc(m_pGuardStore->m_arNpcList[i]);
						if(pNpc) 
						{
							pNpc->m_tGuildWar = GUILD_WAR_AFFTER;
							pNpc->m_tNpcAttType = 0;
						}
					}
					m_tGuildWar = GUILD_WAR_AFFTER;
					flag = TRUE;
					break;
				}
			}
		}
	}

	if(flag)
	{
		for(j = 0; j < GUILD_ATTACK_MAX_NUM; j++)
		{
			m_pGuardStore->m_arAttackGuild[j] = 0;
		}
	}

	return;
}

void CNpc::Send(USER *pUser, TCHAR *pBuf, int nLength)
{
	if ( !pUser ) return;

	pUser->Send( pBuf, nLength );
}

///////////////////////////////////////////////////////////////////////////////////
//	임시 이벤트 코드임 (기간 : 2001년 12월 29일 ~~ 2002년 1월 2일)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
void CNpc::GiveEventItemToUser(USER *pUser)
{
	return;

	BOOL bFlag = FALSE;

	int iEventItemSid = 0;
	int iEventNum = -1;
	int iEvent = 0;
	int iSlot = 0;
	
	int j;

	SYSTEMTIME gTime;
	GetLocalTime(&gTime);
//	if(gTime.wYear == 2002 && gTime.wDay >= 2) return;

//	if(gTime.wMonth != 2) return;					// 2월 설날용 이벤트
	if(gTime.wDay < 7 || gTime.wDay > 13) return;// 8일부터 13일까지	

	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	
	if(abs(m_byClassLevel - pUser->m_sLevel) > 25)
	{
		if(m_byClassLevel < pUser->m_sLevel) return;
	}

	iEventNum = GetEventItemNum(pUser->m_pCom);

	if(iEventNum < 0) return;
	
	int type = (int)g_arAddEventItemTable[iEventNum]->m_tType;
	if(type < 100 || type > 255) return;

	if(!UpdateEventItem(iEventNum)) 
	{
		g_arAddEventItemTable[iEventNum]->m_tEnd = 0;
		return;
	}

	CString strMsg = _T("");

	iSlot = pUser->GetEmptySlot(INVENTORY_SLOT);

	if(iSlot != -1)
	{
		if(NPC_EVENT_ITEM >= g_arItemTable.GetSize())
		{
			int ttt = 0;
		}
		if(pUser->m_iMaxWeight >= pUser->m_iCurWeight + g_arItemTable[NPC_EVENT_ITEM]->m_byWeight) bFlag = TRUE;
	}

	switch(type)
	{
/*	case 1:
		if(bFlag) { iEvent = EVENT_SP1_ITEM; strMsg.Format("현재 %s님께서 백화점 상품권를 얻으셨습니다.", pUser->m_strUserID); }
		else      iEvent = 1001;
		break;
	case 2:
		if(bFlag) { iEvent = EVENT_SP2_ITEM; strMsg.Format("현재 %s님께서 문화 상품권를 얻으셨습니다.", pUser->m_strUserID); }
		else      iEvent = 1002;
		break;
	case 3:
		if(bFlag) { iEvent = EVENT_DEF_ITEM; strMsg.Format("현재 %s님께서 방어구 교환권를 얻으셨습니다.", pUser->m_strUserID); }
		else      iEvent = 1003;
		break;
	case 4:
		if(bFlag) { iEvent = EVENT_ATT_ITEM; strMsg.Format("현재 %s님께서 무기 교환권를 얻으셨습니다.", pUser->m_strUserID); }
		else      iEvent = 1004;
		break;
	case 5:
		if(bFlag) { iEvent = EVENT_POT_ITEM; strMsg.Format("현재 %s님께서 물약 교환권를 얻으셨습니다.", pUser->m_strUserID); }
		else      iEvent = 1005;
		break;
*/
	case EVENT_ATT7_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT7_ITEM; strMsg.Format(IDS_EVENT_ATT7_ITEM, pUser->m_strUserID); }
		else      iEvent = 1001;
		break;
	case EVENT_DEF7_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF7_ITEM; strMsg.Format(IDS_EVENT_DEF7_ITEM, pUser->m_strUserID); }
		else      iEvent = 1002;
		break;
	case EVENT_ATT6_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT6_ITEM; strMsg.Format(IDS_EVENT_ATT6_ITEM, pUser->m_strUserID); }
		else      iEvent = 1003;
		break;
	case EVENT_DEF6_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF6_ITEM; strMsg.Format(IDS_EVENT_DEF6_ITEM, pUser->m_strUserID); }
		else      iEvent = 1004;
		break;
	case EVENT_ATT_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT_ITEM; strMsg.Format(IDS_EVENT_ATT5_ITEM, pUser->m_strUserID); }
		else      iEvent = 1005;
		break;
	case EVENT_DEF_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF_ITEM; strMsg.Format(IDS_EVENT_DEF5_ITEM, pUser->m_strUserID); }
		else      iEvent = 1006;
		break;
	case EVENT_ATT4_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT4_ITEM; strMsg.Format(IDS_EVENT_ATT4_ITEM, pUser->m_strUserID); }
		else      iEvent = 1007;
		break;
	case EVENT_DEF4_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF4_ITEM; strMsg.Format(IDS_EVENT_DEF4_ITEM, pUser->m_strUserID); }
		else      iEvent = 1008;
		break;
	case EVENT_ATT3_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_ATT3_ITEM; strMsg.Format(IDS_EVENT_ATT3_ITEM, pUser->m_strUserID); }
		else      iEvent = 1009;
		break;
	case EVENT_DEF3_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_DEF3_ITEM; strMsg.Format(IDS_EVENT_DEF3_ITEM, pUser->m_strUserID); }
		else      iEvent = 1010;
		break;

	case EVENT_INIT_STAT_ITEM:
		if(bFlag) { iEventItemSid = NPC_EVENT_INIT_STAT; iEvent = EVENT_INIT_STAT_ITEM; strMsg.Format(IDS_EVENT_RESET_STAT, pUser->m_strUserID); }
		else      iEvent = 1011;
		break;

	case EVENT_USER_GAME_TIME:
		if(bFlag) { iEventItemSid = NPC_EVENT_ITEM; iEvent = EVENT_USER_GAME_TIME; strMsg.Format(IDS_EVENT_PERSONAL, pUser->m_strUserID); }
		else      iEvent = 1012;
		break;
		break;
	default:
		return;
		break;
	}

	if(bFlag)								// 자동으로 인벤에 찾아서 들어간다.
	{
		if(iEventItemSid == NPC_EVENT_ITEM || iEventItemSid == NPC_EVENT_INIT_STAT)
		{
			pUser->m_UserItem[iSlot].tType = TYPE_ITEM;
			pUser->m_UserItem[iSlot].sLevel = g_arItemTable[iEventItemSid]->m_byRLevel;
			pUser->m_UserItem[iSlot].sSid = g_arItemTable[iEventItemSid]->m_sSid;
			pUser->m_UserItem[iSlot].sCount = 1;
			pUser->m_UserItem[iSlot].sDuration = g_arItemTable[iEventItemSid]->m_sDuration;
			pUser->m_UserItem[iSlot].sBullNum = g_arItemTable[iEventItemSid]->m_sBullNum;
			pUser->m_UserItem[iSlot].tIQ = (BYTE)iEvent;
			pUser->m_UserItem[iSlot].iItemSerial = 0;

			SetISerialToItem(&pUser->m_UserItem[iSlot], iEventNum);
/*			for(j = 0; j < MAGIC_NUM; j++)
			{
				pUser->m_UserItem[iSlot].tMagic[j] = 0;
				pUser->m_UserItem[iSlot].tMagic[j] = tSerial[j];//g_arAddEventItemTable[iEventNum]->m_strSerialNum[j];
			}
*/
			CBufferEx TempBuf;

			TempBuf.Add(ITEM_LOAD_RESULT);
			TempBuf.Add(SUCCESS);
			TempBuf.Add((BYTE)0x01);

			TempBuf.Add((BYTE)iSlot);
			TempBuf.Add(pUser->m_UserItem[iSlot].sLevel);
			TempBuf.Add(pUser->m_UserItem[iSlot].sSid);
			TempBuf.Add(pUser->m_UserItem[iSlot].sDuration);
			TempBuf.Add(pUser->m_UserItem[iSlot].sBullNum);
			TempBuf.Add(pUser->m_UserItem[iSlot].sCount);
			for(j = 0; j < MAGIC_NUM; j++) TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tMagic[j]);

			TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tIQ);

			pUser->Send(TempBuf, TempBuf.GetLength());

			pUser->m_iCurWeight += g_arItemTable[iEventItemSid]->m_byWeight;
			pUser->GetRecoverySpeed();			// 아이템 무게에 변동이 생기면 회복속도 변환

			pUser->m_pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_NORMAL);
//			pUser->m_pCom->Announce(strMsg.GetBuffer(strMsg.GetLength()), SYSTEM_NORMAL);
		}
		return;
	}
											// 인벤넣기에 실패하면 맵에 셋팅
	GiveItemToMap(pUser->m_pCom, iEvent, TRUE, iEventNum);		// 이벤트 아이템
}

///////////////////////////////////////////////////////////////////////////////////
//	이벤트 코드임 (기간 : 2002년 4월 8일 ~~ 2002년 4월 13일)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
void CNpc::SetISerialToItem(ItemList *pItem, int iEventSid)
{
	int i, j = 0;
	TCHAR strTemp[3];

	if(!pItem) return;
	if(iEventSid < 0 || iEventSid >= g_arAddEventItemTable.GetSize()) return;

	for(i = 0; i < MAGIC_NUM; i++)
	{	
		::ZeroMemory(strTemp, sizeof(strTemp));
		strncpy(strTemp,g_arAddEventItemTable[iEventSid]->m_strSerialNum+j, 3);

		pItem->tMagic[i] = 0;
		pItem->tMagic[i] = atoi(strTemp);
		j = j + 4;
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	이벤트 코드임 (기간 : 2002년 4월 8일 ~~ 2002년 4월 13일)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
int CNpc::GetEventItemNum(COM *pCom)
{
	int i, iRet = -1;
	DWORD dwCurTick = 0;
	DWORD dwPreTick = 0;

	EnterCriticalSection( &(pCom->m_critEvent) );

	dwCurTick = GetTickCount();

	for(i = 0; i < g_arAddEventItemTable.GetSize(); i++)
	{
		int tt = g_arAddEventItemTable[i]->m_tEnd;
		if(!g_arAddEventItemTable[i]->m_tEnd)				// 아직 떨어지지 않았다면
		{
			if(i == 0) dwPreTick = 0;
			else dwPreTick = g_arAddEventItemTable[i - 1]->m_dwTick;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@22
			if(dwCurTick - dwPreTick >= 60000 * 20)		// 24분이 넘었다면
//			if(dwCurTick - dwPreTick >= 1000)				// 1분이 넘었다면	
			{
				g_arAddEventItemTable[i]->m_dwTick = dwCurTick;
				g_arAddEventItemTable[i]->m_tEnd = 1;
														// 실제수만 번호를 셋팅해서 준다.	
				if(g_arAddEventItemTable[i]->m_tGiveFlag)	iRet = g_arAddEventItemTable[i]->m_sSid;
			}

			LeaveCriticalSection( &(pCom->m_critEvent) );
			return iRet;
		}
	}

	LeaveCriticalSection( &(pCom->m_critEvent) );
	return iRet;
}

///////////////////////////////////////////////////////////////////////////////////
//	임시 이벤트 코드임 (기간 : 2001년 12월 29일 ~~ 2002년 1월 2일)
//
//@@@@@@@@@@@@@@@@@@@@@@@@
BOOL CNpc::UpdateEventItem(int sid)
{
	SQLHSTMT		hstmt = NULL;
	SQLRETURN		retcode = 0;
	BOOL			bQuerySuccess = TRUE;
	TCHAR			szSQL[8000];		

	SQLINTEGER		iRetInd = SQL_NTS;

	SQLSMALLINT		sRet = 0;

	::ZeroMemory(szSQL, sizeof(szSQL));

	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call UPDATE_EVENT_ITEM(%d, ?)}"), sid);

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return FALSE;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );
	if( retcode != SQL_SUCCESS )
	{
		return FALSE;
	}

	retcode = SQLBindParameter( hstmt, 1 ,SQL_PARAM_OUTPUT,SQL_C_SSHORT, SQL_SMALLINT,0,0, &sRet,0, &iRetInd);
	if( retcode != SQL_SUCCESS )
	{
		SQLFreeHandle((SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
		return FALSE;
	}

	if (retcode == SQL_SUCCESS)
	{
		retcode = SQLExecDirect(hstmt, (unsigned char *)szSQL, SQL_NTS);
		
		if (retcode ==SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
		}
		else if (retcode==SQL_ERROR)
		{
			DisplayErrorMsg( hstmt );
			SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
			return FALSE;
		}
	}	
	else
	{
		DisplayErrorMsg( hstmt );
		SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
		return FALSE;
	}

	if (hstmt!=NULL) SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
	
	if( !bQuerySuccess ) return FALSE;
	if(sRet = 0) return FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////
//	수리가 안되어 있으면 현재 HP를 유지한다.	
//
void CNpc::SetFortressState()
{
	for(int i = 0; i < GUILD_REPAIR_MAX_NUM; i++)
	{
		if(m_pGuardFortress->m_arRepairDBList[i].sUid == m_sEZone)
		{
			if(m_pGuardFortress->m_arRepairDBList[i].sHP < m_sMaxHP)
			{
				m_sHP = m_pGuardFortress->m_arRepairDBList[i].sHP;

				if(m_sHP == 0)  m_tRepairDamaged = NPC_DEAD_REPAIR_STATE; 
				else			m_tRepairDamaged = NPC_NEED_REPAIR_STATE;

				break;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
//	N_Circle에 대한 처리를 계산한다.
//
//void CNpc::SetDamagedInFortressWar(int nDamage, TCHAR *id, int uuid, COM *pCom)
void CNpc::SetDamagedInFortressWar(int nDamage, USER *pUser)
{
	int i;
	int iCount = 0;
	int index = 0;

	BOOL bSuccess = FALSE;
	
	CBufferEx TempBuf;
	CNpc *pNpc = NULL;
														// 길드전을 신청한 길드인지 판단.
	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;
	if(pUser->m_dwGuild <= 0 || !m_pGuardFortress) return;

	if(pUser->m_tFortressWar == GUILD_WAR_AFFTER) return;

	if(m_pGuardFortress->m_lUsed == 0) return;			// 길드전이 끝났다.

	if(m_pGuardFortress->m_lChangeUsed == 1) return;

	for(i = 0; i < GUILDFORTRESS_ATTACK_MAX_NUM; i++)
	{
		if(pUser->m_dwGuild == m_pGuardFortress->m_arAttackGuild[i].lGuild)
		{
			bSuccess = TRUE;
			break;
		}
	}

	if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) bSuccess = TRUE;
	
	if(!bSuccess) return;								// 신청한 길드가 아님

	if(InterlockedCompareExchange((LONG*)&m_lFortressState, (long)1, (long)0) == (long)0)
	{
		if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid)	// 방어측은 
		{
			if(m_tNCircle != NPC_NCIRCLE_ATT_STATE)
			{
				InterlockedExchange(&m_lFortressState, (LONG)0); 
				return;
			}

			m_sHP -= nDamage;									// 공격측은 - 값
			if(m_sHP <= 0)
			{
				m_sHP = m_sMaxHP;
				m_byColor = 0;
				m_tNCircle = NPC_NCIRCLE_DEF_STATE;
				SendFortressNCircleColor(pUser->m_pCom);
			}
		}
		else
		{
			if(m_tNCircle != NPC_NCIRCLE_DEF_STATE) 
			{
				InterlockedExchange(&m_lFortressState, (LONG)0); 
				return;
			}

			m_sHP -= nDamage;									// 공격측은 - 값
			if(m_sHP <= 0)
			{
				m_sHP = m_sMaxHP;
				m_byColor = 1;
				m_tNCircle = NPC_NCIRCLE_ATT_STATE;
				SendFortressNCircleColor(pUser->m_pCom);
			}
		}

		iCount = 0;
		for(i = 0; i < FORTRESS_TARGET_MAX_NUM; i++)
		{
			pNpc = NULL;
			pNpc = GetNpc(m_pGuardFortress->m_arFortressTarget[i].sTargertID);	
			if(pNpc)
			{
				if(pNpc->m_tNCircle == NPC_NCIRCLE_ATT_STATE) iCount++; 
			}
		}

		if(iCount == FORTRESS_TARGET_MAX_NUM)
		{
			if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid)
			{
				InterlockedExchange(&m_lFortressState, (LONG)0); 
				return;
			}

			for(i = 0; i < g_arGuildFortress.GetSize(); i++)
			{
				if(!g_arGuildFortress[i]) continue;

				if(g_arGuildFortress[i]->m_sFortressID == m_pGuardFortress->m_sFortressID)
				{
					if(g_arGuildFortress[i]->m_lUsed == 1)
					{
						if(InterlockedCompareExchange((LONG*)&g_arGuildFortress[i]->m_lChangeUsed, (long)1, (long)0) == (long)0)
						{
							FORTRESSDATAPACKET *pFDP = NULL;
							pFDP = new FORTRESSDATAPACKET;

							pFDP->sFortressIndex = i;
							
							memset(pFDP->FORTRESS, NULL, CHAR_NAME_LENGTH+sizeof(int)+1);
							index = strlen(pUser->m_strGuildName);
							if(index > 0 && index <= CHAR_NAME_LENGTH) memcpy(pFDP->FORTRESS, pUser->m_strGuildName, index );

							EnterCriticalSection( &m_CS_FortressData );
							RecvFortressData.AddTail(pFDP);
 							nFortressDataCount = RecvFortressData.GetCount();
							LeaveCriticalSection( &m_CS_FortressData );	

							pUser->StoppingTheFortressWar(g_arGuildFortress[i]);		// 정해진 시간전이므로 게임은 계속되어야 한다. 
							InterlockedExchange(&g_arGuildFortress[i]->m_lChangeUsed, (LONG)0); 
						}
					}
					break;
				}
			}
		}

		InterlockedExchange(&m_lFortressState, (LONG)0); 
	}

	return;
}

//void CNpc::SetDoorDamagedInFortressWar(int nDamage, TCHAR *id, int uuid, COM *pCom)
void CNpc::SetDoorDamagedInFortressWar(int nDamage, USER *pUser)
{													// 공성전 기간이라면 누구나 공격하도록.. 단 방어측은 안됨
	if(!pUser || !m_pGuardFortress) return;
	if(pUser->m_dwGuild == m_pGuardFortress->m_iGuildSid) return;	// 방어측이 고의로 공격하는것을 방지한다.

	if(m_pGuardFortress->m_lUsed == 0) return;				// 길드전이 끝났다.

	m_sHP -= nDamage;

	if( m_sHP <= 0 )
	{
		m_sHP = 0;

		MAP* pMap = g_zone[m_ZoneIndex];
		pMap->m_pMap[m_sCurX][m_sCurY].m_lUser = 0;

		m_NpcState = NPC_DEAD;

		m_Delay = m_sRegenTime;
		m_bFirstLive = FALSE;

		SetMapAfterGuildWar();

		SendDead(pUser->m_pCom);
	}
}

void CNpc::SendFortressNCircleColor(COM *pCom)
{
	int modify_index = 0;
	char modify_send[2048];	

	CBufferEx TempBuf;

	TempBuf.Add(GUILD_FORTRESS_NCIRCLE);
	TempBuf.Add((BYTE)0x00);					// 해당 N_Circle의 색이 변화
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	TempBuf.Add(m_tNCircle);

	SendFortressInsight(pCom, TempBuf, TempBuf.GetLength());

	::ZeroMemory(modify_send, sizeof(modify_send));
	FillNpcInfo(modify_send, modify_index, INFO_MODIFY);
	SendFortressInsight(pCom, modify_send, modify_index);

}


void CNpc::SetMapTypeBeforeGuildWar(COM *pCom)
{
	int i;
	int uid = 0;

	USER *pUser = NULL;
	CNpc *pNpc = NULL;

	int x, y;

	long lNpcUid = 0;

//	POINT temp1Map[12] = {{-2,-2}, {-2,-1}, {-2,0}, {-1,-1}, {-1,0}, {0,-1}, {0,0},{1,-1},{1,0}, {2,-1}, {2,0}, {2,1}};
	POINT temp1Map[16] = {{-3,-2}, {-4,-1}, {-3,-1}, {-2,-1}, {-4,0}, {-3,0}, {-2,0},{-1,0},{0,0}, {1,0}, {2,0}, {1,1}, {2,1}, {2,2},{3,2},{3,3}};
	POINT temp2Map[17] = {{-2,-3}, {-1,-3}, {0,-3}, {-1,-2}, {0,-2}, {0,-1}, {0,0},{0,1},{1,1}, {0,2}, {1,2}, {2,2}, {0,3}, {1,3},{2,3},{0,4},{1,4}};
	POINT temp3Map[6] = {{-2,0},{-1,0},{0,0},{1,0},{2,0},{2,1}};
	
//	POINT temp2Map[] = {{1,-2}, {1,-1}, {1,0}, {1,1}, {1,2}, {0,-2},{0,-1},{0,0},{0,1},{0,2}};

	MAP* pMap = g_zone[m_ZoneIndex];

	switch(m_sDimension)
	{
	case 1:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < sizeof(temp1Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp1Map[i].x;
			y = m_sCurY + temp1Map[i].y;
	
			uid = pMap->m_pMap[x][y].m_lUser;

			if(uid >= USER_BAND && uid < NPC_BAND)	// Target 이 User 인 경우
			{
				pUser = GetUser(pCom, uid - USER_BAND);
				if( pUser->m_tIsOP != 1 ) pUser->TownPotal();
			}

			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;
	case 2:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < sizeof(temp2Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp2Map[i].x;
			y = m_sCurY + temp2Map[i].y;
	
			uid = pMap->m_pMap[x][y].m_lUser;

			if(uid >= USER_BAND && uid < NPC_BAND)	// Target 이 User 인 경우
			{
				pUser = GetUser(pCom, uid - USER_BAND);
				if( pUser->m_tIsOP != 1 ) pUser->TownPotal();
			}

			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;
	case 3:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < sizeof(temp3Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp3Map[i].x;
			y = m_sCurY + temp3Map[i].y;
	
			uid = pMap->m_pMap[x][y].m_lUser;

			if(uid >= USER_BAND && uid < NPC_BAND)	// Target 이 User 인 경우
			{
				pUser = GetUser(pCom, uid - USER_BAND);
				if( pUser->m_tIsOP != 1 ) pUser->TownPotal();
			}

			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;

	}
}


void CNpc::SetMapAfterGuildWar()
{
	int i;
	int uid = 0;

	USER *pUser = NULL;

	int x, y;

//	POINT temp1Map[12] = {{-2,-2}, {-2,-1}, {-2,0}, {-1,-1}, {-1,0}, {0,-1}, {0,0},{1,-1},{1,0}, {2,-1}, {2,0}, {2,1}};
//	POINT temp2Map[] = {{1,-2}, {1,-1}, {1,0}, {1,1}, {1,2}, {0,-2},{0,-1},{0,0},{0,1},{0,2}};
	POINT temp1Map[16] = {{-3,-2}, {-4,-1}, {-3,-1}, {-2,-1}, {-4,0}, {-3,0}, {-2,0},{-1,0},{0,0}, {1,0}, {2,0}, {1,1}, {2,1}, {2,2},{3,2},{3,3}};
	POINT temp2Map[17] = {{-2,-3}, {-1,-3}, {0,-3}, {-1,-2}, {0,-2}, {0,-1}, {0,0},{0,1},{1,1}, {0,2}, {1,2}, {2,2}, {0,3}, {1,3},{2,3},{0,4},{1,4}};
	POINT temp3Map[6] = {{-2,0},{-1,0},{0,0},{1,0},{2,0},{2,1}};

	MAP* pMap = g_zone[m_ZoneIndex];

	switch(m_sDimension)
	{
	case 1:
		for(i =0; i < sizeof(temp1Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp1Map[i].x;
			y = m_sCurY + temp1Map[i].y;

			InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, 0);
		}
		break;
	case 2:
		for(i =0; i < sizeof(temp2Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp2Map[i].x;
			y = m_sCurY + temp2Map[i].y;

			InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, 0);
		}
		break;
	case 3:
		for(i =0; i < sizeof(temp3Map)/sizeof(POINT); i++)
		{
			x = m_sCurX + temp3Map[i].x;
			y = m_sCurY + temp3Map[i].y;

			InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, 0);
		}
		break;
	}
}

void CNpc::SendFortressInsight(COM *pCom, TCHAR *pBuf, int nLength)
{
	if(nLength <= 0 || nLength >= SEND_BUF_SIZE) return;

	int insight_range = 10;

	int sx = m_sCurX / SIGHT_SIZE_X;
	int sy = m_sCurY / SIGHT_SIZE_Y;
	
	int min_x = (sx-8)*(SIGHT_SIZE_X); if( min_x < 0 ) min_x = 0;
	int max_x = (sx+9)*(SIGHT_SIZE_X);
	int min_y = (sy-8)*(SIGHT_SIZE_Y); if( min_y < 0 ) min_y = 0;
	int max_y = (sy+9)*(SIGHT_SIZE_Y);
	
	MAP* pMap = g_zone[m_ZoneIndex];
	if( !pMap ) return;
	
	if( max_x >= pMap->m_sizeMap.cx ) max_x = pMap->m_sizeMap.cx - 1;
	if( max_y >= pMap->m_sizeMap.cy ) max_y = pMap->m_sizeMap.cy - 1;
	
	int temp_uid;
	USER* pUser = NULL;

	for( int i = min_x; i < max_x; i++ )
	{
		for( int j = min_y; j < max_y; j++ )
		{				
			temp_uid = pMap->m_pMap[i][j].m_lUser;

			if(temp_uid < USER_BAND || temp_uid >= NPC_BAND) continue;
			else temp_uid -= USER_BAND;
			
			if( temp_uid >= 0 && temp_uid < MAX_USER )
			{
				pUser = pCom->GetUserUid(temp_uid);
				if(pUser == NULL) continue;
				
				if( pUser->m_state == STATE_GAMESTARTED )
				{
					if( pUser->m_curx == i && pUser->m_cury == j && pUser->m_curz == m_sCurZ )
					{
						Send( pUser, pBuf, nLength );
					}
				}
			}
		}
	}
}

void CNpc::TestCode(COM *pCom, USER *pUser)
{
	int i;
	int uid = 0;

	CNpc *pNpc = NULL;

	int x, y;

	long lNpcUid = 0;

	if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) return;

	POINT temp1Map[12] = {{-2,-2}, {-2,-1}, {-2,0}, {-1,-1}, {-1,0}, {0,-1}, {0,0},{1,-1},{1,0}, {2,-1}, {2,0}, {2,1}};// server
//	POINT temp2Map[8] = {{0,0}, {0,1}, {0,2}, {0,3}, {-1,0}, {-1,1}, {-1,2},{-1,3}};
//	POINT temp1Map[12] = {{147,1183}, {148,1184}, {149,1185}, {149,1183}, {150,1184}, {150,1182}, {151,1183},{151,1181},{152,1182}, {152,1180}, {153,1181}, {154,1182}};
	POINT temp2Map[] = {{-1,-3}, {0,-2}, {1,-1}, {2,0}, {3,1}, {-2,-2}, {-1,-1}, {0,0}, {1,1}, {2,2}};	// client

	MAP* pMap = g_zone[m_ZoneIndex];

	CPoint temp = ConvertToClient(m_sCurX, m_sCurY);
	switch(m_sDimension)
	{
	case 1:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < 12; i++)
		{
			x = m_sCurX + temp1Map[i].x;
			y = m_sCurY + temp1Map[i].y;
	
			CString strMsg = _T("");
			CPoint pt = ConvertToClient(x, y);
//			CPoint pt = ConvertToServer(temp1Map[i].x, temp1Map[i].y);
			strMsg.Format("1Luinet locked door x = %d, y = %d", pt.x - temp.x, pt.y - temp.y);

//			pUser->NormalChat(strMsg.GetBuffer(strMsg.GetLength()));

//			::InterlockedExchange(&pMap->m_pMap[x][y].m_lUser, lNpcUid);
		}
		break;
	case 2:
		lNpcUid = m_sNid + NPC_BAND;

		for(i =0; i < 10; i++)
		{
			x = temp.x + temp2Map[i].x;
			y = temp.y + temp2Map[i].y;

			CPoint pt = ConvertToServer(x, y);

			CString strMsg = _T("");			
//			CPoint pt = ConvertToServer(temp1Map[i].x, temp1Map[i].y);
			strMsg.Format("1Sanad locked door x = %d, y = %d", pt.x - m_sCurX, pt.y - m_sCurY);

//			pUser->NormalChat(strMsg.GetBuffer(strMsg.GetLength()));

		}
		break;
	}
}

int CNpc::PsiAttack(COM *pCom) //NPC침랬묑샌
{
	DWORD	dwExp = 0;
	int		nDamage = 0;
	int		nTempHP = 0;

	USER*	pUser = NULL;
	CNpc*	pNpc = NULL;

	BYTE	tWeaponClass = 0;
	BOOL	bCanUseSkill = FALSE;
	int		bSuccessSkill[SKILL_NUM] = {FALSE, FALSE, FALSE, FALSE, FALSE};

	int		nPsiRange = 0;
	int		nTPosX	= 0;
	int		nTPosY	= 0;
	int		nDist	= 100;
	short	sNeedPP	= 25000;
	BYTE	tPsiRegi = 0;
	DWORD	dwPsiCast = 0;

	BOOL	bPsiSuccess = FALSE;

	int index = 0;

	int delay = -1;
	int nTargetID	= m_Target.id;			// Target ID 를 얻는다.
	BYTE byPsi		= m_byPsi;				// Psionic sid 를 얻는다.

	int nPsiX = -1;							// Teleport할 위치
	int nPsiY = -1;
	CPoint ptPsi(-1, -1);

	if( byPsi < 0 || byPsi >= g_arMonsterPsi.GetSize() ) return -1;

	if( nTargetID < USER_BAND || nTargetID >= INVALID_BAND ) return-1;	// 잘못된 Target 이면 return

	pUser = GetUser( pCom, nTargetID - USER_BAND );
	if( !pUser ) return -1;

	CMonsterPsi* pMagic = g_arMonsterPsi[(int)byPsi];
	if( !pMagic ) return -1;
	
	// 사정거리 계산 ------------------------------------------------------------------------//
	if( !IsCloseTarget( pCom, (int)pMagic->m_byRange ) ) return -1;

	short damage, result;

	if(pMagic->m_sSid != 0)	
	{	
		damage = myrand( pMagic->m_sMinDmg, pMagic->m_sMaxDmg );
	
		result = damage * m_sVOL - pUser->GetUserSpellDefence();

/*		//흔벎닸瞳빱랬，橙묑샌빱랬
		if(pUser->m_tHuFaType &&pUser->m_nHuFaHP>0)
		{
			int nID = pUser->m_uid+USER_BAND+USER_HUFA_BAND;
			//�襁┟暄�
			pUser->SendDamageNum(0,nID,(short)result);

			SendAttackSuccess(pCom, nID, 0, pUser->m_nHuFaHP, pUser->m_nHuFaMaxHP);//yskang 0.3
			if(nDamage > 0)
				pUser->SetHuFaDamage(result);
			if(pUser->m_nHuFaHP>0)
			{
				pUser->HuFaAttack(m_sNid+NPC_BAND);
			}
			CBufferEx TempBuf;
			TempBuf.Add(PSI_ATTACK_RESULT);
			TempBuf.Add(SUCCESS);
			TempBuf.Add( (BYTE)33 );				// Psionic sid
			TempBuf.Add( m_sNid + NPC_BAND );
			TempBuf.Add( nID );
			SendExactScreen(pCom, TempBuf, TempBuf.GetLength());
			return 1200;
		}*/
		pUser->SetDamage((int)result);	
//		pUser->SetFaNu(result);
		pUser->SendDamageNum(0,pUser->m_uid+USER_BAND,result);
		if(pUser->m_lDeadUsed == 1)
		{
			InitTarget();
			m_NpcState = NPC_STANDING;
			delay = m_sStandTime;

			if(m_NpcVirtualState == NPC_STANDING) 
			{
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // 침공용 몬스터일경우 경험치 1%감소
				else			pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);		// 경험치와 그외 변화량를 반영한다.
			}
		}
		else
		{
			
			if(m_sPid == 212) //붚갠价�� 긴침랬徠밍
			{
				int iRandom = myrand(1, 10000);
				if(iRandom <= 3000)	
				{					
					CBufferEx TempBuf;
					TempBuf.Add(PSI_ATTACK_RESULT);
					TempBuf.Add(SUCCESS);
					TempBuf.Add( (BYTE)33 );				// Psionic sid
					TempBuf.Add( m_sNid + NPC_BAND );
					TempBuf.Add( nTargetID );
					SendExactScreen(pCom, TempBuf, TempBuf.GetLength());
					delay = (int)1200;					
					CPoint pt(-1, -1);
					pt = pUser->FindNearAvailablePoint_S(m_sCurX, m_sCurY);
					for(int i = 0; i< 2;i++){
						pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
				    //    pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
					 //   pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
					  //  pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
					   // pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
					    //pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
					    //pUser->SummonQuestMonster(174,m_sCurZ,pt.x,pt.y);
					}
					return (int)delay;
				}									
				
			}
			switch(pMagic->m_sSid)
			{
				case	8:
				case	27:
				case	31:
				case	32:
					GetWideRangeAttack( pCom, pUser->m_curx, pUser->m_cury, (int)damage, nTargetID - USER_BAND );				
					break;
				case	2:		// 쏘는 마법
				case	5:
				case	28:
				case	37:
				case	38:
				case	40:
				case	41:
				case	42:
				case	43:
					pUser->SetFireDamage();					
					break;				
				case	4:
				case	10:
				case	21:				
					pUser->SetColdDamage();					
					break;				
				case	24:
//					pUser->SetConFusion();					
					GetWideRangeAttack( pCom, pUser->m_curx, pUser->m_cury, (int)damage, nTargetID - USER_BAND );				
					break;				
			}
			
		}

	}

	CBufferEx TempBuf;

	TempBuf.Add(PSI_ATTACK_RESULT);
	TempBuf.Add(SUCCESS);

	TempBuf.Add( (BYTE)pMagic->m_sPid );				// Psionic sid
	TempBuf.Add( m_sNid + NPC_BAND );
	TempBuf.Add( nTargetID );

//	SendInsight( pCom, TempBuf, TempBuf.GetLength());
	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());

	delay = (int)pMagic->m_sCasting;

	return (int)delay;
}

void CNpc::GetWideRangeAttack(COM* pCom, int x, int y, int damage, int except_uid)	// 지금은 공격만 처리...
{
	int dir[9][2];
	int ix, iy;
	int nTarget = 0;
	int nDamage = 0;
	double result = 0;

	USER* pUser = NULL;
	MAP* pMap = g_zone[m_ZoneIndex];
	if(!pMap) return;

	dir[0][0]  =  0;		dir[0][1] =  0;		// 
	dir[1][0]  = -1;		dir[1][1] =  0;		// 
	dir[2][0]  = -1;		dir[2][1] =  1;		// 
	dir[3][0]  =  0;		dir[3][1] =  1;		// 
	dir[4][0]  =  1;		dir[4][1] =  1;		// 

	dir[5][0]  =  1;		dir[5][1] =  0;		// 
	dir[6][0]  =  1;		dir[6][1] = -1;		// 
	dir[7][0]  =  0;		dir[7][1] = -1;		// 
	dir[8][0]  = -1;		dir[8][1] = -1;		// 

	for(int i = 1; i < 9; i++)
	{
		ix = x + dir[i][0];
		iy = y + dir[i][1];

		if(ix < 0) ix = 0;
		if(iy < 0) iy = 0;
		if(ix >= pMap->m_sizeMap.cx) ix = pMap->m_sizeMap.cx - 1;
		if(iy >= pMap->m_sizeMap.cy) iy = pMap->m_sizeMap.cy - 1;

		nTarget = pMap->m_pMap[ix][iy].m_lUser;

		if(nTarget >= USER_BAND && nTarget < NPC_BAND)	// USER
		{
			pUser = GetUser( pCom, nTarget - USER_BAND);			// User Pointer 를 얻는다.

			if(pUser == NULL || pUser->m_state != STATE_GAMESTARTED) continue;						// 잘못된 USER 이면 리턴
			if(pUser->m_bLive == USER_DEAD)	continue;		// Target User 가 이미 죽어있으면 리턴
			if(pUser->m_uid == except_uid ) continue;	// 중심에 있는 유저는 계산하지 않는다

			result = (double)damage * (double)( m_sVOL * 20 ) / (double)( pUser->m_sMagicVOL * 15 + pUser->m_DynamicUserData[MAGIC_PSI_RESIST_UP] + m_sVOL * 20 );
			pUser->SetDamage((int)result);

			if(pUser->m_sHP > 0)		// 살은 경우 전기데미지 추가
			{
//				pUser->SetColdDamage();
			}
			else
			{
//				IsChangeCityRank(pUser);
				if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // 침공용 몬스터일경우 경험치 1%감소
				else			pUser->GetLevelDownExp(USER_PK, -1, FALSE,m_strName);			// 경험치와 그외 변화량를 반영한다.
			}
		}
/*
		else if(nTarget >= NPC_BAND)				// NPC
		{
			pNpc = GetNpc(nTarget - NPC_BAND);				// NPC Point 를 얻는다.
			if(pNpc == NULL) continue;					// 잘못된 NPC 이면 리턴
			if(pNpc->m_NpcState == NPC_DEAD || pNpc->m_tNpcType != NPCTYPE_MONSTER) continue;	// NPC 가 이미 죽어 있으면 리턴
			if(pNpc->m_sHP <= 0) continue;

			nDamage = (int)(damage *  ((double)m_sMagicVOL / (m_sMagicVOL + pNpc->m_sVOL)));
			nDamage = (int)((double)nDamage/2 + 0.5);	// 데미지의 50%만 들어간다.

			if(pNpc->SetDamage(nDamage, m_strUserID, m_uid + USER_BAND, m_pCom) == FALSE)
			{
				if(m_tGuildHouseWar == GUILD_WARRING && pNpc->m_NpcVirtualState == NPC_WAIT)
				{
					CheckGuildHouseWarEnd();
				}

				pNpc->SendExpToUserList(m_pCom); // 경험치 분배!!
				pNpc->SendDead(m_pCom);
				int diffLevel = abs(m_sLevel - pNpc->m_byClassLevel);
				if(difflevel < 30)
				{
					CheckMaxValue(m_dwXP, 1);		// 몹이 죽을때만 1 증가!	
					SendXP();
				}
			}
			else									// 살은 경우 전기데미지 추가
			{
//				pNpc->SetColdDamage();
			}
		}
*/
	}
}

int CNpc::AreaAttack(COM *pCom)
{
	if(!pCom) return 10000;
	if(m_tNpcType == NPCTYPE_GUARD) return -1;
	if(m_tNpcType == NPCTYPE_GUILD_GUARD) return -1;

	int nStandingTime = m_sStandTime;

	// 총기계열 일때는 타겟과의 거리계산을 달리해야 한다.
	if(IsCloseTarget(pCom, m_byRange) == FALSE)// Check Code (단지 방어적인 측면에서 넣은 코드)
	{
		m_NpcState = NPC_TRACING;			// 공격하고 도망가는 유저를 따라 잡기위해(반응을 좀더 빠르게) 
		TRACE("AreaAttack - 거리 멀어서 실패\n");
		return -1;							// IsCloseTarget()에 유저 x, y값을 갱신하고 Delay = 0으로 줌
	}

	USER* pUser = NULL;
	int nRange = 1;				// 공격 범위 : 1 - 주위 8칸, 2 - 주위 24칸...
	int nTargetCount = 0;
	int target_uid = -1;

	int center_x = m_sCurX;		// 공격 범위의 중심점 : 중심이 공격하는 NPC일 수도 있고 어떤 점을 구할 수도 있다.
	int center_y = m_sCurY;		// 현재는 자기 주위 공격으로 한정

	switch( (int)m_tSPATRange )
	{
	case	0:
	case	1:
		nRange = 2;
		center_x = m_sCurX;
		center_y = m_sCurY;
		break;

	case	2:
		nRange = 2;
		center_x = m_sCurX;
		center_y = m_sCurY;
		break;

	case	3:
		nRange = 1;
		center_x = m_Target.x;
		center_y = m_Target.y;
		break;

	case	4:
		nRange = 2;
		center_x = m_Target.x;
		center_y = m_Target.y;
		break;

	default:
		nRange = 1;
		center_x = m_sCurX;
		center_y = m_sCurY;
		break;
	}

	MAP* pMap = g_zone[m_ZoneIndex];
	if(!pMap)
	{
		TRACE("AreaAttack - 맵없어서 실패\n");
		return -1;
	}

	int min_x = center_x - nRange;		if( min_x < 0 ) min_x = 0;
	int min_y = center_y - nRange;		if( min_y < 0 ) min_y = 0;
	int max_x = center_x + nRange;
	int max_y = center_y + nRange;

	if(max_x >= pMap->m_sizeMap.cx) max_x = pMap->m_sizeMap.cx - 1;
	if(max_y >= pMap->m_sizeMap.cy) max_y = pMap->m_sizeMap.cy - 1;

	TargetUser tuser[25];


	int		nAvoid = 0;
	int		iRandom = 0;
	int		determine = 0;
	int		iDexHitRate = 0, iLevelHitRate = 0;
	short	sTempHP		= 0;

	int		nHit = 0;

	BOOL	bIsHit = FALSE;
	BOOL	bIsCritical = FALSE;

	int		nDamage		= 0;
	int		nDefense	= 0;

	int nID = m_Target.id;					// Target 을 구한다.

	// 명중여부 판단 변수 초기화
	bIsHit = FALSE;		


	for( int ix = min_x; ix <= max_x; ix++ )
	{
		for( int iy = min_y; iy <= max_y; iy++ )
		{
			target_uid = pMap->m_pMap[ix][iy].m_lUser;

			if( target_uid < USER_BAND || target_uid >= NPC_BAND )
			{
				continue;
			}

			pUser = GetUser(pCom, target_uid - USER_BAND);

			if( !pUser ) continue;
			if( pUser->m_bLive != USER_LIVE ) continue;

			if( ix != pUser->m_curx || iy != pUser->m_cury ) continue;

			//if(pUser->m_state == STATE_DISCONNECTED) continue;
			if(pUser->m_state != STATE_GAMESTARTED) continue;
			if(pUser->m_tIsOP == 1 ) continue;
			if(pUser->m_bPShopOpen == TRUE) continue;
            if(pUser->m_bSessionOnline == true) continue;
			// 회피값 계산 
			nAvoid = pUser->GetAvoid();

			// 명중여부 판단
			iRandom = (int)((double)XdY(1, 1000) / 10 + 0.5); 
			
			iDexHitRate = (int)( 30.0 * ( (double)m_sDEX/(m_sDEX + pUser->m_sMagicDEX) ) + 15.0 );
			iLevelHitRate = (int)( 70.0 * ( (double)m_byClassLevel/(pUser->m_sLevel + m_byClassLevel) ) + 15.0);

			determine = iDexHitRate + iLevelHitRate - (nAvoid+pUser->m_Avoid);

			if(determine < ATTACK_MIN) determine = ATTACK_MIN;			// 최소 20
			else if(determine > ATTACK_MAX) determine = ATTACK_MAX;		// 최대

			if(iRandom < determine)	bIsHit = TRUE;		// 명중

			// 공격 미스
			if(bIsHit == FALSE)
			{
				TRACE("AreaAttack - 공격 미스\n");
				continue;
			}

			// 명중이면 //Damage 처리 ----------------------------------------------------------------//

			nDamage = GetFinalDamage(pUser);	// 최종 대미지

			if(nDamage > 0) 
			{
		        pUser->SetDamage(nDamage);
			    pUser->SendDamageNum(0,pUser->m_uid+USER_BAND,nDamage);
			}
			// 방어측 내구도 감소
			pUser->SendDamagedItem(nDamage);

//			if(pUser->m_bLive == USER_DEAD || pUser->m_sHP <= 0)//@@@ 나중에 고침
			if(pUser->m_lDeadUsed == 1)
			{
				if(m_NpcVirtualState == NPC_STANDING) 
				{
					if(m_sPid == 179) pUser->GetLevelDownExp(FALSE, -1, TRUE,m_strName); // 침공용 몬스터일경우 경험치 1%감소
					else			pUser->GetLevelDownExp(FALSE, -1, FALSE,m_strName);		// 경험치와 그외 변화량를 반영한다.
				}
			}

			tuser[nTargetCount].iUid = target_uid;
			tuser[nTargetCount].sHP = pUser->m_sHP;
			tuser[nTargetCount].sMaxHP = pUser->m_sMagicMaxHP;
			pUser->SendHP();

			nTargetCount++;

			if( nTargetCount >= 25 ) break;
		}

		if( nTargetCount >= 25 ) break;
	}

	if( !nTargetCount )
	{
		TRACE("AreaAttack - 범위 안에 유저 없어서 실패\n");
//		return -1;
	}

	CBufferEx TempBuf;
//	2a 0 0 0 ca 1 1 9f 5b 0 0 6a 2c 0 0 0 0
	TempBuf.Add(AREA_ATTACK_RESULT);
	TempBuf.Add(ATTACK_SUCCESS);
	TempBuf.Add( (byte)1 );
	TempBuf.Add((int)(m_sNid + NPC_BAND));
	
	for(int i = 0; i < 1; i++ )
	{
		TempBuf.Add( (int)tuser[i].iUid );
		TempBuf.Add( (short)0 );
		TempBuf.Add( (short)0 );
	}

	SendInsight(pCom, TempBuf, TempBuf.GetLength());
//	SendExactScreen(pCom, TempBuf, TempBuf.GetLength());

	TRACE("AreaAttack - 성공\n");
	
	return m_sAttackDelay;
}



void CNpc::GiveEventItemNewToUser(USER *pUser)
{
	if( !pUser ) return;
	if( pUser->m_state != STATE_GAMESTARTED ) return;
//	if( pUser->m_iDisplayType == 6 && pUser->m_sLevel > 25) return; //yskang 0.5
	if( pUser->m_iDisplayType == 6) return; //yskang 0.5

	int i;
	CEventItemNew* pNewItem = NULL;

	BOOL bFlag = FALSE;

	int sItemSid = -1;
	BYTE tItemQuality = 0;
	BYTE tItemWear = 0;

	int j;
	int iSlot = -1;

	SYSTEMTIME time;
	GetLocalTime( &time );
	CString strMsg = _T("");

	MYSHORT upper;	upper.i = 0;
	MYINT lower;	lower.i = 0;

	for( i = 0; i < g_arEventItemNew.GetSize(); i++ )
	{
		if( g_arEventItemNew[i] )
		{
			pNewItem = g_arEventItemNew[i];

			if( ::InterlockedCompareExchange( (long*)&(pNewItem->m_lGive), (long)0, (long)1 ) == (long)0 ) continue;

			if( pNewItem->m_sSid != NPC_EVENT_LOTTO )
			{
				// 복권이 아닌 경우 유저랩과 몹의 랩의 차이가 25랩을 초과하면 주지 않는다.
				if(abs(m_byClassLevel - pUser->m_sLevel) > 25)
				{
					if(m_byClassLevel < pUser->m_sLevel) return;
				}
			}
			else
			{
				// 복권은 유저랩과 몹의 랩의 차이가 40랩을 초과하면 주지 않는다.
				if(abs(m_byClassLevel - pUser->m_sLevel) > 40)
				{
					if(m_byClassLevel < pUser->m_sLevel) return;
				}
			}

			//////////////////////////////////////////////////////////////////////
			// 추가되는 이벤트 아이템이 있으면 아래에 추가한다.
			//////////////////////////////////////////////////////////////////////

			// 꽃바구니 이벤트
			if( pNewItem->m_sSid == NPC_EVENT_FLOWER )
			{
				if( time.wYear == 2002 && time.wMonth == 5 && ( time.wDay >= 1 || time.wDay <= 5 ) )
				{
					sItemSid = pNewItem->m_sSid;
					tItemQuality = 0;
				}
				else
				{
					return;
				}
			}

			if( pNewItem->m_sSid == NPC_EVENT_LOTTO )
			{
				if( time.wYear == 2002 && ( ( time.wMonth == 5 && time.wDay >= 16 ) || ( time.wMonth == 6 && time.wDay <= 22 ) ) )
				{
					sItemSid = pNewItem->m_sSid;
					tItemQuality = pNewItem->m_tQuality;
				}
				else
				{
					return;
				}

				if( pUser->m_sLevel < 25 )		// 이벤트 복권은 25레벨 미만은 주지 않는다.
				{
					return;
				}
			}

			/////////////////////////////////////////////////////////////////////

			if( sItemSid < 0 || sItemSid >= g_arItemTable.GetSize() ) return;
			CItemTable* pItemTable = g_arItemTable[sItemSid];

			iSlot = pUser->GetEmptySlot(INVENTORY_SLOT);

			if( iSlot != -1 )
			{
				if(pUser->m_iMaxWeight >= pUser->m_iCurWeight + pItemTable->m_byWeight) bFlag = TRUE;
			}

			switch( sItemSid )
			{
				case NPC_EVENT_FLOWER:
					if(bFlag) { strMsg.Format(IDS_EVENT_FLOWER, pUser->m_strUserID); }
					break;
				case NPC_EVENT_LOTTO:
					if(bFlag) { strMsg.Format(IDS_EVENT_LOTTO); }
					break;
				default:
					return;
			}

			ItemList newItem;
			pUser->ReSetItemSlot( &newItem );

			newItem.tType = TYPE_ITEM;
			newItem.sLevel = pItemTable->m_byRLevel;
			newItem.sSid = sItemSid;
			newItem.sCount = 1;
			newItem.sDuration = pItemTable->m_sDuration;
			newItem.sBullNum = pItemTable->m_sBullNum;
			newItem.tIQ = tItemQuality;
			newItem.iItemSerial = 0;

			for( j = 0; j < MAGIC_NUM; j++ ) newItem.tMagic[j] = 0;

			// 이벤트 아이템 주기 테이블에서 남은 개수를 한개 줄여준다.
			pNewItem->m_sRemain--;

			if( pNewItem->m_sRemain < 0 )
			{
				pNewItem->m_sRemain = 0;
			}
			if( !UpdateEventItemNewRemain( pNewItem ) )
			{
				pNewItem->m_sRemain++;
				::InterlockedExchange( &(pNewItem->m_lGive), 1 );
				return;
			}

			if( pNewItem->m_tSerialExist != 255 )		// 시리얼 번호를 부여해야 하는 상황이라면
			{
				upper.i = pNewItem->m_tSerialExist;		// 10000 번대 번호
				lower.i = pNewItem->m_sRemain;

				newItem.tMagic[0] = upper.b[0];
				newItem.tMagic[1] = upper.b[1];

				newItem.tMagic[2] = lower.b[0];
				newItem.tMagic[3] = lower.b[1];
				newItem.tMagic[4] = lower.b[2];
				newItem.tMagic[5] = lower.b[3];
			}

			// bFlag - 인벤에 빈슬롯이 있고, 무게제한에 걸리지 않았을때 TRUE이다.
			if(bFlag)
			{
				pUser->m_UserItem[iSlot].tType = newItem.tType;
				pUser->m_UserItem[iSlot].sLevel = newItem.sLevel;
				pUser->m_UserItem[iSlot].sSid = newItem.sSid;
				pUser->m_UserItem[iSlot].sCount = newItem.sCount;
				pUser->m_UserItem[iSlot].sDuration = newItem.sDuration;
				pUser->m_UserItem[iSlot].sBullNum = newItem.sBullNum;
				pUser->m_UserItem[iSlot].tIQ = newItem.tIQ;
				pUser->m_UserItem[iSlot].iItemSerial = newItem.iItemSerial;

				for( j = 0; j < MAGIC_NUM; j++ ) pUser->m_UserItem[iSlot].tMagic[j] = newItem.tMagic[j];

				CBufferEx TempBuf;

				TempBuf.Add(ITEM_LOAD_RESULT);
				TempBuf.Add(SUCCESS);
				TempBuf.Add((BYTE)0x01);

				TempBuf.Add((BYTE)iSlot);
				TempBuf.Add(pUser->m_UserItem[iSlot].sLevel);
				TempBuf.Add(pUser->m_UserItem[iSlot].sSid);
				TempBuf.Add(pUser->m_UserItem[iSlot].sDuration);
				TempBuf.Add(pUser->m_UserItem[iSlot].sBullNum);
				TempBuf.Add(pUser->m_UserItem[iSlot].sCount);
				for(j = 0; j < MAGIC_NUM; j++) TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tMagic[j]);

				TempBuf.Add((BYTE)pUser->m_UserItem[iSlot].tIQ);

				pUser->Send(TempBuf, TempBuf.GetLength());

				pUser->m_iCurWeight += pItemTable->m_byWeight;
				pUser->GetRecoverySpeed();			// 아이템 무게에 변동이 생기면 회복속도 변환

				switch( sItemSid )
				{
					case NPC_EVENT_FLOWER:
						pUser->m_pCom->Announce((LPTSTR)(LPCTSTR)strMsg, SYSTEM_NORMAL);
//						pUser->m_pCom->Announce(strMsg.GetBuffer(strMsg.GetLength()), SYSTEM_NORMAL);
						break;
					case NPC_EVENT_LOTTO:
						pUser->SendSystemMsg( IDS_EVENT_LOTTO, SYSTEM_NORMAL, TO_ME);
						break;
					default:
						return;
				}

				strMsg.Format("(%04d-%02d-%02d %02d:%02d:%02d) %s - Get %d Item(%d)\r\n",
					time.wYear, 
					time.wMonth, 
					time.wDay, 
					time.wHour, 
					time.wMinute, 
					time.wSecond,	
					pUser->m_strUserID, 
					newItem.sSid,
					upper.i * 10000 + lower.i );

				EnterCriticalSection( &m_CS_EventItemLogFileWrite );
				g_fpEventItem.Write( strMsg, strMsg.GetLength() );
				LeaveCriticalSection( &m_CS_EventItemLogFileWrite );
			}
			else
			{
				// 인벤넣기에 실패하면 맵에 셋팅
				GiveItemToMap( pUser->m_pCom, &newItem );

				strMsg.Format("(%04d-%02d-%02d %02d:%02d:%02d) %s - Map %d Item(%d)\r\n",
					time.wYear, 
					time.wMonth, 
					time.wDay, 
					time.wHour, 
					time.wMinute, 
					time.wSecond,	
					pUser->m_strUserID, 
					newItem.sSid,
					upper.i * 10000 + lower.i );

				EnterCriticalSection( &m_CS_EventItemLogFileWrite );
				g_fpEventItem.Write( strMsg, strMsg.GetLength() );
				LeaveCriticalSection( &m_CS_EventItemLogFileWrite );
			}
		}
	}
}

void CNpc::GiveItemToMap(COM *pCom, ItemList *pItem)
{
	CPoint pt = FindNearRandomPointForItem(m_sCurX, m_sCurY);							// 현재 자기좌표를 제외한 24칸
	if(pt.x <= -1 || pt.y <= -1) return;
	if(pt.x >= g_zone[m_ZoneIndex]->m_sizeMap.cx || pt.y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) return;

	if( InterlockedCompareExchange((LONG*)&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, (long)1, (long)0) == (long)0 )
	{
		ItemList* pNewItem = new ItemList;

		memcpy( pNewItem, pItem, sizeof( ItemList ) );

		// 해당 유저에게 알린다.			
		//pCom->DelThrowItem();
		pCom->SetThrowItem( pNewItem, pt.x, pt.y, m_ZoneIndex );

		::InterlockedExchange(&g_zone[m_ZoneIndex]->m_pMap[pt.x][pt.y].m_FieldUse, 0);
	}
}

BOOL CNpc::UpdateEventItemNewRemain(CEventItemNew *pEventItem)
{
	SQLSMALLINT	sRet = -1;
	SQLINTEGER	iRetInd = SQL_NTS;

	SQLHSTMT	hstmt = NULL;
	SQLRETURN	retcode;
	TCHAR		szSQL[8000];	::ZeroMemory(szSQL, sizeof(szSQL));

	_sntprintf(szSQL, sizeof(szSQL), TEXT("{call update_event_item_new_remain ( %d, %d, ? )}"), 
		pEventItem->m_sIndex, 
		pEventItem->m_sRemain );

	int db_index = 0;
	CDatabase* pDB = g_DBNew[AUTOMATA_THREAD].GetDB( db_index );
	if( !pDB ) return FALSE;

	retcode = SQLAllocHandle( (SQLSMALLINT)SQL_HANDLE_STMT, pDB->m_hdbc, &hstmt );

	if( retcode != SQL_SUCCESS )
	{
		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return FALSE;
	}

	int i = 1;
	SQLBindParameter( hstmt, i++ ,SQL_PARAM_OUTPUT,SQL_C_SSHORT, SQL_SMALLINT, 0, 0, &sRet, 0, &iRetInd);

	retcode = SQLExecDirect( hstmt, (unsigned char*)szSQL, sizeof(szSQL));
	if( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
	}
	else
	{
		DisplayErrorMsg(hstmt);
		retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);

		g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);
		return FALSE;
	}

	retcode = SQLFreeHandle( (SQLSMALLINT)SQL_HANDLE_STMT, hstmt);
	g_DBNew[AUTOMATA_THREAD].ReleaseDB(db_index);

	if( sRet == -1 ) return FALSE;

	return TRUE;
}

void CNpc::UserListSort()
{
	int i, j;
	int total = 0;

	ItemUserRightlist temp;

	for(i = 0; i < NPC_HAVE_USER_LIST; i++)
	{
		m_iHaveItemUid[i].uid = -1;
		m_iHaveItemUid[i].nDamage = 0;

		if( m_DamagedUserList[i].nDamage > 0 )
		{
			m_iHaveItemUid[i].uid = m_DamagedUserList[i].iUid;
			m_iHaveItemUid[i].nDamage = m_DamagedUserList[i].nDamage;
		}
	}

	for(i = 2; i < NPC_HAVE_USER_LIST; i++)
	{
		temp.uid = m_iHaveItemUid[i].uid;
		temp.nDamage = m_iHaveItemUid[i].nDamage;
		
		j = i;

		while(m_iHaveItemUid[j-1].nDamage < temp.nDamage)
		{
			m_iHaveItemUid[j].uid = m_iHaveItemUid[j-1].uid;
			m_iHaveItemUid[j].nDamage = m_iHaveItemUid[j-1].nDamage;
			j--;

			if(j <= 0) break;
		}

		m_iHaveItemUid[j].uid = temp.uid;
		m_iHaveItemUid[j].nDamage = temp.nDamage;
	}

	for(i = 0; i < ITEM_USER_RIGHT_NUM; i++)
	{
		if(m_iHaveItemUid[i].nDamage > 0) total += m_iHaveItemUid[i].nDamage;
	}

	if(total <= 0) total = 1;

	for(i = 0; i < ITEM_USER_RIGHT_NUM; i++)
	{
		j = 0;
		j = (int)( (m_iHaveItemUid[i].nDamage * 100)/total );

		if(j > 100) j = 100;
		else if(j <= 0) j = 1;

		m_iHaveItemUid[i].nDamage = (BYTE)j;	
	}
}

DWORD CNpc::GetItemThrowTime()
{
	DWORD dwCurTime = 0;

	SYSTEMTIME SaveTime;
	GetLocalTime(&SaveTime);
	
	WORD wTemp = 0;
	DWORD dwYear = 0;
	DWORD dwMon = 0;
	DWORD dwDay = 0;
	DWORD dwHour = 0;
	DWORD dwMin = 0;
	DWORD dwSecond = 0;
										// 2 Byte 버리고
	wTemp = SaveTime.wYear << 12;		// 상위 4 Byte
	wTemp = wTemp >> 12;
	dwYear = (DWORD)wTemp; 
	dwYear = dwYear << 26;

	wTemp = SaveTime.wMonth << 12;		// 4 Byte
	wTemp = wTemp >> 12;
	dwMon = (DWORD)wTemp; 
	dwMon = dwMon << 22;

	wTemp = SaveTime.wDay << 11;		// 5 Byte
	wTemp = wTemp >> 11;
	dwDay = (DWORD)wTemp;
	dwDay = dwDay << 17;

	wTemp = SaveTime.wHour << 11;		// 5 Byte
	wTemp = wTemp >> 11;
	dwHour = (DWORD)wTemp;
	dwHour = dwHour << 12;

	wTemp = SaveTime.wMinute << 10;		// 6 Byte
	wTemp = wTemp >> 10;
	dwMin = (DWORD)wTemp;
	dwMin = dwMin << 6;

	wTemp = SaveTime.wSecond << 10;		// 6 Byte
	wTemp = wTemp >> 10;
	dwSecond = (DWORD)wTemp;

	dwCurTime = dwYear^dwMon^dwDay^dwHour^dwMin^dwSecond;

	return dwCurTime;
}

BOOL CNpc::CheckUserForNpc_Live(int x, int y)
{
	return TRUE;

	int min_x, min_y, max_x, max_y;

	min_x = m_sCurX - m_bySearchRange;		if( min_x < 0 ) min_x = 0;
	min_y = m_sCurY - m_bySearchRange;		if( min_y < 0 ) min_y = 0;
	max_x = m_sCurX + m_bySearchRange;
	max_y = m_sCurY + m_bySearchRange;

	if(max_x >= g_zone[m_ZoneIndex]->m_sizeMap.cx) max_x = g_zone[m_ZoneIndex]->m_sizeMap.cx - 2;
	if(max_y >= g_zone[m_ZoneIndex]->m_sizeMap.cy) max_y = g_zone[m_ZoneIndex]->m_sizeMap.cy - 2;

	int ix, iy;
	int target_uid;

	int tempLevel = 0, oldLevel = 1000;

	for(ix = min_x; ix <= max_x; ix++)
	{
		for(iy = min_y; iy <= max_y; iy++)
		{
			target_uid = m_pOrgMap[ix][iy].m_lUser;

			if( target_uid >= USER_BAND && target_uid < NPC_BAND ) return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//	Summon 으로 인해 변경된 위치정보를 주변에 보낸다.
//
void CNpc::SendNpcInfoBySummon(COM *pCom)
{
	int min_x = 0, min_y = 0;
	int max_x = 0, max_y = 0;

	int sx = m_sCurX / SIGHT_SIZE_X;
	int sy = m_sCurY / SIGHT_SIZE_Y;

	int delete_index = 0;
	char delete_send[1024];		::ZeroMemory(delete_send, sizeof(delete_send));
	FillNpcInfo(delete_send, delete_index, INFO_DELETE);

	min_x = (sx-1)*SIGHT_SIZE_X;
	max_x = (sx+2)*SIGHT_SIZE_X;
	min_y = (sy-1)*SIGHT_SIZE_Y;
	max_y = (sy+2)*SIGHT_SIZE_Y;

	SendToRange(pCom, delete_send, delete_index, min_x, min_y, max_x, max_y);
}
