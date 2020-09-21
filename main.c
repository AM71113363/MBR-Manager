#include "main.h"
char szClassName[ ] = "MBRBackUpManager";

#define CHANGEIT(_x_,_y_) CheckMenuItem(GetMenu(hWnd),_x_,_y_)

static HFONT hFont;
LPBYTE lpSector;
DWORD  dwSize =512; 
unsigned char num[4];
HWND POS[512];
#define ADDSHELL(_a_,_b_,_c_,_d_) POS[_a_]=CreateWindow("STATIC","",WS_CHILD|WS_VISIBLE ,10+(_b_*20),20+(_c_*18),17,16,hwnd,(HMENU)_d_,ins,NULL); //SendMessage(POS[_a_], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1, 0));}
#define ADDSHELLP(_a_,_b_,_c_,_d_) POS[_a_]=CreateWindow("STATIC","",WS_CHILD|WS_VISIBLE ,10+(_b_*20),12+(_c_*18),17,16,hwnd,(HMENU)_d_,ins,NULL); //SendMessage(POS[_a_], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1, 0));}
			
void FillTable(int c)
{
     DWORD i;
      for(i=0;i<512;i++)
      {
         if(c)
         {
             if(isprint(lpSector[i]))  
                   sprintf(num,"% 2C\0",lpSector[i]); 
             else    
                   sprintf(num,"% 2C\0",' '); 
         }
         else
         {               
            sprintf(num,"%02X\0",lpSector[i]);                  
         }
            SetWindowText(POS[i],num);             
      }    
}            
void CenterOnScreen(HWND target)
{
     RECT rcClient, rcDesktop;
	 int nX, nY;
     SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
     GetWindowRect(target, &rcClient);
     nX=((rcDesktop.right - rcDesktop.left) / 2) -((rcClient.right - rcClient.left) / 2);
     nY=((rcDesktop.bottom - rcDesktop.top) / 2) -((rcClient.bottom - rcClient.top) / 2);
     SetWindowPos(target, NULL, nX, nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
     SetWindowPos(target, HWND_TOPMOST,0,0,0,0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE);
							
  return;
}

void OpenDrive_help(DWORD id)
{
      CHANGEIT(D_A,(id==D_A)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_B,(id==D_B)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_C,(id==D_C)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_D,(id==D_D)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_E,(id==D_E)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_F,(id==D_F)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_G,(id==D_G)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_H,(id==D_H)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_I,(id==D_I)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_J,(id==D_J)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_K,(id==D_K)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_L,(id==D_L)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_M,(id==D_M)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_N,(id==D_N)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_O,(id==D_O)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_P,(id==D_P)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_Q,(id==D_Q)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_R,(id==D_R)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_S,(id==D_S)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_T,(id==D_T)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_U,(id==D_U)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_V,(id==D_V)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_W,(id==D_W)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_X,(id==D_X)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_Y,(id==D_Y)?MF_CHECKED:MF_UNCHECKED );
      CHANGEIT(D_Z,(id==D_Z)?MF_CHECKED:MF_UNCHECKED );    

      CHANGEIT(PD_0,(id==PD_0)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_1,(id==PD_1)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_2,(id==PD_2)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_3,(id==PD_3)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_4,(id==PD_4)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_5,(id==PD_5)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_6,(id==PD_6)?MF_CHECKED:MF_UNCHECKED ); 
      CHANGEIT(PD_7,(id==PD_7)?MF_CHECKED:MF_UNCHECKED );      
}



void StartScan(HANDLE hd)
{
    DISK_GEOMETRY ge;
    DWORD rs;
    __int64 dd;
    unsigned char temp[1024];

    if(DeviceIoControl(hd, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &ge, sizeof(ge), &rs, NULL))
    {
          
          
       dd = (__int64)ge.Cylinders.LowPart;
       dd *= (__int64)ge.TracksPerCylinder;
       dd *= (__int64)ge.SectorsPerTrack;
       dd *= (__int64)ge.BytesPerSector;
       
       sprintf(temp,"[ %I64d bytes = %f Gb ]\r\n"
						 "Cylinders                  : %d [ 0x%X ]\r\n"
                         "Tracks/Cylinder       : %d [ 0x%X ]\r\n"
                         "Sectors/Track         : %d [ 0x%X ]\r\n"
                         "Bytes/Sector           : %d [ 0x%X ]\0",dd, ((FLOAT)dd)/(1024*1024*1024),
                         ge.Cylinders.LowPart,ge.Cylinders.LowPart,
          ge.TracksPerCylinder,ge.TracksPerCylinder, 
          ge.SectorsPerTrack, ge.SectorsPerTrack,
          ge.BytesPerSector, ge.BytesPerSector); 
          SetWindowText(INFO_DISK,temp); 
     }
     else
     {
         SetWindowText(INFO_DISK,"Error: DeviceIoControl"); 
     }
}

void LoadDrive(DWORD n,DWORD id)
{
   unsigned char dn[8] = "\\\\?\\A:\0";
   HANDLE  hCD;
   DWORD   dwNotUsed;	
   dn[4]= n;
   sprintf(CurrentDisk,"%s\0",dn);
   hCD = CreateFile (dn,GENERIC_READ,1|2,NULL,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING|FILE_FLAG_WRITE_THROUGH,NULL);
   if (hCD != INVALID_HANDLE_VALUE)
   {
       SetFilePointer(hCD,0,NULL,FILE_BEGIN);
       if(ReadFile (hCD, lpSector, dwSize, &dwNotUsed, NULL))
       {
         FillTable(0); 
         OpenDrive_help(id);
         StartScan(hCD);
       }
       CloseHandle (hCD); 
   }
   else
   {
      MessageBox(hWnd,dn,"Can't Open Drive",MB_OK	|MB_ICONERROR|MB_SYSTEMMODAL);    
   }

return;    
}
/////////////////////////////

void LoadPhysicalDrive(DWORD n,DWORD id)
{
   unsigned char dn[24] = "\\\\?\\PhysicalDrive0\0";
   HANDLE  hCD;
   DWORD   dwNotUsed;	
   dn[17]= n;
   sprintf(CurrentDisk,"%s\0",dn);
   hCD = CreateFile (dn,GENERIC_READ,1|2,NULL,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING|FILE_FLAG_WRITE_THROUGH,NULL);
   if (hCD != INVALID_HANDLE_VALUE)
   {
       SetFilePointer(hCD,0,NULL,FILE_BEGIN);
       if(ReadFile (hCD, lpSector, dwSize, &dwNotUsed, NULL))
       {
         FillTable(0); 
         OpenDrive_help(id);
         StartScan(hCD);
       }
       CloseHandle (hCD); 
   }
   else
   {
      MessageBox(hWnd,dn,"Can't Open Drive",MB_OK	|MB_ICONERROR|MB_SYSTEMMODAL);    
   }

return;    
}

void WriteToDisk()
{
     int res;
     HANDLE  hCD;
     DWORD   dwNotUsed;
     if(CurrentDisk[0]!='\\')
     {
        MessageBox(hWnd,"Must Open A Drive First!","Info",MB_OK	|MB_ICONERROR|MB_SYSTEMMODAL); 
        return;
     }
     
     res = MessageBox(hWnd,"Write Data To Disk",CurrentDisk,MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL); 
     if(res != IDYES)
     {
        return;      
     }
   	
     hCD = CreateFile (CurrentDisk,GENERIC_READ|GENERIC_WRITE,1|2,NULL,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING|FILE_FLAG_WRITE_THROUGH,NULL);
     if (hCD == INVALID_HANDLE_VALUE)
     {
         MessageBox(hWnd,"Can't Open Drive",CurrentDisk,MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);    
         return;
     }
     SetFilePointer(hCD,0,NULL,FILE_BEGIN);
     if(!WriteFile (hCD, lpSector, dwSize, &dwNotUsed, NULL))
     {
        MessageBox(hWnd,"Can't Write To Disk",CurrentDisk,MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);             
     }
     CloseHandle (hCD);   
}

void SaveToFile()
{
     
   OPENFILENAME ofn;
   char szFileName[MAX_PATH];

   ZeroMemory(&ofn, sizeof(ofn));
   szFileName[0] = 0;

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hWnd;
   ofn.lpstrFilter = "Bin Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0\0";
   ofn.lpstrFile = szFileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.lpstrDefExt = "bin";
   ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
         
   if(GetSaveFileName(&ofn))
   {
   HANDLE sFile;
   DWORD dwWritten;
   sFile = CreateFile(szFileName, GENERIC_WRITE, 0, 0,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
   if(sFile == INVALID_HANDLE_VALUE)
   {
      MessageBox(hWnd, "Can't Create File", "Error", MB_OK | MB_ICONEXCLAMATION);
      return;
   }
   
   if(!WriteFile (sFile, lpSector, dwSize, &dwWritten, NULL))
   {
      MessageBox(hWnd, "Can't Write to File", "Error", MB_OK | MB_ICONEXCLAMATION);
   }
   else
   {
      MessageBox(hWnd, "File Saved", "Info", MB_OK | MB_ICONINFORMATION);
   }
   CloseHandle(sFile);
   }
}

void UpdateData()
{
   HANDLE sFile;
   DWORD dwFileSize;
   unsigned char pszFileText[512];
   DWORD dwRead;
   DWORD i;
      OPENFILENAME ofn;
   char szFileName[MAX_PATH];

   ZeroMemory(&ofn, sizeof(ofn));
   szFileName[0] = 0;

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hWnd;
   ofn.lpstrFilter = "All Files (*.*)\0*.*\0\0";
   ofn.lpstrFile = szFileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.lpstrDefExt = "";
   ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
   if(GetOpenFileName(&ofn))
   {
   sFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
   if(sFile == INVALID_HANDLE_VALUE)
   {
      MessageBox(hWnd, "Can't Open File", "Error", MB_OK | MB_ICONEXCLAMATION);
      return;
   }
   dwFileSize = GetFileSize(sFile, NULL);
   if(dwFileSize!=446 && dwFileSize!=512)
   {
      MessageBox(hWnd, "It's not a valid MBR File", "Error", MB_OK | MB_ICONEXCLAMATION);
      return;
   }
   if(!ReadFile(sFile, pszFileText, dwFileSize, &dwRead, NULL))
   {
      MessageBox(hWnd, "Can't Read File", "Error", MB_OK | MB_ICONEXCLAMATION);
      CloseHandle(sFile);
      return;
   }
   
   if(upMODE == UP_BOOT)
   {
	 for(i=0;i<446;i++)
	 {
	     lpSector[i] = pszFileText[i]; 
	 }
	 FillTable(0); 
	
   }
   
   else if(upMODE == UP_PART)
   {
      if(dwFileSize!=512)
      {
            MessageBox(hWnd, "File must be 512 Bytes", "Error", MB_OK | MB_ICONEXCLAMATION);
			CloseHandle(sFile);
			return;
      }
     
	  for(i=446;i<512;i++)
	  {
	     lpSector[i] = pszFileText[i]; 
	  }
	  FillTable(0); 
	
   }
   else if(upMODE == UP_ALL)
   {
      if(dwFileSize!=512)
      {
            MessageBox(hWnd, "File must be 512 Bytes", "Error", MB_OK | MB_ICONEXCLAMATION);
			CloseHandle(sFile);
			return;
      }
     
	  for(i=0;i<512;i++)
	  {
	     lpSector[i] = pszFileText[i]; 
	  }
	  FillTable(0); 
	
   }
   CloseHandle(sFile);
   }
  else
  {
     MessageBox(hWnd, "Load of file failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
  }
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
             
			HWND aaa;
			hWnd = hwnd;
            hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");	
            
			aaa= CreateWindow("BUTTON","Boot Loader",WS_CHILD|WS_VISIBLE| BS_GROUPBOX,2,0,635,296,hwnd,NULL,ins,NULL);
            SendMessage(aaa, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1, 0));
            aaa= CreateWindow("BUTTON","Partition Table",WS_CHILD|WS_VISIBLE| BS_GROUPBOX,2,299,375,98,hwnd,NULL,ins,NULL);
            SendMessage(aaa, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1, 0));
   
            INFO_DISK= CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE| ES_WANTRETURN,380,306,256,90,hwnd,NULL,ins,NULL);
            SendMessage(INFO_DISK, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1, 0));
                    
			aaa = CreateWindow("STATIC",NULL,SS_BITMAP | WS_CHILD |WS_VISIBLE  ,0,0,570,186,hwnd,0,ins,NULL);
            SendMessage(aaa, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(ins,MAKEINTRESOURCE(300)));    
            DWORD r = 0;
            DWORD c = 0;
            DWORD n = 0; 
           for(r=0;r<14;r++)
            {
               for(c=0;c<31;c++){ ADDSHELL(n++,c,r,0);}
            } 
            for(c=0;c<12;c++) ADDSHELL(n++,c,r,0);
            
            r+=3;
            for(c=0;c<16;c++) ADDSHELLP(n++,c,r,0);//part 1
            r++;
            for(c=0;c<16;c++) ADDSHELLP(n++,c,r,0);//part2
            r++;
            for(c=0;c<16;c++) ADDSHELLP(n++,c,r,0);//part3
            r++;
            for(c=0;c<18;c++) ADDSHELLP(n++,c,r,0);//part4
             
            for(c=0;c<512;c++) SendMessage(POS[c], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(1, 0));
            
           lpSector = VirtualAlloc(NULL,dwSize,0x1000|0x2000,4);
            CenterOnScreen(hwnd);  
        }
        break;
        case WM_COMMAND:
        { //WM_COMMAND
          switch(LOWORD(wParam))
          { //switch
      ////////////////////////
      case PD_0: { LoadPhysicalDrive('0',PD_0);} break;
      case PD_1: { LoadPhysicalDrive('1',PD_1);} break;
      case PD_2: { LoadPhysicalDrive('2',PD_2);} break;
      case PD_3: { LoadPhysicalDrive('3',PD_3);} break;
      case PD_4: { LoadPhysicalDrive('4',PD_4);} break;
      case PD_5: { LoadPhysicalDrive('5',PD_5);} break;
      case PD_6: { LoadPhysicalDrive('6',PD_6);} break;
      case PD_7: { LoadPhysicalDrive('7',PD_7);} break;
      
      case D_A: { LoadDrive('A',D_A); } break;
      case D_B: { LoadDrive('B',D_B); } break;
      case D_C: { LoadDrive('C',D_C); } break;
      case D_D: { LoadDrive('D',D_D); } break;
      case D_E: { LoadDrive('E',D_E); } break;
      case D_F: { LoadDrive('F',D_F); } break;
      case D_G: { LoadDrive('G',D_G); } break;
      case D_H: { LoadDrive('H',D_H); } break;
      case D_I: { LoadDrive('I',D_I); } break;
      case D_J: { LoadDrive('J',D_J); } break;
      case D_K: { LoadDrive('K',D_K); } break;
      case D_L: { LoadDrive('L',D_L); } break;
      case D_M: { LoadDrive('M',D_M); } break;
      case D_N: { LoadDrive('N',D_N); } break;
      case D_O: { LoadDrive('O',D_O); } break;
      case D_P: { LoadDrive('P',D_P); } break;
      case D_Q: { LoadDrive('Q',D_Q); } break;
      case D_R: { LoadDrive('R',D_R); } break;
      case D_S: { LoadDrive('S',D_S); } break;
      case D_T: { LoadDrive('T',D_T); } break;
      case D_U: { LoadDrive('U',D_U); } break;
      case D_V: { LoadDrive('V',D_V); } break;
      case D_W: { LoadDrive('W',D_W); } break;
      case D_X: { LoadDrive('X',D_X); } break;
      case D_Y: { LoadDrive('Y',D_Y); } break;
      case D_Z: { LoadDrive('Z',D_Z); } break;
      
      // change View hex or text
      case M_Hex: {  FillTable(0); } break;
      case M_Text: {  FillTable(1); } break;
      
      //write to disk
      case MBR_W: { CreateThread(0,0,(LPTHREAD_START_ROUTINE)WriteToDisk,0,0,0); } break;
      // save mbr to file
      case MBR_S: { CreateThread(0,0,(LPTHREAD_START_ROUTINE)SaveToFile,0,0,0); } break;
      //update table data
      case MBR_RB: { upMODE = UP_BOOT; CreateThread(0,0,(LPTHREAD_START_ROUTINE)UpdateData,0,0,0); } break;
      case MBR_RP: { upMODE = UP_PART; CreateThread(0,0,(LPTHREAD_START_ROUTINE)UpdateData,0,0,0); } break;
      case MBR_RA: { upMODE = UP_ALL; CreateThread(0,0,(LPTHREAD_START_ROUTINE)UpdateData,0,0,0); } break;
      
      
      case 8000: {  exit(0);} break;
      case 1000: { } break;

      ////////////////////////////////////////     
      } 
      }
      break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue   if(SendDlgItemMessage(hwnd,4000,BM_GETCHECK,0,0)==BST_CHECKED)*/
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    ins = hThisInstance;
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(ins,MAKEINTRESOURCE(200));
    wincl.hIconSm = LoadIcon(ins,MAKEINTRESOURCE(200));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = "MAINMENU";                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+1;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "MBR Manager",       /* Title Text */
           WS_SYSMENU | WS_OVERLAPPED, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           647,                 /* The programs width */
           450,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

