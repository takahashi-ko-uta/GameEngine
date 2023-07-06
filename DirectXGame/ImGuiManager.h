#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

//ImGui�̊Ǘ�
class ImGuiManager
{
private:
	//SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;
private://�����o�ϐ�
	WinApp* winApp_;
	DirectXCommon* dxCommon_;
public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp,DirectXCommon* dxCommon);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ImGui��t�J�n
	/// </summary>
	void Begin();

	/// <summary>
	/// ImGui��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// ��ʂւ̕`��
	/// </summary>
	void Draw();
};

