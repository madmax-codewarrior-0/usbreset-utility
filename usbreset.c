#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>

void color_red()
{
    fprintf(stderr, "\033[0;31m");
    printf("\033[0;31m");
}

void color_yellow()
{
    fprintf(stderr, "\033[0;33m");
    printf("\033[0;33m");
}

void color_green()
{
    printf("\033[0;32m");
}

void color_reset()
{
    fprintf(stderr, "\033[0m");
    fprintf(stdout, "\033[0m");
    fprintf(stderr, "");
    fprintf(stdout, "");
    
    fprintf(stdout, "\n");

    fflush(stderr);
    fflush(stdout);
}

int main(int argc, char **argv)
{
    const char *filename;
    int fd;
    int rc;

    if (argc != 2)
    {
        fprintf(stderr, "\n  Usage: usbreset /dev/bus/usb/<BUS>/<DEVICE>\n   Hint: Use 'lsusb' to find the device\n\n");
        return 1;
    }

    filename = argv[1];

    fd = open(filename, O_WRONLY);
    if (fd < 0)
    {
        color_red();
        perror("\n  Error opening output file! ");
        color_reset();
        return 1;
    }
    
    color_yellow();
    printf("\n  Resetting USB device %s ... ", filename);

    rc = ioctl(fd, USBDEVFS_RESET, 0);
    if (rc < 0)
    {
        color_red();
        perror("\n  Error in ioctl! \n");
        color_reset();
        return 1;
    }

    color_green();
    printf("Successful\n");
    color_reset();

    close(fd);
    return 0;
}
