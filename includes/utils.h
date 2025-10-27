#ifndef UTILS_H
#define UTILS_H
#include <ApplicationServices/ApplicationServices.h>
#include <stdbool.h>
#include <stdlib.h>


bool isGetNumber(const char* str, long* res)
{
    if (str == NULL || *str == '\0' || res == NULL)
    {
        return false;
    }

    char* endptr;
    long temp = strtol(str, &endptr, 10);
    if (*endptr == '\0') // is number
    {
        *res = temp;
        return true;
    }

    return false;
}

#ifdef __APPLE__
void SimulateMouseClick()
{
    CGEventRef click_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown, CGEventGetLocation(CGEventCreate(NULL)), kCGMouseButtonLeft);

    CGEventRef click_up = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseUp, CGEventGetLocation(CGEventCreate(NULL)), kCGMouseButtonLeft);

    CGEventPost(kCGHIDEventTap, click_down);
    CGEventPost(kCGHIDEventTap, click_up);

    CFRelease(click_down);
    CFRelease(click_up);
}
#endif

#endif //UTILS_H
