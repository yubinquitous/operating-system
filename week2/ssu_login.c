#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char userID[16][32];
char pwdID[16][32];

void get_user_list()
{
    int fd;
    int j;
    char c, n;

    fd = open("list.txt", O_RDONLY);

    for (int i = 0; i < 16; i++)
    {
		j = -1;
        while (++j < 32)
        {
			n = read(fd, &c, 1);
			if (c == ' ')
            {
                userID[i][j] = '\0';
                break;
            }
            userID[i][j] = c;
        }
        j = -1;
        while (++j < 32)
        {
            n = read(fd, &c, 1);
            if (c == '\n' || n == 0)
            {
                pwdID[i][j] = '\0';
                break;
            }
            pwdID[i][j] = c;
        }
		if (n == 0)
			break;
    }

    close(fd);
}

int check_idpw()
{
    char user[32];
    char pwd[32];
    int n;
    int i = -1;

    // 입력받은 Username, Password와 list.txt 비교
    printf(1, "Username: ");
    if ((n = read(0, user, 32)) < 0)
    {
        printf(1, "read error\n");
        exit();
    }
    user[n - 1] = 0;

    printf(1, "Password: ");
    if ((n = read(0, pwd, 32)) < 0)
    {
        printf(1, "read error\n");
        exit();
    }
    pwd[n - 1] = 0;

    for (i = 0; i < 16; i++)
    {
        if (!strcmp(user, userID[i]) && !strcmp(pwd, pwdID[i]))
            return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int wpid, pid;

    get_user_list();
    while (!check_idpw(argc, argv))
    {
        printf(1, "Login failed. Try again.\n");
    }

    pid = fork();
    if (pid < 0)
    {
        printf(1, "init: fork failed\n");
        exit();
    }
    if (pid == 0)
    {
        exec("sh", argv);
        printf(1, "init: exec sh failed\n");
        exit();
    }
    while ((wpid = wait()) >= 0 && wpid != pid)
        printf(1, "zombie!\n");
    return 0;
}
