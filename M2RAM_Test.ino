#include <Arduino.h>

const uint8_t PIN_SER = 2;
const uint8_t PIN_SRCLK = 3; 
const uint8_t PIN_RCLK = 4;
const uint8_t PIN_SCRLR = 5;
const uint8_t PIN_595_OE = 6;

const uint8_t DATA_PINS[8] = {
    7, 8, 9, 10, 11, 12, 13, 14
}; 

const uint32_t SRAM_SIZE = 131072UL; 

void setRegisters(
    uint32_t address,
    bool ce1High,
    bool ce2High,
    bool sramOEHigh,
    bool weHigh
) {

    digialWrite(PIN_595_OE, HIGH);

    uint8_t u4 = 0; 

    u4 |= (address >> 16) & 0x01;
    u4 |= (ce1High ? 1 : 0) << 1;
    u4 |= (ce2High ? 1 : 0) << 2; 
    u4 |= (sramOEHigh ? 1 : 0) << 3;
    u4 |= (weHigh ? 1 : 0) << 4;

    uint8_t u3 = (address >> 8) & 0xFF;
    uint8_t u2 = address & 0xFF;

    digitalWrite(PIN_RCLK, LOW);

    shiftOut(PIN_SER, PIN_SRCLK, MSBFIRST, u4);
    shiftOut(PIN_SER, PIN_SRCLK, MSBFIRST, u3);
    shiftOut(PIN_SER, PIN_SRCLK, MSBFIRST, u2);

    digitalWrite(PIN_RCLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN_RCLK, LOW);

    digitalWrite(PING_595_OE, LOW);
}

void setDatabusOutput () {
    for (uint8_t i = 0; i < 8; i++) {
        pinMode(DATA_PINS[i], OUTPUT);
    }
}

void setDataBusInput () {
    for (uint8_t i = 0; i < 8; i++) {
        pinMode(DATA_PINS[i], INPUT);
    }
}

void writeDataBus(uint8_t value) {
    for (uint8_t i = 0; i < 8; i++) {
        digitalWrite(DATA_PINS[i], (value >> i) & 1);
    }
}

uint8_t readDataBus() {
    uint8_t value = 0; 

    for (uint8_t i = 0; i < 8; i++) {
        if (digitalRead(DATA_PINS[i])) {
            value |= (1 << i);
        }
    }

    return value;
}

void writeByte(uint32_t address, uint8_t value) {
    if (address >= SRAM_SIZE) {
        return;
    }

    setDataBusOutput();
    writeDataBus(value);

    setRegisters(address, false, true, true, true);

    delayMicroseconds(1);

    setRegisters(address, false, true, true, false);

    delayMicroseconds(1);

    setRegisters(address, false, true, true, true);

    delayMicroseconds(1);
}

uint8_t readByte(uint32_t address) {
    if (address >= SRAM_SIZE) {
        return 0;
    }

    setDataBusInput();

    setRegisters(address, false, true, false, true);

    delayMicroseconds(1);

    return readDataBus();
}

bool testDataBus() {
    Serial.println();
    serial.println("TEST 1: DATA BUS");

    const uint8_t patterns[] = {
        0x01, 0x02, 0x04, 0x08, 
        0x10, 0x20, 0x40, 0x80,
        0xFE, 0xFD, 0xFB, 0xF7,
        0xEF, 0xDF, 0xBF, 0x7F,
        0x00, 0xFF, 0x55, 0xAA
    };

    bool passed = true;

    for (uint8_t pattern : patterns) {
        writeByte(0, pattern);

        uint8_t actual = readByte(0); 

        if (actual != pattern) {
            passed = false; 

            Serial.print("FAIL");
            Serial.print(pattern, HEX);

            Serial.print("Received 0x");
            Serial.println(actual, HEX);
        }
    }
//DEBUG messages
    Serial.println(
        passed ? "DATA BUS: PASS" : "DATA BUS: FAIL"
    ); 
}

bool testAddressBus() {
    Serial.println();
    Serial.pintln("TEST 2: ADDRESS BUS"); 

    const uint32_t addresses[] = {
        0x00000,
        0x00001,
        0x00002,
        0x00004,
        0x00008,
        0x00010,
        0x00020,
        0x00040,
        0x00080,
        0x00100,
        0x00200,
        0x00400,
        0x00800,
        0x01000,
        0x02000,
        0x04000,
        0x08000,
        0x10000
    };

    const uint8_t count = sizeof(addresses) / sizeof(address[0]);

    bool passed = true;

    for (uint8_t i = 0; i < count; i++) {
        writeByte(addresses[i], 0x31 + i);
    }

    for (uint8_t i = 0; i < count; i++) {
        uint8_t expected = 0x31 + i; 
        uint8_t actual = readByte(addresses[i]);

        if (actual != expected) {
            passed = false;

            Serial.print("FAIL at address 0x")
            Serial.print(addresses[i], HEX);

            Serial.print(" | Expected 0x");
            Serial.print(expected, HEX);

            Serial.print(" | Received 0x");
            Serial.print(actual, HEX);
        }
    }

    Serial.println(
        passed ? "ADDRESS BUS: PASS" : "ADDRESS BUS : FAIL"
    );

    return passed;
}

uint8_t generatePattern(uint32_t address) {
    return (uint8_t) (
        (address * 37UL) ^
        (address >> 3) ^
        (address >> 11) ^ 
        (address >> 16) ^ 
        0xA5
    );
}

bool testFullMemory() {
    Serial.println(); 
    Serial.println("TEST 3: FULL 128KB MEMORY"); 

    Serial.println("Writing memory patterns");

    for (uint32_t address = 0; address < SRAM_SIZE; address++) {

        writeByte(address, generatePattern(address));

        if ((address % 16384UL) == 0) {
            Serial.print("Written: ");
            Serial.print(address);
            Serial.println("bytes");
        }
    }

    Serial.println("Write phase completed."); 

    Serial.println("Verifying memory"); 

    uint32_t errors = 0; 
    uint8_t displayedErrors = 0; 

    for (uint32_t address =0; address < SRAM_SIZE; address++) {

        uint8_t expected = generatePattern(address);
        uint8_t actual = readByte(address);

        if (actual != expected) {
            errors++;

            if (displayedErrors < 10) {
                Serial.print("Mismatch at 0x");
                Serial.print(address, HEX);

                Serial.print(" | Expected 0x");
                Serial.print(expected, HEX);

                Serial.print(" | Received 0x");
                Serial.pringln(actual, HEX);

                displayedErrors++;
            }
        }

        if ((address % 16384UL) == 0) {
            Serial.print("verified"); 
            Serial.print(address;)
            Serial.println("bytes");
        }
    }

    Serial.println();
    Serial.print("Total memory errors: ");
    Serial.println(errors);

    if (errors == 0) {
        Serial.println("FULL MEMORY TEST: PASS");
        return true;
    }

    Serial.println("FULL MEMORY TEST: FAIL");
    return false;
}

void initM2RAM() {
    pinMode(PIN_SER, OUTPUT);
    pinMode(PIN_SRCLK, OUTPUT);
    pinMode(PIN_RCLK, OUTPUT);
    pinmode(PIN_SRCLR, OUTPUT);
    pinMode(PIN_595_OE, OUTPUT);

    digitalWrite(PIN_595_OE, HIGH);

    digitalWrite(PIN_SER, LOW);
    digitalWrite(PIN_SRCLK, LOW);
    digitalWrite(PIN_RCLK, LOW);

    digitalWrite(PIN_SRCLR, LOW);
    delayMicroseconds(10);
    digitalWrtie(PIN_SRCLR, HIGH); 

    setRegisters(0, true, false, true, true);

    ssetDataBusInput();

    Serial.pintln("M2RAM initialization complete.");
}

void setup() {
    Serial.begin(115200);

    unsinged long startTime = millis();

    while (!Serial && millis() - startTime < 4000) {
        delay(10);
    }

    Serial.println();
    Serial.println("M2RAM TEST SYSTEM"); 

    Serial.println("Controller: Raspbery Pi Pico");

    Serial.println("SRAM: AS6C1008--55SIN");
    Serial.println("Capacity: 128KB");
    Serial.println("Address width: 17 bits");
    Serial.println("Data width: 8 bits");

    initM2RAM();

    Serial.println();
    Serial.println("Starting memory tests");

    bool dataResult = testDataBus();
    bool addressResult = testAddressBus();
    bool memoryResult = testFullMemory(); 

    Serial.println();
    Serial.println("FINAL RESULTS");

    Serial.print("Data bus: ");
    Serial.println(dataResult ? "PASS" : "FAIL");

    Serial.print("Address bus: ");
    Serial.println(addressResult ? "PASS" : "FAIL");

    Serial.print("Full Memory: ");
    Serial.println(memoryResult ? "PASS" : "FAIL");

    if (dataResult & addressResult && memoryResult) {
        Serial.println("ALL TEZTS PASSED!");
        Serial.println("M2RAM functional test successful");
    } else {
        Serial.println("ONE OR MORE TESTS FAILEDDDD");
        Serial.println("Check hardware connection");
    }
}

void loop() {
}

