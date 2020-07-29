//https://yq.aliyun.com/articles/15243
#ifndef _WIN32 // �p�G���OWIN32���ҡA�h�n�ۭqgetch()���
#include <termio.h>

int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;

     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }

     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }

     ch = fgetc(stdin);
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
          return -1;
     }

     return ch;
}
#else
#include <conio.h>
#endif // _WIN32
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
/*
* �K�X��J��ơA�Ѽ� passwd ���K�X�w�İϡAbuff_len ���w�İϪ���
*/
char *passwd_input(char *passwd, int buff_len)
{
     char str;
     int i = 0;
     int enter_num = 13;
     int backspace_num;

     #ifndef _WIN32
     backspace_num = 127;
     #else
     backspace_num = 8;
     #endif

     if (passwd == NULL || buff_len <= 0) {
          return passwd;
     }
     while (1)
     {
          // �p�G�S�����U�˰h��
          if ((str = getch()) != (char)backspace_num) {
               if (i < buff_len - 1) {
                    passwd[i++] = str;
                    printf("*");
               }
          } else {
               if (i != 0) {
                    i--;
                    printf("\b \b");
               }
          }
          // �p�G���U�F�^����
          if (str == (char)enter_num) {
               passwd[--i] = '\0';

               if (i != buff_len - 1) {
                   printf("\b \b");
               }
               break;
          } else if (str == -1) {
               fprintf(stderr, "Error to set termio noecho.n");
          }
     }

     return passwd;
}

// ���եܨҡ]�Цۦ�K�[���Y�ɡ^
int main(void)
{
    char pass[7];
    setlocale(LC_ALL,"Chinese_Taiwan.950");
    printf("��J�K�X�]���׭��� 6�^�G");
    passwd_input(pass, 8);// \0+enter(8-2=6)
    printf("\n%s\n", pass);

     return 0;
}


