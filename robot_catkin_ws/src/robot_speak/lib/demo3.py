import snowboydecoder
import sys
import wave


wave_file = "/home/jia/ftp_share/Python3/output.wav"
model_file = "/home/jia/ftp_share/Python3/xx.pmdl"

f = wave.open(wave_file)
assert f.getnchannels() == 1, "Error: Snowboy only supports 1 channel of audio (mono, not stereo)"
assert f.getframerate() == 16000, "Error: Snowboy only supports 16K sampling rate"
assert f.getsampwidth() == 2, "Error: Snowboy only supports 16bit per sample"
data = f.readframes(f.getnframes())
f.close()

sensitivity = 0.5
detection = snowboydecoder.HotwordDetector(model_file, sensitivity=sensitivity)

ans = detection.detector.RunDetection(data)

if ans == 1:
    print('Hotword Detected!')
else:
    print('Hotword Not Detected!')

