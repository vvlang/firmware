#pragma once

#include "ButtonThread.h"

// nRF52 ProMicro DIY Multi-Button Configuration
// P1.00: 确认选择/关机 (3秒)
// P1.01: 向上导航/切换GPS模式 (3秒)  
// P1.02: 向下导航/发送adhoc ping (3秒)
// P1.06: 向左导航/刷机模式 (3秒)
// P1.07: 向右导航/无功能

// Use existing ButtonThread for multi-button support
typedef ButtonThread MultiButtonThread;
typedef ButtonConfig MultiButtonConfig;

// Global instances for each button
extern MultiButtonThread *MainButtonThread;    // P1.00
extern MultiButtonThread *UpButtonThread;     // P1.01  
extern MultiButtonThread *DownButtonThread;    // P1.02
extern MultiButtonThread *LeftButtonThread;    // P1.06
extern MultiButtonThread *RightButtonThread;   // P1.07
