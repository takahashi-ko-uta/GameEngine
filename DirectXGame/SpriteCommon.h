#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>
#include <array>

#include <string>
#include "DirectXCommon.h"

//定数バッファ用データ構造体
struct ConstBufferDataMaterial{
	
};

//スプライト共通部
class SpriteCommon
{
public: //メンバ関数
	//初期化
	void Initialize(DirectXCommon* _dxCommon);

	//描画
	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	/// <summary>
	///テクスチャの読み込み
	/// </summary>
	/// <param name = "index">テクスチャ番号</param>
	void LoadTexture(uint32_t index, const std::string& fileName);
	/// <summary>
	///描画用テクスチャコマンド発行
	/// </summary>
	/// <param name = "index">テクスチャ番号</param>
	void SetTextureCommands(uint32_t index);

	//Getter
	DirectXCommon* GetDirectXCommon() { return dxCommon_; }
	ID3D12Resource* GetTextureBuffer(uint32_t index)const { return texBuffs_[index].Get(); }
private://静的メンバ変数
	//SRVの最大個数
	static const size_t kMaxSRVCount = 2056;
	//デフォルトテクスチャ格納ディレクトリ
	static std::string kDefaultTextureDirectoryPath;
private:
	DirectXCommon* dxCommon_;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	
	//テクスチャバッファ
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxSRVCount> texBuffs_;
};

