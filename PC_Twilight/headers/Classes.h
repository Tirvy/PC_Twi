

class Planet;
class Hex;
class Army;
struct Unit;
struct Roll;
class SystemDeck;
class GameStats;
class Hand;
class Map;
class Player;
class UnitStats;
struct MoveStats;
class GameEffect;
class GameEffectQueue;
class VictoryPoint;
class Interface;
struct ExecuteParams;
struct TradeRoute;
struct GameInitSettings;
class LinkedHexes;			//ZoldnMap
class SpeedMap;				//ZoldnMap
class PathFinder;			//ZoldnMap
struct SpawnUnit;



Army* FindArmy(int a, int b, Player*owner, bool CreateNew = false, Planet * planet = 0);
Army* FindArmy(Hex* hex, Player*owner, bool CreateNew = false, Planet * planet = 0);
Army* FindAnyArmy(Hex* hex, Planet* planet = 0);




/*class Hand{
	Card* cards;
	bool*tapped;
};*/


