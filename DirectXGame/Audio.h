#pragma once
#include <xaudio2.h>
#include <fstream>
#include <wrl.h>
#include <map>
#include <string>

class Audio
{
public:
    //チャンクヘッダ
    struct ChunkHeader
    {
        char id[4];     //チャンク毎のID
        int32_t size;   //チャンクサイズ
    };
    //RIFFヘッダチャンク
    struct RiffHeader
    {
        ChunkHeader chunk;  //"RIFF"
        char type[4];       //"WAVE"
    };
    //FMTチャンク
    struct FormatChunk
    {
        ChunkHeader chunk;  //"fmt"
        WAVEFORMATEX fmt;   //波形フォーマット
    };
    //音声データ
    struct SoundData
    {
        //波形フォーマット
        WAVEFORMATEX wfex;
        //バッファの先頭アドレス
        BYTE* pBuffer;
        //バッファのサイズ
        unsigned int bufferSize;
    };

    //初期化
    void Initialize(const std::string directoryPath = "Resources/");
    //データ解放
    void Finalize();
    //音声読み込み
    void LoadWave(std::string filename);

    /// <summary>
    /// サウンドデータの解放
    /// </summary>
    void Unload(SoundData* soundData);

    //音声再生
    void PlayWave(std::string filename);
private:
    // XAudio2のインスタンス
    Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
    // サウンドデータの連想配列
    std::map<std::string, SoundData> soundDatas_;
    // サウンド格納ディレクトリ
    std::string directoryPath_;
};

