# pwmlib-opi
PWM Library for H3/H2+ Sunxi SoC

このライブラリはOrangePiやNanoPiなど、H3/H2+ベースのボードでハードウェアPWMを使うためのライブラリです。  
以下のボードで動作を確認しています。  
OrangePi PC(H3)  
OrangePi ZERO(H2+)  
NanoPi M1(H3)

このライブラリを使うためには以下のドライバーを有効にする必要が有ります。  
https://github.com/iboguslavsky/pwm-sunxi-opi0  

---

以下のプログラムでSG90マイクロサーボモータが 0°→ -90° → +90° → 0° に動きます。  
cc -o pwmt pwmt.c pwm.c -lwiringPi  
sudo ./pwmt  

サーボモータを使う場合、全体のパルス幅とActiveパルス幅で制御することができます。  
void pwm_begin(float period)  
period : 全体のパルス幅(mSec)  

void pwm_active(float period)  
period : Activeのパルス幅(mSec)  

---

サーバプロセスをバックグラウンドで起動することで、コマンドラインからサーボモータを制御することができます。  

cc -o pwmd pwmd.c pwm.c -lwiringPi  
sudo ./pwmd &  
./pwmc 20.0 1.45  
./pwmc 20.0 2.35  
./pwmc 20.0 0.625  

---

![sg90-1](https://cloud.githubusercontent.com/assets/6020549/24579311/a6b02e34-172d-11e7-82ad-8dacc48f609b.JPG)

---

This is the library to use hardware PWM by a board of H3/H2+ base such as OrangePi and NanoPi.  
It works by the following board.  
OrangePi PC(H3)  
OrangePi ZERO(H2+)  
NanoPi M1(H3)

You have to make the following driver effective to use this library.  
https://github.com/iboguslavsky/pwm-sunxi-opi0  

---

SG90 micro servomotor (http://akizukidenshi.com/download/ds/towerpro/SG90.pdf) works by the following program.  

cc -o pwmt pwmt.c pwm.c -lwiringPi  
sudo ./pwmt  

When using a servomotor, you can control with entire pulse width and active pulse width.  

void pwm_begin(float period)  
period : entire pulse width(mSec)  

void pwm_active(float period)  
period :  active pulse width(mSec)  

---

You can control servomotor from command-line with background server process like pigpio.  

cc -o pwmd pwmd.c pwm.c -lwiringPi  
sudo ./pwmd &  
cc -o pwmc pwmc.c pwm.c -lwiringPi  
./pwmc 20.0 1.45  
./pwmc 20.0 2.35  
./pwmc 20.0 0.625  

pwmc don't need delay time.  
