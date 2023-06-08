# PikoKey ver1.1

![outlineiimage](/image/pikokey.png)

## About this page
- MIDIキーボード PikoKey Ver1.1版 組み立てキットの情報ページです。
- Pikoket 2 で頒布したβ版のバグフィックス版です。回路図に変更があります。

- Arduino Nano Everyは別売ですので、別途入手しておいてください。D20,D21を使用しているので、無印Nanoは使えません。

## Parts List

| リファレンス番号 | 個数 | 部品名 |
| ---------------- | ---- | -------|
| BT1 | 1 | バッテリーケース |
| CN1 | 1 | DINコネクタ | 
| D1, D2, D3, D4 | 4 | LED | 
| D5 | 1 | ショットキーダイオード SBM245L| 
| J1 | 1 | 3.5mmステレオジャック | 
| R1, R2 | 2 | 抵抗 220Ω | 
| R3, R4, R5, R6 | 4 | 抵抗 1kΩ | 
| SW1, SW2, SW3, SW4, SW5, SW6, SW7, SW8, SW9, SW10, SW11, SW12, SW13, SW14, SW15, SW16, SW17 | 17 | タクトスイッチ | 
| SW18 | 1 | スライドスイッチ | 
| U1 | 1 | Arduino Nano Every(別売) | 
| U2 | 1 | 5V出力昇圧DC/DCコンバーターキット | 
| - | 1	| 基板| 
| - | 3	| スペーサー| 
| - | 3 | 	ネジ| 


## 回路図

[Schematics](/Hardware/pikokeyV1_1_schematic.pdf)

## 基板パターン図

[PCB Pattern](/Hardware/pikokeyV1_1_pattern.pdf)

## 部品配置図

![PartsPlacementChart](/image/PikoKeyBeta_parts_place.PNG)

## 部品実装上の注意
### ダイオード
- ダイオードは極性があります。方向に注意してください。
- D5は線が付いている方向がカソード(K)です。

![PartsPlacementImage](/image/IMG_5644.JPG)


- LED(D1～D4)はリード線の短い方がカソード(K)です。以下の図を参考にしてください。

![PartsPlacementImage](/image/diode.PNG)

### U1 Arduino Nano Every

- U1 Arduino Nano Every はUSBコネクタが外側になるように取り付けてください。部品配置図を参考にしてください。

### U2 5V出力昇圧DC/DCコンバーターキット

- U2 5V出力昇圧DC/DCコンバーターキットは以下の写真の方向で取り付けてください。

![PartsPlacementImage](/image/IMG_5643.JPG)

## 追加工

- V1_1では回路図を変更したので追加工の必要はありません。 


## ソフトウェア
- Arduino IDEベースです。
- MIDIライブラリが必要です。MIDIライブラリは多種リリースされていますが、https://github.com/FortySevenEffects/arduino_midi_library を使用しています。

### サンプルコード
- Arduino Nano Every用です。
- ファンクションキーと鍵盤キーの同時押しで、MIDI CH変更や、Program Change等の送信が可能です。下図を参照ください。
 

[PikoKey_V1_1.ino](/Software/PikoKey_V1_1.ino)

![FunctionImage](/image/function.png)
