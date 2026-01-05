#pragma once
//------  GameObjectManager.h  ------
//------  参照  ------
#include"../Object/GameObject.h"
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
		[[nodiscard]] bool CreateGameObject()noexcept {
			//オブジェクトクラス確認
			static_assert(std::is_base_of<GameObject, T>::value, "GameObject ではない物を作ろうとしています");
			//ランダムな数値を入れている可能性がある
			const auto handle = ++Index_;
			//関数をpairで保存
			auto func = []() mutable {
				auto p = std::make_unique<T>();
				p->SetClassID(ID::Get<T>());
				return p;
				};
			Create(std::move(func), handle);

			return true;
		}

		//@brief	---  生成登録関数  ---
		void Create(std::function<std::unique_ptr<GameObject>()> creation, const UINT64 handle) noexcept;

		//@brief	---  UpDate関数  ---
		void UpDate()noexcept;

		//@brief	---  描画指示関数  ---
		void Draw(const CommandList& List)noexcept;
	private:
		GameObjectManager() = default;
		~GameObjectManager() = default;

		std::vector<std::pair<UINT64, std::function<std::unique_ptr<GameObject>()>>> Creation_{};  /// 生成関数
		std::unordered_map<UINT64, std::unique_ptr<GameObject>>                      GameObjects_{};   /// ゲームオブジェクト
		std::vector<std::pair<std::unique_ptr<GameObject>, int>>                     Delete_{};    /// 削除オブジェクトハンドル
		std::vector<UINT64>                                                          Hit_{};       /// 衝突判定オブジェクトハンドル
		UINT64	Index_ = 0;
	};

}