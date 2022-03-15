#ifndef INSTPARA_H
#define INSTPARA_H

extern ApiPara           ProtPara[CN_NUM_PARA];
extern ApiParaGroup      ProtParaGroup[CN_NUM_BOARD_PARA];
extern SalParaEditGroup  HmiParaEditGroup;


void AppParaPowerUpIni();
void AppParaInRef();
bool8 AppParaCoeEditUpdate(SalParaEditGroup* EditParaGroup,WORD wIndexStr,WORD wIndexEnd,WORD wIndexGroup,BOOL*pbChn);
INT32 AppParaDefault(WORD wIndex);
#endif // !INSTPARA_H

