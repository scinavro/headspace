# 순차적으로 돌아가기
from multiprocessing import Process
import time
import initServo
import board
import busio
import digitalio
from adafruit_motor import servo
from adafruit_pca9685 import PCA9685
from ServoControl import ServoControl
from PIL import Image, ImageDraw, ImageFont
from adafruit_epd.epd import Adafruit_EPD
from adafruit_epd.il0373 import Adafruit_IL0373
# pin number 설정- initialize i2c bus for your board
i2c = busio.I2C(board.SCL, board.SDA)

# First define some color constants
WHITE = (0xFF, 0x00, 0x00)
BLACK = (0x00, 0x00, 0x00)

# Next define some constants to allow easy resizing of shapes and colors
BORDER = 20
FONTSIZE = 24
BACKGROUND_COLOR = BLACK
FOREGROUND_COLOR = WHITE
TEXT_COLOR = BLACK

spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
ecs = digitalio.DigitalInOut(board.CE0)
dc = digitalio.DigitalInOut(board.D25)
rst = digitalio.DigitalInOut(board.D17)
busy = digitalio.DigitalInOut(board.D24)
srcs = None

display = Adafruit_IL0373(
    128, 296, spi,
    cs_pin=ecs,
    dc_pin=dc,
    sramcs_pin=srcs,
    rst_pin=rst,
    busy_pin=busy
)
display.rotation = 3

image = Image.new("RGB", (display.width, display.height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

draw.rectangle(
    (0, 0, display.width, display.height),
    fill=FOREGROUND_COLOR
)


# Load a TTF Font
font = ImageFont.truetype(
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", FONTSIZE)

# Draw Some Text
text = "!!!!!MERGE!!!!!"
(font_width, font_height) = font.getsize(text)
draw.text(
    (display.width // 2 - font_width // 2, display.height // 2 - font_height // 2),
    text,
    font=font,
    fill=BACKGROUND_COLOR,
)


# create instance of basic PCA9685 class
pca = PCA9685(i2c)
pca.frequency = 50
# register servos
servo_ch0 = pca.channels[0]
servo_ch1 = pca.channels[2]
servo_ch2 = pca.channels[4]
servo_ch3 = pca.channels[8]
# servo_ch4 = pca.channels[12]


def rotate(servo):
    servo.convert_check()
    if(servo.on):
        if(servo.forward):
            servo.current_angle = servo.angle_change + servo.current_angle
        else:
            servo.current_angle = servo.current_angle - servo.angle_change
    else:
        servo.on_check()


def execute(servos):
    while(True):
        rotate(servos[0])
        rotate(servos[1])
        rotate(servos[2])
        rotate(servos[3])


start_time = time.time()


def display_execute(func, image):
    func.image(image)
    func.display()


# servo.Servo의 객체 생성
servo0 = ServoControl(servo_ch0, 0, start_time, 5)
servo1 = ServoControl(servo_ch1, 0.5, start_time, 5)
servo2 = ServoControl(servo_ch2, 1, start_time, 5)
servo3 = ServoControl(servo_ch3, 1.5, start_time, 5)

#servo0.current_angle = 0
#servo1.current_angle = 0
#servo2.current_angle = 0
#servo3.current_angle = 0
servos = [servo0, servo1, servo2, servo3]
p2 = Process(target=display_execute(display, image))
p1 = Process(target=execute(servos))
p2.start()
p1.start()
