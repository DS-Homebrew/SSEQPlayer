#pragma once

void InstallSoundSys();
void free_pdata(data_t* userdata);
void free_seq();
void PlaySeq(const char* seqFile, const char* bnkFile, const char* war1, const char* war2, const char* war3, const char* war4);
void StopSeq();
void PauseSeq();
void FadeSeq();
void PlaySeqNDS(const char* ndsFile, const u32 SSEQOffset, const u32 SSEQSize, const u32 BANKOffset, const u32 BANKSize, const u32 WAVEARC1Offset, const u32 WAVEARC1Size, const u32 WAVEARC2Offset, const u32 WAVEARC2Size, const u32 WAVEARC3Offset, const u32 WAVEARC3Size, const u32 WAVEARC4Offset, const u32 WAVEARC4Size);
