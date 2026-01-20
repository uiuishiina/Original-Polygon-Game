#pragma once
//------  GameObjectManager.h  ------
//------  参照  ------
#include"../Object/GameObject.h"
#include"../Component/Component.h"
#include"../Component/Collision.h"
#include"Utility.h"
#include <functional>

namespace MyGame {
	//@brief	------  ゲームオブジェクト制御クラス  ------
	class GameObjectManager final
	{
	public:
		//@brief	---  インスタンス取得関数  ---
		static GameObjectManager& Instance()noexcept {
			static GameObjectManager Instance;
			return Instance;
		}

		//@brief	---  オブジェクト生成指示関数  ---
		template <typename T>
		[[nodiscard]] bool CreateGameObject(UINT64 ID = 0)noexcept {
			//オブジェクトクラス確認
			static_assert(std::is_base_of<GameObject, T>::value, "GameObject ではない物を作ろうとしています");
			auto Id = ID::Get<T>();
			auto it = GameObjects_.find(Id);
			if ( it != GameObjects_.end()) {
				return false;
			}
			//ランダムな数値を入れている可能性がある
			const auto handle =  ID::Get<T>();
			//関数をpairで保存
			auto func = [id = std::forward<UINT64>(ID)]() mutable {
				auto p = std::make_unique<T>();
				p->SetClassID(ID::Get<T>());
				p->SetParent(id);
				return p;
				};
			Create(std::move(func), handle);

			return true;
		}

		//@brief	---  初期化関数  ---
		void Clear()noexcept;

		//@brief	---  生成登録関数  ---
		void Create(std::function<std::unique_ptr<GameObject>()> creation, const UINT64 handle) noexcept;

		//@brief	---  UpDate関数  ---
		void UpDate()noexcept;

		//@brief	---  LateUpDate関数  ---
		void LateUpDate()noexcept;

		//@brief	---  SetHit関数  ---
		void SetHit(const UINT64 handle)noexcept;

		//@brief	---  描画指示関数  ---
		void Draw(const CommandList& List)noexcept;

		//@brief	---  ゲームオブジェクト取得関数  ---
		[[nodiscard]] std::optional<GameObject*>  GetGameObject(UINT64 OBNum)const noexcept;

		//@brief	---  ゲームオブジェクト削除関数  ---
		[[nodiscard]] void DeleteGameObject(const UINT64 handle)noexcept;

		//@brief	---  コンポーネント作成関数  ---
		template <typename T>
		void AddComponent()noexcept {
			static_assert(std::is_base_of<Component, T>::value, "Component ではない物を作ろうとしています");
			auto Id = ID::Get<T>();
			if (Component_.find(Id) != Component_.end()) {
				return;
			}
			auto c = std::make_unique<T>();
			Component_.emplace(Id, std::move(c));
		}

		//@brief	---  コンポーネント取得関数  ---
		template <typename T>
		[[nodiscard]] std::optional<Component*> GetComponent()noexcept {
			auto Id = ID::Get<T>();
			if (Component_.find(Id) == Component_.end()) {
				assert(false && "コンポーネント未作成");
				return std::nullopt;
			}
			const auto value = Component_.find(Id);
			return value->second.get();
		}
	private:
		GameObjectManager() = default;
		~GameObjectManager() = default;

		std::unordered_map<UINT64, std::unique_ptr<Component>> Component_{};//コンポーネント
		std::vector<std::pair<UINT64, std::function<std::unique_ptr<GameObject>()>>> Creation_{};  /// 生成関数
		std::unordered_map<UINT64, std::unique_ptr<GameObject>>                      GameObjects_{};   /// ゲームオブジェクト
		std::vector<std::pair<std::unique_ptr<GameObject>, int>>                     Delete_{};    /// 削除オブジェクトハンドル
		std::vector<UINT64>	Hit_{};
		UINT64	Index_ = 0;
	};
}