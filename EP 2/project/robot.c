#pragma config(Sensor, S1,     lightSensor,    sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int sarray[30][30];
TFileHandle mFileHandle;
TFileIOResult mIOResult;
string mFileName = "myFile.txt";
int mFileSize = 5000;

int getThreshold()
{
    int min = 100;
    int max = 0;
    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;
    while (nMotorEncoder[motorB] < 20)
    {
        motor[motorB] = 10;
        motor[motorC] = 10;
    }
    motor[motorB] = 0;
    motor[motorC] = 0;
    
    nMotorEncoder[motorA] = 0;
    while (nMotorEncoder[motorA] < 90)
    {
        motor[motorA] = 10;
        if (SensorValue(lightSensor) < min)
            min = SensorValue(lightSensor);
        if (SensorValue(lightSensor) > max)
            max = SensorValue(lightSensor);
    }
    while(nMotorEncoder[motorA] > 0)
    {
        motor[motorA] = -10;
    }
    motor[motorA] = 0;
    
    return (min + max) / 2;
}

task main()
{
    int threshold = getThreshold();
    int x = 0;
    int y = 0;
    
    while (y < 20)
    {
        nMotorEncoder[motorA] = 0;
        while (x < 20)
        {
            while (nMotorEncoder[motorA] < 4 * (x + 1))
            {
                motor[motorA] = 10;
                if (SensorValue(lightSensor) > threshold)
                    sarray[y][x] = 1;
                else
                    sarray[y][x] = 0;
            }
            motor[motorA] = 0;
            x++;
        }
        while (nMotorEncoder[motorA] > 0)
        {
            motor[motorA] = -10;
        }
        motor[motorA] = 0;
        nMotorEncoder[motorB] = 0;
        while (nMotorEncoder[motorB] < 10)
        {
            motor[motorB] = 10;
            motor[motorC] = 10;
        }
        motor[motorB] = 0;
        motor[motorC] = 0;
        x = 0;
        y++;
    }
    
    Delete(mFileName,mIOResult);
    OpenWrite(mFileHandle, mIOResult, mFileName, mFileSize);
    
    while (y < 20)
    {
        while (x < 20)
        {
            string tmp;
            StringFormat(tmp, "%d", sarray[y][x]);
            WriteText(mFileHandle, mIOResult, tmp);
            x++;
        }
        y++;
    }
    Close(mFileHandle, mIOResult);
}