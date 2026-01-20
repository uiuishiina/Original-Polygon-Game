//------  Collision.cpp  ------
//------  éQè∆  ------
#include"Collision.h"
#include<cassert>
////@brief	---  UpDate()ä÷êî  ---
//void Collision :: UpDate(std::unordered_map<UINT64, std::unique_ptr<GameObject>>& GameObject_)noexcept {
//
//}
//
////@btier	---  LateUpDate()ä÷êî  ---
//void Collision :: LateUpDate(std::unordered_map<UINT64, std::unique_ptr<GameObject>>& GameObject_)noexcept {
//	if (!UseComponentHandle_.empty()) {
//		for (auto handle : UseComponentHandle_) {
//			if (GameObject_.find(handle) != GameObject_.end()) {
//				continue;
//			}
//			const auto value = GameObject_.find(handle);
//			auto myPos = value->second->GetWorld().r[3];
//			for (auto& it : GameObject_) {
//				if (it.first == handle || it.second->GetMyHandle() != value->second->HitClassHandle()) {
//					continue;
//				}
//				auto hitRadius = value->second->GetRadius() + it.second->GetRadius();
//				auto targetPos = it.second->GetWorld().r[3];
//				auto distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(myPos, targetPos)));
//				if (distance < hitRadius) {
//					value->second->OnHit();
//					it.second->OnHit();
//				}
//			}
//		}
//	}
//}