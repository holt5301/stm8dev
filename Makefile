
build/blink.hex: led.rel main.rel
	@echo "Building blink.hex" 
	sdcc -mstm8 -o build/blink.hex build/led.rel build/main.rel

led.rel: led.c
	@mkdir -p build
	sdcc -mstm8 -o build/ -c led.c

main.rel: main.c
	@mkdir -p build
	sdcc -mstm8 -o build/ -c main.c

flash: build/blink.hex
	@echo "Building/flashing blink.hex"
	stm8flash -c stlink -p stm8s105c6 -w build/blink.hex

clean:
	rm -rf build