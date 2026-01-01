#pragma once
//------  PolygonManager.h  ------
//------  参照  ------
#include"Utility.h"
#include"../Polygon/Polygon.h"
#include"../DirectX/CommandList.h"
#include <unordered_map>
#include <memory>

//@brief	------  ポリゴン制御クラス  ------
class PolygonManager final
{
public:
	static PolygonManager& Instance()noexcept {
		static PolygonManager Instance;
		return Instance;
	}

	//@brief	---  ポリゴン作成関数  ---
	template <class T>
	[[nodiscard]] UINT64 Create()noexcept {
		const auto id = ID::Get<T>();
		if (Map_.find(id) != Map_.end()) {
			// 既に存在している場合は何もしない
			return id;
		}

		// 形状の生成と登録
		auto p = std::make_unique<T>();
		if (!p->Create()) {
			assert(false && "形状の生成に失敗しました");
			return 0;
		}
		Map_.emplace(id, std::move(p));
		return id;
	}


	//@brief	---  ポリゴン描画関数  ---
	void Draw(const CommandList& List ,const UINT64 ID);

	//
private:
	PolygonManager() = default;
	~PolygonManager() = default;
	std::unordered_map<UINT64, std::unique_ptr<class Polygon>> Map_;  /// 形状コンテナ
};