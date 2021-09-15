import board
import busio
import adafruit_pca9685
import adafruit_motor.servo

i2c = busio.I2C(board.SCL, board.SDA)
pca = adafruit_pca9685.PCA9685(i2c)
pca.frequency = 50

servo_channel0 = pca.channels[0]
servo_channel1 = pca.channels[2]
servo_channel2 = pca.channels[4]
servo_channel3 = pca.channels[8]
servo0 = adafruit_motor.servo.Servo(servo_channel0)
servo1 = adafruit_motor.servo.Servo(servo_channel1)
servo2 = adafruit_motor.servo.Servo(servo_channel2)
servo3 = adafruit_motor.servo.Servo(servo_channel3)


servo0.angle = 0
servo1.angle = 0
servo2.angle = 0
servo3.angle = 0
