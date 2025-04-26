from serial import Serial
from datetime import datetime

#Этот скрип предназначен для логирования с Ардуино

#напишите свои данные
PORT     = 'COM5' 
BAUDRATE = 9600
OUTFILE  = 'log.csv'

def main():
    with Serial(PORT, BAUDRATE, timeout=1) as ser, \
         open(OUTFILE, 'a', buffering=1) as f:
        print(f'Записываю данные из {PORT} в {OUTFILE} …')
        while True:
            line = ser.readline().decode(errors='ignore').strip()
            if not line:
                continue
            print(line)
            f.write(line + '\n')

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nStopped by user')
