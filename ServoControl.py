import time
from adafruit_motor import servo


class ServoControl(servo.Servo):
    def __init__(self, pwm_out, gap, start_time, angle_change):
        super().__init__(pwm_out, actuation_range=180, min_pulse=750, max_pulse=2250)
        self.gap = gap  # 몇 초 뒤에 시작할 지
        self.start_time = start_time  # 첫 모터의 시작 시간
        self.on = False  # 모터 status
        self.forward = True  # 모터 방향
        self.current_angle = 0  # 모터의 현재 각도
        self.angle_change = angle_change  # 한 수행 당 얼마나 돌아갈 지

    def on_check(self, servo):
        if(time.time()-self.start_time > self.gap):
            self.on = True

    def convert_check(self):
        if(self.forward):
            if(self.current_angle == 160):
                self.forward = False
        else:
            if(self.current_angle == 20):
                self.forward = True
