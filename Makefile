
build/blink.hex: build/mcp9808.rel build/led.rel build/main.rel build/drivers/gpio.rel build/drivers/timers.rel build/drivers/i2c.rel
	@echo "Building blink.hex" 
	sdcc -mstm8 -o build/blink.hex $^

build/%.rel: %.c
	@mkdir -p build/drivers
	sdcc -mstm8 -o build/$* -c $^

.PHONY: flash
flash: build/blink.hex
	@echo "Building/flashing blink.hex"
	stm8flash -c stlink -p stm8s105c6 -w build/blink.hex

.PHONY: clean
clean:
	rm -rf build