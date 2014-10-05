import serial, time, struct
from GeneralObject import *

class Communication(GeneralObject):
    _connection = None
    data = None

    def start(self):
        self._connection = serial.Serial('COM4', 115200)

        #todo: replace this with check
        time.sleep(5)

        self._connection.flushInput()

    def readData(self):
        while self._connection.inWaiting() >= 8:
            headerBytes = self._connection.read(4)

            header, identifier = struct.unpack('=2h', headerBytes)

            if header != 1234:
                self._connection.flushInput()
                print(header)
                print("headerbreak")
                break

            id = identifier % 100
            identifier -= id

            typical = int((identifier % 1000) / 100)
            identifier -= typical * 100

            payloadSize = int(identifier / 1000)
            if payloadSize % 2:
                typical += 10
                payloadSize -= 1

            print(payloadSize)

            payload = self._connection.read(payloadSize)
            footerBytes = self._connection.read(2)

            print(payload)

            footer = struct.unpack('=h', footerBytes)[0]

            if footer != 4321:
                self._connection.flushInput()
                print(footer)
                print("footerbreak")
                break

            yield [
                typical,
                id,
                payload
            ]

    def sendData(self,typical,i,sendBytes):
        data = struct.pack('=2h16c',typical,i,sendBytes)

        self._connection.write(data)