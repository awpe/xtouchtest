/*Test touch devices
 * 
 * compile: gcc -lX11 -lXi
 */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

int
main (void)
{
    XIDeviceInfo * info;
    int            ndevices, i, j;
    Display      * display;

    display = XOpenDisplay (NULL);

    info = XIQueryDevice (display, XIAllDevices, &ndevices);

    for (i = 0; i < ndevices; i++)
    {
        XIDeviceInfo *dev = &info[i];
        printf ("Device name %d\n", dev->name);
        for (j = 0; j < dev->num_classes; j++)
        {
            XIAnyClassInfo   * class = dev->classes[j];
            XITouchClassInfo * t     = (XITouchClassInfo*) class;

            if (class->type != XITouchClass)
            {
                continue;
            }

            printf ("%s touch device, supporting %d touches.\n",
                    (t->mode == XIDirectTouch) ?  "direct" : 
"dependent",
                    t->num_touches);
        }
    }
    return EXIT_SUCCESS;
}

