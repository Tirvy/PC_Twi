

#define UNIT_GF "GF02"
#define UNIT_MU "MU02"
#define UNIT_ST "ST02"
#define UNIT_PDS "PDS02"
#define UNIT_FG "FG02"
#define UNIT_DS "DS02"
#define UNIT_CR "CR02"
#define UNIT_CS "CS02"
#define UNIT_DR "DR02"
#define UNIT_WS "WS02"
#define UNIT_FM "FM02"
#define UNIT_DCK "SD02"

const float PlayerColor[][3] = {
	{1.0,0.0,0.0},//red
	{1.0,1.0,0.0},//yellow
	{1.0,0.0,1.0},//purple
	{0.0,1.0,0.0},//green
	{0.0,1.0,1.0},//cyan
	{0.0,0.0,1.0},//blue
	{1.0,1.0,1.0},//white
	{0.5,0.5,0.5} //gray
};

//Special Models
const char HIGH_ALERT_TOKEN[] = "high_alert";
const char FLAG[] = "flag";


//PlayerColors
const string PLAYER_COLOR_END[] = {"01","02","03","04","05","06","07","08","09"};
const string PLAYER_COLOR_FULL[] = {"Bloody","Asian","That Tasted Purple!","Orcish","Cyan and happy","Blue","White"\
,"Gray","That Looks Like Shiiiieeet"};

//Pictures
const string STRAT_A_PATH[] = {"sca_lead","sca_dipl","sca_asse","sca_prod","sca_trad","sca_warf","sca_tech","sca_bure"};
const string STRAT_B_PATH[] = {"scb_lead","scb_dipl","scb_asse","scb_prod","scb_trad","scb_warf","scb_tech","scb_bure"};
const char EMPTY_EVENT_IMG[] = "empty";
const char TACTICAL_ACTION_IMG[] = "tactical";
const char TRANSFER_ACTION_IMG[] = "transfer";
const char SYSTEM_IMG[] = "system";
const string SHIPS_IMG[] = {"U_GF","U_MU","U_ST","U_PDS","U_FG","U_DS","U_CS","U_CR","U_DR","U_WS","U_FM","U_DCK","U_SP_DCK","Sum Ting Wong"};
const string YESNO_IMG[] = {"img_Yes", "img_No"};
const string COUNTER_POOLS[] = {"CC_strat","CC_fleet","CC_comm"};
const char PLANET_IMG[] = "planet";
const char GOODS_IMG[] = "goods";
const char DICE_IMG[] = "dice";
const string TECHS_IMG[] = {"TechRed","TechGreen","TechBlue","TechYellow"};
const string OBJ_IMG[] = {"obj_preliminary", "obj_secret", "obj_public1", "obj_public2", "obj_special"};
const char ACTION_CARD[] = "action_card";

#define HEX_TAG "hex"

const char PathToTextures[] = "data/textures/";
const char PathToPStuffTextures[] = "data/textures/player_stuff/";
const char PathToUnitTextures[] = "data/textures/units/";
const char PathToCCTextures[] = "data/textures/counters/";
const char PathToSpecialTextures[] = "data/textures/specials/";
const char TextureExtension[] = ".png";
const char PathToSpecialsModel[] = "data/models/specials/";
const char PathToHexModel[] = "data/models/";
const char PathToUnitModel[] = "data/models/units/";
const char PathToCCModel[] = "data/models/counter.egg";
const char ModelsExtension[] = ".egg";
const char StardartHexFile[] = "hex";
#define PATH_TO_AA_TEXTURES "data/menu/actionarea/"