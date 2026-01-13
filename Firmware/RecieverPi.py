import serial

START_BYTE = 0xAA
END_BYTE   = 0x55
MAX_PAYLOAD = 32

ser = serial.Serial(
    port='/dev/serial0',
    baudrate=115200,
    timeout=0.1
)

state = "WAIT_START"
length = 0
payload = bytearray()

while True:
    if ser.in_waiting == 0:
        continue

    byte_in = ser.read(1)[0]

    if state == "WAIT_START":
        if byte_in == START_BYTE:
            state = "READ_LENGTH"

    elif state == "READ_LENGTH":
        length = byte_in
        if length > MAX_PAYLOAD:
            state = "WAIT_START"
        else:
            payload.clear()
            state = "READ_PAYLOAD"

    elif state == "READ_PAYLOAD":
        payload.append(byte_in)
        if len(payload) >= length:
            state = "WAIT_END"

    elif state == "WAIT_END":
        if byte_in == END_BYTE:
            print("Packet received:", list(payload))
        state = "WAIT_START"