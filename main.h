#include <windows.h>
#include <string.h>
#include <winioctl.h>
#include <stdio.h>
#include <fcntl.h>
DWORD upMODE = 0;
#define UP_BOOT   1
#define UP_PART   2
#define UP_ALL    3


#define PD_0       7000
#define PD_1       7001
#define PD_2       7002
#define PD_3       7003
#define PD_4       7004
#define PD_5       7005
#define PD_6       7006
#define PD_7       7007

#define MBR_W      7008
#define MBR_S      7009
#define M_Hex      7010
#define M_Text     7011
#define MBR_RB     7015
#define MBR_RP     7016
#define MBR_RA     7017

#define D_A        7100
#define D_B        7101
#define D_C        7102
#define D_D        7103
#define D_E        7104
#define D_F        7105
#define D_G        7106
#define D_H        7107
#define D_I        7108
#define D_J        7109
#define D_K        7110
#define D_L        7111
#define D_M        7112
#define D_N        7113
#define D_O        7114
#define D_P        7115
#define D_Q        7116
#define D_R        7117
#define D_S        7118
#define D_T        7119
#define D_U        7120
#define D_V        7121
#define D_W        7122
#define D_X        7123
#define D_Y        7124
#define D_Z        7125


HINSTANCE ins;
HWND hWnd;

HWND INFO_DISK;
unsigned char CurrentDisk[24]="\0";
