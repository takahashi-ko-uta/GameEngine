#pragma once
#include <xaudio2.h>
#include <fstream>
#include <wrl.h>
#include <map>
#include <string>

class Audio
{
public:
    //�`�����N�w�b�_
    struct ChunkHeader
    {
        char id[4];     //�`�����N����ID
        int32_t size;   //�`�����N�T�C�Y
    };
    //RIFF�w�b�_�`�����N
    struct RiffHeader
    {
        ChunkHeader chunk;  //"RIFF"
        char type[4];       //"WAVE"
    };
    //FMT�`�����N
    struct FormatChunk
    {
        ChunkHeader chunk;  //"fmt"
        WAVEFORMATEX fmt;   //�g�`�t�H�[�}�b�g
    };
    //�����f�[�^
    struct SoundData
    {
        //�g�`�t�H�[�}�b�g
        WAVEFORMATEX wfex;
        //�o�b�t�@�̐擪�A�h���X
        BYTE* pBuffer;
        //�o�b�t�@�̃T�C�Y
        unsigned int bufferSize;
    };

    //������
    void Initialize(const std::string directoryPath = "Resources/");
    //�f�[�^���
    void Finalize();
    //�����ǂݍ���
    void LoadWave(std::string filename);

    /// <summary>
    /// �T�E���h�f�[�^�̉��
    /// </summary>
    void Unload(SoundData* soundData);

    //�����Đ�
    void PlayWave(std::string filename);
private:
    // XAudio2�̃C���X�^���X
    Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
    // �T�E���h�f�[�^�̘A�z�z��
    std::map<std::string, SoundData> soundDatas_;
    // �T�E���h�i�[�f�B���N�g��
    std::string directoryPath_;
};

