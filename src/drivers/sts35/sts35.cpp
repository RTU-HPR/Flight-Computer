#include "sts35.hpp"

namespace sts35
{
    void sts35_init()
    {
        sensirion_i2c_hal_init();
        init_driver(0x4B);
        uint32_t id;
        sts4x_serial_number(&id);
        printf("STS35 serial id: %d", id);
    }

    void sts35_read_temp(float *temp)
    {
        int16_t error;
        int32_t temperature;
        error = sts4x_measure_high_precision(&temperature);
        if (error)
        {
            printf("Error executing sts4x_measure_high_precision(): %i\n", error);
        }
        else
        {
            *temp = temperature / 1000.0f;
        }
    }
}