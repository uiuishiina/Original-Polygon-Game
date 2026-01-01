//------  PolygonManager.cpp  ------
//------  QÆ  ------
#include"PolygonManager.h"
#include<cassert>


//@brief	---  ƒ|ƒŠƒSƒ“•`‰æŠÖ”  ---
void PolygonManager :: Draw(const CommandList& List, const UINT64 ID) {
    auto id = Map_.find(ID);
    if(id == Map_.end()) {
        return;
    }
    //•`‰æ
    id->second->Draw(List);
}