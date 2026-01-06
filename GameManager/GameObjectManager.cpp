//------  GameObjectManager.h  ------
//------  参照  ------
#include"GameObjectManager.h"

namespace MyGame {
	
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

	//@brief	---  描画指示関数  ---
	void GameObjectManager::Draw(const CommandList& List)noexcept {
		for (auto& it : GameObjects_) {
			it.second->SetDrawCommand(List,1);
		}
	}

	//@brief	---  ゲームオブジェクト取得関数  ---
	[[nodiscard]] std::optional<GameObject*>  GameObjectManager :: GetGameObject(UINT64 OBNum)const noexcept {
		if (GameObjects_.find(OBNum) != GameObjects_.end()) {
			return  std::nullopt;
		}
		const auto value = GameObjects_.find(OBNum);
		assert(value->second && "ゲームオブジェクト取得ミス");
		return value->second.get();
	}
}