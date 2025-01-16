// EXEC.cpp: implementation of the EXEC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EXEC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EXEC::EXEC()
{

}

EXEC::~EXEC()
{

}

void EXEC::Parse(char *pBuf)
{
	int index = 0, i = 0, j = 0;
	char temp[1024];

	index += ParseSpace( temp, pBuf+index );

	if( !strcmp( temp, "STORE_OPEN" ) )
	{
		m_Exec = EXEC_STORE_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "FIELD_STORE_OPEN" ) ) 
	{
		m_Exec = EXEC_FIELD_STORE_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GUILD_SAY" ) )			// 鞘靛 惑牢捞 老馆 蜡历俊霸 辨靛傈 沥焊甫 焊咯淋
	{
		m_Exec = EXEC_GUILD_SAY;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	
	else if( !strcmp( temp, "GUILD_TAX" ) )			// 秦寸 惑痢俊 技陛阑 嘿牢促.
	{
		m_Exec = EXEC_GUILD_TAX;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GUILD_SCHEME" ) )		// 老沥 包府甫 茄促.
	{
		m_Exec = EXEC_GUILD_SCHEME;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GUILD_APPLY" ) )		// 辨靛傈阑 脚没茄促.
	{
		m_Exec = EXEC_GUILD_APPLY;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHECK_GUILD_USER" ) )	// 辨靛 窍快胶 盒剧阑 脚没茄促.
	{
		m_Exec = EXEC_CHECK_GUILD_USER;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}	
	else if( !strcmp( temp, "CHECK_GUILD_RANK" ) )	// 辨靛 窍快胶 盒剧阑 脚没茄促.
	{
		m_Exec = EXEC_CHECK_GUILD_RANK;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}		
	else if( !strcmp( temp, "BANK_OPEN" ) )			// 
	{
		m_Exec = EXEC_BANK_OPEN;
	}
	else if( !strcmp( temp, "ACCOUNT_BANK_OPEN" ) )			// 
	{
		m_Exec = EXEC_ACCOUNT_BANK_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GUILD_WAREHOUSE_OPEN" ) )			// 辨靛 芒绊甫 楷促. 
	{
		m_Exec = EXEC_GUILD_WAREHOUSE_OPEN;
	}	
	else if( !strcmp( temp, "SELL_OPEN" ) )			// 烙矫利栏肺 敬促...(眠饶俊 瘤匡巴)
	{
		m_Exec = EXEC_SELL_OPEN;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "REPAIR_OPEN" ) )
	{
		m_Exec = EXEC_REPAIR_OPEN;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ALL_CURE" ) )			// 葛电 hp, pp, sp甫 勈盲款促.
	{
		m_Exec = EXEC_ALL_CURE;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
/*	else if( !strcmp( temp, "CARE" ) )				// 葛电 惑怕捞惑甫 摹丰茄促
	{
		m_Exec = EXEC_CARE;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}	*/
	else if( !strcmp( temp, "SC_CHENGXU_KA" ) )
	{
		m_Exec = EXEC_SC_CHENGXU_KA;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ZONE_MOVE" ) )			// 眠啊!
	{
		m_Exec = EXEC_ZONE_MOVE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "FT_REPAIR" ) )			// 傍己傈锭巩俊 贸府啊 锅芭肺
	{
		m_Exec = EXEC_FT_REPAIR;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}		
	else if( !strcmp( temp, "FT_PEOPLE" ) )			// 傍己傈锭巩俊 贸府啊 锅芭肺
	{
		m_Exec = EXEC_FT_PEOPLE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}		
	else if( !strcmp( temp, "FT_MOVE" ) )			// 傍己傈锭巩俊 贸府啊 锅芭肺
	{
		m_Exec = EXEC_FT_MOVE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}	
	else if( !strcmp( temp, "MOVE" ) )			
	{
		m_Exec = EXEC_MOVE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "PSI_STORE_OPEN" ) )	
	{
		m_Exec = EXEC_PSI_STORE_OPEN;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "BBS_OPEN" ) )
	{
		m_Exec = EXEC_BBS_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EBODY_OPEN" ) )			// E_Body 惑痢阑 坷锹茄促.
	{
		m_Exec = EXEC_EBODY_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "EBODY_DEFINE" ) )			// E_Body 甫 犬牢茄促.
	{
		m_Exec = EXEC_EBODY_DEFINE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "UPGRADE_OPEN" ) )			// 酒捞袍 诀弊饭捞靛 牢磐其捞胶龋免.
	{
		m_Exec = EXEC_UPGRADE_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}	
	else if( !strcmp( temp, "MAKER_OPEN" ) )
	{
		m_Exec = EXEC_MAKER_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "STORAGE_OPEN" ) )
	{
		m_Exec = EXEC_STORAGE_OPEN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SAY" ) )
	{
		m_Exec = EXEC_SAY;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "PKSAY" ) )
	{
		m_Exec = EXEC_PKSAY;
	}
	else if( !strcmp( temp, "SAYSHAREN" ) )
	{
		m_Exec = EXEC_SAYSHAREN;
	}
	else if(!strcmp(temp,"KILL_BABY"))		//卖宠物
	{
		m_Exec = EXEC_KILL_BABY;
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		
	}
	else if( !strcmp( temp, "SAY_IN" ) )
	{
		m_Exec = EXEC_SAY_IN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "LINK" ) )
	{
		m_Exec = EXEC_LINK;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DISAPPEAR" ) )
	{
		m_Exec = EXEC_DISAPPEAR;
	}
	else if( !strcmp( temp, "RUN_MAGIC" ) )
	{
		m_Exec = EXEC_RUN_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DEAD" ) )
	{
		m_Exec = EXEC_DEAD;
	}
	else if( !strcmp( temp, "ROB_ITEM" ) )
	{
		m_Exec = EXEC_ROB_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SDROB_ITEM" ) )//优惠券
	{
		m_Exec = EXEC_SDROB_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "OPEN_YUANBAO" ) )
	{
		m_Exec = EXEC_OPEN_YUANBAO;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GO_EMO" ) )
	{
		m_Exec = EXEC_GO_EMO;
	}
	else if( !strcmp( temp, "EVENT_ROB_ITEM" ) )
	{
		m_Exec = EXEC_EVENT_ROB_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ROB_DN" ) )
	{
		m_Exec = EXEC_ROB_DN;		//^^

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ROB_LING" ) )
	{
		m_Exec = EXEC_ROB_LING;		//^^

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GIVE_ITEM" ) )
	{
		m_Exec = EXEC_GIVE_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GIVE_MAGIC_ITEM" ) )
	{
		m_Exec = EXEC_GIVE_MAGIC_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GIVE_EVENT_ITEM" ) )
	{
		m_Exec = EXEC_GIVE_EVENT_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}	
	else if( !strcmp( temp, "GIVE_GOLD" ) )
	{
		m_Exec = EXEC_GIVE_GOLD;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = (int)_atoi64( temp );
	}
	else if( !strcmp( temp, "GIVE_MAGIC" ) )
	{
		m_Exec = EXEC_GIVE_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "XP_UP" ) )
	{
		m_Exec = EXEC_XP_UP;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_LEVEL" ) )
	{
		m_Exec = EXEC_CHANGE_LEVEL;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_GENDER" ) )
	{
		m_Exec = EXEC_CHANGE_GENDER;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_HP" ) )
	{
		m_Exec = EXEC_CHANGE_HP;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_MP" ) )
	{
		m_Exec = EXEC_CHANGE_MP;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_STR" ) )
	{
		m_Exec = EXEC_CHANGE_STR;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_DEX" ) )
	{
		m_Exec = EXEC_CHANGE_DEX;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_INT" ) )
	{
		m_Exec = EXEC_CHANGE_INT;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_WIS" ) )
	{
		m_Exec = EXEC_CHANGE_WIS;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_CHR" ) )
	{
		m_Exec = EXEC_CHANGE_CHR;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_CON" ) )
	{
		m_Exec = EXEC_CHANGE_CON;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_DMAGIC" ) )
	{
		m_Exec = EXEC_CHANGE_DMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_WMAGIC" ) )
	{
		m_Exec = EXEC_CHANGE_WMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_BMAGIC" ) )
	{
		m_Exec = EXEC_CHANGE_BMAGIC;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_SWORD" ) )
	{
		m_Exec = EXEC_CHANGE_SWORD;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_SPEAR" ) )
	{
		m_Exec = EXEC_CHANGE_SPEAR;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_AXE" ) )
	{
		m_Exec = EXEC_CHANGE_AXE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_BOW" ) )
	{
		m_Exec = EXEC_CHANGE_BOW;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_KNUCKLE" ) )
	{
		m_Exec = EXEC_CHANGE_KNUCKLE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_WEAPONMAKE" ) )
	{
		m_Exec = EXEC_CHANGE_WEAPONMAKE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_ARMORMAKE" ) )
	{
		m_Exec = EXEC_CHANGE_ARMORMAKE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_ACCMAKE" ) )
	{
		m_Exec = EXEC_CHANGE_ACCMAKE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_POTIONMAKE" ) )
	{
		m_Exec = EXEC_CHANGE_POTIONMAKE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_COOKING" ) )
	{
		m_Exec = EXEC_CHANGE_COOKING;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SHOW_MAGIC" ) )
	{
		m_Exec = EXEC_SHOW_MAGIC;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SELECT_MSG" ) )
	{
		m_Exec = EXEC_SELECT_MSG;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 瘤巩 锅龋

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 急琶巩 1
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 捞亥飘 1

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 急琶巩 2
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 捞亥飘 2

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 急琶巩 3
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 捞亥飘 3

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 急琶巩 4
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );		// 捞亥飘 4
	}
/*	else if( !strcmp( temp, "MESSAGE_OK" ) )
	{
		m_Exec = EXEC_MESSAGE_OK;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "MESSAGE_NONE" ) )
	{
		m_Exec = EXEC_MESSAGE_NONE;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}*/
	else if( !strcmp( temp, "RUN_EVENT" ) )
	{
		m_Exec = EXEC_RUN_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "ADD_EVENT" ) )
	{
		m_Exec = EXEC_ADD_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}else if( !strcmp( temp, "ADD_SKILL" ) )
	{
		m_Exec = EXEC_ADD_SKILL;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DEL_EVENT" ) )
	{
		m_Exec = EXEC_DEL_EVENT;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "RETURN" ) )
	{
		m_Exec = EXEC_RETURN;
	}
	else if( !strcmp( temp, "SHOW_MAGIC" ) )
	{
		m_Exec = EXEC_SHOW_MAGIC;
		
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "CHANGE_MAGETYPE" ) )
	{
		m_Exec = EXEC_CHANGE_MAGETYPE;
		
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GUILD_OPEN" ) )
	{
		m_Exec = EXEC_GUILD_OPEN;
	}
	else if( !strcmp( temp, "GUARD_BOW" ) )
	{
		m_Exec = EXEC_GUARD_BOW;
	}
	else if( !strcmp( temp, "NPC_SAYING" ) )
	{
		m_Exec = EXEC_NPC_SAYING;
	}	
//	else if( !strcmp( temp, "NPC_DA" ) )
//	{
//		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
//		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
//		m_Exec = EXEC_NPC_DA;			//赌博买大
//	}
//	else if( !strcmp( temp, "NPC_XIAO" ) )
//	{
//		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
//		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
//		m_Exec = EXEC_NPC_XIAO;			//赌博买小
//	}
	else if( !strcmp( temp, "JUANKUAN" ) ) //捐款
	{
		m_Exec = EXEC_JUANKUAN;			//捐款
	}
	else if( !strcmp( temp, "BAOLV" ) ) //捐款
	{
		m_Exec = EXEC_BAOLV;			//捐款
	}
	else if( !strcmp( temp, "ADDRESS_WINDOW" ) )
	{
		m_Exec = EXEC_ADDRESS_WINDOW;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "INPUT_WINDOW" ) )
	{
		m_Exec = EXEC_INPUT_WINDOW;
	}	
	else if( !strcmp( temp, "INPUTGAME_WINDOW" ) )
	{
		m_Exec = EXEC_INPUTGAME_WINDOW;
	}		
/*	else if( !strcmp( temp, "ADD_GAMETIME_ITEM" ) )
	{
		m_Exec = EXEC_ADD_GAMETIME_ITEM;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}	*/
	else if( !strcmp( temp, "SC_FUSHU_PIN" ) )
	{
		m_Exec = EXEC_SC_FUSHU_PIN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "DRESSING" ) )
	{
		m_Exec = EXEC_DRESSING;
	}else if( !strcmp( temp, "GIVE_YB" ) )
	{
		m_Exec = EXEC_GIVE_YB;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "GIVE_DN" ) )
	{
		m_Exec = EXEC_GIVE_DN;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}else if( !strcmp( temp, "GIVE_HUFA" ) )
	{
		m_Exec = EXEC_GIVE_HUFA;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "SEND_MSG" ) )
	{
		m_Exec = EXEC_SEND_MSG;

		if( strlen( pBuf+index ) >= 128 )
		{
			strcpy( m_ExecChar, "" );
		}
		else
		{
			strcpy( m_ExecChar, pBuf+index );
		}
	}
	//================================================NPC说话
	else if( !strcmp( temp, "SEND_TOU" ) )
	{
		m_Exec = EXEC_SEND_TOU;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );

		if( strlen( pBuf+index ) >= 128 )
		{
			strcpy( m_ExecChar, "" );
		}
		else
		{
			strcpy( m_ExecChar, pBuf+index );
		}
	}
	else if( !strcmp( temp, "CHANGE_UPGRADE_ACC" ) )
	{
		m_Exec = EXEC_CHANGE_UPGRADE_ACC;
	}
	else if( !strcmp( temp, "APPLY_GUILD_RUN" ) )
	{
		m_Exec = EXEC_APPLY_GUILD_RUN;
	}
	else if( !strcmp( temp, "RR_ENTER" ) )
	{
		m_Exec = EXEC_RR_ENTER;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "MON_SAY" ) )
	{
		m_Exec = EXEC_MON_SAY;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );

		if( strlen( pBuf+index ) >= 128 )
		{
			strcpy( m_ExecChar, "" );
		}
		else
		{
			strcpy( m_ExecChar, pBuf+index );
		}
	}
	else if( !strcmp( temp, "SUMMON" ) )
	{
		m_Exec = EXEC_SUMMON;

		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	else if( !strcmp( temp, "HELPERCURE" ) )
	{
		m_Exec = EXEC_HELPERCURE;
	}
	else if( !strcmp( temp, "GIVE_PSI" ) )
	{
		m_Exec = EXEC_GIVE_PSI;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); // PSI Type
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); // Time
	}
 /*   else if( !strcmp( temp, "ON_WEB" ) ) 
	{
		m_Exec = EXCE_ON_WEB;		
	}*/
	else if( !strcmp( temp, "ON_SHOP" ) ) 
	{
		m_Exec = EXCE_ON_SHOP;		
	}
	else if( !strcmp( temp, "GOPK" ) ) //PK大赛say
	{
		m_Exec = EXCE_GOPK;		
	}
	//else if( !strcmp( temp, "GOSHAREN" ) ) //杀人狂
	//{
	//	m_Exec = EXCE_GOSHAREN;		
	//}
	else if( !strcmp( temp, "TRANSFORM" ) )
	{
		m_Exec = EXEC_TRANSFORM;
	}else if(!strcmp(temp,"C_100_1"))//打开100级防具转换窗口
	{
		m_Exec = EXEC_100_1;
	}else if(!strcmp(temp,"C_100_2"))//解除百级的属性限制
	{
		m_Exec = EXEC_100_2;
	}else if(!strcmp(temp,"C_100_3"))////46   添加及变更属性
	{
		m_Exec = EXEC_100_3;
	}else if(!strcmp(temp,"C_100_4"))////47   属性升级
	{
		m_Exec = EXEC_100_4;
	}else if(!strcmp(temp,"C_100_5"))////48   防具材料化
	{
		m_Exec = EXEC_100_5;
	}else if(!strcmp(temp,"C_100_6"))////48   解除材料化
	{
		m_Exec = EXEC_100_5;
	}else if(!strcmp(temp,"RUN_SKILL")){
		m_Exec = RUN_SKILL;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); // 要转换技能
    }else if(!strcmp(temp,"GIVE_ITEM_ALL")){
		m_Exec = EXEC_GIVE_ITEM_ALL;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //code
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //数量
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //改数
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //颜色
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //属性1
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //属性2
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //属性3
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //属性4
        index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); //属性5

	}else if(!strcmp(temp,"CHANGE_ATTRIBUTE_ITEM")){
		m_Exec = EXEC_CHANGE_ATTRIBUTE_ITEM;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		
    }else if(!strcmp(temp,"HUISHOU")){
		m_Exec = EXEC_HUISHOU;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp ); 
    }
    else if(!strcmp(temp,"CHANGE_JOB"))//转职
	{
		m_Exec = EXEC_CHANGE_JOB;
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//new job
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//new job
	}else if(!strcmp(temp,"STUDY_NEW_JOB_PSI"))//转职学习魔法
	{
		m_Exec = EXEC_STUDY_NEW_JOB_PSI;
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//new job
	}else if(!strcmp(temp,"CAN_GIVE_NEWER_ITEM"))//允许给新手装备
	{
		m_Exec = EXEC_CAN_GIVE_NEWER_ITEM;
	}else if(!strcmp(temp,"GIVE_NEWER_ITEM"))//新手职业装
	{
		m_Exec = EXEC_GIVE_NEWER_ITEM;
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//位置
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品id
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品数量
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品颜色
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品属性1
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品属性2
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品属性3
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品属性4
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品属性5
		index += ParseSpace( temp, pBuf+index );
		m_ExecInt[i++] = atoi( temp );		//物品属性6

	}else if(!strcmp(temp,"GIVE_NEWER_ITEM_FINISH"))//新手装备完成
	{
		m_Exec = EXEC_GIVE_NEWER_ITEM_FINISH;
	}else if( !strcmp( temp, "ONLINE_EXCHANGE" ) )
	{
		m_Exec = EXEC_ONLINE_EXCHANGE;	//充值后领取
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}
	/*else if( !strcmp( temp, "OFF_JJ" ) )		//卸下机甲
	{
		m_Exec = EXEC_OFF_JJ;
		index += ParseSpace( temp, pBuf+index );	m_ExecInt[i++] = atoi( temp );
	}*/
}

void EXEC::Init()
{
	for( int i = 0; i < MAX_EXEC_INT; i++)
	{
		m_ExecInt[i] = -1;
	}

	m_ExecChar[0] = 0;
}
