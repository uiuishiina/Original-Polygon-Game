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
				if (GameObjects_.find(handle) != GameObjects_.end()) {
					continue;
				}
				const auto value = GameObjects_.find(handle);
				auto myPos = value->second->GetWorld().r[3];
				for (auto& it : GameObjects_) {
					if (it.first == handle || it.second->GetMyHandle() != value->second->HitClassHandle()) {
						continue;
					}
					auto hitRadius = value->second->GetRadius() + it.second->GetRadius();
					auto targetPos = it.second->GetWorld().r[3];
					auto distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(myPos, targetPos)));
					if (distance < hitRadius) {
						value->second->OnHit();
						it.second->OnHit();
					}
				}
			}
		}


		// オブジェクト削除処理
		if (!Delete_.empty()) {
			for (auto d = Delete_.begin(); d != Delete_.end();) {
				if ((d->second--) > 0) {
					++d;
					continue;
				}
				d = Delete_.erase(d);
			}
		}
	}

	void GameObjectManager :: SetHit(const UINT64 handle)noexcept {
		Hit_.emplace_back(handle);
	}

	//@brief	---  描画指示関数  ---
	void GameObjectManager::Draw(const CommandList& List)noexcept {
		for (auto& it : GameObjects_) {
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
		
		Delete_.emplace_back(std::move(it->second), 10);
		GameObjects_.erase(it);
	}
}