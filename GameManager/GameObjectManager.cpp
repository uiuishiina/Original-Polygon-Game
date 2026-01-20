//------  GameObjectManager.h  ------
//------  参照  ------
#include"GameObjectManager.h"

namespace MyGame {
	//@brief	---  初期化関数  ---
	void GameObjectManager :: Clear()noexcept {
		Creation_.clear();
		GameObjects_.clear();
		Delete_.clear();
		Component_.clear();
		Hit_.clear();

		Creation_.shrink_to_fit();
		Delete_.shrink_to_fit();
		Hit_.shrink_to_fit();
		Index_ = 0;
	}
	
	//@brief	---  生成登録関数  ---
	void GameObjectManager :: Create(std::function<std::unique_ptr<GameObject>()> creation, const UINT64 handle) noexcept {
		Creation_.emplace_back(handle,std::move(creation));
	}

	//@brief	---  UpDate関数  ---
	void GameObjectManager :: UpDate()noexcept {
		//ゲームオブジェクト作成
		if (!Creation_.empty()) {
			for (auto& create : Creation_) {
				auto p = create.second();
				p->SetMyHandle(create.first);
				p->Initialize();
				GameObjects_.emplace(create.first, std::move(p));
			}
			Creation_.clear();
		}
		for (auto& it : GameObjects_) {
			it.second->UpDate();
		}
	}

	//@brief	---  LateUpDate関数  ---
	void GameObjectManager::LateUpDate()noexcept {
		if (!Hit_.empty()) {
			for (auto handle : Hit_) {
				//Hitがあるか
				if (GameObjects_.find(handle) == GameObjects_.end()) {
					continue;
				}
				
				const auto value = GameObjects_.find(handle);
				if (GameObjects_.find(value->second->HitClassHandle()) == GameObjects_.end()) {
					continue;
				}
				const auto it = GameObjects_.find(value->second->HitClassHandle());
				auto myPos = value->second->GetWorld().r[3];

				auto hitRadius = value->second->GetRadius() + it->second->GetRadius();
				auto targetPos = it->second->GetWorld().r[3];
				auto distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(myPos, targetPos)));
				if (distance < hitRadius) {
					value->second->OnHit();
					it->second->OnHit();
				}
			}
			Hit_.clear();
		}

		if (!DeleteHand_.empty()) {
			for (auto i : DeleteHand_) {
				auto it = GameObjects_.find(i);
				if (it == GameObjects_.end()) {
					continue;
				}
				Delete_.emplace_back(std::move(it->second), 10);
				GameObjects_.erase(it);
			}
			DeleteHand_.clear();
		}

		// オブジェクト削除処理
		if (!Delete_.empty()) {
			auto count = 0;
			for (auto& d : Delete_) {
				if ((d.second--) > 0) {
					count++;
					continue;
				}
				Delete_.erase(Delete_.begin() + count);
			}
		}
	}

	void GameObjectManager :: SetHit(const UINT64 handle)noexcept {
		Hit_.emplace_back(handle);
	}

	//@brief	---  描画指示関数  ---
	void GameObjectManager::Draw(const CommandList& List)noexcept {
		for (auto& it : GameObjects_) {
			if (!Delete_.empty()) {
				Delete_;
			}
			it.second->SetDrawCommand(List,1);
		}
	}

	//@brief	---  ゲームオブジェクト取得関数  ---
	[[nodiscard]] std::optional<GameObject*>  GameObjectManager :: GetGameObject(UINT64 OBNum)const noexcept {
		if (GameObjects_.find(OBNum) == GameObjects_.end()) {
			return  std::nullopt;
		}
		const auto value = GameObjects_.find(OBNum);
		assert(value->second && "ゲームオブジェクト取得ミス");
		return value->second.get();
	}

	//@brief	---  ゲームオブジェクト削除関数  ---
	[[nodiscard]] void GameObjectManager :: DeleteGameObject(const UINT64 handle)noexcept{
		auto it = GameObjects_.find(handle);
		if (it == GameObjects_.end()) { return; }
		//Delete_.emplace_back(std::move(it->second), 10);//std::move(
		DeleteHand_.emplace_back(handle);
	}
	//@brief	---  ゲームオブジェクト削除登録関数  ---
	[[nodiscard]] void GameObjectManager :: SetDeleteHandle(const UINT64 handle)noexcept {
		
	}
}