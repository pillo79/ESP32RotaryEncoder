/**
 * ESP32RotaryEncoder: TwoRotaryEncoders.ino
 * 
 * This is a basic example of how to instantiate two distinct Rotary Encoders.
 * 
 * Rotary Encoder #1:
 *   - Turning the knob will increment/decrement a value between 1 and 10,
 *   and print it to the serial console.
 * 
 * 	 - Pressing the button will enable/disable Rotary Encoder #2.
 * 
 * Rotary Encoder #2:
 *   - Turning the knob will increment/decrement a value between -100 and 100,
 *   and print it to the serial console.
 * 
 * 	 - Pressing the button will enable/disable Rotary Encoder #1.
 * 
 * While a rotary encoder is disabled, turning the knob or pressing the button
 * will have no effect.
 * 
 * Created 3 October 2023
 * By Matthew Clark
 */

#include <ESP32RotaryEncoder.h>

#define RE1_DO_ENCODER_VCC D2
#define RE1_DI_ENCODER_SW  D3
#define RE1_DI_ENCODER_B   D4 // DT
#define RE1_DI_ENCODER_A   D5 // CLK

#define RE2_DO_ENCODER_VCC D6
#define RE2_DI_ENCODER_SW  D7
#define RE2_DI_ENCODER_B   D8 // DT
#define RE2_DI_ENCODER_A   D9 // CLK


RotaryEncoder rotaryEncoder1( RE1_DI_ENCODER_A, RE1_DI_ENCODER_B, RE1_DI_ENCODER_SW, RE1_DO_ENCODER_VCC );
RotaryEncoder rotaryEncoder2( RE2_DI_ENCODER_A, RE2_DI_ENCODER_B, RE2_DI_ENCODER_SW, RE2_DO_ENCODER_VCC );


void printKnob1Value( int value )
{
	Serial.printf( "RE1 value: %i\n", value );
}

void printKnob2Value( int value )
{
	Serial.printf( "RE2 value: %i\n", value );
}

void button1ToggleRE2()
{
	if( rotaryEncoder2.isEnabled() )
	{
		rotaryEncoder2.disable();
		Serial.println( "RE2 is disabled." );
	}
	else
	{
		rotaryEncoder2.enable();
		Serial.println( "RE2 is enaabled." );
	}
}

void button2ToggleRE1()
{
	if( rotaryEncoder1.isEnabled() )
	{
		rotaryEncoder1.disable();
		Serial.println( "RE1 is disabled." );
	}
	else
	{
		rotaryEncoder1.enable();
		Serial.println( "RE1 is enaabled." );
	}
}

void setup_RE1()
{
	// This tells the library that the encoder has its own pull-up resistors
	rotaryEncoder1.setEncoderType( EncoderType::HAS_PULLUP );

	// Range of values to be returned by the encoder: minimum is 1, maximum is 10
	// The third argument specifies whether turning past the minimum/maximum will
	// wrap around to the other side.
	// In this example, turn past 10, wrap to 1; turn past 1, wrap to 10
	rotaryEncoder1.setBoundaries( 1, 10, true );

	// The function specified here will be called every time the knob is turned
	// and the current value will be passed to it
	rotaryEncoder1.onTurned( &printKnob1Value );

	// The function specified here will be called every time the button is pushed
	rotaryEncoder1.onPressed( &button1ToggleRE2 );

	// This is where the inputs are configured and the interrupts get attached
	rotaryEncoder1.begin();
}

void setup_RE2()
{
	// This tells the library that the encoder does not have its own pull-up
	// resistors, so the internal pull-up resistors will be enabled
	rotaryEncoder2.setEncoderType( EncoderType::FLOATING );

	// Range of values to be returned by the encoder: minimum is -100, maximum is 100
	// The third argument specifies whether turning past the minimum/maximum will wrap
	// around to the other side.
    // In this example, turn past 100, stay on 100; turn past -100, stay on -100
	rotaryEncoder2.setBoundaries( -100, 100, false );

	// The function specified here will be called every time the knob is turned
	// and the current value will be passed to it
	rotaryEncoder2.onTurned( &printKnob2Value );

	// The function specified here will be called every time the button is pushed
	rotaryEncoder2.onPressed( &button2ToggleRE1 );

	// This is where the inputs are configured and the interrupts get attached
	rotaryEncoder2.begin();
}

void setup()
{
	Serial.begin( 115200 );

	setup_RE1();
	setup_RE2();
}

void loop()
{
	// Your stuff here
}