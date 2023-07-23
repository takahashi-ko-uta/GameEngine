#include "WinApp.h"
#pragma comment(lib,"winmm.lib")
#include <imgui_impl_dx12.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//�E�B���h�E�v���V�[�W��
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //ImGui�p�E�B���h�E�v���V�[�W��
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
        return true;
    //���b�Z�[�W�ŕ���
    switch (msg)
    {
    case WM_DESTROY://�E�B���h�E���j�����ꂽ
        PostQuitMessage(0);//OS�ɑ΂��āA�A�v���̏I����`����
        return 0;

    }
    return DefWindowProc(hwnd, msg, wparam, lparam);//�W���̏������s��
}
//������
void WinApp::Initialize()
{
    //�V�X�e���^�C�}�[�̕���\���グ��
    timeBeginPeriod(1);

    // �E�B���h�E�N���X�̐ݒ�
    w.cbSize = sizeof(WNDCLASSEX);
    w.lpfnWndProc = (WNDPROC)WindowProc;     // �E�B���h�E�v���V�[�W����ݒ�
    w.lpszClassName = L"DirectXGame";        // �E�B���h�E�N���X��
    w.hInstance = GetModuleHandle(nullptr);  // �E�B���h�E�n���h��
    w.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��

    // �E�B���h�E�N���X��OS�ɓo�^����
    RegisterClassEx(&w);

    RECT wrc = { 0,0,window_width,window_height };
    // �����ŃT�C�Y��␳����
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    // �E�B���h�E�I�u�W�F�N�g�̐���
    hwnd = CreateWindow(w.lpszClassName,    // �N���X��
        L"DirectXGame",                     // �^�C�g���o�[�̕���
        WS_OVERLAPPEDWINDOW,                // �W���I�ȃE�B���h�E�X�^�C��
        CW_USEDEFAULT,                      // �\��X���W�iOS�ɔC����j
        CW_USEDEFAULT,                      // �\��Y���W�iOS�ɔC����j
        wrc.right - wrc.left,               // �E�B���h�E����
        wrc.bottom - wrc.top,               // �E�B���h�E�c��
        nullptr,                            // �e�E�B���h�E�n���h��
        nullptr,                            // ���j���[�n���h��
        w.hInstance,                        // �Ăяo���A�v���P�[�V�����n���h��
        nullptr);                           // �I�v�V����

    // �E�B���h�E��\����Ԃɂ���
    ShowWindow(hwnd, SW_SHOW);
}
//�X�V
void WinApp::Update()
{

}
//�I��
void WinApp::Finalize()
{
    //�E�B���h�E�N���X��o�^����
    UnregisterClass(w.lpszClassName, w.hInstance);
}
//���b�Z�[�W�̏���
bool WinApp::ProcessMessage()
{
    MSG msg{};  // ���b�Z�[�W

    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (msg.message == WM_QUIT)
    {
        return true;
    }

    return false;
}