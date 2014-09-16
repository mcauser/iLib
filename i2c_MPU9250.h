#ifndef i2c_MPU9250_h
#define i2c_MPU9250_h

#include "i2c.h"
#include "i2c_Sensor.h"


/** ######################################################################

Driver for the MPU9250-Sensor

 9D-IMU 3.7mA, 8µA sleep

 GYRO XYZ: [3.9 .. 8000 Hz], ±250, ±500, ±1000, and ±2000°/sec and integrated 16-bit ADCs
 8µA, 3.2mA active

 ACCE XYZ: ±2g, ±4g, ±8g and ±16g and integrated 16-bit ADCs
 8µA, 450µA

 MAGN XYZ: ±4800μT, 14 bit (0.6μT/LSB) or 16 bit (15μT/LSB)
 ?µA, 280μA @8Hz

 DMP: Digital Motion Processing


########################################################################  */

class MPU9250 : public i2cSensor
{

    /** ######### Register-Map ################################################################# */

#define MPU_ADDRESS 	            0x69

//MPU9250 Register map
#define REG_SELF_TEST_X_GYRO        0x00
#define REG_SELF_TEST_Y_GYRO        0x01
#define REG_SELF_TEST_Z_GYRO        0x02
#define REG_SELF_TEST_X_ACCEL       0x0D
#define REG_SELF_TEST_Y_ACCEL       0x0E
#define REG_SELF_TEST_Z_ACCEL       0x0F
#define REG_XG_OFFSET_H             0x13
#define REG_XG_OFFSET_L             0x14
#define REG_YG_OFFSET_H             0x15
#define REG_YG_OFFSET_L             0x16
#define REG_ZG_OFFSET_H             0x17
#define REG_ZG_OFFSET_L             0x18
#define REG_SMPLRT_DIV              0x19

#define REG_CONFIG                  0x1A
#define   MSK_FIFO_MODE             0x40
#define   MSK_EXT_SYNC_SET          0x38
#define   MSK_DLPF_CFG              0x07

#define REG_GYRO_CONFIG             0x1B
#define   MSK_XGYRO_CTEN            0x80
#define   MSK_YGYRO_CTEN            0x40
#define   MSK_ZGYRO_CTEN            0x20
#define   MSK_GYRO_FS_SEL           0x18
#define   MSK_FCHOICE_B             0x03

#define REG_ACCEL_CONFIG            0x1C
#define   MSK_AX_ST_EN              0x80
#define   MSK_AY_ST_EN              0x40
#define   MSK_AZ_ST_EN              0x20
#define   MSK_ACCEL_FS_SEL          0x18

#define REG_ACCEL_CONFIG2           0x1D
#define   MSK_ACCEL_FCHOICE_B       0xC0
#define   MSK_A_DLPF_CFG            0x03

#define REG_LP_ACCEL_ODR            0x1E
#define   MSK_LPOSC_CLKSEL          0x0F

#define REG_WOM_THR                 0x1F

#define REG_FIFO_EN                 0x23
#define   MSK_TEMP_FIFO_EN          0x80
#define   MSK_GYRO_XOUT             0x40
#define   MSK_GYRO_YOUT             0x20
#define   MSK_GYRO_ZOUT             0x10
#define   MSK_ACCEL                 0x08
#define   MSK_SLV2                  0x04
#define   MSK_SLV1                  0x02
#define   MSK_SLV0                  0x01

#define REG_I2C_MST_CTRL            0x24
#define   MSK_MULT_MST_EN           0x80
#define   MSK_WAIT_FOR_ES           0x40
#define   MSK_SLV_3_FIFO_EN         0x20
#define   MSK_I2C_MST_P_NSR         0x10
#define   MSK_I2C_MST_CLK           0x0F

#define REG_I2C_SLV0_ADDR           0x25
#define   MSK_I2C_SLV0_RNW          0x80
#define   MSK_I2C_ID_0              0x7F

#define REG_I2C_SLV0_REG            0x26
#define REG_I2C_SLV0_CTRL           0x27
#define   MSK_I2C_SLV0_EN           0x80
#define   MSK_I2C_SLV0_BYTE_SW      0x40
#define   MSK_I2C_SLV0_REG_DIS      0x20
#define   MSK_I2C_SLV0_GRP          0x10
#define   MSK_I2C_SLV0_LENG         0x0F

// [without SLV0 to SLV4]

#define REG_I2C_MST_STATUS          0x36
#define   MSK_PASS_THROUGH          0x80
#define   MSK_I2C_SLV4_DONE         0x40
#define   MSK_I2C_LOST_ARB          0x20
#define   MSK_I2C_SLV4_NACK         0x10
#define   MSK_I2C_SLV3_NACK         0x08
#define   MSK_I2C_SLV2_NACK         0x04
#define   MSK_I2C_SLV1_NACK         0x02
#define   MSK_I2C_SLV0_NACK         0x01

#define REG_INT_PIN_CFG             0x37
#define   MSK_ACTL                  0x80
#define   MSK_OPEN                  0x40
#define   MSK_LATCH_INT_EN          0x20
#define   MSK_INT_ANYRD_2CLEAR      0x10
#define   MSK_ACTL_FSYNC            0x08
#define   MSK_FSYNC_INT_MODE_EN     0x04
#define   MSK_BYPASS_EN             0x02

#define REG_INT_ENABLE              0x38
#define   MSK_WOM_EN                0x40
#define   MSK_FIFO_OFLOW_EN         0x10
#define   MSK_FSYNC_INT_EN          0x08
#define   MSK_RAW_RDY_EN            0x01

#define REG_INT_STATUS              0x3A
#define   MSK_WOM_INT               0x40
#define   MSK_FIFO_OFLOW_INT        0x10
#define   MSK_FSYNC_INT             0x08
#define   MSK_RAW_DATA_RDY_INT      0x01

#define REG_ACCEL_XOUT_H            0x3B
#define REG_ACCEL_XOUT_L            0x3C
#define REG_ACCEL_YOUT_H            0x3D
#define REG_ACCEL_YOUT_L            0x3E
#define REG_ACCEL_ZOUT_H            0x3F
#define REG_ACCEL_ZOUT_L            0x40
#define REG_TEMP_OUT_H              0x41
#define REG_TEMP_OUT_L              0x42
#define REG_GYRO_XOUT_H             0x43
#define REG_GYRO_XOUT_L             0x44
#define REG_GYRO_YOUT_H             0x45
#define REG_GYRO_YOUT_L             0x46
#define REG_GYRO_ZOUT_H             0x47
#define REG_GYRO_ZOUT_L             0x48

#define REG_EXT_SENS_DATA_00        0x49
#define REG_EXT_SENS_DATA_01        0x4A
#define REG_EXT_SENS_DATA_02        0x4B
#define REG_EXT_SENS_DATA_03        0x4C
#define REG_EXT_SENS_DATA_04        0x4D
#define REG_EXT_SENS_DATA_05        0x4E
#define REG_EXT_SENS_DATA_06        0x4F
#define REG_EXT_SENS_DATA_07        0x50
#define REG_EXT_SENS_DATA_08        0x51
#define REG_EXT_SENS_DATA_09        0x52
#define REG_EXT_SENS_DATA_10        0x53
#define REG_EXT_SENS_DATA_11        0x54
#define REG_EXT_SENS_DATA_12        0x55
#define REG_EXT_SENS_DATA_13        0x56
#define REG_EXT_SENS_DATA_14        0x57
#define REG_EXT_SENS_DATA_15        0x58
#define REG_EXT_SENS_DATA_16        0x59
#define REG_EXT_SENS_DATA_17        0x5A
#define REG_EXT_SENS_DATA_18        0x5B
#define REG_EXT_SENS_DATA_19        0x5C
#define REG_EXT_SENS_DATA_20        0x5D
#define REG_EXT_SENS_DATA_21        0x5E
#define REG_EXT_SENS_DATA_22        0x5F
#define REG_EXT_SENS_DATA_23        0x60

#define REG_I2C_SLV0_DO             0x63
#define REG_I2C_SLV1_DO             0x64
#define REG_I2C_SLV2_DO             0x65
#define REG_I2C_SLV3_DO             0x66

#define REG_I2C_MST_DELAY_CTRL      0x67
#define   MSK_DELAY_ES_SHADOW       0x80
#define   MSK_I2C_SLV4_DLY_EN       0x10
#define   MSK_I2C_SLV3_DLY_EN       0x08
#define   MSK_I2C_SLV2_DLY_EN       0x04
#define   MSK_I2C_SLV1_DLY_EN       0x02
#define   MSK_I2C_SLV0_DLY_EN       0x01

#define REG_SIGNAL_PATH_RESET       0x68
#define   MSK_GYRO_RST              0x04
#define   MSK_ACCEL_RST             0x02
#define   MSK_TEMP_RST              0x01

#define REG_MOT_DETECT_CTRL         0x69
#define   MSK_ACCEL_INTEL_EN        0x80
#define   MSK_ACCEL_INTEL_MODE      0x40

#define REG_USER_CTRL               0x6A
#define   MSK_FIFO_EN               0x40
#define   MSK_I2C_MST_EN            0x20
#define   MSK_I2C_IF_DIS            0x10
#define   MSK_FIFO_RST              0x04
#define   MSK_I2C_MST_RST           0x02
#define   MSK_SIG_COND_RST          0x01

#define REG_PWR_MGMT_1              0x6B
#define   MSK_H_RESET               0x80
#define   MSK_SLEEP                 0x40
#define   MSK_CYCLE                 0x20
#define   MSK_GYRO_STANDBY_CYCLE    0x10
#define   MSK_PD_PTAT               0x08
#define   MSK_CLKSEL                0x07

#define REG_PWR_MGMT_2              0x6C
#define   MSK_DISABLE_XA            0x20
#define   MSK_DISABLE_YA            0x10
#define   MSK_DISABLE_ZA            0x08
#define   MSK_DISABLE_XG            0x04
#define   MSK_DISABLE_YG            0x02
#define   MSK_DISABLE_ZG            0x01
#define   MSK_DISABLE_XYZA          0x38
#define   MSK_DISABLE_XYZG          0x07

#define REG_FIFO_COUNTH             0x72
#define REG_FIFO_COUNTL             0x73
#define REG_FIFO_R_W                0x74
#define REG_WHO_AM_I                0x75
#define REG_XA_OFFSET_H             0x77
#define REG_XA_OFFSET_L             0x78
#define REG_YA_OFFSET_H             0x7A
#define REG_YA_OFFSET_L             0x7B
#define REG_ZA_OFFSET_H             0x7D
#define REG_ZA_OFFSET_L             0x7E

//reset values
#define WHOAMI_RESET_VAL            0x71
#define POWER_MANAGMENT_1_RESET_VAL 0x01
#define DEFAULT_RESET_VALUE         0x00
#define WHOAMI_DEFAULT_VAL          0x68


//Magnetometer register maps
#define REG_MAG_WIA                 0x00
#define REG_MAG_INFO                0x01
#define REG_MAG_ST1                 0x02
#define REG_MAG_XOUT_L              0x03
#define REG_MAG_XOUT_H              0x04
#define REG_MAG_YOUT_L              0x05
#define REG_MAG_YOUT_H              0x06
#define REG_MAG_ZOUT_L              0x07
#define REG_MAG_ZOUT_H              0x08
#define REG_MAG_ST2                 0x09
#define REG_MAG_CNTL                0x0A
#define REG_MAG_RSV                 0x0B //reserved mystery meat
#define REG_MAG_ASTC                0x0C
#define REG_MAG_TS1                 0x0D
#define REG_MAG_TS2                 0x0E
#define REG_MAG_I2CDIS              0x0F
#define REG_MAG_ASAX                0x10
#define REG_MAG_ASAY                0x11
#define REG_MAG_ASAZ                0x12
//Magnetometer register masks
#define MPU9250_WIA                 0x48
#define MPU9250_                    0x


    /** ######### function definition ################################################################# */

public:
    /**< TODO: do i need a constructor? */
    MPU9250(void)
    {
        //_address = MPL_ADDRESS;
    };

    /*

    bool setClockSource(const uint8_t source) {
      return i2c.setRegister(MPU_ADDRESS, uint8_t register_addr, uint8_t mask, source); //MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_CLKSEL_BIT, MPU9250_PWR1_CLKSEL_LENGTH, source);
    }

    bool setFullScaleGyroRange(const uint8_t range) {
      return i2c.setRegister(MPU_ADDRESS, MPU9250_GYRO_CONFIG, uint8_t mask, range); //MPU9250_GCONFIG_FS_SEL_BIT, MPU9250_GCONFIG_FS_SEL_LENGTH, range);
    }

    bool setFullScaleAccelRange(const uint8_t range) {
      return i2c.setRegister(MPU_ADDRESS, MPU9250_ACCEL_CONFIG, uint8_t mask, range); //MPU9250_ACONFIG_AFS_SEL_BIT, MPU9250_ACONFIG_AFS_SEL_LENGTH, range);//check if ACCEL CONFIG2 is relevant
    }

    bool setSleepEnabled(const bool enabled) {
      // Set X-axis accelerometer standby enabled status.
      return i2c.setRegister(MPU_ADDRESS, uint8_t register_addr, uint8_t mask, enabled); //MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_SLEEP_BIT, enabled);
    }


    void mpu_initialize(void) {
      if (i2c.probe(MPU_ADDRESS)) {
        setClockSource(MPU9250_CLOCK_PLL_XGYRO);
        setFullScaleGyroRange(MPU9250_GYRO_FS_250);
        setFullScaleAccelRange(MPU9250_ACCEL_FS_2);
        setSleepEnabled(false);
        return 1;
      }
      return 0;
    }


    */
    void setEnabled(uint8_t enable = 1)
    {
        /**< TODO */
    };

    void reset()
    {
        /**< TODO */
    };

    uint8_t initialize(void)
    {
        /**< TODO */
        return 0;
    };

    /**< check for new data, return 1 when Measurement is ready */
    uint8_t checkMeasurement(void)
    {
        /**< TODO */
    };

    /**<  if you started a measurement and want to actively wait for it to finish */
    uint8_t awaitMeasurement(void)
    {
        uint8_t _counter = 0;
        while(checkMeasurement()==0)
        {
            if(++_counter > 250) return 0; //Error out after max of 250ms for a read
            delay(1);
        }
        return 1; // Measurement finished
    };

    void getMeasurement(float xyz_GyrAccMag[])
    {
        /**< TODO */
    };

};

/** ######### Preinstantiate Object ################################################################# */
/** < it's better when this is done by the user */
//PRESET preset = PRESET();

#endif




