from machine import Pin 
from umqtt.simple import MQTTClient
import utime, xtools
from machine import Pin,PWM
from machine import UART
import random

xtools.connect_wifi_led()
#ledG = Pin(12, Pin.OUT)
#ledG.value(0)
pin = Pin(13, Pin.OUT)
ADAFRUIT_IO_USERNAME = "<Name>"
ADAFRUIT_IO_KEY = "<Key>"
FEED = "final"
com = UART(2, 9600, tx=17, rx=16)
com.init(9600)

# MQTT 客戶端
client = MQTTClient (
    client_id = xtools.get_id(),
    server = "io.adafruit.com",
    user = ADAFRUIT_IO_USERNAME,
    password = ADAFRUIT_IO_KEY,
    ssl = False,
)

t=0
def sub_cb(topic, msg):
    global ledG
    print("收到訊息: ", msg.decode())
    if len(msg.decode())==4 and f==0:
        print(msg.decode())
        guess=""
        guess=guess+str(msg.decode()[0])+str(msg.decode()[1])+str(msg.decode()[2])+str(msg.decode()[3])
        print(guess)
        com.write("g"+guess+"\r\n")
    elif len(msg.decode())!=4 and f==0:
        print("請輸入4個數字")
    elif f==1:
        print("此題已完成")
        
client.set_callback(sub_cb)   # 指定回撥函數來接收訊息
client.connect()              # 連線

topic = ADAFRUIT_IO_USERNAME + "/feeds/" +FEED

print(topic)
client.subscribe(topic)      # 訂閱主題

def create_num():
    s=set()
    while len(s)<4:
        x=random.randint(0,9)
        s.add(x)
    n=""   
    for i in s:
        n=n+str(i)
    print(n)
    com.write("s"+n+"\r\n")
    
def welldone():
    led_pwm = PWM(pin, freq=494, duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=494, duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=523, duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=523, duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=523, duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
                
    led_pwm = PWM(pin, freq=440 , duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=440 , duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=494, duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=494, duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=494, duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
                
    led_pwm = PWM(pin, freq=392 , duty=512)
    utime.sleep(0.5)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=392 , duty=512)
    utime.sleep(0.5)
    led_pwm = PWM(pin, freq=440 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=440 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=440 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=392 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
                
    led_pwm = PWM(pin, freq=370 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=294 , duty=512)
    utime.sleep(0.25)
    led_pwm = PWM(pin, freq=330 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=370 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=392 , duty=512)
    utime.sleep(0.75)
    led_pwm.deinit()
    led_pwm = PWM(pin, freq=392 , duty=512)
    utime.sleep(0.25)
    led_pwm.deinit()

    
    
create_num()
f=0
while True:
    if com.any() > 0:
        a = com.readline()
        print(a)
        if a == b'Reset':
            f=0
            t=0
            create_num()
        if a==b'DOIT SHIN\r\n':
            t=t+1
        if a == b'Finish\r\n':
            f=1
            if t<=10:
                welldone()
            else:
                led_pwm = PWM(pin, freq=659 , duty=512)
                utime.sleep(0.25)
                led_pwm.deinit()
                led_pwm = PWM(pin, freq=523 , duty=512)
                utime.sleep(0.25)
                led_pwm.deinit()
                led_pwm = PWM(pin, freq=659 , duty=512)
                utime.sleep(0.25)
                led_pwm.deinit()
                led_pwm = PWM(pin, freq=523 , duty=512)
                utime.sleep(0.25)
                led_pwm.deinit()
    
    client.check_msg()
