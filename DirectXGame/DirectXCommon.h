#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include <vector>
#include <chrono>

//DirectX���
class DirectXCommon
{
public://�����o�֐�
	//������
	void Initialize(WinApp* winApp);
	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	//getter
	static DirectXCommon* GetInstance();
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
	size_t GetBackBufferCount() const { return backBuffers.size(); }
private:
	//�e������
	void InitializeDevice();
	void InitializeCommand();
	void InitializeSwapChain();
	void InitializeRenderTargetView();
	void InitializeDepthBuffer();
	void InitializeFence();

	//FPS�Œ菉����
	void InitializeFixFPS();
	//FPS�Œ�X�V
	void UpdateFixFPS();

private:
	//DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	//WindowsAPI
	WinApp* winApp = nullptr;
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// �t�F���X�̐���
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	UINT64 fenceVal = 0;

	//�L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference_;

};