#ifndef INSTSTATEIN_H
#define INSTSTATEIN_H

#define CN_NUM_GOCB           (16)
extern ApiGoInCb          GoInCB[CN_NUM_GOCB];


void UpdateNorStateIn();
void AppStateInPowerUpIni();

#endif //INSTSTATEIN_H