#define BAUD_RATE 115200
static const char *UART2_DEV = "/dev/ttyAMA1"; // UART2 장치 파일

// bluetooth
unsigned char serialRead(const int fd)
{
    unsigned char x;
    if (read(fd, &x, 1) != 1)
        return -1;
    return x;
}

void serialWrite(const int fd, const unsigned char c)
{
    write(fd, &c, 1);
}

void *bluetoothThread()
{
    int fd_serial;
    unsigned char c;

    // setting
    if ((fd_serial = serialOpen(UART2_DEV, BAUD_RATE)) < 0)
    {
        printf("Unable to open serial device.\n");
        return NULL;
    }
    printf("bluetooth set\n");

    // running
    while (1)
    {
        if (serialDataAvail(fd_serial)) // 읽을 데이터 존재 시
        {
            unsigned char str[5];
            for (int i = 0; i < 4; i++)
            {
                c = serialRead(fd_serial); // 1byte read
                str[i] = c;
                serialWrite(fd_serial, c); // Echo
            }
            str[4] = '\0';
            strcpy(settingTime, str);
            break;
        }
        
    }
}