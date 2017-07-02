import math

SCREEN_WIDTH = 500
SCREEN_HEIGHT = 550

def gen_sin(filename, gen_type = 0,
            x_init = SCREEN_WIDTH / 2.0, y_init = 1.0,
            omega = 1.0, phase = 0.0, ampitude = SCREEN_WIDTH / 2.0,
            dt = 0.1, time = 1.0):
    try:
        file = open(filename, 'w+')
        y = y_init
        while time > 0:
            x = x_init + ampitude * math.sin(omega * (y - y_init) + phase)
            s = str(x) + ',' + str(y) + ',' + str(gen_type) + '\n'
            file.write(s)
            y += dt
            time -= dt
    except:
        print('ERROR UNKNOW')
    file.close()

def main():
    gen_sin(gen_type=0, filename='Lv7.tmap', phase = math.pi * 2.0 / 2.0, time=2.0, omega = 0.5)

if __name__ == '__main__':
    main()
