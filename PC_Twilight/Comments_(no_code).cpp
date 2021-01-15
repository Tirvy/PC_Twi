/*
Правила кода:
1. Все enum и константы, которые могут пригодяться вне модуля - в Defines.cpp
2. Любое число, которое может поменяться при незначительных изменениях в правилах - в константы
3. Ртуть - FTW
*/

/*
Замеченные баги:
1. cnf и pass дают возможность избежать необходимого выбора.
2. Memory leak в tacticl.cpp
3. A: A Carrier that is transporting Ground Forces or PDSs must be active in order to unload them (TI rules p. 28),
*/


/*
// for's for some situations
for (i=0;i<_GameStats.GetPlayersNumber();++i)
for (i=n;i<_GameStats.GetPlayersNumber()+n;++i)
for (i=0;i<_GameStats.GetPlayersNumber();++i)
*/

// Тестим ртуть
// testestest